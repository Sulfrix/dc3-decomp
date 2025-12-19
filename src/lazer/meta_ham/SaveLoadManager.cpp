#include "meta_ham/SaveLoadManager.h"
#include "meta/FixedSizeSaveable.h"
#include "meta/FixedSizeSaveableStream.h"
#include "meta/MemcardMgr.h"
#include "meta/SongMgr.h"
#include "meta_ham/HamProfile.h"
#include "meta_ham/HamUI.h"
#include "meta_ham/ProfileMgr.h"
#include "meta_ham/UIEventMgr.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/Memcard.h"
#include "os/PlatformMgr.h"
#include "ui/UIPanel.h"
#include "utl/Symbol.h"

SaveLoadManager *TheSaveLoadMgr;

SaveLoadManager::SaveLoadManager()
    : unk2c(0), unk2d(1), unk34(), unk38(0), unk3c(-1), unk40(0), unk4c(0), unk50(0),
      unk54(0), unk58(0), unk5c(0), unk60(0), mWaiting(0), unk64(0), unk68(0), unk6c(0),
      unk6d(0), unk70(0), mDeviceIDState(0), unk78(0) {
    SetName("saveload_mgr", ObjectDir::Main());
    ThePlatformMgr.AddSink(this, SigninChangedMsg::Type());
}

SaveLoadManager::~SaveLoadManager() {
    ThePlatformMgr.RemoveSink(this, SigninChangedMsg::Type());
    TheUIEventMgr->RemoveSink(this);
    RELEASE(unk78);
}

BEGIN_HANDLERS(SaveLoadManager)
    HANDLE_ACTION(autosave, AutoSave())
    HANDLE_ACTION(autoload, AutoLoad())
    HANDLE_ACTION(manual_save, ManualSave(_msg->Obj<HamProfile>(2)))
    HANDLE_EXPR(is_autosave_enabled, IsAutosaveEnabled(_msg->Obj<HamProfile>(2)))
    HANDLE_ACTION(enable_autosave, EnableAutosave(_msg->Obj<HamProfile>(2)))
    HANDLE_ACTION(disable_autosave, DisableAutosave(_msg->Obj<HamProfile>(2)))
    HANDLE_ACTION(handle_eventresponse_start, HandleEventResponseStart(_msg->Int(2)))
    HANDLE_ACTION(
        handle_eventresponse, HandleEventResponse(_msg->Obj<HamProfile>(2), _msg->Int(3))
    )
    HANDLE_EXPR(get_dialog_msg, GetDialogMsg())
    HANDLE_EXPR(get_dialog_opt1, GetDialogOpt1())
    HANDLE_EXPR(get_dialog_opt2, GetDialogOpt2())
    HANDLE_EXPR(get_dialog_focus_option, unk34 == 0x5c)
    HANDLE_EXPR(is_initial_load_done, IsInitialLoadDone())
    HANDLE_EXPR(is_idle, IsIdle())
    HANDLE_ACTION(activate, Activate())
    HANDLE_ACTION(printout_savesize_info, PrintoutSaveSizeInfo())
    HANDLE_MESSAGE(DeviceChosenMsg)
    HANDLE_MESSAGE(NoDeviceChosenMsg)
    HANDLE_MESSAGE(MCResultMsg)
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE_MESSAGE(EventDialogDismissMsg)
    HANDLE_SUPERCLASS(Hmx::Object)
END_HANDLERS

void SaveLoadManager::AutoSave() {
    if (IsReasonToAutosave()) {
        unk6c = true;
    }
}

void SaveLoadManager::AutoLoad() {
    if (IsReasonToAutoload()) {
        unk6d = true;
    }
}

void SaveLoadManager::HandleEventResponseStart(int) { unk38 = unk34; }

__forceinline bool SaveLoadManager::IsIdle() const {
    return unk34 == 0 && (!unk2c || (!unk6c && !unk6d));
}

void SaveLoadManager::PrintoutSaveSizeInfo() {
    FixedSizeSaveable::EnablePrintouts(true);
    MILO_LOG("SAVESIZE\n");
    int profileSize = HamProfile::SaveSize(0x5C);
    int symTableSize = FixedSizeSaveableStream::GetSymbolTableSize(0x5C);
    MILO_LOG("Symbol Table Size = %i\n", symTableSize);
    MILO_LOG("SAVESIZE TOTAL = %i \n", symTableSize + profileSize);
}

bool SaveLoadManager::IsReasonToAutosave() {
    HamProfile *p = GetAutosavableProfile();
    return p || TheProfileMgr.GlobalOptionsNeedsSave() || SongCacheNeedsWrite();
}

bool SaveLoadManager::IsReasonToAutoload() {
    HamProfile *p = GetNewSigninProfile();
    return p || unk2d;
}

void SaveLoadManager::EnableAutosave(HamProfile *p) {
    if (!p) {
        MILO_NOTIFY("Tried to enable autosave without a valid profile.");
    } else {
        ManualSave(p);
    }
}

void SaveLoadManager::ManualSave(HamProfile *pProfile) {
    if (unk34 != 0) {
        MILO_NOTIFY(
            "Attempted to perform a manual save, but saveloadmgr is not idle (state = %d).",
            unk34
        );
    } else {
        MILO_ASSERT(pProfile, 0x364);
        unk40 = pProfile;
        unk3c = pProfile->GetPadNum();
        TheMemcardMgr.AddSink(this);
        SetState((State)0x56);
    }
}

void SaveLoadManager::Start() {
    unk3c = -1;
    TheMemcardMgr.AddSink(this);
    SetState((State)1);
    if (unk30 == 0) {
        UpdateStatus((SaveLoadMgrStatus)3);
    }
}

void SaveLoadManager::Finish() {
    if (unk30 == 0) {
        UpdateStatus((SaveLoadMgrStatus)4);
    }
    TheMemcardMgr.RemoveSink(this);
    SetState((State)0x67);
}

void SaveLoadManager::UpdateStatus(SaveLoadMgrStatus status) {
    static SaveLoadMgrStatusUpdateMsg msg(-1);
    msg[0] = status;
    Export(msg, true);
}

bool SaveLoadManager::SongCacheNeedsWrite() {
    return TheSongMgr.SongCacheNeedsWrite() && !unk60;
}

void SaveLoadManager::DisableAutosave(HamProfile *pProfile) {
    if (!pProfile) {
        MILO_NOTIFY("Tried to disable autosave without a valid profile.");
    } else if (!IsIdle()) {
        MILO_NOTIFY("Tried to disable autosave while saveloadmgr is not idle.");
    } else {
        pProfile->SetSaveState(kMetaProfileError); // error?
    }
}

bool SaveLoadManager::IsSafePlaceToSave() const {
    if (!TheUIEventMgr->HasActiveDialogEvent()
        && !TheUIEventMgr->HasActiveTransitionEvent()) {
        return true;
    } else
        return false;
}

bool SaveLoadManager::IsSafePlaceToLoad() const {
    if (TheUIEventMgr->HasActiveDialogEvent()
        || TheUIEventMgr->HasActiveTransitionEvent()) {
        return false;
    } else {
        bool ret = true;
        UIPanel *panel = TheHamUI.FocusPanel();
        if (panel) {
            static Symbol allow_load("allow_load");
            const DataNode *n = panel->Property(allow_load, false);
            if (n) {
                ret = n->Int();
            }
        }
        return ret;
    }
}

void SaveLoadManager::Activate() {
    if (!unk2c) {
        unk2c = true;
        unk6d = true;
        TheUIEventMgr->AddSink(this, EventDialogDismissMsg::Type());
    }
}

bool SaveLoadManager::IsAutosaveEnabled(HamProfile *p) {
    if (!p) {
        MILO_NOTIFY("Tried to get autosave enabled status without a valid profile.");
        return false;
    } else {
        return p->IsAutosaveEnabled();
    }
}

Symbol SaveLoadManager::GetDialogOpt1() {
    static Symbol mc_button_create_data("mc_button_create_data");
    static Symbol mc_button_choose_device("mc_button_choose_device");
    static Symbol mc_button_continue("mc_button_continue");
    static Symbol mc_button_overwrite("mc_button_overwrite");
    static Symbol song_info_cache_button_create("song_info_cache_button_create");
    static Symbol song_info_cache_button_corrupt_overwrite(
        "song_info_cache_button_corrupt_overwrite"
    );
    static Symbol global_options_button_create("global_options_button_create");
    static Symbol global_options_button_corrupt_overwrite(
        "global_options_button_corrupt_overwrite"
    );
    static Symbol mc_button_delete_saves("mc_button_delete_saves");
    static Symbol mc_button_yes("mc_button_yes");
    Symbol out = gNullStr;
    switch (unk34) {
    case 6:
        out = mc_button_create_data;
        break;
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
        out = mc_button_overwrite;
        break;
    case 0x17:
    case 0x18:
        out = song_info_cache_button_create;
        break;
    case 0x1C:
        out = song_info_cache_button_corrupt_overwrite;
        break;
    case 0x2F:
        out = global_options_button_corrupt_overwrite;
        break;
    case 0x29:
    case 0x2A:
    case 0x3A:
        out = global_options_button_create;
        break;
    case 0x48:
        out = mc_button_overwrite;
        break;
    case 0x4A:
        out = mc_button_delete_saves;
        break;
    case 7:
    case 0xC:
    case 0x4C:
    case 0x58:
    case 0x5E:
        out = mc_button_choose_device;
        break;
    case 0x5B:
        out = mc_button_continue;
        break;
    case 0x5C:
        out = mc_button_yes;
        break;
    default:
        break;
    }
    return out;
}

Symbol SaveLoadManager::GetDialogOpt2() {
    static Symbol mc_button_cancel("mc_button_cancel");
    static Symbol mc_button_continue_no_save("mc_button_continue_no_save");
    static Symbol song_info_cache_button_cancel("song_info_cache_button_cancel");
    static Symbol global_options_button_cancel("global_options_button_cancel");
    static Symbol mc_button_retry("mc_button_retry");
    static Symbol mc_button_disable_autosave("mc_button_disable_autosave");
    static Symbol mc_button_no("mc_button_no");
    Symbol out = gNullStr;
    switch (unk34) {
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
        out = mc_button_continue_no_save;
        break;
    case 0x17:
    case 0x18:
    case 0x1C:
        out = song_info_cache_button_cancel;
        break;
    case 0x29:
    case 0x2A:
    case 0x2F:
    case 0x3A:
        out = global_options_button_cancel;
        break;
    case 0x4A:
        out = mc_button_retry;
        break;
    case 0x4C:
        out = mc_button_disable_autosave;
        break;
    case 0x5C:
        out = mc_button_no;
        break;
    case 6:
    case 7:
    case 0xC:
    case 0x48:
    case 0x58:
    case 0x5B:
    case 0x5E:
        out = mc_button_cancel;
        break;
    default:
        break;
    }
    return out;
}

void SaveLoadManager::Init() {
    MILO_ASSERT(!TheSaveLoadMgr, 0x47);
    TheSaveLoadMgr = new SaveLoadManager();
}

HamProfile *SaveLoadManager::GetAutosavableProfile() {
    std::vector<HamProfile *> shouldAutosaves = TheProfileMgr.GetShouldAutosave();
    if (!shouldAutosaves.empty()) {
        HamProfile *pProfile = shouldAutosaves[0];
        MILO_ASSERT(pProfile, 0x401);
        return pProfile;
    } else {
        return nullptr;
    }
}

HamProfile *SaveLoadManager::GetNewSigninProfile() {
    std::vector<HamProfile *> signIns = TheProfileMgr.GetNewlySignedIn();
    if (!signIns.empty()) {
        HamProfile *pProfile = signIns[0];
        MILO_ASSERT(pProfile, 0x3F2);
        return pProfile;
    } else {
        return nullptr;
    }
}

DataNode SaveLoadManager::OnMsg(const DeviceChosenMsg &msg) {
    MILO_ASSERT(mWaiting, 0x887);
    mWaiting = false;
    switch (unk34) {
    case 0x57:
        unk70 = msg.Device();
        SetState((State)0x45);
        break;
    case 8:
    case 9:
    case 0xA:
    case 0xD:
        unk70 = msg.Device();
        SetState((State)0xB);
        break;
    case 0x4D:
        SetState((State)0x47);
        break;
    case 0x5D:
        SetState((State)0x60);
        break;
    case 0x65:
    case 0x66:
    case 0x67:
        break;
    default:
        State state = unk34;
        State mode = unk30;
        MILO_FAIL("Unhandled DeviceChosenMsg in state %d and mode %d", state, mode);
        break;
    }
    return 0;
}

DataNode SaveLoadManager::OnMsg(const EventDialogDismissMsg &msg) {
    static Symbol saveload_dialog_event("saveload_dialog_event");
    Symbol s2 = msg->ForceSym(2);
    Symbol s3 = msg->ForceSym(3);
    if (s3 != gNullStr && s2 == saveload_dialog_event && s3 != saveload_dialog_event) {
        SetState((State)0x65);
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode SaveLoadManager::GetDialogMsg() {
    String profileName = gNullStr;
    int playerNum = -1;
    if (unk40) {
        profileName = unk40->GetName();
        playerNum = unk40->GetPadNum() + 1;
    }
    switch (unk34) {
    case 6: {
        static Symbol mc_auto_load_no_save_found_fmt("mc_auto_load_no_save_found_fmt");
        return DataArrayPtr(mc_auto_load_no_save_found_fmt, DataArrayPtr(), profileName);
    }
    case 7: {
        static Symbol mc_auto_load_multiple_saves_found_fmt(
            "mc_auto_load_multiple_saves_found_fmt"
        );
        return DataArrayPtr(
            mc_auto_load_multiple_saves_found_fmt, DataArrayPtr(), profileName
        );
    }
    case 0xC: {
        static Symbol mc_load_device_missing_fmt("mc_load_device_missing_fmt");
        return DataArrayPtr(mc_load_device_missing_fmt, DataArrayPtr(), profileName);
    }
    case 0xE: {
        static Symbol mc_auto_load_corrupt("mc_auto_load_corrupt");
        HamProfile *pProfile = unk40;
        MILO_ASSERT(pProfile, 0xAD6);
        return DataArrayPtr(
            mc_auto_load_corrupt,
            DataArrayPtr(),
            ThePlatformMgr.GetName(pProfile->GetPadNum())
        );
    }
    case 0xF: {
        static Symbol mc_auto_load_not_owner("mc_auto_load_not_owner");
        return DataArrayPtr(mc_auto_load_not_owner, DataArrayPtr());
    }
    case 0x10: {
        if (playerNum != -1) {
            static Symbol mc_auto_load_obsolete_version_fmt(
                "mc_auto_load_obsolete_version_fmt"
            );
            return DataArrayPtr(
                mc_auto_load_obsolete_version_fmt, DataArrayPtr(), profileName
            );
        } else {
            static Symbol mc_auto_load_obsolete_version("mc_auto_load_obsolete_version");
            return DataArrayPtr(mc_auto_load_obsolete_version, DataArrayPtr());
        }
    }
    case 0x11: {
        if (playerNum != -1) {
            static Symbol mc_auto_load_newer_version_fmt("mc_auto_load_newer_version_fmt");
            return DataArrayPtr(
                mc_auto_load_newer_version_fmt, DataArrayPtr(), profileName
            );
        } else {
            static Symbol mc_auto_load_newer_version("mc_auto_load_newer_version");
            return DataArrayPtr(mc_auto_load_newer_version, DataArrayPtr());
        }
    }
    case 0x17: {
        static Symbol song_info_cache_create("song_info_cache_create");
        return DataArrayPtr(song_info_cache_create, DataArrayPtr());
    }
    case 0x18: {
        static Symbol song_info_cache_missing("song_info_cache_missing");
        return DataArrayPtr(song_info_cache_missing, DataArrayPtr());
    }
    case 0x1C: {
        static Symbol song_info_cache_corrupt("song_info_cache_corrupt");
        return DataArrayPtr(song_info_cache_corrupt, DataArrayPtr());
    }
    case 0x29: {
        static Symbol global_options_create("global_options_create");
        return DataArrayPtr(global_options_create, DataArrayPtr());
    }
    case 0x2A:
    case 0x3A: {
        static Symbol global_options_missing("global_options_missing");
        return DataArrayPtr(global_options_missing, DataArrayPtr());
    }
    case 0x2F: {
        static Symbol global_options_corrupt("global_options_corrupt");
        return DataArrayPtr(global_options_corrupt, DataArrayPtr());
    }
    case 0x42: {
        static Symbol mc_autosave_disabled("mc_autosave_disabled");
        return DataArrayPtr(mc_autosave_disabled, DataArrayPtr());
    }
    case 0x48: {
        static Symbol mc_save_confirm_overwrite("mc_save_confirm_overwrite");
        return DataArrayPtr(mc_save_confirm_overwrite, DataArrayPtr());
    }
    case 0x49: {
        static Symbol mc_save_not_enough_space("mc_save_not_enough_space");
        return DataArrayPtr(mc_save_not_enough_space, DataArrayPtr());
    }
    case 0x4A: {
        static Symbol mc_save_not_enough_space("mc_save_not_enough_space");
        return DataArrayPtr(
            mc_save_not_enough_space, DataArrayPtr(), -TheMemcardMgr.GetSizeNeeded()
        );
    }
    case 0x4C: {
        static Symbol mc_save_device_missing_fmt("mc_save_device_missing_fmt");
        return DataArrayPtr(mc_save_device_missing_fmt, DataArrayPtr(), profileName);
    }
    case 0x4E: {
        static Symbol mc_save_failed("mc_save_failed");
        return DataArrayPtr(mc_save_failed, DataArrayPtr());
    }
    case 0x4F: {
        static Symbol mc_save_disabled_by_cheat("mc_save_disabled_by_cheat");
        return DataArrayPtr(mc_save_disabled_by_cheat, DataArrayPtr());
    }
    case 0x50: {
        static Symbol mc_load_failed("mc_load_failed");
        return DataArrayPtr(mc_load_failed, DataArrayPtr());
    }
    case 0x58: {
        static Symbol mc_manual_save_no_selection("mc_manual_save_no_selection");
        return DataArrayPtr(mc_manual_save_no_selection, DataArrayPtr());
    }
    case 0x5B: {
        if (playerNum != -1) {
            static Symbol mc_manual_load_confirm_unsaved_fmt(
                "mc_manual_load_confirm_unsaved_fmt"
            );
            return DataArrayPtr(
                mc_manual_load_confirm_unsaved_fmt, DataArrayPtr(), profileName
            );
        } else {
            static Symbol mc_manual_load_confirm_unsaved("mc_manual_load_confirm_unsaved");
            return DataArrayPtr(mc_manual_load_confirm_unsaved, DataArrayPtr());
        }
    }
    case 0x5C: {
        static Symbol mc_manual_load_confirm("mc_manual_load_confirm");
        return DataArrayPtr(mc_manual_load_confirm, DataArrayPtr());
    }
    case 0x5E: {
        static Symbol mc_manual_load_no_selection("mc_manual_load_no_selection");
        return DataArrayPtr(mc_manual_load_no_selection, DataArrayPtr());
    }
    case 0x5F: {
        static Symbol mc_manual_load_storage_missing("mc_manual_load_storage_missing");
        return DataArrayPtr(mc_manual_load_storage_missing, DataArrayPtr());
    }
    case 0x61: {
        static Symbol mc_manual_load_no_file("mc_manual_load_no_file");
        return DataArrayPtr(mc_manual_load_no_file, DataArrayPtr());
    }
    case 0x62: {
        static Symbol mc_manual_load_corrupt("mc_manual_load_corrupt");
        return DataArrayPtr(mc_manual_load_corrupt, DataArrayPtr());
    }
    case 0x63: {
        static Symbol mc_manual_load_not_owner("mc_manual_load_not_owner");
        return DataArrayPtr(mc_manual_load_not_owner, DataArrayPtr());
    }
    default: {
        MILO_ASSERT(false, 0xB73);
        return 0;
    }
    }
}
