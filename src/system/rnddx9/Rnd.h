#pragma once
#include "os/Debug.h"
#include "rnddx9/Object.h"
#include "rndobj/Bitmap.h"
#include "rndobj/Rnd_NG.h"
#include "xdk/D3D9.h"
#include <types.h>

class DxRnd : public NgRnd {
public:
    DxRnd();
    virtual ~DxRnd();
    virtual DataNode Handle(DataArray *, bool);
    virtual void PreInit() { PreInit(nullptr); }
    virtual void Init() { Init(nullptr); }
    virtual void Terminate();
    virtual void Clear(unsigned int, const Hmx::Color &);
    virtual void
    DrawRect(const Hmx::Rect &, const Hmx::Color &, RndMat *, const Hmx::Color *, const Hmx::Color *);
    virtual Vector2 &
    DrawString(const char *, const Vector2 &, const Hmx::Color &, bool); // 0x80
    virtual void
    DrawLine(const Vector3 &, const Vector3 &, const Hmx::Color &, bool); // 0x84
    virtual void BeginDrawing();
    virtual void EndDrawing();
    virtual void MakeDrawTarget();
    virtual void SetSync(int sync);
    virtual RndTex *GetCurrentFrameTex(bool);
    virtual void CaptureNextGpuFrame() { unk3f6 = true; }
    virtual void SetAspect(Aspect a);
    virtual void SetShrinkToSafeArea(bool shrink);
    virtual void PushClipPlanesInternal(ObjPtrVec<RndTransformable> &);
    virtual void PopClipPlanesInternal(ObjPtrVec<RndTransformable> &);
    virtual void DoWorldEnd();
    virtual void DoPostProcess();
    virtual bool CanModal(Debug::ModalType);
    virtual void ModalDraw(Debug::ModalType, const char *);

    virtual void SetViewport(const Viewport &v);
    virtual void
    DrawRect(const Hmx::Rect &, RndMat *, ShaderType, const Hmx::Color &, const Hmx::Color *, const Hmx::Color *);
    virtual void DrawRectDepth(
        const Vector3 &, const Vector3 (&)[4], const Vector4 &, RndMat *, ShaderType
    );
    virtual bool Offscreen() const;
    virtual RndTex *PreProcessTexture() { return unk398; }
    virtual RndTex *PostProcessTexture() { return unk39c; }
    virtual RndTex *PreDepthTexture() { return unk3a0; }
    virtual void Suspend();
    virtual void Resume();
    virtual void CreateLargeQuad(int, int, LargeQuadRenderData &);
    virtual void
    DrawLargeQuad(const LargeQuadRenderData &, const Transform &, RndMat *, ShaderType);
    virtual void SetVertShaderTex(RndTex *, int);
    virtual void UpdateScalerParams();

    D3DDevice *GetD3DDevice() { return mD3DDevice; }
    void AutoRelease(class D3DResource *);
    u8 Unk301() const { return unk_0x301; }
    D3DSurface *BackBuffer() const;
    void PreInit(HWND__ *);
    void Init(HWND__ *);
    D3DTexture *FrontBuffer();
    D3DTexture *NotFrontBuffer();
    void ReleaseAutoRelease();
    void InitRenderState();
    D3DFORMAT D3DFormatForBitmap(const RndBitmap &);
    int BitmapOrderForD3DFormat(D3DFORMAT);

    static const char *Error(long);

private:
    void InitBuffers();
    void PreDeviceReset();
    void PostDeviceReset();
    void CreatePostTextures();

    int unk220;
    D3DDevice *mD3DDevice; // 0x224
    int unk228;
    int unk22c;
    int unk230;
    D3DPRESENT_PARAMETERS mPresentParams; // 0x234
    std::list<DxObject *> unk2b0;
    int unk2b8;
    int unk2bc;
    int unk2c0;
    int unk2c4;
    int unk2c8;
    int unk2cc;
    Timer unk2d0;
    bool unk300;
    u8 unk_0x301;
    std::vector<D3DResource *> unk304;
    std::vector<D3DBaseTexture *> unk310;
    // 0x31c - struct of size 0x30?
    int unk31c;
    int unk320;
    int unk324;
    int unk328;
    int unk32c;
    int unk330;
    int unk334;
    int unk338;
    int unk33c;
    int unk340;
    int unk344;
    int unk348;
    bool unk34c;
    bool unk34d;
    D3DTexture *unk350[2];
    D3DTexture *unk358;
    int unk35c;
    bool unk360;
    bool unk361;
    D3DPerfCounters *unk364; // 0x364
    D3DPerfCounters *unk368; // 0x368
    Timer *unk36c; // 0x36c
    float unk370;
    float unk374;
    bool unk378;
    int unk37c;
    D3DSurface *unk380; // 0x380 - back buffer?
    int unk384;
    int unk388;
    int unk38c;
    D3DTexture *unk390;
    D3DTexture *unk394;
    RndTex *unk398; // DxTex*
    RndTex *unk39c; // DxTex*
    RndTex *unk3a0; // DxTex*
    bool unk3a4;
    int unk3a8;
    int unk3ac;
    int unk3b0;
    int unk3b4;
    int unk3b8;
    int unk3bc;
    int unk3c0;
    int unk3c4;
    int unk3c8;
    int unk3cc;
    int unk3d0;
    int unk3d4;
    int unk3d8;
    int unk3dc;
    int unk3e0;
    int unk3e4;
    int unk3e8;
    int unk3ec;
    int unk3f0;
    bool unk3f4;
    bool unk3f5;
    bool unk3f6;
    bool unk3f7;
    int unk3f8;
    int mDefaultVSRegAlloc; // 0x3fc
    int mDefaultPSRegAlloc; // 0x400
    bool unk404;
    int unk408;
};

#define GPU_GPRS 0x80

extern DxRnd TheDxRnd;

int D3DFORMAT_BitsPerPixel(D3DFORMAT);

#define DX_RELEASE(x) (TheDxRnd.AutoRelease(x), x = nullptr)

inline HRESULT DxCheck(void *v) { return v ? ERROR_SUCCESS : E_OUTOFMEMORY; }

// check that the thing allocated successfully (e.g. no E_OUTOFMEMORY)
#define DX_ASSERT(cond, line)                                                            \
    {                                                                                    \
        HRESULT code = DxCheck(cond);                                                    \
        ((code)                                                                          \
         && (TheDebugFailer << MakeString(                                               \
                 "File: %s Line: %d Error: %s\n", __FILE__, line, DxRnd::Error(code)     \
             ),                                                                          \
             0));                                                                        \
    }
