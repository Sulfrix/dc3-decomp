#include "net_ham/ChallengeSystemJobs.h"
#include "meta_ham/HamProfile.h"
#include "net/JsonUtils.h"
#include "obj/Object.h"
#include "utl/DataPointMgr.h"
#include "utl/MakeString.h"

FlauntScoreJob::FlauntScoreJob(Hmx::Object *callback, FlauntScoreData &data)
    : RCJob("leaderboards/flauntscore/", callback) {
    DataPoint pt;
    static Symbol song_id("song_id");
    static Symbol pid("pid");
    static Symbol score("score");
    static Symbol diff("diff");
    static Symbol xp("xp");
    pt.AddPair(song_id, data.mStatus->mSongID);
    pt.AddPair(pid, data.mProfile ? data.mProfile->GetOnlineID()->ToString() : "N/A");
    pt.AddPair(score, data.mStatus->mScore);
    pt.AddPair(diff, data.mStatus->mDifficulty);
    pt.AddPair(xp, data.mProfile->GetMetagameRank()->RankNumber());
    SetDataPoint(pt);
}

GetPlayerChallengesJob::GetPlayerChallengesJob(
    Hmx::Object *callback, std::vector<HamProfile *> &profiles
)
    : RCJob("leaderboards/getplayerchallenges/", callback) {
    DataPoint pt;
    static Symbol pid000("pid000");
    static Symbol pid001("pid001");
    if (profiles.size() > 1) {
        pt.AddPair(pid001, profiles[1]->GetOnlineID()->ToString());
    }
    pt.AddPair(pid000, profiles[0]->GetOnlineID()->ToString());
    SetDataPoint(pt);
}

GetOfficialChallengesJob::GetOfficialChallengesJob(Hmx::Object *callback)
    : RCJob("leaderboards/getchallenges/", callback) {
    DataPoint pt;
    SetDataPoint(pt);
}

GetChallengeBadgeCountsJob::GetChallengeBadgeCountsJob(
    Hmx::Object *callback, std::vector<HamProfile *> &profiles
)
    : RCJob("leaderboards/getchallengebadgecounts/", callback) {
    MILO_LOG("***********************************\n");
    MILO_LOG("GetChallengeBadgeCountsJob::GetChallengeBadgeCountsJob()\n");
    MILO_LOG(MakeString("   profiles.size()   = %d\n", (int)profiles.size()));
    for (int i = 0; i < profiles.size(); i++) {
        MILO_LOG(MakeString(
            "   profiles[%d]       = '%s'\n", i, profiles[i]->GetOnlineID()->ToString()
        ));
    }
    MILO_LOG("***********************************\n");
    DataPoint pt;
    static Symbol pid000("pid000");
    static Symbol pid001("pid001");
    if (profiles.size() > 1) {
        pt.AddPair(pid001, profiles[1]->GetOnlineID()->ToString());
    }
    pt.AddPair(pid000, profiles[0]->GetOnlineID()->ToString());
    SetDataPoint(pt);
}

void GetBadgeInfo(
    JsonConverter &c,
    const JsonObject *o,
    std::map<String, ChallengeBadgeInfo> &badgeInfos
) {
    JsonArray *a = const_cast<JsonArray *>(static_cast<const JsonArray *>(o));
    unsigned int aSize = a->GetSize();
    for (int i = 0; i < aSize; i++) {
        JsonArray *cur = static_cast<JsonArray *>(c.GetValue(a, i));
        String gamerTag = c.GetValue(cur, 0)->Str();
        int hmxGold = c.GetValue(cur, 3)->Int();
        int hmxSilver = c.GetValue(cur, 2)->Int();
        int hmxBronze = c.GetValue(cur, 1)->Int();
        int dlcGold = c.GetValue(cur, 6)->Int();
        int dlcSilver = c.GetValue(cur, 5)->Int();
        int dlcBronze = c.GetValue(cur, 4)->Int();
        MILO_LOG("***********************************\n");
        MILO_LOG(MakeString(">>>>>>>>>> gamertag = %s\n", gamerTag.c_str()));
        MILO_LOG(MakeString(">>>>>>>>>> hmxGold = %i\n", hmxGold));
        MILO_LOG(MakeString(">>>>>>>>>> hmxSilver = %i\n", hmxSilver));
        MILO_LOG(MakeString(">>>>>>>>>> hmxBronze = %i\n", hmxBronze));
        MILO_LOG(MakeString(">>>>>>>>>> dlcGold = %i\n", dlcGold));
        MILO_LOG(MakeString(">>>>>>>>>> dlcSilver = %i\n", dlcSilver));
        MILO_LOG(MakeString(">>>>>>>>>> dlcBronze = %i\n", dlcBronze));
        MILO_LOG("***********************************\n");
        auto it = badgeInfos.find(gamerTag);
        if (it != badgeInfos.end()) {
            it->second.mGold = dlcGold + hmxGold;
            it->second.mSilver = dlcSilver + hmxSilver;
            it->second.mBronze = dlcBronze + hmxBronze;
        } else {
            ChallengeBadgeInfo value;
            value.mGold = dlcGold + hmxGold;
            value.mSilver = dlcSilver + hmxSilver;
            value.mBronze = dlcBronze + hmxBronze;
            badgeInfos[gamerTag] = value;
        }
    }
}

void GetChallengeBadgeCountsJob::GetBadgeInfo(
    std::map<String, ChallengeBadgeInfo> &badgeInfos
) {
    if (mResult == 1 && mJsonResponse) {
        ::GetBadgeInfo(mJsonReader, mJsonResponse, badgeInfos);
    }
}

void GetRows(
    JsonConverter &c,
    const JsonObject *o,
    std::map<String, std::vector<ChallengeRow> > &,
    bool &
);

void GetPlayerChallengesJob::GetRows(
    std::map<String, std::vector<ChallengeRow> > &challengeRows, bool &bref
) {
    if (mResult == 1 && mJsonResponse) {
        ::GetRows(mJsonReader, mJsonResponse, challengeRows, bref);
    }
}
