#include "hamobj/PoseFatalities.h"
#include "PoseFatalities.h"
#include "char/CharClip.h"
#include "flow/PropertyEventProvider.h"
#include "gesture/BaseSkeleton.h"
#include "hamobj/Difficulty.h"
#include "hamobj/HamDirector.h"
#include "hamobj/HamGameData.h"
#include "hamobj/HamLabel.h"
#include "hamobj/HamMaster.h"
#include "math/Rand.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rndobj/Anim.h"
#include "rndobj/PropKeys.h"
#include "synth/FxSendDelay.h"
#include "synth/Synth.h"
#include "utl/BeatMap.h"
#include "utl/Symbol.h"

PoseFatalities::PoseFatalities()
    : unk15fc(0.5f), mHudPanel(0), unk174c(0), unk1750(0), unk1754(0), unk1764(0),
      unk1768(0), unk176c(0) {
    for (int i = 0; i < 2; i++) {
        mInFatality[i] = 0;
        unk1710[i] = 0;
        unk1720[i] = 0;
        mGotFullCombo[i] = 0;
        unk3c[i] = 0;
    }
    static DataNode &n = DataVariable("pose_fatalities");
    n = this;
}

BEGIN_HANDLERS(PoseFatalities)
    HANDLE_EXPR(get_fatality_beat_lead_in, unk172c)
    HANDLE_EXPR(fatal_active, FatalActive())
    HANDLE_ACTION(activate_fatalities, ActivateFatal(-1))
    HANDLE_ACTION(set_jump, SetJump(_msg->Int(2), _msg->Int(3)))
    HANDLE_EXPR(fatal_end_beat, unk38)
    HANDLE_SUPERCLASS(Hmx::Object)
END_HANDLERS

BEGIN_PROPSYNCS(PoseFatalities)
    SYNC_SUPERCLASS(Hmx::Object)
END_PROPSYNCS

bool PoseFatalities::FatalActive() const {
    for (int i = 0; i < 2; i++) {
        if (mInFatality[i]) {
            return true;
        }
    }
    return false;
}

void PoseFatalities::SetJump(int x, int y) {
    unk1750 = y;
    unk174c = x;
}

bool PoseFatalities::GotFullCombo(int player) const {
    MILO_ASSERT_RANGE(player, 0, 2, 0x3A5);
    return mGotFullCombo[player];
}

Symbol PoseFatalities::GetFatalityFace() {
    Symbol smiles[3] = { "Smile", "Open_Smile_02", "Grin" };
    Symbol ret = smiles[RandomInt(0, 3)];
    if (RandomInt(0, 100) == 0) {
        ret = "O_Face";
    }
    if (RandomInt(0, 100) == 0) {
        ret = "Sexy";
    }
    return ret;
}

bool PoseFatalities::InFatality(int player) const {
    int max = unk1754;
    if (player == -1) {
        bool b1 = false;
        for (int i = 0; i < 2; i++) {
            if (max >= unk30[i]) {
                b1 = true;
            }
        }
        if (b1) {
            return FatalActive();
        }
    } else {
        MILO_ASSERT_RANGE(player, 0, 2, 0x391);
        if (max >= unk30[player]) {
            return mInFatality[player];
        }
    }
    return false;
}

bool PoseFatalities::InStrikeAPose() {
    static Symbol gameplay_mode("gameplay_mode");
    static Symbol strike_a_pose("strike_a_pose");
    return TheHamProvider->Property(gameplay_mode, true)->Sym() == strike_a_pose;
}

void PoseFatalities::SetCombo(int player, int y) {
    unk1738[player] = y;
    if (y != 0) {
        mPoseComboLabels[TheGameData->Player(player)->Side()]->SetInt(y, false);
    }
}

void PoseFatalities::SetFatalitiesStart(int player) {
    mInFatality[player] = true;
    if (InStrikeAPose()) {
        unk30[player] = unk1754 + 3;
        for (int i = 0; i < 4; i++) {
            if (TheBeatMap->IsDownbeat(unk30[player])) {
                return;
            }
            unk30[player]++;
        }
    } else {
        unk30[player] = unk1754 + 7;
    }
}

void PoseFatalities::Reset() {
    for (int i = 0; i < 2; i++) {
        unk30[i] = -1;
        mInFatality[i] = false;
        unk15f4[i] = 0;
    }
    TheHamProvider->SetProperty("in_fatalities", 0);
    RndAnimatable *anim = TheSynth->Find<RndAnimatable>("beat_repeat.anim", true);
    if (anim) {
        anim->SetFrame(4, 1);
    }
}

void PoseFatalities::PlayVO(Symbol s) {
    static Message stopVOMsg("stop_narrator");
    mHudPanel->Handle(stopVOMsg, true);
    static Message playVOMsg("play", 0);
    playVOMsg[0] = s;
    mHudPanel->Handle(playVOMsg, true);
    unk1764 = 5;
}

String PoseFatalities::GetCelebrationClip(int player) {
    Symbol outfit =
        GetOutfitCharacter(TheHamDirector->GetCharacter(player)->Outfit(), true);
    static Symbol strikeapose_celebrations("strikeapose_celebrations");
    DataArray *cfg = SystemConfig(strikeapose_celebrations);
    DataArray *a = cfg->FindArray(outfit, true);
    return a->Node(RandomInt(1, a->Size())).Str();
}

void PoseFatalities::EndFatal(int player) {
    bool b10 = true;
    mInFatality[player] = false;
    unk1720[player] = true;
    static Message endFatalityMsg("fatality_end", 0);
    endFatalityMsg[0] = player;
    TheHamProvider->Handle(endFatalityMsg, false);
    if (!InStrikeAPose()) {
        ObjectDir *poseDisplay = TheHamDirector->GetVenueWorld()->Find<ObjectDir>(
            MakeString("final_pose_display%d", player), true
        );
        HamLabel *label = poseDisplay->Find<HamLabel>("pose_combo.lbl", true);
        int num;
        if (mGotFullCombo[player]) {
            num = 8;
        } else {
            num = unk1738[player] - 1;
        }
        if (unk1738[player] > 1) {
            label->SetTokenFmt("pose_fatality_3d_combo", num);
        } else {
            label->SetTextToken(gNullStr);
        }
        poseDisplay->Find<RndAnimatable>("pose_combo.anim", true)
            ->Animate(0, false, 0, nullptr, kEaseLinear, 0, false);
    }
    unk1738[player] = 0;
    if (!DataVariable("restart_fatals").Int() && !InStrikeAPose()) {
        for (int i = 0; i < 2; i++) {
            b10 &= mInFatality[i] != 0;
        }
        if (b10) {
            unk1760 = 4;
        }
        TheHamDirector->GetCharacter(player)->BlendOutFaceOverrides(100);
    } else {
        unk30[player] = -1;
        ActivateFatal(player);
    }
}

void PoseFatalities::ActivateFatal(int player) {
    if (!DataVariable("disable_fatalities").Int() || InStrikeAPose()) {
        if (!InStrikeAPose()) {
            static Symbol peak_behavior("peak_behavior");
            static Symbol strike_a_pose("strike_a_pose");
            static Symbol game_stage("game_stage");
            static Symbol none("none");
            TheHamProvider->SetProperty(peak_behavior, strike_a_pose);
            TheHamProvider->SetProperty(game_stage, none);
        }
        if (!InStrikeAPose()) {
            TheHamDirector->ForceShot("area1_far01.shot");
        }
        unk1748 = true;
        if (!FatalActive()) {
            static Message fatalityActivateMsg("fatality_active");
            TheHamProvider->Handle(fatalityActivateMsg, false);
        }
        if (player >= 0) {
            MILO_ASSERT(player < MAX_NUM_PLAYERS, 0x29E);
            SetFatalitiesStart(player);
        } else {
            for (int i = 0; i < 2; i++) {
                SetFatalitiesStart(i);
            }
        }
        if (!InStrikeAPose()) {
            MILO_ASSERT(player >= 0, 0x2A9);
            unk38 = unk30[player] + 32;
        }
        TheHamProvider->SetProperty("in_fatalities", true);
        static Message resetDBOvertakeMsg("db_overtake", -1);
        TheHamProvider->Handle(resetDBOvertakeMsg, false);
    }
}

float PoseFatalities::BeatsLeftToMatch(int player) {
    float beat = TheTaskMgr.Beat();
    if (fabsf(beat - unk1754) > 2.0f) {
        beat = (unk1750 - unk174c) + beat;
    }
    int num = 4;
    if (unk44[player] == 1 && !InStrikeAPose()) {
        num = 8;
    }
    return (unk3c[player] + num) - beat;
}

void PoseFatalities::BeginFatal(int player) {
    if (mInFatality[player]) {
        unk1720[player] = false;
        if (!InStrikeAPose()) {
            unk44[player] = 0;
        }
        unk1738[player] = 0;
        mGotFullCombo[player] = false;
        AddFatal(player);
        static Message beginFatalityMsg("fatality_begin", 0);
        beginFatalityMsg[0] = player;
        TheHamProvider->Handle(beginFatalityMsg, false);
        TheHamDirector->GetCharacter(player)->BlendInFaceOverrides(100);
    }
}

bool PoseFatalities::CheckMatchingPose(int player) {
    return InFatality(player) && unk15f4[player] >= unk15fc;
}

void PoseFatalities::LoadFatalityClips() {
    if (InStrikeAPose()) {
        mAllFatalityClips.clear();
        for (ObjDirItr<CharClip> it(mHudPanel, true); it != nullptr; ++it) {
            if (strstr(it->Name(), "pose_fatalities_")) {
                mAllFatalityClips.push_back(it);
            }
        }
        MILO_ASSERT(mAllFatalityClips.size() > 0, 0x2D1);
    }
}

void PoseFatalities::Enter() {
    mHudPanel = DataVariable("hud_panel").Obj<ObjectDir>();
    Reset();
    LoadFatalityClips();
    PropKeys *propKeys = TheHamDirector->GetPropKeys(kDifficultyEasy, "move");
    if (propKeys) {
        Keys<Symbol, Symbol> *symKeys = propKeys->AsSymbolKeys();
        static Symbol Rest("Rest.move");
        static Symbol rest("rest.move");
        int idx = 0;
        for (; idx < symKeys->size(); idx++) {
            Key<Symbol> cur = (*symKeys)[idx];
            if (cur.value != Rest && cur.value != rest)
                break;
        }
        unk172c = Max(idx * 4 - 5, 0);
        for (idx = symKeys->size() - 1; idx >= 0; idx--) {
            Key<Symbol> cur = (*symKeys)[idx];
            if (cur.value != Rest && cur.value != rest)
                break;
        }
        if (InStrikeAPose()) {
            unk38 = idx * 4;
        }
        mPoseComboLabels[kSkeletonLeft] = mHudPanel->Find<ObjectDir>("hud_left", true)
                                              ->Find<HamLabel>("pose_combo.lbl", true);
        mPoseComboLabels[kSkeletonRight] = mHudPanel->Find<ObjectDir>("hud_right", true)
                                               ->Find<HamLabel>("pose_combo.lbl", true);
        mPoseBeatAnims[kSkeletonLeft] = mHudPanel->Find<ObjectDir>("hud_left", true)
                                            ->Find<RndAnimatable>("pose_beat.anim", true);
        mPoseBeatAnims[kSkeletonRight] =
            mHudPanel->Find<ObjectDir>("hud_right", true)
                ->Find<RndAnimatable>("pose_beat.anim", true);
        unk1748 = InStrikeAPose();
        FxSendDelay *delay = TheSynth->Find<FxSendDelay>("BeatRepeat.send", true);
        if (delay) {
            float bpm = TheMaster->SongData()->GetTempoMap()->GetTempoBPM(0);
            delay->SetProperty("tempo", bpm);
        }
        unk1754 = 0;
        unk1760 = -1;
    }
}

void PoseFatalities::PollVO() {
    if (InStrikeAPose()) {
        bool flag1 = unk1768 & 1;
        bool flag2 = (unk1768 >> 1) & 1;
        if (flag1) {
            if (flag2) {
                PlayVO("nar_sap_both_fc");
            } else {
                PlayVO("nar_sap_left_fc");
            }
        } else if (flag2) {
            PlayVO("nar_sap_right_fc");
        }
        if (unk1764 <= 0) {
            if (unk1768 & 4) {
                PlayVO("nar_sap_gen_pos");
            } else if (unk176c > 8.0f) {
                PlayVO("nar_sap_time_limit");
                unk176c = 0;
            }
        } else {
            unk1764 -= TheTaskMgr.DeltaSeconds();
        }
        unk1768 = 0;
        if (InFatality(-1)) {
            float val = Max(0.0f, TheTaskMgr.DeltaSeconds());
            val = Min(val, 1.0f);
            unk176c += val;
        }
    }
}
