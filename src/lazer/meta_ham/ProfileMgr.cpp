#include "meta_ham/ProfileMgr.h"
#include "HamProfile.h"
#include "ProfileMgr.h"
#include "flow/PropertyEventProvider.h"
#include "gesture/SpeechMgr.h"
#include "hamobj/HamGameData.h"
#include "hamobj/HamPlayerData.h"
#include "meta/FixedSizeSaveable.h"
#include "meta/MemcardMgr.h"
#include "meta/Profile.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "rndobj/Overlay.h"
#include "synth/Synth.h"
#include "utl/MemMgr.h"
#include "utl/Symbol.h"
#include "game/HamUser.h"

ProfileMgr TheProfileMgr;

ProfileMgr::ProfileMgr()
    : mPlatformAudioLatency(5), mPlatformVideoLatency(22), unk34(22), unk38(50),
      mGlobalOptionsSaveState(kMetaProfileUnloaded), mGlobalOptionsDirty(0), unk45(0),
      mTutorialsSeen(0), unk4c(0), mMusicVolume(4), mFxVolume(4), mCrowdVolume(4),
      mMono(0), mSyncOffset(0), mSongToTaskMgrMs(0), mBassBoost(0), mDolby(0), unk6a(0),
      mSyncPresetIx(0), mOverscan(0), mDisablePhotos(0), mNoFlashcards(0),
      mDisableVoice(0), mDisableVoiceCommander(0), mDisableVoicePause(0),
      mDisableVoicePractice(0), mShowVoiceTip(1), unk78(0), mDisableFreestyle(0),
      mVenuePreference(gNullStr), unk80(0), unk84(0), mCriticalProfile(0),
      mAllUnlocked(0), mProfileSaveBuffer(0), unka8(0), unka9(0), mProfilesOverlay(0),
      unkb0(0) {
    mSyncOffset = -mPlatformVideoLatency;
}

BEGIN_HANDLERS(ProfileMgr)
    HANDLE_EXPR(get_profile, GetProfile(_msg->Obj<HamUser>(2)))
    HANDLE_EXPR(get_save_data, GetSaveData(_msg->Obj<HamUser>(2)))
    HANDLE_ACTION(purge_old_data, PurgeOldData())
    HANDLE_EXPR(needs_upload, NeedsUpload())
    HANDLE_EXPR(get_profile_from_pad, GetProfileFromPad(_msg->Int(2)))
    HANDLE_EXPR(get_savable_profile_count, GetSavableProfileCount())
    HANDLE_EXPR(get_first_savable_profile, GetFirstSavableProfile())
    HANDLE_EXPR(unlock_all_songs, UnlockAllSongs())
    HANDLE_ACTION(relock_songs, RelockSongs())
    HANDLE_EXPR(get_all_unlocked, GetAllUnlocked())
    HANDLE_EXPR(global_options_needs_save, GlobalOptionsNeedsSave())
    HANDLE_EXPR(get_music_volume, GetMusicVolume())
    HANDLE_EXPR(get_music_volume_db, GetMusicVolumeDb())
    HANDLE_EXPR(get_fx_volume, GetFxVolume())
    HANDLE_EXPR(get_fx_volume_db, GetFxVolumeDb())
    HANDLE_EXPR(get_crowd_volume, GetCrowdVolume())
    HANDLE_EXPR(get_crowd_volume_db, GetCrowdVolumeDb())
    HANDLE_EXPR(get_bass_boost, GetBassBoost())
    HANDLE_EXPR(get_dolby, GetDolby())
    HANDLE_EXPR(get_venue_preference, mVenuePreference)
    HANDLE_EXPR(get_disable_photos, mDisablePhotos)
    HANDLE_EXPR(get_disable_voice, mDisableVoice)
    HANDLE_EXPR(get_disable_voice_commander, mDisableVoiceCommander)
    HANDLE_EXPR(get_disable_voice_pause, mDisableVoicePause)
    HANDLE_EXPR(get_disable_voice_practice, mDisableVoicePractice)
    HANDLE_EXPR(get_show_voice_tip, GetShowVoiceTip())
    HANDLE_EXPR(get_disable_freestyle, mDisableFreestyle)
    HANDLE_EXPR(get_no_flashcards, mNoFlashcards)
    HANDLE_EXPR(get_overscan, mOverscan)
    HANDLE_EXPR(get_mono, mMono)
    HANDLE_EXPR(get_sync_preset_ix, mSyncPresetIx)
    HANDLE_EXPR(get_sync_offset_raw, GetSyncOffsetRaw())
    HANDLE_EXPR(get_sync_offset, GetSyncOffset(_msg->Int(2)))
    HANDLE_EXPR(get_song_to_taskmgr_ms, mSongToTaskMgrMs - unk34)
    HANDLE_EXPR(get_song_to_taskmgr_ms_raw, GetSongToTaskMgrMsRaw())
    HANDLE_EXPR(get_excess_audio_lag, GetExcessAudioLag())
    HANDLE_EXPR(get_excess_video_lag, GetExcessVideoLag())
    HANDLE_EXPR(get_pad_extra_lag, GetPadExtraLag(_msg->Int(2), kGame))
    HANDLE_ACTION(set_music_volume, SetMusicVolume(_msg->Int(2)))
    HANDLE_ACTION(set_fx_volume, SetFxVolume(_msg->Int(2)))
    HANDLE_ACTION(set_crowd_volume, SetCrowdVolume(_msg->Int(2)))
    HANDLE_ACTION(set_bass_boost, SetBassBoost(_msg->Int(2)))
    HANDLE_ACTION(set_dolby, SetDolby(_msg->Int(2)))
    HANDLE_ACTION(toggle_disable_photos, ToggleDisablePhotos())
    HANDLE_ACTION(toggle_no_flashcards, ToggleNoFlashcards())
    HANDLE_ACTION(toggle_disable_voice, ToggleDisableVoice())
    HANDLE_ACTION(toggle_show_voice_tip, ToggleShowVoiceTip())
    HANDLE_ACTION(toggle_disable_freestyle, ToggleDisableFreestyle())
    HANDLE_ACTION(set_overscan, SetOverscan(_msg->Int(2)))
    HANDLE_ACTION(set_mono, SetMono(_msg->Int(2)))
    HANDLE_ACTION(set_sync_preset_ix, SetSyncPresetIx(_msg->Int(2)))
    HANDLE_ACTION(set_sync_offset, SetSyncOffset(_msg->Float(2)))
    HANDLE_ACTION(set_song_to_taskmgr_ms, SetSongToTaskMgrMs(_msg->Float(2)))
    HANDLE_ACTION(set_excess_audio_lag, SetExcessAudioLag(_msg->Float(2)))
    HANDLE_ACTION(set_excess_video_lag, SetExcessVideoLag(_msg->Float(2)))
    HANDLE_EXPR(is_autosave_enabled, IsAutosaveEnabled(_msg->Obj<HamProfile>(2)))
    HANDLE_EXPR(has_seen_tutorial, HasSeenTutorial(_msg->Int(2)))
    HANDLE_ACTION(mark_tutorial_seen, MarkTutorialSeen(_msg->Int(2)))
    HANDLE_EXPR(get_active_profile, GetActiveProfile(true))
    HANDLE_EXPR(has_active_profile, GetActiveProfile(true) != nullptr)
    HANDLE_EXPR(get_non_active_profile, GetNonActiveProfile())
    HANDLE_EXPR(is_any_profile_signed_into_live, IsAnyProfileSignedIntoLive())
    HANDLE_EXPR(get_active_profile_no_override, GetActiveProfile(false))
    HANDLE_EXPR(has_active_profile_no_override, GetActiveProfile(false) != nullptr)
    HANDLE_EXPR(is_content_unlocked, IsContentUnlocked(_msg->ForceSym(2)))
    HANDLE_EXPR(is_difficulty_unlocked, IsDifficultyUnlocked(_msg->Sym(2), _msg->Sym(3)))
    HANDLE_ACTION(set_critical_profile, mCriticalProfile = _msg->Obj<HamProfile>(2))
    HANDLE_ACTION(clear_critical_profile, mCriticalProfile = nullptr)
    HANDLE_EXPR(get_num_valid_profiles, GetNumValidProfiles())
    HANDLE_ACTION(pose_found, _msg->Int(2))
    HANDLE_ACTION(on_player_name_change, HandlePlayerNameChange())
    HANDLE_ACTION(enable_force_speech_language_support, EnableForceSpeechLanguageSupport())
    HANDLE_ACTION(enable_fitness_for_active_profiles, EnableFitnessForActiveProfiles())
    HANDLE_EXPR(is_voice_commander_suboptimal, !TheSpeechMgr->SpeechSupported())
    HANDLE_EXPR(has_finished_campaign, HasFinishedCampaign())
    HANDLE_ACTION(swag_jacked, HandleSwagJacked())
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE_ACTION(toggle_overlay, ToggleOverlay())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_SUPERCLASS(Hmx::Object)
END_HANDLERS

bool ProfileMgr::UnlockAllSongs() {
    bool old = mAllUnlocked;
    mAllUnlocked = true;
    return old == 0;
}

void ProfileMgr::RelockSongs() { mAllUnlocked = false; }
bool ProfileMgr::GetAllUnlocked() { return mAllUnlocked; }

bool ProfileMgr::GlobalOptionsNeedsSave() {
    if (mGlobalOptionsSaveState != kMetaProfileLoaded)
        return false;
    else
        return mGlobalOptionsDirty;
}

int ProfileMgr::GetMusicVolume() const { return mMusicVolume; }
int ProfileMgr::GetFxVolume() const { return unk6a ? 0 : mFxVolume; }
int ProfileMgr::GetCrowdVolume() const { return mCrowdVolume; }

float ProfileMgr::GetMusicVolumeDb() const { return SliderIxToDb(GetMusicVolume()); }
float ProfileMgr::GetFxVolumeDb() const { return SliderIxToDb(GetFxVolume()); }
float ProfileMgr::GetCrowdVolumeDb() const { return SliderIxToDb(GetCrowdVolume()); }
bool ProfileMgr::GetShowVoiceTip() const { return !mDisableVoice && mShowVoiceTip; }

void ProfileMgr::SetFxVolume(int vol) {
    mFxVolume = vol;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetCrowdVolume(int vol) {
    mCrowdVolume = vol;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetBassBoost(bool b) {
    mBassBoost = b;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetDolby(bool b) {
    mDolby = b;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::ToggleDisablePhotos() {
    mGlobalOptionsDirty = true;
    mDisablePhotos = !mDisablePhotos;
}

void ProfileMgr::ToggleNoFlashcards() {
    mGlobalOptionsDirty = true;
    mNoFlashcards = !mNoFlashcards;
}

void ProfileMgr::ToggleDisableVoice() {
    mGlobalOptionsDirty = true;
    mDisableVoice = !mDisableVoice;
    mDisableVoiceCommander = !mDisableVoiceCommander;
    mDisableVoicePause = !mDisableVoicePause;
    mDisableVoicePractice = !mDisableVoicePractice;
}

void ProfileMgr::ToggleShowVoiceTip() {
    mGlobalOptionsDirty = true;
    mShowVoiceTip = !mShowVoiceTip;
}

void ProfileMgr::ToggleDisableFreestyle() {
    mGlobalOptionsDirty = true;
    mDisableFreestyle = !mDisableFreestyle;
}

void ProfileMgr::SetMono(bool mono) {
    mGlobalOptionsDirty = true;
    mMono = mono;
    PushAllOptions();
}

void ProfileMgr::SetSyncPresetIx(int idx) {
    mSyncPresetIx = idx;
    mGlobalOptionsDirty = true;
}

void ProfileMgr::SetSyncOffset(float offset) {
    if (mSyncOffset != offset) {
        mSyncOffset = offset;
        mGlobalOptionsDirty = true;
        PushAllOptions();
    }
}

void ProfileMgr::SetSongToTaskMgrMs(float ms) {
    if (mSongToTaskMgrMs != ms) {
        mSongToTaskMgrMs = ms;
        mGlobalOptionsDirty = true;
    }
}

void ProfileMgr::SetExcessAudioLag(float lag) {
    SetSongToTaskMgrMsRaw(-(lag + mPlatformAudioLatency + GetSyncOffsetRaw()));
}

void ProfileMgr::SetSongToTaskMgrMsRaw(float ms) {
    if (mSongToTaskMgrMs != ms) {
        mSongToTaskMgrMs = ms;
        mGlobalOptionsDirty = true;
    }
}

bool ProfileMgr::IsAutosaveEnabled(HamProfile *p) const {
    return p && p->GetSaveState() != kMetaProfileError;
}

bool ProfileMgr::HasSeenTutorial(int tutorial) {
    return mTutorialsSeen & tutorial
        || TheProfileMgr.mGlobalOptionsSaveState != kMetaProfileLoaded;
}

void ProfileMgr::MarkTutorialSeen(int tutorial) {
    mGlobalOptionsDirty = true;
    mTutorialsSeen |= tutorial;
}

void ProfileMgr::EnableForceSpeechLanguageSupport() {
    mDisableVoiceCommander = false;
    mDisableVoice = false;
    mDisableVoicePause = false;
    mDisableVoicePractice = false;
    unk78 = true;
    mGlobalOptionsDirty = true;
}

void ProfileMgr::ToggleOverlay() {
    if (mProfilesOverlay) {
        mProfilesOverlay->SetShowing(!mProfilesOverlay->Showing());
    }
}

float ProfileMgr::GetSyncOffsetRaw() const { return mSyncOffset; }
float ProfileMgr::GetSongToTaskMgrMsRaw() const { return mSongToTaskMgrMs; }
float ProfileMgr::GetExcessAudioLag() const {
    return -(mPlatformAudioLatency + GetSongToTaskMgrMsRaw() + GetSyncOffsetRaw());
}
float ProfileMgr::GetExcessVideoLag() const {
    return -(mPlatformVideoLatency + GetSyncOffsetRaw());
}

void ProfileMgr::Init() {
    for (int i = 0; i < 4; i++) {
        unk90.push_back(new HamProfile(i));
    }
    SetName("profile_mgr", ObjectDir::Main());
    ThePlatformMgr.AddSink(this, SigninChangedMsg::Type());
    if (TheGameData) {
        TheGameData->AddSink(this, "pose_found");
        HamPlayerData *pPlayer0 = TheGameData->Player(0);
        MILO_ASSERT(pPlayer0, 0xA0);
        HamPlayerData *pPlayer1 = TheGameData->Player(1);
        MILO_ASSERT(pPlayer1, 0xA2);
        PropertyEventProvider *pProvider0 = pPlayer0->Provider();
        MILO_ASSERT(pProvider0, 0xA5);
        PropertyEventProvider *pProvider1 = pPlayer1->Provider();
        MILO_ASSERT(pProvider1, 0xA7);
        static Symbol on_player_name_change("on_player_name_change");
        pProvider0->AddSink(this, on_player_name_change, gNullStr, kHandle, false);
        pProvider1->AddSink(this, on_player_name_change, gNullStr, kHandle, false);
        static Symbol swag_jacked("swag_jacked");
        pProvider0->AddSink(this, swag_jacked, gNullStr, kHandle, false);
        pProvider1->AddSink(this, swag_jacked, gNullStr, kHandle, false);
    }
    InitSliders();
    static Symbol eng("eng");
    if (ThePlatformMgr.GetRegion() == kRegionNA && SystemLanguage() == eng) {
        unk4c = 0;
    } else {
        unk4c = 1;
    }
    MILO_ASSERT(mProfileSaveBuffer == NULL, 0xBC);
    int size = FixedSizeSaveableStream::GetSymbolTableSize(0x5C) + 8;
    size += HamProfile::SaveSize(0x5C);
    mProfileSaveBuffer = MemAlloc(size, __FILE__, 0xBE, "ProfileSaveBuffer");
    TheMemcardMgr.SetProfileSaveBuffer(mProfileSaveBuffer, size);
    static Symbol defaultSym("default");
    mVenuePreference = defaultSym;
    MILO_ASSERT(TheSynth, 0xCA);
    mDolby = TheSynth->IsUsingDolby();
    if (!TheSpeechMgr->SpeechSupported()) {
        mDisableVoiceCommander = true;
        mDisableVoice = true;
        mDisableVoicePause = true;
        mDisableVoicePractice = true;
        mShowVoiceTip = false;
    }
    mProfilesOverlay = RndOverlay::Find("profiles", false);
}
