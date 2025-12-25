#pragma once
#include "meta_ham/HamProfile.h"
#include "meta_ham/SongStatusMgr.h"
#include "net_ham/RCJobDingo.h"
#include "obj/Object.h"

// size 0x3c
class ChallengeRow {
public:
    int unk0;
    String unk4;
    int unkc;
    String unk10;
    String unk18;
    int unk20;
    int unk24;
    int unk28;
    String unk2c;
    int unk34;
    int unk38;
};

class ChallengeBadgeInfo {
public:
    int mGold; // 0x0
    int mSilver; // 0x4
    int mBronze; // 0x8
};

class FlauntScoreData {
public:
    FlauntScoreData() : mProfile(0), mStatus(0) {}
    virtual ~FlauntScoreData() {}

    HamProfile *mProfile; // 0x4
    FlauntStatusData *mStatus; // 0x8
};

class FlauntScoreJob : public RCJob {
public:
    FlauntScoreJob(Hmx::Object *callback, FlauntScoreData &data);
};

class GetPlayerChallengesJob : public RCJob {
public:
    GetPlayerChallengesJob(Hmx::Object *callback, std::vector<HamProfile *> &profiles);
    void GetRows(std::map<String, std::vector<ChallengeRow> > &, bool &);
};

class GetOfficialChallengesJob : public RCJob {
public:
    GetOfficialChallengesJob(Hmx::Object *callback);
};

class GetChallengeBadgeCountsJob : public RCJob {
public:
    GetChallengeBadgeCountsJob(Hmx::Object *callback, std::vector<HamProfile *> &profiles);
    void GetBadgeInfo(std::map<String, ChallengeBadgeInfo> &);
};
