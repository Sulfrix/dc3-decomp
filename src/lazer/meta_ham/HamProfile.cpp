#include "meta_ham/HamProfile.h"
#include "meta_ham/HamSongMgr.h"
#include "meta_ham/MetagameRank.h"
#include "meta_ham/MoveRatingHistory.h"
#include "meta_ham/SongStatusMgr.h"
#include "os/OnlineID.h"
#include "utl/Std.h"
#include "utl/Symbol.h"

HamProfile::HamProfile(int i1)
    : Profile(i1), unk34(this), unk2fc(0), unk2fd(0), unk300(130), unk304(0), unk308(0),
      unk30c(0), unk310(0), unk314(0), unk318(new OnlineID()), unk31c(0), unk320(0),
      unk324(0), unk328(0), unk32c(0), unk330(0), unk334(0), unk338(gNullStr), unk33c(0),
      unk340(0), unk344(0), unk348(0), unk34c(0), unk350(0), unk354(0), unk358(0),
      unk35c(0), unk360(0), unk364(0), unk368(0), unk36c(1), unk370(0), unk374(3) {
    mSaveSizeMethod = SaveSize;
    unk18 = new SongStatusMgr(&TheHamSongMgr);
    unk208 = new MetagameStats();
    unk20c = new MetagameRank(this);
    unk210 = new MoveRatingHistory();
    unk158[0].SetProfile(this);
    unk158[1].SetProfile(this);
    unk158[2].SetProfile(this);
    ResetOutfitPrefs();
    static Symbol playlist_custom("playlist_custom");
    for (int i = 0; i < 5; i++) {
        Symbol cur = MakeString("playlist_custom_%02i", i + 1);
        unk220[i].SetParentProfile(this);
        unk220[i].SetName(cur);
    }
}

HamProfile::~HamProfile() {
    DeleteAll();
    delete unk18;
    delete unk208;
    delete unk20c;
    delete unk210;
}

void HamProfile::CheckForNinjaUnlock() {}
void HamProfile::CheckForIconManUnlock() {}
