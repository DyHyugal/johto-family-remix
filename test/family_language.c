#include "global.h"
#include "family_language.h"
#include "test/test.h"

#if IS_HNS
TEST("Family localization: only the persisted French value selects French")
{
    static const u8 english[] = _("English");
    static const u8 french[] = _("Francais");

    EXPECT_EQ(FamilyLanguage_Normalize(FAMILY_LANGUAGE_ENGLISH), FAMILY_LANGUAGE_ENGLISH);
    EXPECT_EQ(FamilyLanguage_Normalize(FAMILY_LANGUAGE_FRENCH), FAMILY_LANGUAGE_FRENCH);
    EXPECT_EQ(FamilyLanguage_Normalize(0xFF), FAMILY_LANGUAGE_ENGLISH);
    EXPECT_EQ(FamilyLanguage_SelectFor(FAMILY_LANGUAGE_ENGLISH, english, french), english);
    EXPECT_EQ(FamilyLanguage_SelectFor(FAMILY_LANGUAGE_FRENCH, english, french), french);
}

TEST("Family localization: language choice persists in challenge settings")
{
    u32 saved = GetFamilyLanguage();

    SetFamilyLanguage(FAMILY_LANGUAGE_FRENCH);
    EXPECT(FamilyLanguage_IsFrench());
    SetFamilyLanguage(FAMILY_LANGUAGE_ENGLISH);
    EXPECT(!FamilyLanguage_IsFrench());
    SetFamilyLanguage(saved);
}
#endif
