#include "Env.h"
#include "Mat.h"
#include "RenderState.h"
#include "TexRenderer.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rnddx9/OcclusionQueryMgr.h"
#include "rnddx9/Rnd.h"
#include "rndobj/Rnd_NG.h"
#include "rndobj/ShaderMgr.h"
#include "rndobj/ShadowMap.h"
#include "utl/Option.h"
#include "xdk/D3D9.h"

DxRnd::DxRnd()
    : unk220(0), mD3DDevice(nullptr), unk22c(0), unk230(1), unk_0x301(1), unk360(0),
      unk361(0), unk364(0), unk368(0), unk36c(0), unk370(0), unk374(0), unk378(0),
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
    unk3b0 = 0;
    unk34d = true;
}

DxRnd::~DxRnd() {
    if ((unsigned int)unk220) {
        unk220 = 0;
    }
}

void CDError();

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
        //     SVar6 = DxTexRenderer::StaticClassName();
        //                     /* WARNING: Load size is inaccurate */
        //     Hmx::Object::RegisterFactory(*SVar6.mStr,DxTexRenderer::NewObject);
        //     SVar6 = DxCam::StaticClassName();
        //                     /* WARNING: Load size is inaccurate */
        //     Hmx::Object::RegisterFactory(*SVar6.mStr,DxCam::NewObject);
        REGISTER_OBJ_FACTORY(DxEnviron);
        //     SVar6 = DxMesh::StaticClassName();
        //                     /* WARNING: Load size is inaccurate */
        //     Hmx::Object::RegisterFactory(*SVar6.mStr,DxMesh::NewObject);
        DxMat::Init();
        //     SVar6 = DxTex::StaticClassName();
        //                     /* WARNING: Load size is inaccurate */
        //     Hmx::Object::RegisterFactory(*SVar6.mStr,DxTex::NewObject);
        //     SVar6 = DxCubeTex::StaticClassName();
        //                     /* WARNING: Load size is inaccurate */
        //     Hmx::Object::RegisterFactory(*SVar6.mStr,DxCubeTex::NewObject);
        //     DxMultiMesh::Init();
        //     SVar6 = DxMovie::StaticClassName();
        //                     /* WARNING: Load size is inaccurate */
        //     Hmx::Object::RegisterFactory(*SVar6.mStr,DxMovie::NewObject);
        //     DxParticleSys::Init();
        //     DxLight::Init();
        //     CreatePostTextures(this);
        //     DxTex::sEDRamChecksEnabled = false;
        //     NgPostProc::Init();
        //     NgDOFProc::Init();
        //     DxTex::sEDRamChecksEnabled = true;
        RndShadowMap::Init();
        Rnd::CreateDefaults();
        //     Debug::SetModalCallback(&TheDebug,DxModal);
    }
}

void DxRnd::Init(HWND__ *h) {
    PreInit(h);
    mOcclusionQueryMgr = new DxRndOcclusionQueryMgr();
    NgRnd::Init();
    //   DxTex::Init();
    unk360 = false;
}

D3DSurface *DxRnd::BackBuffer() const {
    D3DResource_AddRef(unk380);
    return unk380;
}

D3DTexture *DxRnd::FrontBuffer() { return unk350[unk35c / 2]; }
D3DTexture *DxRnd::NotFrontBuffer() { return unk350[unk35c]; }

const char *DxRnd::Error(long code) { return MakeString("code %d", code); }
