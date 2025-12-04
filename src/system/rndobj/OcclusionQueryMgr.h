#pragma once

#include "os/Debug.h"
class RndOcclusionQueryMgr {
public:
    enum QueryState {
        kMaxQueries = 256
    };

    RndOcclusionQueryMgr() {
        for (unsigned int i = 0; i < kMaxQueries; i++) {
            for (int j = 0; j < 2; j++) {
                unk1004[i][j] = 0;
                unk804[i][j] = 0;
                mQueryStates[i][j] = (QueryState)0;
            }
        }
        unk1804 = 0;
        unk1808 = 0;
        unk180c = 0;
    }

    virtual ~RndOcclusionQueryMgr() {}
    virtual void OnCreateQuery(unsigned int) = 0;
    virtual void OnBeginQuery(unsigned int) = 0;
    virtual void OnEndQuery(unsigned int) = 0;
    virtual bool OnGetQueryResult(unsigned int, unsigned int &) = 0;
    virtual bool OnIsValidQuery(unsigned int) const = 0;
    virtual void OnReleaseQuery(unsigned int, unsigned int &) = 0;
    virtual void OnBeginFrame() = 0;
    virtual void OnEndFrame() = 0;

    void ReleaseQuery(unsigned int idx) {
        if (idx < kMaxQueries) {
            for (unsigned int i = 0; i < 2; i++) {
                OnReleaseQuery(idx, i);
                unk1004[idx][i] = 0;
                mQueryStates[idx][i] = (QueryState)0;
                unk804[idx][i] = 0;
            }
        }
    }
    void ReleaseQueries() {
        for (unsigned int i = 0; i < kMaxQueries; i++) {
            ReleaseQuery(i);
        }
    }

protected:
    QueryState GetQueryState(unsigned int queryIndex) const {
        MILO_ASSERT(queryIndex < kMaxQueries, 0xDD);
        return mQueryStates[queryIndex][unk1804];
    }

    QueryState mQueryStates[256][2]; // 0x4
    int unk804[256][2]; // 0x804
    int unk1004[256][2]; // 0x1004
    int unk1804; // 0x1804
    int unk1808; // 0x1808
    int unk180c; // 0x180c
};
