#pragma once
#include "game/HamUser.h"
#include "hamobj/Difficulty.h"
#include "meta/Profile.h"
#include "meta_ham/AccomplishmentProgress.h"
#include "meta_ham/CampaignProgress.h"
#include "meta_ham/MetagameRank.h"
#include "meta_ham/MetagameStats.h"
#include "meta_ham/MoveRatingHistory.h"
#include "meta_ham/Playlist.h"
#include "meta_ham/SongStatusMgr.h"
#include "os/OnlineID.h"

struct CharacterPref {
    int unk0;
    int unk4;
    int unk8;
};

class HamProfile : public Profile {
public:
    HamProfile(int);
    virtual ~HamProfile();
    // Hmx::Object
    virtual DataNode Handle(DataArray *, bool);
    // FixedSizeSaveable
    virtual void SaveFixed(FixedSizeSaveableStream &) const;
    virtual void LoadFixed(FixedSizeSaveableStream &, int);
    virtual bool HasCheated() const;
    virtual bool IsUnsaved() const;
    virtual void SaveLoadComplete(ProfileSaveState);
    virtual bool HasSomethingToUpload();
    virtual void DeleteAll();

    static int SaveSize(int);

    void CheckForIconManUnlock();
    void CheckForNinjaUnlock();
    void SetFitnessMode(bool);
    HamUser *GetHamUser() const;
    SongStatusMgr *GetSongStatusMgr() const;
    CampaignProgress &GetCampaignProgress(Difficulty) const;
    const AccomplishmentProgress &GetAccomplishmentProgress() const;
    AccomplishmentProgress &AccessAccomplishmentProgress();
    void EarnAccomplishment(Symbol);
    void GetFitnessStats(float &, float &, float &);
    void UnlockContent(Symbol);

private:
    void ResetOutfitPrefs();

    SongStatusMgr *unk18; // 0x18
    std::vector<Symbol> unk1c;
    std::vector<Symbol> unk28;
    AccomplishmentProgress unk34;
    CampaignProgress unk158[4];
    MetagameStats *unk208;
    MetagameRank *unk20c;
    MoveRatingHistory *unk210;
    std::vector<CharacterPref> unk214;
    CustomPlaylist unk220[5];
    bool unk2fc;
    bool unk2fd;
    float unk300;
    bool unk304;
    float unk308;
    float unk30c;
    float unk310;
    int unk314;
    OnlineID *unk318;
    bool unk31c;
    int unk320;
    int unk324;
    int unk328;
    int unk32c;
    int unk330;
    bool unk334;
    Symbol unk338;
    bool unk33c;
    int unk340;
    int unk344;
    int unk348;
    int unk34c;
    int unk350;
    int unk354;
    int unk358;
    int unk35c;
    bool unk360;
    int unk364;
    int unk368;
    bool unk36c;
    int unk370;
    int unk374;
};
