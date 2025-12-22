#pragma once
#include "meta/FixedSizeSaveable.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "ui/UIListProvider.h"

class HamProfile;

class MetagameStats : public Hmx::Object,
                      public UIListProvider,
                      public FixedSizeSaveable {
public:
    struct FavoriteStat {
        std::map<int, int> mCounts;
    };
    enum CountStatID {
        kNumCountStats = 0x17
    };
    enum FavoriteStatID {
        kNumFavoriteStats = 7
    };
    MetagameStats();
    // Hmx::Object
    virtual DataNode Handle(DataArray *, bool);
    // UIListProvider
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual RndMat *Mat(int, int, UIListMesh *) const;
    virtual int NumData() const { return unk13c->Size() - 1; }

    void Clear();
    void IncrementCount(CountStatID, int);
    void TallyFavorite(FavoriteStatID, int, int);
    int GetCount(CountStatID) const;
    int GetFavorite(FavoriteStatID) const;
    int GetFavoriteCount(FavoriteStatID, int) const;
    void UpdatePartyStats(int);
    void PhotoTaken();
    void WriteTimePlayed(HamProfile *, int);

    static int SaveSize(int);

private:
    // FixedSizeSaveable
    virtual void SaveFixed(FixedSizeSaveableStream &) const;
    virtual void LoadFixed(FixedSizeSaveableStream &, int);

    Symbol SetTitleByThreshold(int, DataArray *) const;

protected:
    int unk38[kNumCountStats]; // 0x38
    FavoriteStat mFavoriteStats[kNumFavoriteStats]; // 0x94
    DataArray *unk13c; // 0x13c
    int unk140;
    bool unk144;
};
