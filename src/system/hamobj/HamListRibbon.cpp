#include "hamobj/HamListRibbon.h"
#include "obj/Object.h"
#include "rndobj/Dir.h"

HamListRibbon::HamListRibbon()
    : mScrollAnims(this), mTestMode(0), mTestNumDisplay(4), mTestSelectedIndex(0),
      mSpacing(25), mMode(kRibbonSlide), mTestEntering(0), mPaddedSize(0),
      mPaddedSpacing(29), unk26c(0), mSwellAnim(this), mSlideAnim(this),
      mSelectAnim(this), mSelectToggleAnim(this), mSelectInactiveAnim(this),
      mSelectAllAnim(this), mDisengageAnim(this), mEnterAnim(this),
      mLabelPlaceholder(this), mHighlightSounds(this), mSelectSounds(this),
      mEnterFlow(this), mSlideSound(this), mSlideSoundAnim(this), mScrollSound(this),
      mScrollSoundAnim(this) {}

BEGIN_CUSTOM_PROPSYNC(HamListRibbon::ScrollAnims)
    SYNC_PROP(scroll_anim, o.mScrollAnim)
    SYNC_PROP(scroll_active, o.mScrollActive)
    SYNC_PROP(scroll_fade, o.mScrollFade)
    SYNC_PROP(scroll_faded, o.mScrollFaded)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(HamListRibbon)
    SYNC_PROP(test_mode, mTestMode)
    SYNC_PROP(test_entering, mTestEntering)
    SYNC_PROP(test_num_display, mTestNumDisplay)
    SYNC_PROP(test_selected_index, mTestSelectedIndex)
    SYNC_PROP(spacing, mSpacing)
    SYNC_PROP(padded_size, mPaddedSize)
    SYNC_PROP(padded_spacing, mPaddedSpacing)
    SYNC_PROP_SET(mode, (int &)mMode, mMode = (RibbonMode)_val.Int())
    SYNC_PROP(swell_anim, mSwellAnim)
    SYNC_PROP(slide_anim, mSlideAnim)
    SYNC_PROP(select_anim, mSelectAnim)
    SYNC_PROP(select_inactive_anim, mSelectInactiveAnim)
    SYNC_PROP(select_all_anim, mSelectAllAnim)
    SYNC_PROP(select_toggle_anim, mSelectToggleAnim)
    SYNC_PROP(enter_flow, mEnterFlow)
    SYNC_PROP(enter_anim, mEnterAnim)
    SYNC_PROP(disengage_anim, mDisengageAnim)
    SYNC_PROP(scroll_anims, mScrollAnims)
    SYNC_PROP(label_placeholder, mLabelPlaceholder)
    SYNC_PROP(highlight_sounds, mHighlightSounds)
    SYNC_PROP(select_sounds, mSelectSounds)
    SYNC_PROP(slide_sound, mSlideSound)
    SYNC_PROP(slide_sound_anim, mSlideSoundAnim)
    SYNC_PROP(scroll_sound, mScrollSound)
    SYNC_PROP(scroll_sound_anim, mScrollSoundAnim)
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS
