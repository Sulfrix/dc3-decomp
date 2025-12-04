#pragma once
#include "xdk/win_types.h"
#include "xdk/XMVECTOR.h"

// Enums and very small struct definitions go here.

#pragma region Enums

typedef enum _D3DFORMAT {
    D3DFMT_DXT1 = 0x1a200152,
    D3DFMT_LIN_DXT1 = 0x1a200052,
    D3DFMT_DXT2 = 0x1a200153,
    D3DFMT_LIN_DXT2 = 0x1a200053,
    D3DFMT_DXT3 = 0x1a200153,
    D3DFMT_LIN_DXT3 = 0x1a200053,
    D3DFMT_DXT3A = 0x1a20017a,
    D3DFMT_LIN_DXT3A = 0x1a20007a,
    D3DFMT_DXT3A_1111 = 0x1a20017d,
    D3DFMT_LIN_DXT3A_1111 = 0x1a20007d,
    D3DFMT_DXT4 = 0x1a200154,
    D3DFMT_LIN_DXT4 = 0x1a200054,
    D3DFMT_DXT5 = 0x1a200154,
    D3DFMT_LIN_DXT5 = 0x1a200054,
    D3DFMT_DXT5A = 0x1a20017b,
    D3DFMT_LIN_DXT5A = 0x1a20007b,
    D3DFMT_DXN = 0x1a200171,
    D3DFMT_LIN_DXN = 0x1a200071,
    D3DFMT_CTX1 = 0x1a20017c,
    D3DFMT_LIN_CTX1 = 0x1a20007c,
    D3DFMT_A8 = 0x04900102,
    D3DFMT_LIN_A8 = 0x04900002,
    D3DFMT_L8 = 0x28000102,
    D3DFMT_LIN_L8 = 0x28000002,
    D3DFMT_R5G6B5 = 0x28280144,
    D3DFMT_LIN_R5G6B5 = 0x28280044,
    D3DFMT_R6G5B5 = 0x28280145,
    D3DFMT_LIN_R6G5B5 = 0x28280045,
    D3DFMT_L6V5U5 = 0x2a200b45,
    D3DFMT_LIN_L6V5U5 = 0x2a200a45,
    D3DFMT_X1R5G5B5 = 0x28280143,
    D3DFMT_LIN_X1R5G5B5 = 0x28280043,
    D3DFMT_A1R5G5B5 = 0x18280143,
    D3DFMT_LIN_A1R5G5B5 = 0x18280043,
    D3DFMT_A4R4G4B4 = 0x1828014f,
    D3DFMT_LIN_A4R4G4B4 = 0x1828004f,
    D3DFMT_X4R4G4B4 = 0x2828014f,
    D3DFMT_LIN_X4R4G4B4 = 0x2828004f,
    D3DFMT_Q4W4V4U4 = 0x1a20ab4f,
    D3DFMT_LIN_Q4W4V4U4 = 0x1a20aa4f,
    D3DFMT_A8L8 = 0x0800014a,
    D3DFMT_LIN_A8L8 = 0x0800004a,
    D3DFMT_G8R8 = 0x2d20014a,
    D3DFMT_LIN_G8R8 = 0x2d20004a,
    D3DFMT_V8U8 = 0x2d20ab4a,
    D3DFMT_LIN_V8U8 = 0x2d20aa4a,
    D3DFMT_D16 = 0x1a220158,
    D3DFMT_LIN_D16 = 0x1a220058,
    D3DFMT_L16 = 0x28000158,
    D3DFMT_LIN_L16 = 0x28000058,
    D3DFMT_R16F = 0x2da2ab5e,
    D3DFMT_LIN_R16F = 0x2da2aa5e,
    D3DFMT_R16F_EXPAND = 0x2da2ab5b,
    D3DFMT_LIN_R16F_EXPAND = 0x2da2aa5b,
    D3DFMT_UYVY = 0x1a20014c,
    D3DFMT_LIN_UYVY = 0x1a20004c,
    D3DFMT_LE_UYVY = 0x1a20010c,
    D3DFMT_LE_LIN_UYVY = 0x1a20000c,
    D3DFMT_G8R8_G8B8 = 0x1828014c,
    D3DFMT_LIN_G8R8_G8B8 = 0x1828004c,
    D3DFMT_R8G8_B8G8 = 0x1828014b,
    D3DFMT_LIN_R8G8_B8G8 = 0x1828004b,
    D3DFMT_YUY2 = 0x1a20014b,
    D3DFMT_LIN_YUY2 = 0x1a20004b,
    D3DFMT_LE_YUY2 = 0x1a20010b,
    D3DFMT_LE_LIN_YUY2 = 0x1a20000b,
    D3DFMT_A8R8G8B8 = 0x18280186,
    D3DFMT_LIN_A8R8G8B8 = 0x18280086,
    D3DFMT_X8R8G8B8 = 0x28280186,
    D3DFMT_LIN_X8R8G8B8 = 0x28280086,
    D3DFMT_A8B8G8R8 = 0x1a200186,
    D3DFMT_LIN_A8B8G8R8 = 0x1a200086,
    D3DFMT_X8B8G8R8 = 0x2a200186,
    D3DFMT_LIN_X8B8G8R8 = 0x2a200086,
    D3DFMT_X8L8V8U8 = 0x2a200b86,
    D3DFMT_LIN_X8L8V8U8 = 0x2a200a86,
    D3DFMT_Q8W8V8U8 = 0x1a20ab86,
    D3DFMT_LIN_Q8W8V8U8 = 0x1a20aa86,
    D3DFMT_A2R10G10B10 = 0x182801b6,
    D3DFMT_LIN_A2R10G10B10 = 0x182800b6,
    D3DFMT_X2R10G10B10 = 0x282801b6,
    D3DFMT_LIN_X2R10G10B10 = 0x282800b6,
    D3DFMT_A2B10G10R10 = 0x1a2001b6,
    D3DFMT_LIN_A2B10G10R10 = 0x1a2000b6,
    D3DFMT_A2W10V10U10 = 0x1a202bb6,
    D3DFMT_LIN_A2W10V10U10 = 0x1a202ab6,
    D3DFMT_A16L16 = 0x08000199,
    D3DFMT_LIN_A16L16 = 0x08000099,
    D3DFMT_G16R16 = 0x2d200199,
    D3DFMT_LIN_G16R16 = 0x2d200099,
    D3DFMT_V16U16 = 0x2d20ab99,
    D3DFMT_LIN_V16U16 = 0x2d20aa99,
    D3DFMT_R10G11B11 = 0x282801b7,
    D3DFMT_LIN_R10G11B11 = 0x282800b7,
    D3DFMT_R11G11B10 = 0x282801b8,
    D3DFMT_LIN_R11G11B10 = 0x282800b8,
    D3DFMT_W10V11U11 = 0x2a20abb7,
    D3DFMT_LIN_W10V11U11 = 0x2a20aab7,
    D3DFMT_W11V11U10 = 0x2a20abb8,
    D3DFMT_LIN_W11V11U10 = 0x2a20aab8,
    D3DFMT_G16R16F = 0x2d22ab9f,
    D3DFMT_LIN_G16R16F = 0x2d22aa9f,
    D3DFMT_G16R16F_EXPAND = 0x2d22ab9c,
    D3DFMT_LIN_G16R16F_EXPAND = 0x2d22aa9c,
    D3DFMT_L32 = 0x280001a1,
    D3DFMT_LIN_L32 = 0x280000a1,
    D3DFMT_R32F = 0x2da2aba4,
    D3DFMT_LIN_R32F = 0x2da2aaa4,
    D3DFMT_D24S8 = 0x2d200196,
    D3DFMT_LIN_D24S8 = 0x2d200096,
    D3DFMT_D24X8 = 0x2da00196,
    D3DFMT_LIN_D24X8 = 0x2da00096,
    D3DFMT_D24FS8 = 0x1a220197,
    D3DFMT_LIN_D24FS8 = 0x1a220097,
    D3DFMT_D32 = 0x1a2201a1,
    D3DFMT_LIN_D32 = 0x1a2200a1,
    D3DFMT_A16B16G16R16 = 0x1a20015a,
    D3DFMT_LIN_A16B16G16R16 = 0x1a20005a,
    D3DFMT_Q16W16V16U16 = 0x1a20ab5a,
    D3DFMT_LIN_Q16W16V16U16 = 0x1a20aa5a,
    D3DFMT_A16B16G16R16F = 0x1a22ab60,
    D3DFMT_LIN_A16B16G16R16F = 0x1a22aa60,
    D3DFMT_A16B16G16R16F_EXPAND = 0x1a22ab5d,
    D3DFMT_LIN_A16B16G16R16F_EXPAND = 0x1a22aa5d,
    D3DFMT_A32L32 = 0x080001a2,
    D3DFMT_LIN_A32L32 = 0x080000a2,
    D3DFMT_G32R32 = 0x2d2001a2,
    D3DFMT_LIN_G32R32 = 0x2d2000a2,
    D3DFMT_V32U32 = 0x2d20aba2,
    D3DFMT_LIN_V32U32 = 0x2d20aaa2,
    D3DFMT_G32R32F = 0x2d22aba5,
    D3DFMT_LIN_G32R32F = 0x2d22aaa5,
    D3DFMT_A32B32G32R32 = 0x1a2001a3,
    D3DFMT_LIN_A32B32G32R32 = 0x1a2000a3,
    D3DFMT_Q32W32V32U32 = 0x1a20aba3,
    D3DFMT_LIN_Q32W32V32U32 = 0x1a20aaa3,
    D3DFMT_A32B32G32R32F = 0x1a22aba6,
    D3DFMT_LIN_A32B32G32R32F = 0x1a22aaa6,
    D3DFMT_A2B10G10R10F_EDRAM = 0x1a2201bf,
    D3DFMT_G16R16_EDRAM = 0x2d20ab8d,
    D3DFMT_A16B16G16R16_EDRAM = 0x1a20ab55,
    D3DFMT_LE_X8R8G8B8 = 0x28280106,
    D3DFMT_LE_A8R8G8B8 = 0x18280106,
    D3DFMT_LE_X2R10G10B10 = 0x28280136,
    D3DFMT_LE_A2R10G10B10 = 0x18280136,
    D3DFMT_INDEX16 = 0x0001,
    D3DFMT_INDEX32 = 0x0006,
    D3DFMT_LE_INDEX16 = 0x0000,
    D3DFMT_LE_INDEX32 = 0x0004,
    D3DFMT_VERTEXDATA = 0x0008,
    D3DFMT_UNKNOWN = 0xff,
    D3DFMT_FORCE_DWORD = 0x7fffffff,
} D3DFORMAT;

typedef enum _D3DCMPFUNC {
    D3DCMP_NEVER = 0x0000,
    D3DCMP_LESS = 0x0001,
    D3DCMP_EQUAL = 0x0002,
    D3DCMP_LESSEQUAL = 0x0003,
    D3DCMP_GREATER = 0x0004,
    D3DCMP_NOTEQUAL = 0x0005,
    D3DCMP_GREATEREQUAL = 0x0006,
    D3DCMP_ALWAYS = 0x0007,
    D3DCMP_FORCE_DWORD = 0x7fffffff,
} D3DCMPFUNC, *LPD3DCMPFUNC;

/// https://learn.microsoft.com/en-us/windows/win32/direct3d9/d3dpool
typedef enum D3DPOOL {
    D3DPOOL_DEFAULT = 0,
    D3DPOOL_MANAGED = 1,
    D3DPOOL_SYSTEMMEM = 2,
    D3DPOOL_SCRATCH = 3,
    D3DPOOL_FORCE_DWORD = 0x7fffffff
} D3DPOOL, *LPD3DPOOL;

typedef enum _D3DRESOURCETYPE {
    D3DRTYPE_NONE = 0x0000,
    D3DRTYPE_VERTEXBUFFER = 0x0001,
    D3DRTYPE_INDEXBUFFER = 0x0002,
    D3DRTYPE_TEXTURE = 0x0003,
    D3DRTYPE_SURFACE = 0x0004,
    D3DRTYPE_VERTEXDECLARATION = 0x0005,
    D3DRTYPE_VERTEXSHADER = 0x0006,
    D3DRTYPE_PIXELSHADER = 0x0007,
    D3DRTYPE_CONSTANTBUFFER = 0x0008,
    D3DRTYPE_COMMANDBUFFER = 0x0009,
    D3DRTYPE_VOLUME = 0x0010,
    D3DRTYPE_VOLUMETEXTURE = 0x0011,
    D3DRTYPE_CUBETEXTURE = 0x0012,
    D3DRTYPE_ARRAYTEXTURE = 0x0013,
    D3DRTYPE_LINETEXTURE = 0x0014,
    D3DRTYPE_FORCE_DWORD = 0x7fffffff,
} D3DRESOURCETYPE, *LPD3DRESOURCETYPE;

typedef enum _D3DMULTISAMPLE_TYPE {
    D3DMULTISAMPLE_NONE = 0x0000,
    D3DMULTISAMPLE_2_SAMPLES = 0x0001,
    D3DMULTISAMPLE_4_SAMPLES = 0x0002,
    D3DMULTISAMPLE_FORCE_DWORD = 0x7fffffff,
} D3DMULTISAMPLE_TYPE, *LPD3DMULTISAMPLE_TYPE;

#pragma endregion
#pragma region D3D Structs

struct _D3DTAGCOLLECTION { /* Size=0x28 */
    /* 0x0000 */ UINT64 m_Mask[5];
};

/// https://learn.microsoft.com/en-us/windows/win32/direct3d9/d3dindexbuffer-desc
typedef struct _D3DINDEXBUFFER_DESC {
    D3DFORMAT Format;
    D3DRESOURCETYPE Type;
    DWORD Usage;
    D3DPOOL Pool; // pdb says this is a UINT (and not an enum)
    UINT Size;
} D3DINDEXBUFFER_DESC, *LPD3DINDEXBUFFER_DESC;

/// https://learn.microsoft.com/en-us/windows/win32/direct3d9/d3dvertexbuffer-desc
typedef struct _D3DVERTEXBUFFER_DESC {
    D3DFORMAT Format;
    D3DRESOURCETYPE Type;
    DWORD Usage;
    D3DPOOL Pool; // pdb says this is a UINT (and not an enum)
    UINT Size;
    DWORD FVF;
} D3DVERTEXBUFFER_DESC, *LPD3DVERTEXBUFFER_DESC;

typedef struct _D3DSURFACE_DESC { /* Size=0x20 */
    /* 0x0000 */ _D3DFORMAT Format;
    /* 0x0004 */ _D3DRESOURCETYPE Type;
    /* 0x0008 */ DWORD Usage;
    /* 0x000c */ DWORD Pool;
    /* 0x0010 */ _D3DMULTISAMPLE_TYPE MultiSampleType;
    /* 0x0014 */ DWORD MultiSampleQuality;
    /* 0x0018 */ DWORD Width;
    /* 0x001c */ DWORD Height;
} D3DSURFACE_DESC, *LPD3DSURFACE_DESC;

typedef enum _D3DHIZFUNC {
    D3DHIZFUNC_DEFAULT = 0x0000,
    D3DHIZFUNC_LESS_EQUAL = 0x0001,
    D3DHIZFUNC_GREATER_EQUAL = 0x0002,
    D3DHIZFUNC_FORCE_DWORD = 0x7fffffff,
} D3DHIZFUNC;

typedef struct _D3DSURFACE_PARAMETERS { /* Size=0x10 */
    /* 0x0000 */ UINT Base;
    /* 0x0004 */ UINT HierarchicalZBase;
    /* 0x0008 */ INT ColorExpBias;
    /* 0x000c */ D3DHIZFUNC HiZFunc;
} D3DSURFACE_PARAMETERS;

typedef struct _D3DVOLUME_DESC { /* Size=0x1c */
    /* 0x0000 */ _D3DFORMAT Format;
    /* 0x0004 */ _D3DRESOURCETYPE Type;
    /* 0x0008 */ UINT Usage;
    /* 0x000c */ UINT Pool;
    /* 0x0010 */ UINT Width;
    /* 0x0014 */ UINT Height;
    /* 0x0018 */ UINT Depth;
} D3DVOLUME_DESC;

typedef struct _D3DLOCKED_RECT { /* Size=0x8 */
    /* 0x0000 */ INT Pitch;
    /* 0x0004 */ VOID *pBits;
} D3DLOCKED_RECT;

struct tagRECT { /* Size=0x10 */
    /* 0x0000 */ INT left;
    /* 0x0004 */ INT top;
    /* 0x0008 */ INT right;
    /* 0x000c */ INT bottom;
};

typedef struct _D3DLOCKED_BOX { /* Size=0xc */
    /* 0x0000 */ INT RowPitch;
    /* 0x0004 */ INT SlicePitch;
    /* 0x0008 */ VOID *pBits;
} D3DLOCKED_BOX;

typedef struct _D3DBOX { /* Size=0x18 */
    /* 0x0000 */ UINT Left;
    /* 0x0004 */ UINT Top;
    /* 0x0008 */ UINT Right;
    /* 0x000c */ UINT Bottom;
    /* 0x0010 */ UINT Front;
    /* 0x0014 */ UINT Back;
} D3DBOX;

typedef struct _D3DRECT { /* Size=0x10 */
    /* 0x0000 */ INT x1;
    /* 0x0004 */ INT y1;
    /* 0x0008 */ INT x2;
    /* 0x000c */ INT y2;
} D3DRECT;

typedef struct _D3DRING_BUFFER_PARAMETERS { /* Size=0x18 */
    /* 0x0000 */ UINT Flags;
    /* 0x0004 */ UINT PrimarySize;
    /* 0x0008 */ void *pPrimary;
    /* 0x000c */ UINT SecondarySize;
    /* 0x0010 */ void *pSecondary;
    /* 0x0014 */ UINT SegmentCount;
} D3DRING_BUFFER_PARAMETERS;

typedef enum _D3DCOLORSPACE {
    D3DCOLORSPACE_RGB = 0x0000,
    D3DCOLORSPACE_YCbCr601 = 0x0001,
    D3DCOLORSPACE_YCbCr709 = 0x0002,
    D3DCOLORSPACE_FORCE_DWORD = 0x7fffffff,
} D3DCOLORSPACE;

typedef struct _D3DVIDEO_SCALER_PARAMETERS { /* Size=0x1c */
    /* 0x0000 */ _D3DRECT ScalerSourceRect;
    /* 0x0010 */ UINT ScaledOutputWidth;
    /* 0x0014 */ UINT ScaledOutputHeight;
    /* 0x0018 */ UINT FilterProfile;
} D3DVIDEO_SCALER_PARAMETERS;

typedef enum _D3DSWAPEFFECT {
    D3DSWAPEFFECT_DISCARD = 0x0001,
    D3DSWAPEFFECT_FLIP = 0x0002,
    D3DSWAPEFFECT_COPY = 0x0003,
    D3DSWAPEFFECT_FORCE_DWORD = 0x7fffffff,
} D3DSWAPEFFECT;

struct HWND__ { /* Size=0x4 */
    /* 0x0000 */ INT unused;
};

typedef struct _D3DPRESENT_PARAMETERS_ { /* Size=0x7c */
    /* 0x0000 */ UINT BackBufferWidth;
    /* 0x0004 */ UINT BackBufferHeight;
    /* 0x0008 */ _D3DFORMAT BackBufferFormat;
    /* 0x000c */ UINT BackBufferCount;
    /* 0x0010 */ _D3DMULTISAMPLE_TYPE MultiSampleType;
    /* 0x0014 */ UINT MultiSampleQuality;
    /* 0x0018 */ _D3DSWAPEFFECT SwapEffect;
    /* 0x001c */ HWND__ *hDeviceWindow;
    /* 0x0020 */ INT Windowed;
    /* 0x0024 */ INT EnableAutoDepthStencil;
    /* 0x0028 */ _D3DFORMAT AutoDepthStencilFormat;
    /* 0x002c */ UINT Flags;
    /* 0x0030 */ UINT FullScreen_RefreshRateInHz;
    /* 0x0034 */ UINT PresentationInterval;
    /* 0x0038 */ INT DisableAutoBackBuffer;
    /* 0x003c */ INT DisableAutoFrontBuffer;
    /* 0x0040 */ _D3DFORMAT FrontBufferFormat;
    /* 0x0044 */ _D3DCOLORSPACE FrontBufferColorSpace;
    /* 0x0048 */ _D3DRING_BUFFER_PARAMETERS RingBufferParameters;
    /* 0x0060 */ _D3DVIDEO_SCALER_PARAMETERS VideoScalerParameters;
} D3DPRESENT_PARAMETERS;

#pragma endregion
#pragma region GPU Structs

union GPUVERTEX_FETCH_CONSTANT { /* Size=0x8 */
    struct {
        /* 0x0000 */ UINT Type : 2; /* BitPos=0 */
        /* 0x0000 */ UINT BaseAddress : 30; /* BitPos=2 */
        /* 0x0000 */ UINT : 0; /* BitPos=32 */
        /* 0x0004 */ UINT Endian : 2; /* BitPos=0 */
        /* 0x0004 */ UINT Size : 24; /* BitPos=2 */
        /* 0x0004 */ UINT AddressClamp : 1; /* BitPos=26 */
        /* 0x0004 */ UINT : 1; /* BitPos=27 */
        /* 0x0004 */ UINT RequestSize : 2; /* BitPos=28 */
        /* 0x0004 */ UINT ClampDisable : 2; /* BitPos=30 */
    };
    /* 0x0000 */ UINT dword[2];
};

struct GPUTEXTURESIZE_2D { /* Size=0x4 */
    /* 0x0000 */ DWORD Width : 13; /* BitPos=0 */
    /* 0x0000 */ DWORD Height : 13; /* BitPos=13 */
};

struct GPUTEXTURESIZE_1D { /* Size=0x4 */
    /* 0x0000 */ DWORD Width : 24; /* BitPos=0 */
};

struct GPUTEXTURESIZE_STACK { /* Size=0x4 */
    /* 0x0000 */ DWORD Width : 13; /* BitPos=0 */
    /* 0x0000 */ DWORD Height : 13; /* BitPos=13 */
    /* 0x0000 */ DWORD Depth : 6; /* BitPos=26 */
};

struct GPUTEXTURESIZE_3D { /* Size=0x4 */
    /* 0x0000 */ DWORD Width : 11; /* BitPos=0 */
    /* 0x0000 */ DWORD Height : 11; /* BitPos=11 */
    /* 0x0000 */ DWORD Depth : 10; /* BitPos=22 */
};

union GPUTEXTURE_FETCH_CONSTANT { /* Size=0x18 */
    struct {
        /* 0x0000 */ DWORD Type : 2; /* BitPos=0 */
        /* 0x0000 */ DWORD SignX : 2; /* BitPos=2 */
        /* 0x0000 */ DWORD SignY : 2; /* BitPos=4 */
        /* 0x0000 */ DWORD SignZ : 2; /* BitPos=6 */
        /* 0x0000 */ DWORD SignW : 2; /* BitPos=8 */
        /* 0x0000 */ DWORD ClampX : 3; /* BitPos=10 */
        /* 0x0000 */ DWORD ClampY : 3; /* BitPos=13 */
        /* 0x0000 */ DWORD ClampZ : 3; /* BitPos=16 */
        /* 0x0000 */ UINT : 3; /* BitPos=19 */
        /* 0x0000 */ DWORD Pitch : 9; /* BitPos=22 */
        /* 0x0000 */ DWORD Tiled : 1; /* BitPos=31 */
        /* 0x0000 */ UINT : 0; /* BitPos=32 */
        /* 0x0004 */ DWORD DataFormat : 6; /* BitPos=0 */
        /* 0x0004 */ DWORD Endian : 2; /* BitPos=6 */
        /* 0x0004 */ DWORD RequestSize : 2; /* BitPos=8 */
        /* 0x0004 */ DWORD Stacked : 1; /* BitPos=10 */
        /* 0x0004 */ DWORD ClampPolicy : 1; /* BitPos=11 */
        /* 0x0004 */ DWORD BaseAddress : 20; /* BitPos=12 */
        /* 0x0008 */ union { /* Size=0x4 */
            /* 0x0000 */ GPUTEXTURESIZE_1D OneD;
            /* 0x0000 */ GPUTEXTURESIZE_2D TwoD;
            /* 0x0000 */ GPUTEXTURESIZE_3D ThreeD;
            /* 0x0000 */ GPUTEXTURESIZE_STACK Stack;
        } Size;
        /* 0x000c */ DWORD NumFormat : 1; /* BitPos=0 */
        /* 0x000c */ DWORD SwizzleX : 3; /* BitPos=1 */
        /* 0x000c */ DWORD SwizzleY : 3; /* BitPos=4 */
        /* 0x000c */ DWORD SwizzleZ : 3; /* BitPos=7 */
        /* 0x000c */ DWORD SwizzleW : 3; /* BitPos=10 */
        /* 0x000c */ INT ExpAdjust : 6; /* BitPos=13 */
        /* 0x000c */ DWORD MagFilter : 2; /* BitPos=19 */
        /* 0x000c */ DWORD MinFilter : 2; /* BitPos=21 */
        /* 0x000c */ DWORD MipFilter : 2; /* BitPos=23 */
        /* 0x000c */ DWORD AnisoFilter : 3; /* BitPos=25 */
        /* 0x000c */ UINT : 3; /* BitPos=28 */
        /* 0x000c */ DWORD BorderSize : 1; /* BitPos=31 */
        /* 0x000c */ UINT : 0; /* BitPos=32 */
        /* 0x0010 */ DWORD VolMagFilter : 1; /* BitPos=0 */
        /* 0x0010 */ DWORD VolMinFilter : 1; /* BitPos=1 */
        /* 0x0010 */ DWORD MinMipLevel : 4; /* BitPos=2 */
        /* 0x0010 */ DWORD MaxMipLevel : 4; /* BitPos=6 */
        /* 0x0010 */ DWORD MagAnisoWalk : 1; /* BitPos=10 */
        /* 0x0010 */ DWORD MinAnisoWalk : 1; /* BitPos=11 */
        /* 0x0010 */ INT LODBias : 10; /* BitPos=12 */
        /* 0x0010 */ INT GradExpAdjustH : 5; /* BitPos=22 */
        /* 0x0010 */ INT GradExpAdjustV : 5; /* BitPos=27 */
        /* 0x0010 */ INT : 0; /* BitPos=32 */
        /* 0x0014 */ DWORD BorderColor : 2; /* BitPos=0 */
        /* 0x0014 */ DWORD ForceBCWToMax : 1; /* BitPos=2 */
        /* 0x0014 */ DWORD TriClamp : 2; /* BitPos=3 */
        /* 0x0014 */ INT AnisoBias : 4; /* BitPos=5 */
        /* 0x0014 */ DWORD Dimension : 2; /* BitPos=9 */
        /* 0x0014 */ DWORD PackedMips : 1; /* BitPos=11 */
        /* 0x0014 */ DWORD MipAddress : 20; /* BitPos=12 */
    };
    /* 0x0000 */ DWORD dword[6];
};

union GPUFETCH_CONSTANT { /* Size=0x18 */
    /* 0x0000 */ GPUTEXTURE_FETCH_CONSTANT Texture;
    /* 0x0000 */ GPUVERTEX_FETCH_CONSTANT Vertex[3];
};

union GPU_POINT { /* Size=0x4 */
    struct {
        /* 0x0000 */ INT X : 15; /* BitPos=0 */
        /* 0x0000 */ INT : 1; /* BitPos=15 */
        /* 0x0000 */ INT Y : 15; /* BitPos=16 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_COLORINFO { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT ColorBase : 12; /* BitPos=0 */
        /* 0x0000 */ UINT : 4; /* BitPos=12 */
        /* 0x0000 */ UINT ColorFormat : 4; /* BitPos=16 */
        /* 0x0000 */ UINT ColorExpBias : 6; /* BitPos=20 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_DEPTHINFO { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT DepthBase : 12; /* BitPos=0 */
        /* 0x0000 */ UINT : 4; /* BitPos=12 */
        /* 0x0000 */ UINT DepthFormat : 1; /* BitPos=16 */
        /* 0x0000 */ UINT DisableHZClamp : 1; /* BitPos=17 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_SURFACEINFO { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT SurfacePitch : 14; /* BitPos=0 */
        /* 0x0000 */ UINT : 2; /* BitPos=14 */
        /* 0x0000 */ UINT MsaaSamples : 2; /* BitPos=16 */
        /* 0x0000 */ UINT HiZPitch : 14; /* BitPos=18 */
    };
    /* 0x0000 */ UINT dword;
};

struct GPU_DESTINATIONPACKET { /* Size=0x40 */
    /* 0x0000 */ GPU_SURFACEINFO SurfaceInfo;
    /* 0x0004 */ GPU_COLORINFO Color0Info;
    /* 0x0008 */ GPU_DEPTHINFO DepthInfo;
    /* 0x000c */ GPU_COLORINFO Color1Info;
    /* 0x0010 */ GPU_COLORINFO Color2Info;
    /* 0x0014 */ GPU_COLORINFO Color3Info;
    /* 0x0018 */ UINT CoherDestBase0;
    /* 0x001c */ UINT CoherDestBase1;
    /* 0x0020 */ UINT CoherDestBase2;
    /* 0x0024 */ UINT CoherDestBase3;
    /* 0x0028 */ UINT CoherDestBase4;
    /* 0x002c */ UINT CoherDestBase5;
    /* 0x0030 */ UINT CoherDestBase6;
    /* 0x0034 */ UINT CoherDestBase7;
    /* 0x0038 */ GPU_POINT ScreenScissorTL;
    /* 0x003c */ GPU_POINT ScreenScissorBR;
};

struct GPU_WINDOWPACKET { /* Size=0xc */
    /* 0x0000 */ GPU_POINT WindowOffset;
    /* 0x0004 */ GPU_POINT WindowScissorTL;
    /* 0x0008 */ GPU_POINT WindowScissorBR;
};

union GPU_COLORMASK { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT Write0 : 4; /* BitPos=0 */
        /* 0x0000 */ UINT Write1 : 4; /* BitPos=4 */
        /* 0x0000 */ UINT Write2 : 4; /* BitPos=8 */
        /* 0x0000 */ UINT Write3 : 4; /* BitPos=12 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_STENCILREFMASK { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT Ref : 8; /* BitPos=0 */
        /* 0x0000 */ UINT Mask : 8; /* BitPos=8 */
        /* 0x0000 */ UINT WriteMask : 8; /* BitPos=16 */
    };
    /* 0x0000 */ UINT dword;
};

struct GPU_VALUESPACKET { /* Size=0x54 */
    /* 0x0000 */ UINT MaxVtxIndx;
    /* 0x0004 */ UINT MinVtxIndx;
    /* 0x0008 */ UINT IndxOffset;
    /* 0x000c */ UINT MultiPrimIbResetIndx;
    /* 0x0010 */ GPU_COLORMASK ColorMask;
    /* 0x0014 */ float BlendRed;
    /* 0x0018 */ float BlendGreen;
    /* 0x001c */ float BlendBlue;
    /* 0x0020 */ float BlendAlpha;
    /* 0x0024 */ UINT Unused[3];
    /* 0x0030 */ GPU_STENCILREFMASK StencilRefMaskBF;
    /* 0x0034 */ GPU_STENCILREFMASK StencilRefMask;
    /* 0x0038 */ float AlphaRef;
    /* 0x003c */ float VportXScale;
    /* 0x0040 */ float VportXOffset;
    /* 0x0044 */ float VportYScale;
    /* 0x0048 */ float VportYOffset;
    /* 0x004c */ float VportZScale;
    /* 0x0050 */ float VportZOffset;
};

union GPU_CONTEXTMISC { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT InstPredOptimize : 1; /* BitPos=0 */
        /* 0x0000 */ UINT OutputScreenXY : 1; /* BitPos=1 */
        /* 0x0000 */ UINT SampleControl : 2; /* BitPos=2 */
        /* 0x0000 */ UINT : 4; /* BitPos=4 */
        /* 0x0000 */ UINT ParamGenPos : 8; /* BitPos=8 */
        /* 0x0000 */ UINT PerfCounterRef : 1; /* BitPos=16 */
        /* 0x0000 */ UINT YieldOptimize : 1; /* BitPos=17 */
        /* 0x0000 */ UINT TxCacheSelect : 1; /* BitPos=18 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_PROGRAMCONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT VsMaxReg : 6; /* BitPos=0 */
        /* 0x0000 */ UINT : 2; /* BitPos=6 */
        /* 0x0000 */ UINT PsMaxReg : 6; /* BitPos=8 */
        /* 0x0000 */ UINT : 2; /* BitPos=14 */
        /* 0x0000 */ UINT VsResource : 1; /* BitPos=16 */
        /* 0x0000 */ UINT PsResource : 1; /* BitPos=17 */
        /* 0x0000 */ UINT ParamGen : 1; /* BitPos=18 */
        /* 0x0000 */ UINT GenIndexPix : 1; /* BitPos=19 */
        /* 0x0000 */ UINT VsExportCount : 4; /* BitPos=20 */
        /* 0x0000 */ UINT VsExportMode : 3; /* BitPos=24 */
        /* 0x0000 */ UINT PsExportZ : 1; /* BitPos=27 */
        /* 0x0000 */ UINT PsExportColorCount : 3; /* BitPos=28 */
        /* 0x0000 */ UINT GenIndexVtx : 1; /* BitPos=31 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_INTERPOLATORCONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT ParamShade : 16; /* BitPos=0 */
        /* 0x0000 */ UINT SamplingPattern : 16; /* BitPos=16 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_WRAPPING1 { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT Wrap0 : 4; /* BitPos=0 */
        /* 0x0000 */ UINT Wrap1 : 4; /* BitPos=4 */
        /* 0x0000 */ UINT Wrap2 : 4; /* BitPos=8 */
        /* 0x0000 */ UINT Wrap3 : 4; /* BitPos=12 */
        /* 0x0000 */ UINT Wrap4 : 4; /* BitPos=16 */
        /* 0x0000 */ UINT Wrap5 : 4; /* BitPos=20 */
        /* 0x0000 */ UINT Wrap6 : 4; /* BitPos=24 */
        /* 0x0000 */ UINT Wrap7 : 4; /* BitPos=28 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_WRAPPING0 { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT Wrap8 : 4; /* BitPos=0 */
        /* 0x0000 */ UINT Wrap9 : 4; /* BitPos=4 */
        /* 0x0000 */ UINT Wrap10 : 4; /* BitPos=8 */
        /* 0x0000 */ UINT Wrap11 : 4; /* BitPos=12 */
        /* 0x0000 */ UINT Wrap12 : 4; /* BitPos=16 */
        /* 0x0000 */ UINT Wrap13 : 4; /* BitPos=20 */
        /* 0x0000 */ UINT Wrap14 : 4; /* BitPos=24 */
        /* 0x0000 */ UINT Wrap15 : 4; /* BitPos=28 */
    };
    /* 0x0000 */ UINT dword;
};

struct GPU_PROGRAMPACKET { /* Size=0x14 */
    /* 0x0000 */ GPU_PROGRAMCONTROL ProgramControl;
    /* 0x0004 */ GPU_CONTEXTMISC ContextMisc;
    /* 0x0008 */ GPU_INTERPOLATORCONTROL InterpolatorControl;
    /* 0x000c */ GPU_WRAPPING0 Wrapping0;
    /* 0x0010 */ GPU_WRAPPING1 Wrapping1;
};

union GPU_MODECONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT CullMode : 3; /* BitPos=0 */
        /* 0x0000 */ UINT PolyMode : 2; /* BitPos=3 */
        /* 0x0000 */ UINT PolyModeFrontPType : 3; /* BitPos=5 */
        /* 0x0000 */ UINT PolyModeBackPType : 3; /* BitPos=8 */
        /* 0x0000 */ UINT PolyOffsetFrontEnable : 1; /* BitPos=11 */
        /* 0x0000 */ UINT PolyOffsetBackEnable : 1; /* BitPos=12 */
        /* 0x0000 */ UINT PolyOffsetParaEnable : 1; /* BitPos=13 */
        /* 0x0000 */ UINT : 1; /* BitPos=14 */
        /* 0x0000 */ UINT MsaaEnable : 1; /* BitPos=15 */
        /* 0x0000 */ UINT VtxWindowOffsetEnable : 1; /* BitPos=16 */
        /* 0x0000 */ UINT : 2; /* BitPos=17 */
        /* 0x0000 */ UINT ProvokingVtxLast : 1; /* BitPos=19 */
        /* 0x0000 */ UINT PerspCorrDisable : 1; /* BitPos=20 */
        /* 0x0000 */ UINT MultiPrimIbEnable : 1; /* BitPos=21 */
        /* 0x0000 */ UINT : 1; /* BitPos=22 */
        /* 0x0000 */ UINT QuadOrderEnable : 1; /* BitPos=23 */
        /* 0x0000 */ UINT ScOneQuadPerClock : 1; /* BitPos=24 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_COLORCONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT AlphaFunc : 3; /* BitPos=0 */
        /* 0x0000 */ UINT AlphaTestEnable : 1; /* BitPos=3 */
        /* 0x0000 */ UINT AlphaToMaskEnable : 1; /* BitPos=4 */
        /* 0x0000 */ UINT : 19; /* BitPos=5 */
        /* 0x0000 */ UINT AlphaToMaskOffset0 : 2; /* BitPos=24 */
        /* 0x0000 */ UINT AlphaToMaskOffset1 : 2; /* BitPos=26 */
        /* 0x0000 */ UINT AlphaToMaskOffset2 : 2; /* BitPos=28 */
        /* 0x0000 */ UINT AlphaToMaskOffset3 : 2; /* BitPos=30 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_VTECONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT VportXScaleEnable : 1; /* BitPos=0 */
        /* 0x0000 */ UINT VportXOffsetEnable : 1; /* BitPos=1 */
        /* 0x0000 */ UINT VportYScaleEnable : 1; /* BitPos=2 */
        /* 0x0000 */ UINT VportYOffsetEnable : 1; /* BitPos=3 */
        /* 0x0000 */ UINT VportZScaleEnable : 1; /* BitPos=4 */
        /* 0x0000 */ UINT VportZOffsetEnable : 1; /* BitPos=5 */
        /* 0x0000 */ UINT : 2; /* BitPos=6 */
        /* 0x0000 */ UINT VtxXyFmt : 1; /* BitPos=8 */
        /* 0x0000 */ UINT VtxZFmt : 1; /* BitPos=9 */
        /* 0x0000 */ UINT VtxW0Fmt : 1; /* BitPos=10 */
        /* 0x0000 */ UINT PerfCounterRef : 1; /* BitPos=11 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_BLENDCONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT ColorSrcBlend : 5; /* BitPos=0 */
        /* 0x0000 */ UINT ColorBlendOp : 3; /* BitPos=5 */
        /* 0x0000 */ UINT ColorDestBlend : 5; /* BitPos=8 */
        /* 0x0000 */ UINT : 3; /* BitPos=13 */
        /* 0x0000 */ UINT AlphaSrcBlend : 5; /* BitPos=16 */
        /* 0x0000 */ UINT AlphaBlendOp : 3; /* BitPos=21 */
        /* 0x0000 */ UINT AlphaDestBlend : 5; /* BitPos=24 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_DEPTHCONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT StencilEnable : 1; /* BitPos=0 */
        /* 0x0000 */ UINT ZEnable : 1; /* BitPos=1 */
        /* 0x0000 */ UINT ZWriteEnable : 1; /* BitPos=2 */
        /* 0x0000 */ UINT : 1; /* BitPos=3 */
        /* 0x0000 */ UINT ZFunc : 3; /* BitPos=4 */
        /* 0x0000 */ UINT BackFaceEnable : 1; /* BitPos=7 */
        /* 0x0000 */ UINT StencilFunc : 3; /* BitPos=8 */
        /* 0x0000 */ UINT StencilFail : 3; /* BitPos=11 */
        /* 0x0000 */ UINT StencilZPass : 3; /* BitPos=14 */
        /* 0x0000 */ UINT StencilZFail : 3; /* BitPos=17 */
        /* 0x0000 */ UINT StencilFuncBF : 3; /* BitPos=20 */
        /* 0x0000 */ UINT StencilFailBF : 3; /* BitPos=23 */
        /* 0x0000 */ UINT StencilZPassBF : 3; /* BitPos=26 */
        /* 0x0000 */ UINT StencilZFailBF : 3; /* BitPos=29 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_CLIPCONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT ClipPlaneEnable0 : 1; /* BitPos=0 */
        /* 0x0000 */ UINT ClipPlaneEnable1 : 1; /* BitPos=1 */
        /* 0x0000 */ UINT ClipPlaneEnable2 : 1; /* BitPos=2 */
        /* 0x0000 */ UINT ClipPlaneEnable3 : 1; /* BitPos=3 */
        /* 0x0000 */ UINT ClipPlaneEnable4 : 1; /* BitPos=4 */
        /* 0x0000 */ UINT ClipPlaneEnable5 : 1; /* BitPos=5 */
        /* 0x0000 */ UINT : 8; /* BitPos=6 */
        /* 0x0000 */ UINT ClipPlaneMode : 2; /* BitPos=14 */
        /* 0x0000 */ UINT ClipDisable : 1; /* BitPos=16 */
        /* 0x0000 */ UINT ClipPlaneCullOnlyEnable : 1; /* BitPos=17 */
        /* 0x0000 */ UINT BoundaryEdgeFlagEnable : 1; /* BitPos=18 */
        /* 0x0000 */ UINT DxClipSpaceDef : 1; /* BitPos=19 */
        /* 0x0000 */ UINT DisableClipErrDetect : 1; /* BitPos=20 */
        /* 0x0000 */ UINT VtxKillOr : 1; /* BitPos=21 */
        /* 0x0000 */ UINT XyNanRetain : 1; /* BitPos=22 */
        /* 0x0000 */ UINT ZNanRetain : 1; /* BitPos=23 */
        /* 0x0000 */ UINT WNanRetain : 1; /* BitPos=24 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_EDRAMMODECONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT EdramMode : 3; /* BitPos=0 */
        /* 0x0000 */ UINT ColorDepthMacro : 1; /* BitPos=3 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_HICONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT HiZWriteEnable : 1; /* BitPos=0 */
        /* 0x0000 */ UINT HiZEnable : 1; /* BitPos=1 */
        /* 0x0000 */ UINT HiStencilWriteEnable : 1; /* BitPos=2 */
        /* 0x0000 */ UINT HiStencilEnable : 1; /* BitPos=3 */
        /* 0x0000 */ UINT HiZFunc : 1; /* BitPos=4 */
        /* 0x0000 */ UINT HiStencilFunc : 1; /* BitPos=5 */
        /* 0x0000 */ UINT : 2; /* BitPos=6 */
        /* 0x0000 */ UINT HiStencilRef : 8; /* BitPos=8 */
        /* 0x0000 */ UINT : 1; /* BitPos=16 */
        /* 0x0000 */ UINT HiBaseAddr : 15; /* BitPos=17 */
    };
    /* 0x0000 */ UINT dword;
};

struct GPU_CONTROLPACKET { /* Size=0x30 */
    /* 0x0000 */ GPU_DEPTHCONTROL DepthControl;
    /* 0x0004 */ GPU_BLENDCONTROL BlendControl0;
    /* 0x0008 */ GPU_COLORCONTROL ColorControl;
    /* 0x000c */ GPU_HICONTROL HiControl;
    /* 0x0010 */ GPU_CLIPCONTROL ClipControl;
    /* 0x0014 */ GPU_MODECONTROL ModeControl;
    /* 0x0018 */ GPU_VTECONTROL VteControl;
    /* 0x001c */ UINT Unused;
    /* 0x0020 */ GPU_EDRAMMODECONTROL EdramModeControl;
    /* 0x0024 */ GPU_BLENDCONTROL BlendControl1;
    /* 0x0028 */ GPU_BLENDCONTROL BlendControl2;
    /* 0x002c */ GPU_BLENDCONTROL BlendControl3;
};

union GPU_LINECONTROL { /* Size=0x4 */
    /* 0x0000 */ UINT Width : 16; /* BitPos=0 */
    /* 0x0000 */ UINT dword;
};

union GPU_VIZQUERY { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT VizQueryEnable : 1; /* BitPos=0 */
        /* 0x0000 */ UINT VizQueryId : 6; /* BitPos=1 */
        /* 0x0000 */ UINT KillPixPostHiZ : 1; /* BitPos=7 */
        /* 0x0000 */ UINT KillPixPostDetailMask : 1; /* BitPos=8 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_ENHANCE { /* Size=0x4 */
    /* 0x0000 */ UINT Misc : 16; /* BitPos=0 */
    /* 0x0000 */ UINT dword;
};

union GPU_GROUPVECTCONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT CompXEnable : 1; /* BitPos=0 */
        /* 0x0000 */ UINT CompYEnable : 1; /* BitPos=1 */
        /* 0x0000 */ UINT CompZEnable : 1; /* BitPos=2 */
        /* 0x0000 */ UINT CompWEnable : 1; /* BitPos=3 */
        /* 0x0000 */ UINT : 4; /* BitPos=4 */
        /* 0x0000 */ UINT Stride : 8; /* BitPos=8 */
        /* 0x0000 */ UINT Shift : 8; /* BitPos=16 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_POINTSIZE { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT Height : 16; /* BitPos=0 */
        /* 0x0000 */ UINT Width : 16; /* BitPos=16 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_GROUPPRIMTYPE { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT GroupPrimType : 4; /* BitPos=0 */
        /* 0x0000 */ UINT : 10; /* BitPos=4 */
        /* 0x0000 */ UINT GroupRetainOrder : 1; /* BitPos=14 */
        /* 0x0000 */ UINT GroupRetainQuads : 1; /* BitPos=15 */
        /* 0x0000 */ UINT GroupPrimOrder : 3; /* BitPos=16 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_HOSCONTROL { /* Size=0x4 */
    /* 0x0000 */ UINT TessMode : 2; /* BitPos=0 */
    /* 0x0000 */ UINT dword;
};

union GPU_OUTPUTPATHCONTROL { /* Size=0x4 */
    /* 0x0000 */ UINT PathSelect : 2; /* BitPos=0 */
    /* 0x0000 */ UINT dword;
};

union GPU_POINTMINMAX { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT MinSize : 16; /* BitPos=0 */
        /* 0x0000 */ UINT MaxSize : 16; /* BitPos=16 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_GROUPVECTFMTCONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT XConv : 4; /* BitPos=0 */
        /* 0x0000 */ UINT XOffset : 4; /* BitPos=4 */
        /* 0x0000 */ UINT YConv : 4; /* BitPos=8 */
        /* 0x0000 */ UINT YOffset : 4; /* BitPos=12 */
        /* 0x0000 */ UINT ZConv : 4; /* BitPos=16 */
        /* 0x0000 */ UINT ZOffset : 4; /* BitPos=20 */
        /* 0x0000 */ UINT WConv : 4; /* BitPos=24 */
        /* 0x0000 */ UINT WOffset : 4; /* BitPos=28 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_MPASSPSCONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT MPassPixVecPerPass : 20; /* BitPos=0 */
        /* 0x0000 */ UINT : 11; /* BitPos=20 */
        /* 0x0000 */ UINT MPassPsEnable : 1; /* BitPos=31 */
    };
    /* 0x0000 */ UINT dword;
};

struct GPU_TESSELLATORPACKET { /* Size=0x54 */
    /* 0x0000 */ GPU_POINTSIZE PointSize;
    /* 0x0004 */ GPU_POINTMINMAX PointMinMax;
    /* 0x0008 */ GPU_LINECONTROL LineControl;
    /* 0x000c */ UINT Unused1;
    /* 0x0010 */ GPU_OUTPUTPATHCONTROL OutputPathControl;
    /* 0x0014 */ GPU_HOSCONTROL HosControl;
    /* 0x0018 */ float HosMaxTessLevel;
    /* 0x001c */ float HosMinTessLevel;
    /* 0x0020 */ UINT HosReuseDepth;
    /* 0x0024 */ GPU_GROUPPRIMTYPE GroupPrimType;
    /* 0x0028 */ UINT GroupFirstDecr;
    /* 0x002c */ UINT GroupDecr;
    /* 0x0030 */ GPU_GROUPVECTCONTROL GroupVect0Control;
    /* 0x0034 */ GPU_GROUPVECTCONTROL GroupVect1Control;
    /* 0x0038 */ GPU_GROUPVECTFMTCONTROL GroupVect0FmtControl;
    /* 0x003c */ GPU_GROUPVECTFMTCONTROL GroupVect1FmtControl;
    /* 0x0040 */ UINT Unused2[2];
    /* 0x0048 */ GPU_MPASSPSCONTROL MPassPsControl;
    /* 0x004c */ GPU_VIZQUERY VizQuery;
    /* 0x0050 */ GPU_ENHANCE Enhance;
};

union GPU_DEBUGMISC0 { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT DbProgOn : 1; /* BitPos=0 */
        /* 0x0000 */ UINT : 3; /* BitPos=1 */
        /* 0x0000 */ UINT DbProbBreak : 1; /* BitPos=4 */
        /* 0x0000 */ UINT : 3; /* BitPos=5 */
        /* 0x0000 */ UINT DbProbAddr : 11; /* BitPos=8 */
        /* 0x0000 */ UINT : 5; /* BitPos=19 */
        /* 0x0000 */ UINT DbProbCount : 8; /* BitPos=24 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_COPYFUNC { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT CopyFuncRed : 3; /* BitPos=0 */
        /* 0x0000 */ UINT : 1; /* BitPos=3 */
        /* 0x0000 */ UINT CopyFuncGreen : 3; /* BitPos=4 */
        /* 0x0000 */ UINT : 1; /* BitPos=7 */
        /* 0x0000 */ UINT CopyFuncBlue : 3; /* BitPos=8 */
        /* 0x0000 */ UINT : 1; /* BitPos=11 */
        /* 0x0000 */ UINT CopyFuncAlpha : 3; /* BitPos=12 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_COPYMASK { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT CopyMaskRed : 8; /* BitPos=0 */
        /* 0x0000 */ UINT CopyMaskGreen : 8; /* BitPos=8 */
        /* 0x0000 */ UINT CopyMaskBlue : 8; /* BitPos=16 */
        /* 0x0000 */ UINT CopyMaskAlpha : 8; /* BitPos=24 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_SCLINECONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT BresControl : 8; /* BitPos=0 */
        /* 0x0000 */ UINT UseBresControl : 1; /* BitPos=8 */
        /* 0x0000 */ UINT ExpandLineWidth : 1; /* BitPos=9 */
        /* 0x0000 */ UINT LastPixel : 1; /* BitPos=10 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_VTXCONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT PixCenter : 1; /* BitPos=0 */
        /* 0x0000 */ UINT RoundMode : 2; /* BitPos=1 */
        /* 0x0000 */ UINT QuantMode : 3; /* BitPos=3 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_AACONFIG { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT MsaaNumSamples : 3; /* BitPos=0 */
        /* 0x0000 */ UINT : 10; /* BitPos=3 */
        /* 0x0000 */ UINT MaxSampleDist : 4; /* BitPos=13 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_SAMPLECOUNTCONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT ResetSampleCount : 1; /* BitPos=0 */
        /* 0x0000 */ UINT CopySampleCount : 1; /* BitPos=1 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_COPYDESTINFO { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT CopyDestEndian : 3; /* BitPos=0 */
        /* 0x0000 */ UINT CopyDestArray : 1; /* BitPos=3 */
        /* 0x0000 */ UINT CopyDestSlice : 3; /* BitPos=4 */
        /* 0x0000 */ UINT CopyDestFormat : 6; /* BitPos=7 */
        /* 0x0000 */ UINT CopyDestNumber : 3; /* BitPos=13 */
        /* 0x0000 */ UINT CopyDestExpBias : 6; /* BitPos=16 */
        /* 0x0000 */ UINT : 2; /* BitPos=22 */
        /* 0x0000 */ UINT CopyDestSwap : 1; /* BitPos=24 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_COPYREF { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT CopyRefRed : 8; /* BitPos=0 */
        /* 0x0000 */ UINT CopyRefGreen : 8; /* BitPos=8 */
        /* 0x0000 */ UINT CopyRefBlue : 8; /* BitPos=16 */
        /* 0x0000 */ UINT CopyRefAlpha : 8; /* BitPos=24 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_COPYCONTROL { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT CopySrcSelect : 3; /* BitPos=0 */
        /* 0x0000 */ UINT : 1; /* BitPos=3 */
        /* 0x0000 */ UINT CopySampleSelect : 3; /* BitPos=4 */
        /* 0x0000 */ UINT : 1; /* BitPos=7 */
        /* 0x0000 */ UINT ColorClearEnable : 1; /* BitPos=8 */
        /* 0x0000 */ UINT DepthClearEnable : 1; /* BitPos=9 */
        /* 0x0000 */ UINT : 10; /* BitPos=10 */
        /* 0x0000 */ UINT CopyCommand : 2; /* BitPos=20 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_COPYDESTPITCH { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT CopyDestPitch : 14; /* BitPos=0 */
        /* 0x0000 */ UINT : 2; /* BitPos=14 */
        /* 0x0000 */ UINT CopyDestHeight : 14; /* BitPos=16 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_OUTDEALLOCCONTROL { /* Size=0x4 */
    /* 0x0000 */ UINT DeallocDist : 7; /* BitPos=0 */
    /* 0x0000 */ UINT dword;
};

union GPU_CONST { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT Base : 9; /* BitPos=0 */
        /* 0x0000 */ UINT : 3; /* BitPos=9 */
        /* 0x0000 */ UINT Size : 9; /* BitPos=12 */
    };
    /* 0x0000 */ UINT dword;
};

union GPU_VERTEXREUSEBLOCKCONTROL { /* Size=0x4 */
    /* 0x0000 */ UINT VtxReuseDepth : 8; /* BitPos=0 */
    /* 0x0000 */ UINT dword;
};

union GPU_DEBUGMISC1 { /* Size=0x4 */
    struct {
        /* 0x0000 */ UINT DbOnPix : 1; /* BitPos=0 */
        /* 0x0000 */ UINT DbOnVtx : 1; /* BitPos=1 */
        /* 0x0000 */ UINT : 6; /* BitPos=2 */
        /* 0x0000 */ UINT DbInstCount : 8; /* BitPos=8 */
        /* 0x0000 */ UINT DbBreakAddr : 11; /* BitPos=16 */
    };
    /* 0x0000 */ UINT dword;
};

struct GPU_MISCPACKET { /* Size=0x98 */
    /* 0x0000 */ GPU_SCLINECONTROL ScLineControl;
    /* 0x0004 */ GPU_AACONFIG AaConfig;
    /* 0x0008 */ GPU_VTXCONTROL VtxControl;
    /* 0x000c */ float GbVertClipAdj;
    /* 0x0010 */ float GbVertDiscAdj;
    /* 0x0014 */ float GbHorzClipAdj;
    /* 0x0018 */ float GbHorzDiscAdj;
    /* 0x001c */ GPU_CONST VsConst;
    /* 0x0020 */ GPU_CONST PsConst;
    /* 0x0024 */ GPU_DEBUGMISC0 DebugMisc0;
    /* 0x0028 */ GPU_DEBUGMISC1 DebugMisc1;
    /* 0x002c */ UINT Unused1[5];
    /* 0x0040 */ UINT Unused2[2];
    /* 0x0048 */ UINT AaMask;
    /* 0x004c */ UINT Unused3[3];
    /* 0x0058 */ GPU_VERTEXREUSEBLOCKCONTROL VertexReuseBlockControl;
    /* 0x005c */ GPU_OUTDEALLOCCONTROL OutDeallocControl;
    /* 0x0060 */ GPU_COPYCONTROL CopyControl;
    /* 0x0064 */ UINT CopyDestBase;
    /* 0x0068 */ GPU_COPYDESTPITCH CopyDestPitch;
    /* 0x006c */ GPU_COPYDESTINFO CopyDestInfo;
    /* 0x0070 */ UINT HiClear;
    /* 0x0074 */ UINT DepthClear;
    /* 0x0078 */ UINT ColorClear;
    /* 0x007c */ UINT ColorClearLo;
    /* 0x0080 */ GPU_COPYFUNC CopyFunc;
    /* 0x0084 */ GPU_COPYREF CopyRef;
    /* 0x0088 */ GPU_COPYMASK CopyMask;
    /* 0x008c */ UINT CopySurfaceSlice;
    /* 0x0090 */ GPU_SAMPLECOUNTCONTROL SampleCountControl;
    /* 0x0094 */ UINT SampleCountAddress;
};

struct GPU_POINTPACKET { /* Size=0x20 */
    /* 0x0000 */ float PolyOffsetFrontScale;
    /* 0x0004 */ float PolyOffsetFrontOffset;
    /* 0x0008 */ float PolyOffsetBackScale;
    /* 0x000c */ float PolyOffsetBackOffset;
    /* 0x0010 */ float PointXRad;
    /* 0x0014 */ float PointYRad;
    /* 0x0018 */ float PointConstantSize;
    /* 0x001c */ float PointCullRad;
};
