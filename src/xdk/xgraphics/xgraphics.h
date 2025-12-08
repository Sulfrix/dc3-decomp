#pragma once
#include "xdk/XAPILIB.h"
#include "xdk/D3D9.h"
// This is where Xbox related functions that use D3D9 stuff will go.

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _XGTEXTURE_DESC { /* Size=0x3c */
    /* 0x0000 */ D3DRESOURCETYPE ResourceType;
    /* 0x0004 */ UINT Width;
    /* 0x0008 */ UINT Height;
    /* 0x000c */ UINT Depth;
    /* 0x0010 */ D3DFORMAT Format;
    /* 0x0014 */ UINT RowPitch;
    /* 0x0018 */ UINT SlicePitch;
    /* 0x001c */ UINT BitsPerPixel;
    /* 0x0020 */ UINT WidthInBlocks;
    /* 0x0024 */ UINT HeightInBlocks;
    /* 0x0028 */ UINT DepthInBlocks;
    /* 0x002c */ UINT BytesPerBlock;
    /* 0x0030 */ INT ExpBias;
    /* 0x0034 */ UINT Flags;
    /* 0x0038 */ D3DMULTISAMPLE_TYPE MultiSampleType;
} XGTEXTURE_DESC;

typedef struct _XGLAYOUT_REGION { /* Size=0x8 */
    /* 0x0000 */ UINT StartOffset;
    /* 0x0004 */ UINT EndOffset;
} XGLAYOUT_REGION;

UINT XGSurfaceSize(UINT, UINT, D3DFORMAT, D3DMULTISAMPLE_TYPE);
UINT XGHierarchicalZSize(UINT, UINT, D3DMULTISAMPLE_TYPE);
VOID XGGetTextureDesc(D3DBaseTexture *, UINT, XGTEXTURE_DESC *);
VOID XGTileTextureLevel(UINT, UINT, UINT, UINT, UINT, VOID *, const tagPOINT *, const VOID *, UINT, const tagRECT *);

void XGGetTextureLayout(
    D3DBaseTexture *pTexture,
    UINT *pBaseData,
    UINT *pBaseSize,
    XGLAYOUT_REGION *pBaseRegionList,
    UINT *pBaseRegionListCount,
    UINT BaseRegionAlignment,
    UINT *pMipData,
    UINT *pMipSize,
    XGLAYOUT_REGION *pMipRegionList,
    UINT *pMipRegionListCount,
    UINT MipRegionAlignment
);

#ifdef __cplusplus
}
#endif
