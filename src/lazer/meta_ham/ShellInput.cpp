#include "ShellInput.h"
#include "flow/PropertyEventProvider.h"
#include "gesture/GestureMgr.h"
#include "gesture/HandInvokeGestureFilter.h"
#include "gesture/HandsUpGestureFilter.h"
#include "gesture/SkeletonExtentTracker.h"
#include "gesture/SkeletonUpdate.h"
#include "gesture/SpeechMgr.h"
#include "hamobj/HamGameData.h"
#include "hamobj/HamNavList.h"
#include "meta_ham/DepthBuffer.h"
#include "meta_ham/HamUI.h"
#include "meta_ham/HelpBarPanel.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/JoypadMsgs.h"
#include "rndobj/Anim.h"
#include "ui/UI.h"

ShellInput::ShellInput()
    : mVoiceControlEnabled(0), unk_0x34(this), unk_0x48(0, 15, 0), unk_0x9C(0.2),
      unk_0xA0(0.25), unk_0xA4(0), mWrongHandPosAnim(this), mInputPanel(0),
      mCursorPanel(nullptr), unk_0xC4(0), mDepthBuffer(0), mSkelIdentifier(0),
      mSkelChooser(0), mSkelExtTracker(0) {
    unk_0x31 = 0;
    unk_0x32 = 0;
}

ShellInput::~ShellInput() {
    SkeletonUpdateHandle handle = SkeletonUpdate::InstanceHandle();
    handle.RemoveCallback(this);
    delete mDepthBuffer;
    delete mSkelIdentifier;
    delete mSkelChooser;
    delete mSkelExtTracker;
}

BEGIN_HANDLERS(ShellInput)
    HANDLE_ACTION_IF(
        panel_navigated, !TheGestureMgr->InControllerMode(), EnterControllerMode(false)
    )
    HANDLE_EXPR(has_skeleton, HasSkeleton())
    HANDLE_EXPR(num_tracked_skeletons, NumTrackedSkeletons())
    HANDLE_ACTION(
        enter_controller_mode,
        EnterControllerMode(_msg->Size() >= 3 ? _msg->Int(2) : false)
    )
    HANDLE_ACTION(exit_controller_mode, ExitControllerMode(true))
    HANDLE_EXPR(in_controller_mode, TheGestureMgr->InControllerMode())
    HANDLE_ACTION(
        set_last_select_in_controller_mode,
        HamNavList::sLastSelectInControllerMode = _msg->Int(2)
    )
    HANDLE_EXPR(voice_control_enabled, mVoiceControlEnabled)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(JoypadConnectionMsg)
    HANDLE_MESSAGE(SpeechRecoMessage)
    HANDLE_MESSAGE(SpeechEnableMsg)
    HANDLE_MESSAGE(LeftHandListEngagementMsg)
    HANDLE_MESSAGE(ResetControllerModeTimeoutMsg)
    HANDLE_SUPERCLASS(Hmx::Object)
END_HANDLERS

void ShellInput::PostUpdate(const SkeletonUpdateData *updata) {
    if (updata) {
        Skeleton *skeleton = TheGestureMgr->GetActiveSkeleton();
        if (skeleton) {
            mHandInvokeGestureFilter->Update(*skeleton, skeleton->ElapsedMs());
            mHandsUpGestureFilter->Update(*skeleton, skeleton->ElapsedMs());
        }
    }
}

void ShellInput::Init() {
    SetName("shell_input", ObjectDir::Main());
    SkeletonUpdateHandle handle = SkeletonUpdate::InstanceHandle();
    handle.AddCallback(this);
    mCursorPanel = ObjectDir::Main()->Find<UIPanel>("cursor_panel");
    MILO_ASSERT(mCursorPanel->CheckIsLoaded(), 95);
    MILO_ASSERT(mCursorPanel->LoadedDir(), 96);
    mDepthBuffer = new DepthBuffer();
    mDepthBuffer->Init(mCursorPanel);
    mWrongHandPosAnim =
        mCursorPanel->DataDir()->Find<RndAnimatable>("wrong_hand_position.anim", true);
    MILO_ASSERT(TheGameData, 102);
    mSkelIdentifier = new SkeletonIdentifier;
    mSkelIdentifier->Init();
    mSkelChooser = new SkeletonChooser;
    mHandInvokeGestureFilter = new HandInvokeGestureFilter;
    mHandsUpGestureFilter = Hmx::Object::New<HandsUpGestureFilter>();
    mHandsUpGestureFilter->mRequiredMs = 1200;
    mCursorPanel->Enter();
    TheSpeechMgr->AddSink(TheUI);
    mSkelExtTracker = new SkeletonExtentTracker;

    static Symbol reset_controller_mode_timeout("reset_controller_mode_timeout");
    TheHamUI.AddSink(this, reset_controller_mode_timeout);
}

void ShellInput::Draw() { mCursorPanel->Draw(); }

void ShellInput::Poll() {
    static Symbol is_in_shell_pause("is_in_shell_pause");
    static Symbol is_in_party_mode("is_in_party_mode");
    static Symbol is_in_infinite_party_mode("is_in_infinite_party_mode");
    // if (TheUI->FocusPanel() == TheGamePanel) {}

    if (TheUI->InTransition()) {
        SetCursorAlpha(0);
    }
}

void ShellInput::UpdateInputPanel(UIPanel *panel) { mInputPanel = panel; }

bool ShellInput::IsGameplayPanel() const {
    static Symbol is_gameplay_panel("is_gameplay_panel");
    if (TheUI->FocusPanel() != nullptr) {
        const DataNode *gamepanel =
            TheUI->FocusPanel()->Property(is_gameplay_panel, false);
        if (gamepanel != nullptr && gamepanel->Int() == 1)
            return true;
    }
    return false;
}

bool ShellInput::HasSkeleton() const {
    Skeleton *skel = TheGestureMgr->GetActiveSkeleton();
    return skel != nullptr && skel->IsValid();
}

int ShellInput::NumTrackedSkeletons() const {
    int count = 0;
    for (int i = 0; i < 6; i++) {
        if (TheGestureMgr->GetSkeleton(i).IsTracked())
            count++;
    }
    return count;
}

int ShellInput::CycleDrawCursor() {
    unk_0xC4 = !unk_0xC4;
    return unk_0xC4;
}

void ShellInput::SyncVoiceControl() {
    static Symbol allow_voice_control("allow_voice_control");
}

void ShellInput::ExitControllerMode(bool b) {
    HelpBarPanel *hbp = TheHamUI.GetHelpBarPanel();
    if (hbp)
        hbp->ExitControllerMode(b);
    TheGestureMgr->SetInControllerMode(false);
    static Message controllerModeExited("controller_mode_exited");
    TheUI->Handle(controllerModeExited, false);
    static Symbol in_controller_mode("in_controller_mode");
    TheHamProvider->SetProperty(in_controller_mode, 0);
    // TheRockCentral.unk_0x12C++;
}

void ShellInput::SyncToCurrentScreen() {}

DataNode ShellInput::OnMsg(const SpeechEnableMsg &msg) {
    if (msg->Int(2))
        SyncVoiceControl();
    return 0;
}
DataNode ShellInput::OnMsg(const ButtonDownMsg &msg) { return 0; }
DataNode ShellInput::OnMsg(const JoypadConnectionMsg &msg) {
    if (TheGestureMgr->InControllerMode() && msg->Int(3) == 0) {
        if (msg->Int(5) == TheHamUI.Unk108())
            ExitControllerMode(false);
    }
    return DataNode(kDataUnhandled, 0);
}
