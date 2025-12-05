#pragma once
#include "d3d9types.h"
#include "xdk/xapilibi/xbase.h"

// Larger struct definitions and functions go here.

#ifdef __cplusplus
extern "C" {
#endif

// source for most if not all of this: the kinect joyride pdb

typedef struct _D3DConstants { /* Size=0x23a0 */
    union {
        /* 0x0000 */ GPUFETCH_CONSTANT Fetch[32];
        struct {
            /* 0x0000 */ GPUTEXTURE_FETCH_CONSTANT TextureFetch[26];
            /* 0x0270 */ GPUVERTEX_FETCH_CONSTANT VertexFetch[18];
        };
    };
    union {
        /* 0x0300 */ XMVECTOR Alu[512];
        struct {
            /* 0x0300 */ XMVECTOR VertexShaderF[256];
            /* 0x1300 */ XMVECTOR PixelShaderF[256];
        };
    };
    union {
        /* 0x2300 */ UINT Flow[40];
        struct {
            /* 0x2300 */ UINT VertexShaderB[4];
            /* 0x2310 */ UINT PixelShaderB[4];
            /* 0x2320 */ UINT VertexShaderI[16];
            /* 0x2360 */ UINT PixelShaderI[16];
        };
    };
} D3DConstants;

#pragma region D3DDevice

typedef struct D3DDevice { /* Size=0x2a80 */
    /* 0x0000 */ _D3DTAGCOLLECTION m_Pending;
    /* 0x0028 */ UINT64 m_Predicated_PendingMask2;
    /* 0x0030 */ UINT *m_pRing;
    /* 0x0034 */ UINT *m_pRingLimit;
    /* 0x0038 */ UINT *m_pRingGuarantee;
    /* 0x003c */ UINT m_ReferenceCount;
    /* 0x0040 */ VOID (*m_SetRenderStateCall[101])(D3DDevice *, UINT);
    /* 0x01d4 */ VOID (*m_SetSamplerStateCall[20])(D3DDevice *, UINT, UINT);
    /* 0x0224 */ UINT (*m_GetRenderStateCall[101])(D3DDevice *);
    /* 0x03b8 */ UINT (*m_GetSamplerStateCall[20])(D3DDevice *, UINT);
    /* 0x0480 */ D3DConstants m_Constants;
    /* 0x2820 */ float m_ClipPlanes[6][4];
    /* 0x2880 */ GPU_DESTINATIONPACKET m_DestinationPacket;
    /* 0x28c0 */ GPU_WINDOWPACKET m_WindowPacket;
    /* 0x28cc */ GPU_VALUESPACKET m_ValuesPacket;
    /* 0x2920 */ GPU_PROGRAMPACKET m_ProgramPacket;
    /* 0x2934 */ GPU_CONTROLPACKET m_ControlPacket;
    /* 0x2964 */ GPU_TESSELLATORPACKET m_TessellatorPacket;
    /* 0x29b8 */ GPU_MISCPACKET m_MiscPacket;
    /* 0x2a50 */ GPU_POINTPACKET m_PointPacket;
} D3DDevice;

#pragma endregion
#pragma region D3DResource

typedef struct D3DResource { /* Size=0x18 */
    /* 0x0000 */ UINT Common;
    /* 0x0004 */ UINT ReferenceCount;
    /* 0x0008 */ UINT Fence;
    /* 0x000c */ UINT ReadFence;
    /* 0x0010 */ UINT Identifier;
    /* 0x0014 */ UINT BaseFlush;

    UINT AddRef();
    UINT Release();
    INT GetDevice(D3DDevice **);
    D3DRESOURCETYPE GetType();
    BOOL IsBusy();
    BOOL IsSet(D3DDevice *);
    VOID BlockUntilNotBusy();
    VOID SetIdentifier(UINT);
    UINT GetIdentifier();
} D3DResource;

// D3DResource methods
UINT D3DResource_AddRef(D3DResource *self);
VOID D3DResource_BlockUntilNotBusy(D3DResource *self);
VOID D3DResource_GetDevice(D3DResource *self, D3DDevice **);
D3DRESOURCETYPE D3DResource_GetType(D3DResource *self);
BOOL D3DResource_IsBusy(D3DResource *self);
BOOL D3DResource_IsSet(D3DResource *self, D3DDevice *);
UINT D3DResource_Release(D3DResource *self);

#pragma endregion
#pragma region D3DIndexBuffer

struct D3DIndexBuffer;

VOID D3DIndexBuffer_GetDesc(D3DIndexBuffer *self, D3DINDEXBUFFER_DESC *pDesc);
HANDLE
D3DIndexBuffer_Lock(D3DIndexBuffer *self, UINT OffsetToLock, UINT SizeToLock, DWORD Flags);
HANDLE D3DIndexBuffer_AsyncLock(D3DIndexBuffer *, UINT64, UINT, UINT, UINT);
VOID D3DIndexBuffer_Unlock(D3DIndexBuffer *self);

typedef struct D3DIndexBuffer : public D3DResource { /* Size=0x20 */
    /* 0x0018 */ UINT Address;
    /* 0x001c */ UINT Size;

    HANDLE Lock(UINT offset, UINT size, DWORD flags) {
        return D3DIndexBuffer_Lock(this, offset, size, flags);
    }
    VOID Unlock() { D3DIndexBuffer_Unlock(this); }

    //   public: int32_t Lock(uint32_t, uint32_t, void**, uint32_t);
    //   public: int32_t AsyncLock(uint64_t, uint32_t, uint32_t, void**, uint32_t);
    //   public: int32_t Unlock();
    //   public: int32_t GetDesc(_D3DINDEXBUFFER_DESC*);

} D3DIndexBuffer;

#pragma endregion
#pragma region D3DVertexBuffer

struct D3DVertexBuffer;

VOID D3DVertexBuffer_GetDesc(D3DVertexBuffer *self, D3DVERTEXBUFFER_DESC *pDesc);
HANDLE D3DVertexBuffer_Lock(
    D3DVertexBuffer *self, UINT OffsetToLock, UINT SizeToLock, DWORD Flags
);
VOID D3DVertexBuffer_Unlock(D3DVertexBuffer *self);

typedef struct D3DVertexBuffer : public D3DResource { /* Size=0x20 */
    /* 0x0018 */ GPUVERTEX_FETCH_CONSTANT Format;

    HANDLE Lock(UINT offset, UINT size, DWORD flags) {
        return D3DVertexBuffer_Lock(this, offset, size, flags);
    }
    VOID Unlock() { D3DVertexBuffer_Unlock(this); }

    //   public: int32_t Lock(uint32_t, uint32_t, void**, uint32_t);
    //   public: int32_t AsyncLock(uint64_t, uint32_t, uint32_t, void**, uint32_t);
    //   public: int32_t Unlock();
    //   public: int32_t GetDesc(_D3DVERTEXBUFFER_DESC*);
} D3DVertexBuffer;

#pragma endregion
#pragma region D3DSurface

struct D3DSurface : public D3DResource { /* Size=0x30 */
    union {
        struct {
            /* 0x0018 */ GPU_SURFACEINFO SurfaceInfo;
            union {
                /* 0x001c */ GPU_DEPTHINFO DepthInfo;
                /* 0x001c */ GPU_COLORINFO ColorInfo;
            };
            /* 0x0020 */ GPU_HICONTROL HiControl;
            /* 0x0024 */ UINT Height : 15; /* BitPos=3 */
            /* 0x0024 */ UINT Width : 14; /* BitPos=18 */
            /* 0x0028 */ D3DFORMAT Format;
            /* 0x002c */ UINT Size;
        };
        struct {
            /* 0x0018 */ struct D3DBaseTexture *Parent;
            /* 0x001c */ UINT MipLevel : 4; /* BitPos=28 */
        };
    };

    INT GetContainer(const _GUID &, VOID **);
    INT GetDesc(D3DSURFACE_DESC *);
    INT LockRect(D3DLOCKED_RECT *, const tagRECT *, UINT);
    INT AsyncLockRect(UINT64, D3DLOCKED_RECT *, const tagRECT *, UINT);
    INT UnlockRect();
};

VOID D3DSurface_AsyncLockRect(
    D3DSurface *, UINT64, D3DLOCKED_RECT *, const tagRECT *, UINT
);
VOID D3DSurface_GetContainer(D3DSurface *, const _GUID &);
VOID D3DSurface_GetDesc(D3DSurface *, D3DSURFACE_DESC *);
VOID D3DSurface_LockRect(D3DSurface *, D3DLOCKED_RECT *, const tagRECT *, UINT);
VOID D3DSurface_UnlockRect(D3DSurface *);

#pragma endregion
#pragma region D3DTexture

struct D3DBaseTexture : public D3DResource { /* Size=0x34 */
    /* 0x0018 */ DWORD MipFlush;
    /* 0x001c */ GPUTEXTURE_FETCH_CONSTANT Format;

    UINT GetLevelCount();
    INT GetTailDesc(D3DMIPTAIL_DESC *);
    INT LockTail(UINT, D3DLOCKED_TAIL *, UINT);
    INT AsyncLockTail(UINT64, UINT, D3DLOCKED_TAIL *, UINT);
    INT UnlockTail(UINT);
};

VOID D3DBaseTexture_AsyncLockTail(D3DBaseTexture *, UINT64, UINT, D3DLOCKED_TAIL *, UINT);
UINT D3DBaseTexture_GetLevelCount(D3DBaseTexture *self);
VOID D3DBaseTexture_GetTailDesc(D3DBaseTexture *, D3DMIPTAIL_DESC *);
VOID D3DBaseTexture_LockTail(D3DBaseTexture *, UINT, D3DLOCKED_TAIL *, UINT);
VOID D3DBaseTexture_UnlockTail(D3DBaseTexture *, UINT);

struct D3DTexture : public D3DBaseTexture { /* Size=0x34 */
    /* 0x0000: fields for D3DBaseTexture */
    INT GetLevelDesc(UINT, D3DSURFACE_DESC *);
    INT GetSurfaceLevel(UINT, D3DSurface **);
    INT LockRect(UINT, D3DLOCKED_RECT *, const tagRECT *, UINT);
    INT AsyncLockRect(UINT64, UINT, D3DLOCKED_RECT *, const tagRECT *, UINT);
    INT UnlockRect(UINT);
    INT LockTail(D3DLOCKED_TAIL *, UINT);
    INT AsyncLockTail(UINT64, D3DLOCKED_TAIL *, UINT);
    INT UnlockTail();
};

VOID D3DTexture_AsyncLockRect(
    D3DTexture *, UINT64, UINT, D3DLOCKED_RECT *, const tagRECT *, UINT
);
VOID D3DTexture_GetLevelDesc(D3DTexture *, DWORD, D3DSURFACE_DESC *);
D3DSurface *D3DTexture_GetSurfaceLevel(D3DTexture *, UINT);
VOID D3DTexture_LockRect(D3DTexture *, UINT, D3DLOCKED_RECT *, const tagRECT *, UINT);
VOID D3DTexture_UnlockRect(D3DTexture *, UINT level);

struct D3DArrayTexture : public D3DBaseTexture { /* Size=0x34 */
    /* 0x0000: fields for D3DBaseTexture */
    UINT GetArraySize();
    INT GetLevelDesc(UINT, D3DSURFACE_DESC *);
    INT GetSurfaceLevel(UINT, D3DSurface **);
    INT GetArraySurface(UINT, UINT, D3DSurface **);
    INT LockRect(UINT, UINT, D3DLOCKED_RECT *, const tagRECT *, UINT);
    INT AsyncLockRect(UINT64, UINT, UINT, D3DLOCKED_RECT *, const tagRECT *, UINT);
    INT UnlockRect(UINT, UINT);
    INT LockTail(UINT, D3DLOCKED_TAIL *, UINT);
    INT AsyncLockTail(UINT64, UINT, D3DLOCKED_TAIL *, UINT);
    INT UnlockTail(UINT);
};

VOID D3DArrayTexture_AsyncLockRect(
    D3DArrayTexture *, UINT64, UINT, UINT, D3DLOCKED_RECT *, const tagRECT *, UINT
);
UINT D3DArrayTexture_GetArraySize(D3DArrayTexture *);
D3DSurface *D3DArrayTexture_GetArraySurface(D3DArrayTexture *, UINT, UINT);
VOID D3DArrayTexture_GetLevelDesc(D3DArrayTexture *, UINT, D3DSURFACE_DESC *);
VOID D3DArrayTexture_LockRect(
    D3DArrayTexture *, UINT, UINT, D3DLOCKED_RECT *, const tagRECT *, UINT
);
VOID D3DArrayTexture_UnlockRect(D3DArrayTexture *, UINT, UINT);

struct D3DCubeTexture : public D3DBaseTexture { /* Size=0x34 */
    /* 0x0000: fields for D3DBaseTexture */

    INT GetLevelDesc(UINT, D3DSURFACE_DESC *);
    INT GetCubeMapSurface(D3DCUBEMAP_FACES, UINT, D3DSurface **);
    INT LockRect(D3DCUBEMAP_FACES, UINT, D3DLOCKED_RECT *, const tagRECT *, UINT);
    INT
    AsyncLockRect(UINT64, D3DCUBEMAP_FACES, UINT, D3DLOCKED_RECT *, const tagRECT *, UINT);
    INT UnlockRect(D3DCUBEMAP_FACES, UINT);
    INT LockTail(D3DCUBEMAP_FACES, D3DLOCKED_TAIL *, UINT);
    INT AsyncLockTail(UINT64, D3DCUBEMAP_FACES, D3DLOCKED_TAIL *, UINT);
    INT UnlockTail(D3DCUBEMAP_FACES);
};

VOID D3DCubeTexture_AsyncLockRect(
    D3DCubeTexture *,
    UINT64,
    D3DCUBEMAP_FACES,
    UINT,
    D3DLOCKED_RECT *,
    const tagRECT *,
    UINT
);
D3DSurface *D3DCubeTexture_GetCubeMapSurface(D3DCubeTexture *, D3DCUBEMAP_FACES, UINT);
VOID D3DCubeTexture_GetLevelDesc(D3DCubeTexture *, UINT, D3DSURFACE_DESC *);
VOID D3DCubeTexture_LockRect(
    D3DCubeTexture *, D3DCUBEMAP_FACES, UINT, D3DLOCKED_RECT *, const tagRECT *, UINT
);
VOID D3DCubeTexture_UnlockRect(D3DCubeTexture *, D3DCUBEMAP_FACES, UINT);

struct D3DLineTexture : public D3DBaseTexture { /* Size=0x34 */
    /* 0x0000: fields for D3DBaseTexture */

    INT GetLevelDesc(UINT, D3DSURFACE_DESC *);
    INT GetSurfaceLevel(UINT, D3DSurface **);
    INT LockRect(UINT, D3DLOCKED_RECT *, const tagRECT *, UINT);
    INT AsyncLockRect(UINT64, UINT, D3DLOCKED_RECT *, const tagRECT *, UINT);
    INT UnlockRect(UINT);
    INT LockTail(D3DLOCKED_TAIL *, UINT);
    INT AsyncLockTail(UINT64, D3DLOCKED_TAIL *, UINT);
    INT UnlockTail();
};

VOID D3DLineTexture_AsyncLockRect(
    D3DLineTexture *, UINT64, UINT, D3DLOCKED_RECT *, const tagRECT *, UINT
);
VOID D3DLineTexture_GetLevelDesc(D3DLineTexture *, UINT, D3DSURFACE_DESC *);
D3DSurface *D3DLineTexture_GetSurfaceLevel(D3DLineTexture *, UINT);
VOID D3DLineTexture_LockRect(
    D3DLineTexture *, UINT, D3DLOCKED_RECT *, const tagRECT *, UINT
);
VOID D3DLineTexture_UnlockRect(D3DLineTexture *, UINT);

struct D3DVolumeTexture : public D3DBaseTexture { /* Size=0x34 */
    /* 0x0000: fields for D3DBaseTexture */

    INT GetLevelDesc(UINT, D3DVOLUME_DESC *);
    INT GetVolumeLevel(UINT, struct D3DVolume **);
    INT LockBox(UINT, D3DLOCKED_BOX *, const D3DBOX *, UINT);
    INT AsyncLockBox(UINT64, UINT, D3DLOCKED_BOX *, const D3DBOX *, UINT);
    INT UnlockBox(UINT);
    INT LockTail(D3DLOCKED_TAIL *, UINT);
    INT AsyncLockTail(UINT64, D3DLOCKED_TAIL *, UINT);
    INT UnlockTail();
};

VOID D3DVolumeTexture_GetLevelDesc(D3DVolumeTexture *, UINT, D3DVOLUME_DESC *);
D3DVolume *D3DVolumeTexture_GetVolumeLevel(D3DVolumeTexture *, UINT);
VOID D3DVolumeTexture_LockBox(
    D3DVolumeTexture *, UINT, D3DLOCKED_BOX *, const D3DBOX *, UINT
);
VOID D3DVolumeTexture_UnlockBox(D3DVolumeTexture *, UINT);

#pragma endregion
#pragma region D3DVolume

struct D3DVolume : public D3DResource { /* Size=0x20 */
    /* 0x0018 */ D3DBaseTexture *Parent;
    /* 0x001c */ UINT ArrayIndex : 6; /* BitPos=22 */
    /* 0x001c */ UINT MipLevel : 4; /* BitPos=28 */

    INT GetContainer(const _GUID &, VOID **);
    INT GetDesc(D3DVOLUME_DESC *);
    INT LockBox(D3DLOCKED_BOX *, const D3DBOX *, UINT);
    INT AsyncLockBox(UINT64, D3DLOCKED_BOX *, const D3DBOX *, UINT);
    INT UnlockBox();
};

void *D3DVolume_GetContainer(D3DVolume *, const _GUID &);
void D3DVolume_GetDesc(D3DVolume *, D3DVOLUME_DESC *);
void D3DVolume_LockBox(D3DVolume *, D3DLOCKED_BOX *, D3DBOX *, UINT);
void D3DVolume_UnlockBox(D3DVolume *);

#pragma endregion
#pragma region D3DQuery

struct D3DQuery { /* Size=0x1 */
    UINT AddRef();
    UINT Release();
    INT GetDevice(D3DDevice **);
    D3DQUERYTYPE GetType();
    UINT GetDataSize();
    INT Issue(UINT);
    INT GetData(VOID *, UINT, UINT);
};

UINT D3DQuery_AddRef(D3DQuery *);
UINT D3DQuery_Release(D3DQuery *);
INT D3DQuery_GetData(D3DQuery *, VOID *, UINT, UINT);
UINT D3DQuery_GetDataSize(D3DQuery *);
VOID D3DQuery_GetDevice(D3DQuery *, D3DDevice **);
D3DQUERYTYPE D3DQuery_GetType(D3DQuery *);
VOID D3DQuery_Issue(D3DQuery *, UINT);

#pragma endregion
#pragma region D3DPerfCounters

struct D3DPerfCounters { /* Size=0x1 */
    UINT AddRef();
    UINT Release();
    INT GetDevice(D3DDevice **);
    BOOL IsBusy();
    VOID BlockUntilNotBusy();
    UINT GetNumPasses();
    INT GetValues(D3DPERFCOUNTER_VALUES *, UINT, UINT *);
};

UINT D3DPerfCounters_AddRef(D3DPerfCounters *);
UINT D3DPerfCounters_Release(D3DPerfCounters *);
VOID D3DPerfCounters_GetDevice(D3DQuery *, D3DDevice **);
VOID D3DPerfCounters_BlockUntilNotBusy(D3DPerfCounters *);
UINT D3DPerfCounters_GetNumPasses(D3DPerfCounters *);
BOOL D3DPerfCounters_IsBusy(D3DPerfCounters *);
INT D3DPerfCounters_GetValues(D3DPerfCounters *, D3DPERFCOUNTER_VALUES *, UINT, UINT *);

struct D3DVertexDeclaration : public D3DResource { /* Size=0x18 */
    /* 0x0000: fields for D3DResource */
    INT GetDeclaration(D3DVERTEXELEMENT9 *, UINT *);
};

VOID D3DVertexDeclaration_GetDeclaration(D3DVertexDeclaration *, D3DVERTEXELEMENT9 *, UINT *);

#pragma endregion
#pragma region RenderState

uint D3DDevice_GetRenderState_BlendOp(D3DDevice *);
uint D3DDevice_GetRenderState_SrcBlend(D3DDevice *);
uint D3DDevice_GetRenderState_DestBlend(D3DDevice *);
uint D3DDevice_GetRenderState_SrcBlendAlpha(D3DDevice *);
uint D3DDevice_GetRenderState_DestBlendAlpha(D3DDevice *);

void D3DDevice_SetRenderState_AlphaBlendEnable(D3DDevice *, uint);
void D3DDevice_SetRenderState_AlphaFunc(D3DDevice *, D3DCMPFUNC);
void D3DDevice_SetRenderState_AlphaRef(D3DDevice *, DWORD);
void D3DDevice_SetRenderState_AlphaTestEnable(D3DDevice *, uint);
void D3DDevice_SetRenderState_BlendOp(D3DDevice *, uint);
void D3DDevice_SetRenderState_SrcBlend(D3DDevice *, uint);
void D3DDevice_SetRenderState_DestBlend(D3DDevice *, uint);
void D3DDevice_SetRenderState_SrcBlendAlpha(D3DDevice *, uint);
void D3DDevice_SetRenderState_DestBlendAlpha(D3DDevice *, uint);
void D3DDevice_SetRenderState_ColorWriteEnable(D3DDevice *, uint);
void D3DDevice_SetRenderState_FillMode(D3DDevice *, uint);
void D3DDevice_SetRenderState_CullMode(D3DDevice *, uint);
void D3DDevice_SetRenderState_StencilEnable(D3DDevice *, uint);
void D3DDevice_SetRenderState_StencilFail(D3DDevice *, uint);
void D3DDevice_SetRenderState_StencilZFail(D3DDevice *, uint);
void D3DDevice_SetRenderState_StencilPass(D3DDevice *, uint);
void D3DDevice_SetRenderState_StencilFunc(D3DDevice *, D3DCMPFUNC);
void D3DDevice_SetRenderState_StencilRef(D3DDevice *, DWORD);
void D3DDevice_SetRenderState_ZEnable(D3DDevice *, DWORD);
void D3DDevice_SetRenderState_ZFunc(D3DDevice *, D3DCMPFUNC);
void D3DDevice_SetRenderState_ZWriteEnable(D3DDevice *, DWORD);

#pragma endregion
#pragma region Misc

D3DVertexBuffer *D3DDevice_CreateVertexBuffer(UINT Length, DWORD Usage, D3DPOOL Pool);

D3DIndexBuffer *
D3DDevice_CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool);

HRESULT D3DDevice_SetStreamSource(
    D3DDevice *,
    UINT StreamNumber,
    D3DVertexBuffer *pStreamData,
    UINT OffsetInBytes,
    UINT Stride,
    UINT64 unk_r8
);

void D3DDevice_SetTexture(D3DDevice *, UINT, D3DBaseTexture *, UINT64);
D3DSurface *D3DDevice_GetRenderTarget(D3DDevice *, UINT);
D3DBaseTexture *D3DDevice_CreateTexture(
    UINT, UINT, UINT, UINT, UINT, D3DFORMAT, UINT, D3DRESOURCETYPE
);

#ifdef __cplusplus
}
#endif
