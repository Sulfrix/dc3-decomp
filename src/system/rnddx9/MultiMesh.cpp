#include "rnddx9/MultiMesh.h"
#include "obj/Object.h"
#include "rnddx9/Rnd.h"
#include "xdk/D3D9.h"
#include "xdk/d3d9i/d3d9.h"
#include "xdk/d3d9i/d3d9types.h"

DxMultiMesh::DxMultiMesh() : unk5c(0), unk60(0) {
    for (int i = 0; i < 3; i++) {
        unk64[i] = unk70[i] = nullptr;
    }
}

DxMultiMesh::~DxMultiMesh() {
    for (int i = 0; i < 3; i++) {
        DX_RELEASE(unk70[i]);
        DX_RELEASE(unk64[i]);
    }
}

void DxMultiMesh::Init() {
    REGISTER_OBJ_FACTORY(DxMultiMesh);
    static D3DVERTEXELEMENT9 sVertexElement[] = {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        { 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
        { 0, 16, D3DDECLTYPE_FLOAT16_2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
        { 0, 20, D3DDECLTYPE_DEC4N, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
        { 0, 24, D3DDECLTYPE_DEC4N, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
        { 0, 28, D3DDECLTYPE_UDEC4N, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
        { 0, 32, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
        { 1, 0, D3DDECLTYPE_UINT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 1 },
        D3DDECL_END()
    };
    sVertexDecl = D3DDevice_CreateVertexDeclaration(sVertexElement);
    {
        HRESULT hr = sVertexDecl != nullptr ? 0 : 0x8007000E;
        if (hr) {
            MILO_FAIL("File: %s Line: %d Error: %s\n", __FILE__, 0x97, DxRnd::Error(hr));
        }
    }
    static D3DVERTEXELEMENT9 sMutableVertexElement[] = {
        { 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        { 0, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
        { 0, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
        { 0, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
        { 0, 64, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
        { 0, 72, D3DDECLTYPE_SHORT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
        { 0, 80, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
        { 1, 0, D3DDECLTYPE_UINT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 1 },
        D3DDECL_END()
    };
    sMutableVertexDecl = D3DDevice_CreateVertexDeclaration(sMutableVertexElement);
    {
        HRESULT hr = sMutableVertexDecl != nullptr ? 0 : 0x8007000E;
        if (hr) {
            MILO_FAIL("File: %s Line: %d Error: %s\n", __FILE__, 0x9A, DxRnd::Error(hr));
        }
    }
}

void DxMultiMesh::Shutdown() {
    if (sVertexDecl) {
        D3DResource_Release(sVertexDecl);
        sVertexDecl = nullptr;
    }
    if (sMutableVertexDecl) {
        D3DResource_Release(sMutableVertexDecl);
        sMutableVertexDecl = nullptr;
    }
}
