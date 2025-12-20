#include "meta_ham/AccomplishmentCountConditional.h"
#include "hamobj/Difficulty.h"
#include "meta_ham/AccomplishmentConditional.h"
#include "meta_ham/AccomplishmentProgress.h"
#include "meta_ham/HamProfile.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Std.h"
#include "utl/Symbol.h"

AccomplishmentCountConditional::AccomplishmentCountConditional(DataArray *d, int i)
    : AccomplishmentConditional(d, i) {
    Configure(d);
}

AccomplishmentCountConditional::~AccomplishmentCountConditional() {}

void AccomplishmentCountConditional::Configure(DataArray *i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x1c);
}

bool AccomplishmentCountConditional::IsFulfilled(HamProfile *profile) const {
    static Symbol character("character");
    static Symbol stars("stars");
    static Symbol character_no_outfit("character_no_outfit");
    Difficulty d = kDifficultyEasy;
    FOREACH (it, m_lConditions) {
        Symbol s = it->unk8;
        if (s == character) {
            MILO_NOTIFY("Character-based achievements aren't supported in turbo (yet)");
        } else if (s == stars) {
            d = it->mDifficulty;
        } else if (s == character_no_outfit) {
            continue;
        } else {
            MILO_NOTIFY("Condition is not currently supported: %s ", s);
            return false;
        }
    }
    AccomplishmentProgress &progress = profile->AccessAccomplishmentProgress();
    // relies on MetaPerformer->unk38
    return false;
}
