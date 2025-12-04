#include "rnddx9/Rnd.h"
#include "obj/Object.h"
#include "xdk/D3D9.h"

BEGIN_HANDLERS(DxRnd)
    HANDLE_ACTION(suspend, Suspend())
    HANDLE_SUPERCLASS(Rnd)
END_HANDLERS

bool DxRnd::Offscreen() const {
    D3DSurface *back = BackBuffer();
    D3DSurface *target = D3DDevice_GetRenderTarget(mD3DDevice, 0);
    bool ret = back != target;
    if (target) {
        D3DResource_Release(target);
    }
    if (back) {
        D3DResource_Release(back);
    }
    return ret;
}

void DxRnd::PreDeviceReset() {
    if (mOcclusionQueryMgr) {
        mOcclusionQueryMgr->ReleaseQueries();
    }
    FOREACH (it, unk2b0) {
        (*it)->PreDeviceReset();
    }
    ReleaseAutoRelease();
}

void DxRnd::PostDeviceReset() {
    FOREACH (it, unk2b0) {
        (*it)->PostDeviceReset();
    }
    MakeDrawTarget();
    InitRenderState();
}
