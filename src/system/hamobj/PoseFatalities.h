#pragma once
#include "FreestyleMoveRecorder.h"
#include "char/CharClip.h"
#include "gesture/BaseSkeleton.h"
#include "gesture/Skeleton.h"
#include "hamobj/HamLabel.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "rndobj/Anim.h"
#include "utl/MemMgr.h"

#define MAX_NUM_PLAYERS 2
#define NUM_FATALITIES 8

class PoseFatalities : public Hmx::Object {
public:
    // Hmx::Object
    PoseFatalities();
    virtual ~PoseFatalities() {}
    OBJ_CLASSNAME(PoseFatalities);
    OBJ_SET_TYPE(PoseFatalities);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);

    NEW_OBJ(PoseFatalities)

    void DrawDebug();
    void Enter();
    bool InFatality(int) const;
    void ActivateFatal(int);
    bool FatalActive() const;
    void SetJump(int, int);
    bool GotFullCombo(int) const;

private:
    Symbol GetFatalityFace();
    bool InStrikeAPose();
    void SetCombo(int, int);
    void SetFatalitiesStart(int);
    void Reset();
    void PlayVO(Symbol);
    String GetCelebrationClip(int);
    void EndFatal(int);
    float BeatsLeftToMatch(int);
    void BeginFatal(int);
    void AddFatal(int);
    bool CheckMatchingPose(int);
    void LoadFatalityClips();
    void PollVO();

    bool mInFatality[2]; // 0x2c
    int unk30[2]; // 0x30
    int unk38;
    int unk3c[2];
    int unk44[2];
    Skeleton unk4c[2]; // 0x4c
    float unk15f4[2];
    float unk15fc;
    FreestyleMoveRecorder unk1600; // 0x1600
    float unk1710[2];
    int unk1718;
    int unk171c;
    bool unk1720[2];
    std::list<CharClip *> mAllFatalityClips; // 0x1724
    int unk172c;
    HamLabel *mPoseComboLabels[kNumSkeletonSides]; // 0x1730
    int unk1738[2]; // 0x1738
    bool mGotFullCombo[2]; // 0x1740
    ObjectDir *mHudPanel; // 0x1744
    bool unk1748;
    int unk174c;
    int unk1750;
    int unk1754;
    RndAnimatable *mPoseBeatAnims[kNumSkeletonSides]; // 0x1758
    float unk1760;
    float unk1764;
    int unk1768;
    float unk176c;
};
