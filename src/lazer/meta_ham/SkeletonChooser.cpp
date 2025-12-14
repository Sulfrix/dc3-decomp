#include "meta_ham/SkeletonChooser.h"
#include "flow/PropertyEventProvider.h"
#include "gesture/BaseSkeleton.h"
#include "gesture/DirectionGestureFilter.h"
#include "gesture/GestureMgr.h"
#include "gesture/HandRaisedGestureFilter.h"
#include "gesture/HighFiveGestureFilter.h"
#include "gesture/Skeleton.h"
#include "gesture/StandingStillGestureFilter.h"
#include "hamobj/HamGameData.h"
#include "hamobj/HamPlayerData.h"
#include "math/Vec.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"

SkeletonChooser::SkeletonChooser()
    : unk34(false), unk3c(0), unk44(1), unk48(true), unk80(0), unk84(0), unk88(0),
      unk8c(0), unk90(0), unk94(-1), unka0(false), unkbc(-1), unkc0(false) {
    SetName("skeleton_chooser", ObjectDir::Main());
    unk2c = new DirectionGestureFilterSingleUser(kSkeletonRight, kSkeletonLeft, 0, 0);
    unk30 = new DirectionGestureFilterSingleUser(kSkeletonLeft, kSkeletonRight, 0, 0);
    unk7c = Hmx::Object::New<HighFiveGestureFilter>();
    for (int i = 0; i < 6; i++) {
        unk4c[i] = Hmx::Object::New<HandRaisedGestureFilter>();
        unk4c[i]->SetRequiredMs(750);
        unk4c[i]->Clear();
        unk64[i] = Hmx::Object::New<StandingStillGestureFilter>();
        // unk64[i]->unk34 = 750;
        unka4[i] = 0;
    }
    for (int i = 0; i < 2; i++) {
        unk98[i] = Hmx::Object::New<HandRaisedGestureFilter>();
        unk98[i]->SetRequiredMs(750);
        unk98[i]->Clear();
    }
}

SkeletonChooser::~SkeletonChooser() {
    delete unk2c;
    delete unk30;
    for (int i = 0; i < 6; i++) {
        delete unk4c[i];
        delete unk64[i];
    }
    delete unk7c;
}

BEGIN_HANDLERS(SkeletonChooser)
    HANDLE_EXPR(toggle_draw_debug, unk34 = !unk34)
    HANDLE_ACTION(
        switch_active_to_player_index_immediate,
        SwitchActiveToPlayerIndexImmediate(_msg->Int(2))
    )
    HANDLE_EXPR(check_hand_raised, IsHandRaised(_msg->Int(2)))
    HANDLE(get_joint_depth_pos, OnGetJointDepthPos)
    HANDLE_EXPR(is_skeleton_valid, IsSkeletonValid(_msg->Int(2)))
    HANDLE_ACTION(lock_enrollment, unkc0 = _msg->Int(2))
    HANDLE_EXPR(is_enrollment_locked, unkc0)
    HANDLE_EXPR(is_left_player_hand_raised, IsLeftPlayerHandRaised())
    HANDLE_EXPR(is_right_player_hand_raised, IsRightPlayerHandRaised())
    HANDLE_ACTION(force_swap_player_sides, ForceSwapPlayerSides())
    HANDLE_SUPERCLASS(Hmx::Object)
END_HANDLERS

int SkeletonChooser::GetAssignedPlayerSkeletonID(int player) {
    MILO_ASSERT_RANGE(player, 0, 2, 0x7F);
    return TheGameData->Player(player)->GetSkeletonTrackingID();
}

bool SkeletonChooser::AreArmsCrossed(int id) {
    Skeleton *pSkeleton = TheGestureMgr->GetSkeletonByTrackingID(id);
    MILO_ASSERT(pSkeleton, 0x55F);
    Vector2 leftHandPos, rightHandPos;
    pSkeleton->ScreenPos(kJointHandLeft, leftHandPos);
    pSkeleton->ScreenPos(kJointHandRight, rightHandPos);
    if (leftHandPos.x > rightHandPos.x) {
        return true;
    } else {
        return false;
    }
}

void SkeletonChooser::GetJointDepthPos(int i1, int i2, Vector3 &v) {
    Skeleton *pSkeleton = TheGestureMgr->GetSkeletonByTrackingID(
        TheGestureMgr->GetSkeleton(i1).TrackingID()
    );
    if (pSkeleton) {
        Vector2 jointPos;
        pSkeleton->ScreenPos((SkeletonJoint)i2, jointPos);
        Vector3 jointV3 = pSkeleton->TrackedJoints()[i2].unk60;
        v.z = jointV3.z;
        v.x = jointPos.x;
        v.y = jointPos.y;
    } else {
        v.Zero();
    }
}

bool SkeletonChooser::IsSkeletonValid(int idx) {
    return TheGestureMgr->GetSkeletonByTrackingID(
        TheGestureMgr->GetSkeleton(idx).TrackingID()
    );
}

bool SkeletonChooser::IsHandRaised(int idx) {
    if (IsSkeletonValid(idx)) {
        return unka4[idx];
    } else {
        return false;
    }
}

bool SkeletonChooser::IsPlayerHandRaised(int player) {
    MILO_ASSERT_RANGE(player, 0, 2, 0x6DC);
    return unk98[player]->unk2c;
}

void SkeletonChooser::ClearPlayerSkeletonID(int id) {
    SetPlayerSkeletonID(id, -1);
    TheGestureMgr->SetPlayerSkeletonID(id, -1);
}

SkeletonSide SkeletonChooser::GetPlayerSide(int player) {
    MILO_ASSERT_RANGE(player, 0, 2, 0x86);
    HamPlayerData *pPlayer = TheGameData->Player(player);
    MILO_ASSERT(pPlayer, 0x89);
    Hmx::Object *pPlayerProvider = pPlayer->Provider();
    MILO_ASSERT(pPlayerProvider, 0x8B);
    static Symbol side("side");
    const DataNode *pPlayerSide = pPlayerProvider->Property(side);
    MILO_ASSERT(pPlayerSide, 0x8F);
    return (SkeletonSide)pPlayerSide->Int();
}

void SkeletonChooser::SetActivePlayer(int playerIndex) {
    MILO_ASSERT_RANGE(playerIndex, 0, 2, 0x635);
    unk3c = playerIndex;
    TheGameData->Player(playerIndex)->GetSkeletonTrackingID();
}

bool SkeletonChooser::IsLeftPlayerHandRaised() {
    for (int i = 0; i < 2; i++) {
        if (GetPlayerSide(i) == kSkeletonLeft) {
            return IsPlayerHandRaised(i);
        }
    }
    return false;
}

bool SkeletonChooser::IsRightPlayerHandRaised() {
    for (int i = 0; i < 2; i++) {
        if (GetPlayerSide(i) == kSkeletonRight) {
            return IsPlayerHandRaised(i);
        }
    }
    return false;
}

void SkeletonChooser::Poll() {
    if (!PotentiallyRecoverSkeletons()) {
        CheckToSwitchActivePlayer();
        if (unk38 >= 0) {
            unk40 += TheTaskMgr.DeltaUISeconds();
            if (unk40 > unk44) {
                Skeleton *pSkeleton = TheGestureMgr->GetSkeletonByTrackingID(
                    TheGestureMgr->GetPlayerSkeletonID(unk38)
                );
                if (pSkeleton && pSkeleton->IsTracked()) {
                    SetActivePlayer(unk38);
                }
                unk38 = -1;
                unk40 = 0;
            }
        }
        if (unk38 < 0) {
            UpdateTrackedSkeletonsElective();
            unk7c->Update(
                TheGestureMgr->GetSkeletonByTrackingID(
                    TheGameData->Player(0)->GetSkeletonTrackingID()
                ),
                TheGestureMgr->GetSkeletonByTrackingID(
                    TheGameData->Player(1)->GetSkeletonTrackingID()
                )
            );
            if (unk7c->CheckHighFive()) {
                static Message highFiveMsg("high_five");
                TheHamProvider->Handle(highFiveMsg, false);
            }
        }
    }
}

DataNode SkeletonChooser::OnGetJointDepthPos(const DataArray *a) {
    MILO_ASSERT(a->Size() == 7, 0x6B0);
    Vector3 v;
    GetJointDepthPos(a->Int(2), a->Int(3), v);
    *a->Var(4) = v.x;
    *a->Var(5) = v.y;
    *a->Var(6) = v.z;
    return 0;
}
