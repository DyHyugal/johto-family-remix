#ifndef GUARD_FAMILY_LANGUAGE_H
#define GUARD_FAMILY_LANGUAGE_H

enum FamilyTextId
{
    FAMILY_TEXT_STARTER_CONFIRM_SPECIES,
    FAMILY_TEXT_STARTER_CONFIRM_EVOLUTION,
    FAMILY_TEXT_STARTER_EVOLUTION_PROMPT,
    FAMILY_TEXT_STARTER_ITEM_SENT_PC,
    FAMILY_TEXT_TRAINING_WELCOME,
    FAMILY_TEXT_TRAINING_CHOOSE_STAT,
    FAMILY_TEXT_TRAINING_CHOOSE_ACTION,
    FAMILY_TEXT_TRAINING_CHOOSE_EXP,
    FAMILY_TEXT_TRAINING_CHOOSE_NATURE,
    FAMILY_TEXT_TRAINING_CHOOSE_ABILITY,
    FAMILY_TEXT_TRAINING_CONFIRM_NATURE,
    FAMILY_TEXT_TRAINING_IV_DONE,
    FAMILY_TEXT_TRAINING_EV_DONE,
    FAMILY_TEXT_TRAINING_FRIENDSHIP_DONE,
    FAMILY_TEXT_TRAINING_NATURE_DONE,
    FAMILY_TEXT_TRAINING_ABILITY_DONE,
    FAMILY_TEXT_TRAINING_ALREADY_OPTIMIZED,
    FAMILY_TEXT_TRAINING_EV_AT_CAP,
    FAMILY_TEXT_TRAINING_EXP_AT_CAP,
    FAMILY_TEXT_TRAINING_NOT_ENOUGH_MONEY,
    FAMILY_TEXT_TRAINING_NO_EGGS,
    FAMILY_TEXT_TRAINING_GOODBYE,
    FAMILY_TEXT_STARTER_PROMPT,
    FAMILY_TEXT_EGG_PROMPT,
    FAMILY_TEXT_EGG_RECOGNIZED,
    FAMILY_TEXT_EGG_KEEP,
    FAMILY_TEXT_EGG_FULL,
    FAMILY_TEXT_EGG_SENT_PC,
    FAMILY_TEXT_EGG_RECEIVED,
    FAMILY_TEXT_EGG_CALL,
    FAMILY_TEXT_TM_SHOP_WELCOME,
    FAMILY_TEXT_TM_SHOP_CATEGORY,
    FAMILY_TEXT_TM_SHOP_TYPE,
    FAMILY_TEXT_ITEM_SHOP_WELCOME,
    FAMILY_TEXT_ITEM_SHOP_CATEGORY,
    FAMILY_TEXT_ITEM_SHOP_SUBCATEGORY,
    FAMILY_TEXT_GYM_GUIDE_BAG_FULL,
    FAMILY_TEXT_COUNT,
};

enum FamilyLanguage
{
    FAMILY_LANGUAGE_ENGLISH,
    FAMILY_LANGUAGE_FRENCH,
    FAMILY_LANGUAGE_COUNT,
};

enum FamilyLanguage FamilyLanguage_Normalize(u32 language);
enum FamilyLanguage GetFamilyLanguage(void);
void SetFamilyLanguage(u32 language);
bool32 FamilyLanguage_IsFrench(void);
const u8 *FamilyLanguage_Select(const u8 *english, const u8 *french);
const u8 *FamilyLanguage_SelectFor(u32 language, const u8 *english, const u8 *french);
void FamilyLanguage_SetScriptResult(void);
void FamilyLanguage_BufferText(void);
void FamilyLanguage_BuildTmShopMainMenu(void);
void FamilyLanguage_BuildTmShopCategoryMenu(void);
void FamilyLanguage_BuildTmShopSupportTypeMenu(void);
void FamilyLanguage_BuildTmShopWeakTypeMenu(void);
void FamilyLanguage_BuildTmShopPowerfulTypeMenu(void);
void FamilyLanguage_BuildTmShopUltimateTypeMenu(void);
void FamilyLanguage_BuildItemShopMainMenu(void);
void FamilyLanguage_BuildItemShopCategoryMenu(void);
void FamilyLanguage_BuildItemShopEvolutionMenu(void);
void FamilyLanguage_BuildItemShopStrategicMenu(void);
void FamilyLanguage_BuildItemShopOtherMenu(void);

#endif // GUARD_FAMILY_LANGUAGE_H
