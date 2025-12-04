#pragma once
#include "rndobj/OcclusionQueryMgr.h"

// size 0x2010
class DxRndOcclusionQueryMgr : public RndOcclusionQueryMgr {
public:
    DxRndOcclusionQueryMgr() {
        for (unsigned int i = 0; i < 256; i++) {
            for (int j = 0; j < 2; j++) {
                unk1810[i][j] = 0;
            }
        }
    }
    virtual ~DxRndOcclusionQueryMgr() { ReleaseQueries(); }
    virtual void OnCreateQuery(unsigned int);
    virtual void OnBeginQuery(unsigned int);
    virtual void OnEndQuery(unsigned int);
    virtual bool OnGetQueryResult(unsigned int, unsigned int &);
    virtual bool OnIsValidQuery(unsigned int) const;
    virtual void OnReleaseQuery(unsigned int, unsigned int &);
    virtual void OnBeginFrame() {}
    virtual void OnEndFrame() {}

private:
    int unk1810[256][2]; // 0x1810
};
