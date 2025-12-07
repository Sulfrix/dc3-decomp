#include "Cam.h"
#include "Env.h"
#include "Lit.h"
#include "Mat.h"
#include "Mesh.h"
#include "Movie.h"
#include "MultiMesh.h"
#include "Part.h"
#include "RenderState.h"
#include "Tex.h"
#include "TexRenderer.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/System.h"
#include "os/Timer.h"
#include "rnddx9/CubeTex.h"
#include "rnddx9/OcclusionQueryMgr.h"
#include "rnddx9/Rnd.h"
#include "rndobj/DOFProc_NG.h"
#include "rndobj/PostProc_NG.h"
#include "rndobj/Rnd_NG.h"
#include "rndobj/ShaderMgr.h"
#include "rndobj/ShadowMap.h"
#include "utl/Option.h"
#include "xdk/D3D9.h"
#include "xdk/d3d9i/d3d9.h"
#include "xdk/d3d9i/d3d9caps.h"
#include "xdk/d3d9i/d3d9types.h"
#include "xdk/win_types.h"

void CreateBackBuffers(int, int, D3DMULTISAMPLE_TYPE, unsigned int &, unsigned int &, D3DSurface *&, D3DSurface *&);

DxRnd::DxRnd()
    : unk220(0), mD3DDevice(nullptr), unk22c(0), mDeviceType(D3DDEVTYPE_HAL),
      unk_0x301(1), unk360(0), mAsyncSwapCurrent(0), mPerfCounterStart(0),
      mPerfCounterEnd(0), mGPUTimer(0), unk370(0), unk374(0), mCreatedPerfCounters(0),
      unk3a4(0), unk3f4(0), unk3f7(0), unk404(0), unk408(0) {
    unk220 = 1;
    unk350[0] = 0;
    unk350[1] = 0;
    unk380 = 0;
    unk388 = 0;
    unk384 = 0;
    unk38c = 0;
    unk37c = 0;
    unk35c = 0;
    mNumTiles = 0;
    unk34d = true;
}

DxRnd::~DxRnd() {
    if ((unsigned int)unk220) {
        unk220 = 0;
    }
}

void CDError() {
    TheDxRnd.Suspend();
    ShowDirtyDiscError();
}

void DxModal(Debug::ModalType &t, FixedString &s, bool b) { TheDxRnd.Modal(t, s, b); }

void DxRnd::PreInit(HWND__ *) {
    if (!unk404) {
        unk404 = true;
        DataArray *cfg = SystemConfig("rnd");
        mDefaultVSRegAlloc = 32;
        mDefaultPSRegAlloc = 96;
        DataArray *gprArr = cfg->FindArray("shader_gpr_alloc", false);
        if (gprArr) {
            mDefaultVSRegAlloc = gprArr->Int(1);
            mDefaultPSRegAlloc = gprArr->Int(2);
        }
        MILO_ASSERT(mDefaultVSRegAlloc + mDefaultPSRegAlloc == GPU_GPRS, 0x1F0);
        MILO_ASSERT(mDefaultVSRegAlloc >= 16, 0x1F1);
        MILO_ASSERT(mDefaultPSRegAlloc >= 16, 0x1F2);
        SetDiskErrorCallback(CDError);
        unk3f5 = OptionBool("print_glitches", false);
        unk3f6 = false;
        mD3DDevice = nullptr;
        unk22c = 0;
        NgRnd::PreInit();
        InitBuffers();
        TheShaderMgr.PreInit();
        TheRenderState.Init();
        Suspend();
        REGISTER_OBJ_FACTORY(DxTexRenderer)
        REGISTER_OBJ_FACTORY(DxCam)
        REGISTER_OBJ_FACTORY(DxEnviron);
        REGISTER_OBJ_FACTORY(DxMesh)
        DxMat::Init();
        REGISTER_OBJ_FACTORY(DxTex)
        REGISTER_OBJ_FACTORY(DxCubeTex);
        DxMultiMesh::Init();
        REGISTER_OBJ_FACTORY(DxMovie)
        DxParticleSys::Init();
        DxLight::Init();
        CreatePostTextures();
        DxTex::SetEDRamChecksEnabled(false);
        NgPostProc::Init();
        NgDOFProc::Init();
        DxTex::SetEDRamChecksEnabled(true);
        RndShadowMap::Init();
        Rnd::CreateDefaults();
        TheDebug.SetModalCallback(DxModal);
    }
}

void DxRnd::Init(HWND__ *h) {
    PreInit(h);
    mOcclusionQueryMgr = new DxRndOcclusionQueryMgr();
    NgRnd::Init();
    DxTex::Init();
    unk360 = false;
}

void DxRnd::Terminate() {
    Resume();
    DxLight::Terminate();
    DxMultiMesh::Shutdown();
    NgPostProc::Terminate();
    NgRnd::Terminate();
    RELEASE(unk398);
    RELEASE(unk39c);
    RELEASE(unk3a0);
    TerminateBuffers();
}

void DxRnd::SetSync(int sync) {
    Rnd::SetSync(sync);
    Resume();
    if (mSync == 0) {
        D3DDevice_SetRenderState_PresentInterval(TheDxRnd.GetD3DDevice(), 0x80000000);
    } else if (mSync == 1) {
        D3DDevice_SetRenderState_PresentInterval(TheDxRnd.GetD3DDevice(), 1);
    } else if (mSync == 2) {
        D3DDevice_SetRenderState_PresentInterval(TheDxRnd.GetD3DDevice(), 2);
    } else {
        MILO_FAIL("Not allowed to sync %d\n", mSync);
    }
}

void DxRnd::SetAspect(Aspect a) {
    if (mAspect != a) {
        Rnd::SetAspect(a);
        UpdateScalerParams();
        ResetDevice();
    }
}

void DxRnd::SetShrinkToSafeArea(bool shrink) {
    if (shrink != mShrinkToSafe) {
        Rnd::SetShrinkToSafeArea(shrink);
        UpdateScalerParams();
        ResetDevice();
    }
}

void DxRnd::Suspend() {
    if (mD3DDevice && !mAsyncSwapCurrent) {
        MILO_ASSERT(!mDrawing, 0x695);
        if (!unk3f4) {
            static Timer *cpuTimer = AutoTimer::GetTimer("cpu");
            if (unk3f5 && cpuTimer->SplitMs() > 30.0f) {
                MILO_LOG("GLITCH (pre-suspend): %i ms\n", (int)cpuTimer->SplitMs());
            }
            unk360 = false;
            D3DDevice_Suspend(mD3DDevice);
        }
        unk3f4 = true;
    }
}

void DxRnd::Resume() {
    if ((int)mD3DDevice) {
        if (unk3f4) {
            MILO_ASSERT(mAsyncSwapCurrent == false, 0x6AE);
            D3DDevice_Resume(mD3DDevice);
            unk360 = false;
        }
        unk3f4 = false;
    }
}

D3DSurface *DxRnd::BackBuffer() const {
    D3DResource_AddRef(unk380);
    return unk380;
}

D3DTexture *DxRnd::FrontBuffer() { return unk350[unk35c - 1 & 1]; }
D3DTexture *DxRnd::NotFrontBuffer() { return unk350[unk35c]; }

const char *DxRnd::Error(long code) { return MakeString("code %d", code); }

void DxRnd::Present() {
    unk35c = (unk35c - 1) & 1;
    if (mAsyncSwapCurrent) {
        static D3DSWAP_STATUS sSwapStatus;
        while (D3DDevice_QuerySwapStatus(mD3DDevice, &sSwapStatus),
               sSwapStatus.EnqueuedCount != 0) {
            Sleep(0);
        }

    } else {
        D3DDevice_SynchronizeToPresentationInterval(mD3DDevice);
    }
    D3DDevice_Swap(mD3DDevice, NotFrontBuffer(), nullptr);
    if (mAsyncSwapCurrent != unk360) {
        mAsyncSwapCurrent = unk360;
        D3DDevice_BlockUntilIdle(mD3DDevice);
        D3DDevice_SetSwapMode(mD3DDevice, mAsyncSwapCurrent);
    }
    unk3f7 = (PIXGetCaptureState() & 2);
}

void DxRnd::TerminateBuffers() {
    PreDeviceReset();
    if (mD3DDevice) {
        D3DDevice_Release(mD3DDevice);
        mD3DDevice = nullptr;
    }
}

void DxRnd::SetupGamma() {
    DataArray *cfg = SystemConfig("rnd");
    float gamma;
    if (cfg->FindData("gamma", gamma, false)) {
        D3DGAMMARAMP ramp;
        for (int i = 0; i < 256; i++) {
            float powed = (float)std::pow(i * 0.00390625f, gamma) * 1024.0f;
            ramp.red[i] = powed;
            ramp.green[i] = powed;
            ramp.blue[i] = powed;
        }
        D3DDevice_SetGammaRamp(mD3DDevice, 0, &ramp);
    }
}

void DxRnd::SetDefaultRenderStates() {
    D3DCAPS9 caps;
    memset(&caps, 0, sizeof(D3DCAPS9));
    GetDeviceCaps(&caps);
    D3DDevice_SetRenderState_AlphaRef(TheDxRnd.GetD3DDevice(), 0);
    D3DDevice_SetRenderState_AlphaFunc(TheDxRnd.GetD3DDevice(), D3DCMP_GREATER);
    D3DDevice_SetRenderState_PointSizeMax(
        TheDxRnd.GetD3DDevice(), reinterpret_cast<UINT &>(caps.MaxPointSize) // ???
    );
    D3DDevice_SetRenderState_SeparateAlphaBlendEnable(TheDxRnd.GetD3DDevice(), 1);
    D3DDevice_SetRenderState_SrcBlendAlpha(TheDxRnd.GetD3DDevice(), 1);
    D3DDevice_SetRenderState_DestBlendAlpha(TheDxRnd.GetD3DDevice(), 1);
    D3DDevice_SetRenderState_BlendOpAlpha(TheDxRnd.GetD3DDevice(), 3);
    for (int i = 0; i < caps.MaxTextureBlendStages; i++) {
        D3DDevice_SetSamplerState_MinFilter(TheDxRnd.GetD3DDevice(), i, 1);
        D3DDevice_SetSamplerState_MagFilter(TheDxRnd.GetD3DDevice(), i, 1);
    }
    D3DDevice_SetRenderState_PresentImmediateThreshold(TheDxRnd.GetD3DDevice(), 100);
}

void DxRnd::BeginTiling(const Hmx::Color &c, float f, unsigned int ui) {
    if (mNumTiles == 0) {
        D3DDevice_Clear(mD3DDevice, 0, nullptr, 0x31, MakeColor(c), f, ui, 0);
    } else {
        XMVECTOR v;
        v.v[0] = c.red;
        v.v[1] = c.green;
        v.v[2] = c.blue;
        v.v[3] = c.alpha;
        D3DDevice_BeginTiling(mD3DDevice, 0, mNumTiles, &unk3b4, &v, f, ui);
        unk34c = true;
    }
}

void DxRnd::PerfCountersInit() {
    if (!mCreatedPerfCounters) {
        mCreatedPerfCounters = true;
        mPerfCounterStart = D3DDevice_CreatePerfCounters(mD3DDevice, 1);
        DX_ASSERT(mPerfCounterStart, 0x230);
        mPerfCounterEnd = D3DDevice_CreatePerfCounters(mD3DDevice, 1);
        DX_ASSERT(mPerfCounterEnd, 0x231);
        D3DPERFCOUNTER_EVENTS perfEvents;
        memset(&perfEvents, 0, sizeof(D3DPERFCOUNTER_EVENTS));
        perfEvents.RBBM[0] = GPUPE_RBBM_NRT_BUSY;
        perfEvents.CP[0] = GPUPE_CP_COUNT;
        perfEvents.RBBM[1] = GPUPE_RBBM_COUNT;
        D3DDevice_EnablePerfCounters(mD3DDevice, 1);
        D3DDevice_SetPerfCounterEvents(mD3DDevice, &perfEvents, 0);
        mGPUTimer = AutoTimer::GetTimer("gs");
    }
}

void DxRnd::PerfCountersStart() {
    MILO_ASSERT(mGsTiming == true, 0x249);
    MILO_ASSERT(mCreatedPerfCounters == true, 0x24A);
    MILO_ASSERT(mGPUTimer != NULL, 0x24B);
    MILO_ASSERT(mPerfCounterStart != NULL, 0x24C);
    MILO_ASSERT(mPerfCounterEnd != NULL, 0x24D);
    mGPUTimer->SetLastMs(unk370 * 1.075f);
    D3DDevice_QueryPerfCounters(mD3DDevice, mPerfCounterStart, 1);
}

void DxRnd::PerfCountersStop() {
    MILO_ASSERT(mGsTiming == true, 0x25D);
    MILO_ASSERT(mCreatedPerfCounters == true, 0x25E);
    MILO_ASSERT(mGPUTimer != NULL, 0x25F);
    MILO_ASSERT(mPerfCounterStart != NULL, 0x260);
    MILO_ASSERT(mPerfCounterEnd != NULL, 0x261);
    D3DDevice_QueryPerfCounters(mD3DDevice, mPerfCounterEnd, 1);
    D3DPERFCOUNTER_VALUES startValues;
    HRESULT code = D3DPerfCounters_GetValues(mPerfCounterStart, &startValues, 0, nullptr);
    DX_ASSERT_CODE(code, 0x269);
    D3DPERFCOUNTER_VALUES endValues;
    code = D3DPerfCounters_GetValues(mPerfCounterEnd, &endValues, 0, nullptr);
    DX_ASSERT_CODE(code, 0x26A);
    ULARGE_INTEGER *startLargeIntegers = (ULARGE_INTEGER *)&startValues;
    ULARGE_INTEGER *endLargeIntegers = (ULARGE_INTEGER *)&endValues;
    for (int i = 0; i < (sizeof(D3DPERFCOUNTER_VALUES) / sizeof(ULARGE_INTEGER)); i++) {
        endLargeIntegers[i].QuadPart =
            endLargeIntegers[i].QuadPart - startLargeIntegers[i].QuadPart;
    }
    unk370 = endLargeIntegers[1].QuadPart * 2e-06f;
    unk374 = endLargeIntegers[2].QuadPart * 2e-06f;
}

void DxRnd::EndTiling(D3DBaseTexture *tex, int i2) {
    int l2 = 0;
    if (tex && i2) {
        l2 = (i2 & 0x3F) << 0x1A;
    }
    if (unk34c) {
        MILO_ASSERT(mNumTiles > 0, 0x480);
        HRESULT hr =
            D3DDevice_EndTiling(mD3DDevice, l2, nullptr, tex, nullptr, 0, 0, nullptr);
        DX_ASSERT_CODE(hr, 0x481);
        unk34c = false;
    } else {
        MILO_ASSERT(mNumTiles == 0, 0x486);
        D3DDevice_Resolve(
            mD3DDevice, l2, nullptr, tex, nullptr, 0, 0, nullptr, 0, 0, nullptr
        );
    }
}

void DxRnd::SavePreBuffer() {
    XMVECTOR vector;
    vector.v[0] = mClearColor.red;
    vector.v[1] = mClearColor.green;
    vector.v[2] = mClearColor.blue;
    vector.v[3] = 0;
    D3DDevice_Resolve(
        mD3DDevice, 0x14, nullptr, unk358, nullptr, 0, 0, nullptr, 1, 0, nullptr
    );
    D3DDevice_Resolve(
        mD3DDevice, 0x300, nullptr, unk390, nullptr, 0, 0, &vector, 0, 0, nullptr
    );
}

void DxRnd::SavePostBuffer() {
    D3DDevice_Resolve(
        mD3DDevice, 0, nullptr, unk394, nullptr, 0, 0, nullptr, 0, 0, nullptr
    );
}

void DxRnd::SetShaderRegisterAlloc(RegisterAlloc s) {
    MILO_ASSERT(s >=0 && s < kNumRegAlloc, 0x6BA);
    if (mRegAlloc != s) {
        mRegAlloc = s;
        switch (s) {
        case 0:
            D3DDevice_SetShaderGPRAllocation(mD3DDevice, 0, 0, 0);
            break;
        case 1:
            D3DDevice_SetShaderGPRAllocation(
                mD3DDevice, 0, mDefaultVSRegAlloc, mDefaultPSRegAlloc
            );
            break;
        case 2:
            D3DDevice_SetShaderGPRAllocation(mD3DDevice, 0, 0x10, 0x70);
            break;
        case 3:
            D3DDevice_SetShaderGPRAllocation(mD3DDevice, 0, 0x10, 0x70);
            break;
        default:
            MILO_NOTIFY("Invalid Shader Register Allocation");
            break;
        }
    }
}
