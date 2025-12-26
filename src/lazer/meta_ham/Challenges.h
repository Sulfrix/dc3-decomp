#pragma once
#include "hamobj/HamPlayerData.h"
#include "meta_ham/HamProfile.h"
#include "meta_ham/SongStatusMgr.h"
#include "net_ham/RCJobDingo.h"
#include "net_ham/ChallengeSystemJobs.h"
#include "obj/Data.h"
#include "obj/Object.h"

class Challenges : public Hmx::Object {
public:
    Challenges();
    virtual ~Challenges();
    virtual DataNode Handle(DataArray *, bool);

    static void Init();

    void DownloadPlayerChallenges();
    void UploadFlauntForOne();
    void UploadFlauntForAll(bool);
    int GetTotalXpEarned(int);
    void DownloadOfficialChallenges();
    void DownloadAllChallenges() {
        DownloadOfficialChallenges();
        DownloadPlayerChallenges();
    }
    bool CanDownloadPlayerChallenges() const;
    bool IsExportedSongDC1(int);
    bool IsExportedSongDC2(int);
    bool HasNewChallenges();
    int GetGlobalChallengeSongID();
    int GetDlcChallengeSongID();
    String GetGlobalChallengeSongName();
    String GetDlcChallengeSongName();
    int CalculateChallengeXp(int, int);
    int GetMedalCount(int);
    bool GetBeatenChallengeXPs(const HamPlayerData *, int, std::vector<int> &);
    void GetPlayerChallenges(std::vector<ChallengeRow> &);
    void GetOfficialChallenges(std::vector<ChallengeRow> &);
    void UploadFlaunt(HamProfile *, bool);

protected:
    void AddPendingProfile(HamProfile *);

    DataNode OnMsg(const RCJobCompleteMsg &);

private:
    bool HasFlaunted(HamProfile *);
    void UpdateChallengeTimeStamp();
    void SetupInGameData();
    String GetMissionInfoGamertag();
    int GetMissionInfoScore();
    void UpdateInGameEvent();
    void ResetInGameEvent();
    void PollInGameStatus();
    bool NeedToReSyncChallenges();
    void DownloadBadgeInfo();
    void UploadNextFlaunt();
    void ReadPlayerChallengesComplete(bool);
    void ReadOfficialChallengesComplete(bool);
    void StartUploadingNextProfile();
    void ReadBadgeInfo(bool);

    bool unk2c;
    GetPlayerChallengesJob *unk30; // 0x30
    GetOfficialChallengesJob *unk34; // 0x34
    // key = profile name, value = that player's challenges
    std::map<String, std::vector<ChallengeRow> > unk38;
    // official challenges? like, hmx's gold/silver/bronze challenge sets?
    std::vector<ChallengeRow> unk50; // 0x50
    Timer unk60;
    Timer unk90;
    int mScoreFactorDenom; // 0xc0
    std::vector<int> mSongTierFactor; // 0xc4
    int mConsolationXP; // 0xd0
    int unkd4;
    double unkd8;
    bool unke0;
    bool unke1;
    HamProfile *unke4; // 0xe4 - flaunting profile?
    std::list<FlauntStatusData> mFlauntList; // 0xe8
    std::list<HamProfile *> unkf0;
    FlauntScoreData mFlauntScoreData; // 0xf8
    std::vector<String> unk104;
    bool unk110;
    // challenge rows, 1 per player
    /** The series of live challenges each player has to beat. */
    std::vector<ChallengeRow> mPlayerChallenges[2]; // 0x114
    GetChallengeBadgeCountsJob *unk12c;
    std::map<String, ChallengeBadgeInfo> unk130;
    std::vector<int> mExportedDC1SongIDs; // 0x148
    std::vector<int> mExportedDC2SongIDs; // 0x154
};

extern Challenges *TheChallenges;
