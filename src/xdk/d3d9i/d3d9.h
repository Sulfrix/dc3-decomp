#pragma once
#include "d3d9types.h"
#include "d3d9caps.h"
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
UINT D3DResource_AddRef(D3DResource *pResource);
VOID D3DResource_BlockUntilNotBusy(D3DResource *pResource);
VOID D3DResource_GetDevice(D3DResource *pThis, D3DDevice **ppDevice);
D3DRESOURCETYPE D3DResource_GetType(D3DResource *pResource);
BOOL D3DResource_IsBusy(D3DResource *pResource);
BOOL D3DResource_IsSet(D3DResource *pResource, D3DDevice *pDevice);
UINT D3DResource_Release(D3DResource *pResource);

#pragma endregion
#pragma region D3DIndexBuffer

struct D3DIndexBuffer;

VOID D3DIndexBuffer_GetDesc(D3DIndexBuffer *pIndexBuffer, D3DINDEXBUFFER_DESC *pDesc);
HANDLE
D3DIndexBuffer_Lock(
    D3DIndexBuffer *pIndexBuffer, UINT OffsetToLock, UINT SizeToLock, DWORD Flags
);
HANDLE D3DIndexBuffer_AsyncLock(
    D3DIndexBuffer *pIndexBuffer,
    UINT64 AsyncBlock,
    UINT OffsetToLock,
    UINT SizeToLock,
    DWORD Flags
);
VOID D3DIndexBuffer_Unlock(D3DIndexBuffer *pIndexBuffer);

typedef struct D3DIndexBuffer : public D3DResource { /* Size=0x20 */
    /* 0x0018 */ UINT Address;
    /* 0x001c */ UINT Size;

    INT Lock(UINT OffsetToLock, UINT SizeToLock, void **ppbData, DWORD Flags) {
        *ppbData = D3DIndexBuffer_Lock(this, OffsetToLock, SizeToLock, Flags);
        return 0;
    }
    INT Unlock() {
        D3DIndexBuffer_Unlock(this);
        return 0;
    }

    //   public: int32_t AsyncLock(uint64_t, uint32_t, uint32_t, void**, uint32_t);
    //   public: int32_t GetDesc(_D3DINDEXBUFFER_DESC*);

} D3DIndexBuffer;

#pragma endregion
#pragma region D3DVertexBuffer

struct D3DVertexBuffer;

VOID D3DVertexBuffer_GetDesc(D3DVertexBuffer *pVertexBuffer, D3DVERTEXBUFFER_DESC *pDesc);
HANDLE D3DVertexBuffer_Lock(
    D3DVertexBuffer *pVertexBuffer, UINT OffsetToLock, UINT SizeToLock, DWORD Flags
);
VOID D3DVertexBuffer_Unlock(D3DVertexBuffer *pVertexBuffer);

typedef struct D3DVertexBuffer : public D3DResource { /* Size=0x20 */
    /* 0x0018 */ GPUVERTEX_FETCH_CONSTANT Format;

    INT Lock(UINT OffsetToLock, UINT SizeToLock, void **ppbData, DWORD Flags) {
        *ppbData = D3DVertexBuffer_Lock(this, OffsetToLock, SizeToLock, Flags);
        return 0;
    }
    INT Unlock() {
        D3DVertexBuffer_Unlock(this);
        return 0;
    }

    //   public: int32_t AsyncLock(uint64_t, uint32_t, uint32_t, void**, uint32_t);
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
    D3DSurface *pSurface,
    UINT64 AsyncBlock,
    D3DLOCKED_RECT *pLockedRect,
    const tagRECT *pRect,
    DWORD Flags
);
VOID D3DSurface_GetContainer(D3DSurface *pSurface, const _GUID &UnusedRiid);
VOID D3DSurface_GetDesc(D3DSurface *pSurface, D3DSURFACE_DESC *pDesc);
VOID D3DSurface_LockRect(
    D3DSurface *pSurface, D3DLOCKED_RECT *pLockedRect, const tagRECT *pRect, DWORD Flags
);
VOID D3DSurface_UnlockRect(D3DSurface *pSurface);

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

VOID D3DBaseTexture_AsyncLockTail(
    D3DBaseTexture *pTexture,
    UINT64 AsyncBlock,
    UINT ArrayIndex,
    D3DLOCKED_TAIL *pLockedTail,
    DWORD Flags
);
UINT D3DBaseTexture_GetLevelCount(D3DBaseTexture *pTexture);
VOID D3DBaseTexture_GetTailDesc(D3DBaseTexture *pTexture, D3DMIPTAIL_DESC *pDesc);
VOID D3DBaseTexture_LockTail(
    D3DBaseTexture *pTexture, UINT, D3DLOCKED_TAIL *pLockedTail, DWORD Flags
);
VOID D3DBaseTexture_UnlockTail(D3DBaseTexture *pTexture, UINT ArrayIndex);

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
    D3DTexture *pTexture,
    UINT64 AsyncBlock,
    UINT Level,
    D3DLOCKED_RECT *pLockedRect,
    const tagRECT *pRect,
    DWORD Flags
);
VOID D3DTexture_GetLevelDesc(D3DTexture *pTexture, UINT Level, D3DSURFACE_DESC *pDesc);
D3DSurface *D3DTexture_GetSurfaceLevel(D3DTexture *pTexture, UINT Level);
VOID D3DTexture_LockRect(
    D3DTexture *pTexture,
    UINT Level,
    D3DLOCKED_RECT *pLockedRect,
    const tagRECT *pRect,
    DWORD Flags
);
VOID D3DTexture_UnlockRect(D3DTexture *pTexture, UINT Level);

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
    D3DArrayTexture *pTexture,
    UINT64 AsyncBlock,
    UINT ArrayIndex,
    UINT Level,
    D3DLOCKED_RECT *pLockedRect,
    const tagRECT *pRect,
    DWORD Flags
);
UINT D3DArrayTexture_GetArraySize(D3DArrayTexture *pTexture);
D3DSurface *
D3DArrayTexture_GetArraySurface(D3DArrayTexture *pTexture, UINT ArrayIndex, UINT Level);
VOID D3DArrayTexture_GetLevelDesc(
    D3DArrayTexture *pTexture, UINT Level, D3DSURFACE_DESC *pDesc
);
VOID D3DArrayTexture_LockRect(
    D3DArrayTexture *pTexture,
    UINT ArrayIndex,
    UINT Level,
    D3DLOCKED_RECT *pLockedRect,
    const tagRECT *pRect,
    DWORD Flags
);
VOID D3DArrayTexture_UnlockRect(D3DArrayTexture *pTexture, UINT ArrayIndex, UINT Level);

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
    D3DCubeTexture *pTexture,
    UINT64 AsyncBlock,
    D3DCUBEMAP_FACES FaceType,
    UINT Level,
    D3DLOCKED_RECT *pLockedRect,
    const tagRECT *pRect,
    DWORD Flags
);
D3DSurface *D3DCubeTexture_GetCubeMapSurface(
    D3DCubeTexture *pTexture, D3DCUBEMAP_FACES FaceType, UINT Level
);
VOID D3DCubeTexture_GetLevelDesc(
    D3DCubeTexture *pTexture, UINT Level, D3DSURFACE_DESC *pDesc
);
VOID D3DCubeTexture_LockRect(
    D3DCubeTexture *pTexture,
    D3DCUBEMAP_FACES FaceType,
    UINT Level,
    D3DLOCKED_RECT *pLockedRect,
    const tagRECT *pRect,
    DWORD Flags
);
VOID D3DCubeTexture_UnlockRect(
    D3DCubeTexture *pTexture, D3DCUBEMAP_FACES FaceType, UINT Level
);

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
    D3DLineTexture *pTexture,
    UINT64 AsyncBlock,
    UINT Level,
    D3DLOCKED_RECT *pLockedRect,
    const tagRECT *pRect,
    DWORD Flags
);
VOID D3DLineTexture_GetLevelDesc(
    D3DLineTexture *pTexture, UINT Level, D3DSURFACE_DESC *pDesc
);
D3DSurface *D3DLineTexture_GetSurfaceLevel(D3DLineTexture *pTexture, UINT Level);
VOID D3DLineTexture_LockRect(
    D3DLineTexture *pTexture,
    UINT Level,
    D3DLOCKED_RECT *pLockedRect,
    const tagRECT *pRect,
    DWORD Flags
);
VOID D3DLineTexture_UnlockRect(D3DLineTexture *pTexture, UINT Level);

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

VOID D3DVolumeTexture_GetLevelDesc(
    D3DVolumeTexture *pTexture, UINT Level, D3DVOLUME_DESC *pDesc
);
D3DVolume *D3DVolumeTexture_GetVolumeLevel(D3DVolumeTexture *pTexture, UINT Level);
VOID D3DVolumeTexture_LockBox(
    D3DVolumeTexture *pTexture,
    UINT Level,
    D3DLOCKED_BOX *pLockedVolume,
    const D3DBOX *pBox,
    DWORD Flags
);
VOID D3DVolumeTexture_UnlockBox(D3DVolumeTexture *pTexture, UINT Level);

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

void *D3DVolume_GetContainer(D3DVolume *pVolume, const _GUID &UnusedRiid);
void D3DVolume_GetDesc(D3DVolume *pVolume, D3DVOLUME_DESC *pDesc);
void D3DVolume_LockBox(
    D3DVolume *pVolume, D3DLOCKED_BOX *pLockedVolume, const D3DBOX *pBox, DWORD Flags
);
void D3DVolume_UnlockBox(D3DVolume *pVolume);

#pragma endregion
#pragma region D3DQuery

struct D3DQuery { /* Size=0x1 */
    UINT AddRef();
    UINT Release();
    INT GetDevice(D3DDevice **);
    D3DQUERYTYPE GetType();
    UINT GetDataSize();
    INT Issue(DWORD);
    HRESULT GetData(VOID *, DWORD, DWORD);
};

UINT D3DQuery_AddRef(D3DQuery *pThis);
UINT D3DQuery_Release(D3DQuery *pThis);
UINT D3DQuery_GetDataSize(D3DQuery *pThis);
VOID D3DQuery_GetDevice(D3DQuery *pThis, D3DDevice **ppDevice);
D3DQUERYTYPE D3DQuery_GetType(D3DQuery *pThis);

INT D3DQuery_GetData(D3DQuery *pThis, VOID *pData, DWORD Size, DWORD GetDataFlags);
inline HRESULT D3DQuery::GetData(VOID *pData, DWORD Size, DWORD GetDataFlags) {
    return D3DQuery_GetData(this, pData, Size, GetDataFlags);
}

VOID D3DQuery_Issue(D3DQuery *pThis, DWORD IssueFlags);
inline INT D3DQuery::Issue(DWORD IssueFlags) {
    D3DQuery_Issue(this, IssueFlags);
    return 0;
}

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

UINT D3DPerfCounters_AddRef(D3DPerfCounters *pThis);
UINT D3DPerfCounters_Release(D3DPerfCounters *pThis);
VOID D3DPerfCounters_GetDevice(D3DPerfCounters *pThis, D3DDevice **ppDevice);
VOID D3DPerfCounters_BlockUntilNotBusy(D3DPerfCounters *pThis);
UINT D3DPerfCounters_GetNumPasses(D3DPerfCounters *pThis);
BOOL D3DPerfCounters_IsBusy(D3DPerfCounters *pThis);
HRESULT
D3DPerfCounters_GetValues(
    D3DPerfCounters *pThis, D3DPERFCOUNTER_VALUES *pValues, UINT PassIndex, UINT *pPassType
);

struct D3DVertexDeclaration : public D3DResource { /* Size=0x18 */
    /* 0x0000: fields for D3DResource */
    INT GetDeclaration(D3DVERTEXELEMENT9 *, UINT *);
};

VOID D3DVertexDeclaration_GetDeclaration(
    D3DVertexDeclaration *pThis, D3DVERTEXELEMENT9 *pDecl, UINT *pNumElements
);

#pragma endregion
#pragma region PerfCounters

typedef struct _D3DPERFCOUNTER_EVENTS { /* Size=0xf0 */
    /* 0x0000 */ GPUPERFEVENT_CP CP[1];
    /* 0x0004 */ GPUPERFEVENT_RBBM RBBM[2];
    /* 0x000c */ GPUPERFEVENT_SQ SQ[4];
    /* 0x001c */ GPUPERFEVENT_VGT VGT[4];
    /* 0x002c */ GPUPERFEVENT_VC VC[4];
    /* 0x003c */ GPUPERFEVENT_PA_SU PA_SU[4];
    /* 0x004c */ GPUPERFEVENT_PA_SC PA_SC[4];
    /* 0x005c */ GPUPERFEVENT_HZ HZ[2];
    /* 0x0064 */ GPUPERFEVENT_TCR TCR[2];
    /* 0x006c */ GPUPERFEVENT_TCM TCM[2];
    /* 0x0074 */ GPUPERFEVENT_TCF TCF[12];
    /* 0x00a4 */ GPUPERFEVENT_TP TP0[2];
    /* 0x00ac */ GPUPERFEVENT_TP TP1[2];
    /* 0x00b4 */ GPUPERFEVENT_TP TP2[2];
    /* 0x00bc */ GPUPERFEVENT_TP TP3[2];
    /* 0x00c4 */ GPUPERFEVENT_SX SX[1];
    /* 0x00c8 */ GPUPERFEVENT_BC BC[4];
    /* 0x00d8 */ GPUPERFEVENT_MC MC0[1];
    /* 0x00dc */ GPUPERFEVENT_MC MC1[1];
    /* 0x00e0 */ GPUPERFEVENT_MH MH[3];
    /* 0x00ec */ GPUPERFEVENT_BIF BIF[1];
} D3DPERFCOUNTER_EVENTS;

void D3DDevice_EnablePerfCounters(D3DDevice *pDevice, BOOL Enable);
void D3DDevice_SetPerfCounterEvents(
    D3DDevice *pDevice, const D3DPERFCOUNTER_EVENTS *pEvents, DWORD Flags
);
void D3DDevice_QueryPerfCounters(
    D3DDevice *pDevice, D3DPerfCounters *pCounters, DWORD Flags
);

#pragma endregion
#pragma region D3DPixelShader

struct D3DPixelShader : public D3DResource { /* Size=0x18 */
    /* 0x0000: fields for D3DResource */

    //   public: int32_t GetFunction(void*, uint32_t*);
};

D3DPixelShader *D3DDevice_CreatePixelShader(const DWORD *pFunction);
void D3DPixelShader_GetFunction(D3DPixelShader *pThis, void *pData, UINT *pSizeOfData);

#pragma endregion
#pragma region D3DVertexShader

struct D3DVertexShader : public D3DResource { /* Size=0x18 */
    /* 0x0000: fields for D3DResource */

    //   int32_t GetFunction(void*, uint32_t*);
    //   int32_t Bind(uint32_t, D3DVertexDeclaration*, const uint32_t*, D3DPixelShader*);
    //   int32_t IsBound();
};

D3DVertexShader *D3DDevice_CreateVertexShader(const DWORD *pFunction);

#pragma endregion
#pragma region RenderState

DWORD D3DDevice_GetRenderState_BlendOp(D3DDevice *pDevice);
DWORD D3DDevice_GetRenderState_SrcBlend(D3DDevice *pDevice);
DWORD D3DDevice_GetRenderState_DestBlend(D3DDevice *pDevice);
DWORD D3DDevice_GetRenderState_SrcBlendAlpha(D3DDevice *pDevice);
DWORD D3DDevice_GetRenderState_DestBlendAlpha(D3DDevice *pDevice);

void D3DDevice_SetRenderState_AlphaBlendEnable(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_AlphaFunc(D3DDevice *pDevice, D3DCMPFUNC Value);
void D3DDevice_SetRenderState_AlphaRef(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_AlphaTestEnable(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_BlendOp(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_SrcBlend(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_DestBlend(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_SrcBlendAlpha(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_DestBlendAlpha(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_ColorWriteEnable(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_FillMode(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_CullMode(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_StencilEnable(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_StencilFail(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_StencilZFail(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_StencilPass(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_StencilFunc(D3DDevice *pDevice, D3DCMPFUNC Value);
void D3DDevice_SetRenderState_StencilRef(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_ZEnable(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_ZFunc(D3DDevice *pDevice, D3DCMPFUNC Value);
void D3DDevice_SetRenderState_ZWriteEnable(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_PointSizeMax(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_SeparateAlphaBlendEnable(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_BlendOpAlpha(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_PresentInterval(D3DDevice *pDevice, DWORD Value);
void D3DDevice_SetRenderState_PresentImmediateThreshold(D3DDevice *pDevice, DWORD Value);

#pragma endregion
#pragma region Misc

void D3DDevice_SetSamplerState_MinFilter(D3DDevice *pDevice, DWORD Sampler, DWORD Value);
void D3DDevice_SetSamplerState_MagFilter(D3DDevice *pDevice, DWORD Sampler, DWORD Value);

D3DVertexBuffer *D3DDevice_CreateVertexBuffer(UINT Length, DWORD Usage, D3DPOOL Pool);

D3DIndexBuffer *
D3DDevice_CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool);

HRESULT D3DDevice_SetStreamSource(
    D3DDevice *pDevice,
    UINT StreamNumber,
    D3DVertexBuffer *pVertexBuffer,
    UINT OffsetInBytes,
    UINT StrideInBytes,
    UINT64 PendingMask3
);

void D3DDevice_SetTexture(
    D3DDevice *pDevice, DWORD Sampler, D3DBaseTexture *pTexture, UINT64 PendingMask3
);
D3DSurface *D3DDevice_GetRenderTarget(D3DDevice *pDevice, DWORD RenderTargetIndex);
D3DBaseTexture *D3DDevice_CreateTexture(
    UINT Width,
    UINT Height,
    UINT Depth,
    UINT Levels,
    DWORD Usage,
    D3DFORMAT D3DFormat,
    UINT Pool,
    D3DRESOURCETYPE D3DType
);

D3DVertexDeclaration *
D3DDevice_CreateVertexDeclaration(const D3DVERTEXELEMENT9 *pVertexElements);

void D3DDevice_SetFVF(D3DDevice *pDevice, DWORD FVF);
void D3DDevice_DrawVerticesUP(
    D3DDevice *pDevice,
    D3DPRIMITIVETYPE PrimitiveType,
    UINT VertexCount,
    const void *pVertexStreamZeroData,
    UINT VertexStreamZeroStride
);
void D3DDevice_SetRenderTarget_External(
    D3DDevice *pDevice, UINT RenderTargetIndex, D3DSurface *pRenderTarget
);
void D3DDevice_SetDepthStencilSurface(D3DDevice *pDevice, D3DSurface *pZStencilSurface);
void D3DDevice_SetViewport(D3DDevice *pDevice, const D3DVIEWPORT9 *pViewport);
void D3DDevice_SetIndices(D3DDevice *pDevice, D3DIndexBuffer *pIndexData);
void D3DDevice_DrawIndexedVertices(
    D3DDevice *pDevice,
    D3DPRIMITIVETYPE PrimitiveType,
    INT BaseVertexIndex,
    UINT StartIndex,
    UINT IndexCount
);
HRESULT D3DDevice_Reset(D3DDevice *pDevice, D3DPRESENT_PARAMETERS *);
void D3DDevice_Clear(
    D3DDevice *pDevice,
    UINT Count,
    const D3DRECT *pRects,
    UINT Flags,
    UINT Color,
    float Z,
    UINT Stencil,
    BOOL EDRamClear
);

void D3DDevice_SynchronizeToPresentationInterval(D3DDevice *pDevice);
void D3DDevice_QuerySwapStatus(D3DDevice *pDevice, D3DSWAP_STATUS *pSwapStatus);
void D3DDevice_Swap(
    D3DDevice *pDevice,
    D3DBaseTexture *pFrontBuffer,
    const D3DVIDEO_SCALER_PARAMETERS *pParameters
);
void D3DDevice_BlockUntilIdle(D3DDevice *pDevice);
void D3DDevice_SetSwapMode(D3DDevice *pDevice, BOOL Asynchronous);
UINT D3DDevice_Release(D3DDevice *pDevice);
void D3DDevice_SetGammaRamp(
    D3DDevice *pDevice, DWORD UnusedFlags, const D3DGAMMARAMP *pRamp
);
void D3DDevice_BeginTiling(
    D3DDevice *pDevice,
    DWORD Flags,
    DWORD Count,
    const D3DRECT *pTileRects,
    const XMVECTOR *pClearColor,
    float ClearZ,
    DWORD ClearStencil
);
D3DPerfCounters *D3DDevice_CreatePerfCounters(D3DDevice *pDevice, UINT NumPasses);

HRESULT
D3DDevice_EndTiling(
    D3DDevice *pDevice,
    UINT ResolveFlags,
    const D3DRECT *pResolveRects,
    D3DBaseTexture *pDestTexture,
    const XMVECTOR *pClearColor,
    float ClearZ,
    UINT ClearStencil,
    const D3DRESOLVE_PARAMETERS *pParameters
);

void D3DDevice_Resolve(
    D3DDevice *pDevice,
    UINT Flags,
    const D3DRECT *pSourceRect,
    D3DBaseTexture *pDestTexture,
    const D3DPOINT *pDestPoint,
    UINT DestLevel,
    UINT DestSliceOrFace,
    const XMVECTOR *pClearColor,
    float ClearZ,
    UINT ClearStencil,
    const D3DRESOLVE_PARAMETERS *pParameters
);

void D3DDevice_Suspend(D3DDevice *pDevice);
void D3DDevice_Resume(D3DDevice *pDevice);
void D3DDevice_SetShaderGPRAllocation(
    D3DDevice *pDevice, DWORD Flags, DWORD VertexShaderCount, DWORD PixelShaderCount
);
D3DSurface *D3DDevice_GetDepthStencilSurface(D3DDevice *pDevice);

HRESULT Direct3D_GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9 *pCaps);
HRESULT
Direct3D_CreateDevice(
    UINT Adapter,
    D3DDEVTYPE DeviceType,
    void *pUnused,
    DWORD BehaviorFlags,
    D3DPRESENT_PARAMETERS *pPresentationParameters,
    D3DDevice **ppReturnedDeviceInterface
);

D3DQuery *
D3DDevice_CreateQueryTiled(D3DDevice *pDevice, D3DQUERYTYPE Type, UINT TileCapacity);

#ifdef __cplusplus
}
#endif
