#pragma once
#include "obj/Object.h"
#include "rndobj/MultiMesh.h"
#include "xdk/D3D9.h"

class DxMultiMesh : public RndMultiMesh {
public:
    DxMultiMesh();
    virtual ~DxMultiMesh();
    OBJ_CLASSNAME(MultiMesh);
    OBJ_SET_TYPE(MultiMesh);
    virtual void DrawShowing();

    static void Init();
    static void Shutdown();
    NEW_OBJ(DxMultiMesh)

private:
    void UpdateGeometryBuffers();
    void DrawBatchedNewGfx();

    static D3DVertexDeclaration *sVertexDecl;
    static D3DVertexDeclaration *sMutableVertexDecl;

    int unk5c;
    int unk60;
    D3DVertexBuffer *unk64[3];
    D3DVertexBuffer *unk70[3];
};
