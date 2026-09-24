#include "global.h"
#include "family_language.h"
#include "script.h"
#include "event_data.h"
#include "string_util.h"
#include "script_menu.h"
#include "constants/characters.h"


struct FamilyLocalizedText
{
    const u8 *english;
    const u8 *french;
};

#define FAMILY_TEXT(en, fr) {COMPOUND_STRING(en), COMPOUND_STRING(fr)}

static const struct FamilyLocalizedText sFamilyTexts[FAMILY_TEXT_COUNT] =
{
    [FAMILY_TEXT_STARTER_CONFIRM_SPECIES] = FAMILY_TEXT("Do you choose {STR_VAR_1}?", "Choisis-tu {STR_VAR_1} ?"),
    [FAMILY_TEXT_STARTER_CONFIRM_EVOLUTION] = FAMILY_TEXT("Choose {STR_VAR_1} with\n{STR_VAR_2} planned?", "Choisis-tu {STR_VAR_1}\navec {STR_VAR_2} prévu ?"),
    [FAMILY_TEXT_STARTER_EVOLUTION_PROMPT] = FAMILY_TEXT("Which evolution do you plan?", "Quelle évolution prévois-tu ?"),
    [FAMILY_TEXT_STARTER_ITEM_SENT_PC] = FAMILY_TEXT("The BAG is full.\pThe item was sent to the PC.", "Le SAC est plein.\pL'objet a été envoyé au PC."),
    [FAMILY_TEXT_TRAINING_WELCOME] = FAMILY_TEXT("Pokémon Training!\nWhich service do you want?", "Training Pokémon !\nQuel service veux-tu ?"),
    [FAMILY_TEXT_TRAINING_CHOOSE_STAT] = FAMILY_TEXT("Which stat?", "Quelle statistique ?"),
    [FAMILY_TEXT_TRAINING_CHOOSE_ACTION] = FAMILY_TEXT("Which action?", "Quelle action ?"),
    [FAMILY_TEXT_TRAINING_CHOOSE_EXP] = FAMILY_TEXT("How many levels?", "Combien de niveaux ?"),
    [FAMILY_TEXT_TRAINING_CHOOSE_NATURE] = FAMILY_TEXT("Choose the new Nature.", "Choisis la nouvelle Nature."),
    [FAMILY_TEXT_TRAINING_CHOOSE_ABILITY] = FAMILY_TEXT("Choose an available Ability.", "Choisis un Talent disponible."),
    [FAMILY_TEXT_TRAINING_CONFIRM_NATURE] = FAMILY_TEXT("The {STR_VAR_1} Nature costs ¥5,000.\nConfirm?", "La Nature {STR_VAR_1} coûte 5 000 ¥.\nConfirmer ?"),
    [FAMILY_TEXT_TRAINING_IV_DONE] = FAMILY_TEXT("The selected IVs are now at\nthe maximum: 31!", "Les IV sélectionnés sont maintenant\nau maximum : 31 !"),
    [FAMILY_TEXT_TRAINING_EV_DONE] = FAMILY_TEXT("The EVs were changed within\nthe legal limits.", "Les EV ont été modifiés dans les\nlimites légales."),
    [FAMILY_TEXT_TRAINING_FRIENDSHIP_DONE] = FAMILY_TEXT("Friendship is now at\nthe maximum!", "Son Bonheur est maintenant au\nmaximum !"),
    [FAMILY_TEXT_TRAINING_NATURE_DONE] = FAMILY_TEXT("The Nature is now\n{STR_VAR_1}!", "La Nature est maintenant\n{STR_VAR_1} !"),
    [FAMILY_TEXT_TRAINING_ABILITY_DONE] = FAMILY_TEXT("The Ability is now\n{STR_VAR_1}!", "Le Talent est maintenant\n{STR_VAR_1} !"),
    [FAMILY_TEXT_TRAINING_ALREADY_OPTIMIZED] = FAMILY_TEXT("This Pokémon already has that setting.", "Ce Pokémon possède déjà ce réglage."),
    [FAMILY_TEXT_TRAINING_EV_AT_CAP] = FAMILY_TEXT("Impossible: this stat or the total\nEVs are already at the maximum.", "Impossible : cette statistique ou le\ntotal des EV est déjà au maximum."),
    [FAMILY_TEXT_TRAINING_EXP_AT_CAP] = FAMILY_TEXT("This Pokémon has already reached\nthe current level cap.", "Ce Pokémon a déjà atteint le\nniveau plafond actuel."),
    [FAMILY_TEXT_TRAINING_NOT_ENOUGH_MONEY] = FAMILY_TEXT("You need ¥5,000 to change a\nNature.", "Il faut 5 000 ¥ pour changer de\nNature."),
    [FAMILY_TEXT_TRAINING_NO_EGGS] = FAMILY_TEXT("I cannot train an Egg.", "Je ne peux pas entraîner un Œuf."),
    [FAMILY_TEXT_TRAINING_GOODBYE] = FAMILY_TEXT("Come back whenever you want to\ntrain a Pokémon!", "Reviens quand tu veux optimiser\nun Pokémon !"),
    [FAMILY_TEXT_STARTER_PROMPT] = FAMILY_TEXT("Which partner do you want?", "Quel partenaire souhaites-tu ?"),
    [FAMILY_TEXT_EGG_PROMPT] = FAMILY_TEXT("You seem truly gifted with\nPokémon!\pIf you identify the species in\nthis Egg, you may keep it.", "Tu sembles vraiment doué\navec les POKéMON !\pSi tu reconnais l'espèce de\ncet œuf, tu peux le garder."),
    [FAMILY_TEXT_EGG_RECOGNIZED] = FAMILY_TEXT("Yes, you are right. It is a\n{STR_VAR_1} Egg.\pKeep it and take good care of it!", "Oui, tu as raison, c'est bien\nun œuf de {STR_VAR_1}.\pGarde-le et prends soin de lui !"),
    [FAMILY_TEXT_EGG_KEEP] = FAMILY_TEXT("Keep the Egg. We can talk about\nit again whenever you want.", "Garde l'œuf. Nous pourrons\nen reparler quand tu voudras."),
    [FAMILY_TEXT_EGG_FULL] = FAMILY_TEXT("Your party and PC are full.\pKeep the Egg and return after\nmaking some room.", "Ton équipe et ton PC sont pleins.\pGarde l'œuf et reviens après\navoir fait de la place."),
    [FAMILY_TEXT_EGG_SENT_PC] = FAMILY_TEXT("The Egg was sent to your PC.", "L'œuf a été envoyé dans ton PC."),
    [FAMILY_TEXT_EGG_RECEIVED] = FAMILY_TEXT("PROF. ELM entrusted you with the\nEgg he received from MR. POKéMON.", "Le PROF. ORME t'a confié l'œuf\nreçu de M. POKéMON."),
    [FAMILY_TEXT_EGG_CALL] = FAMILY_TEXT("ELM: How is your Egg?\pMy aide is waiting for you at the\nVIOLET CITY POKéMON CENTER.\pHe has something for you!", "ORME : Comment va ton œuf ?\pMon assistant t'attend au\nCENTRE POKéMON de MAUVILLE.\pIl a quelque chose pour toi !"),
    [FAMILY_TEXT_TM_SHOP_WELCOME] = FAMILY_TEXT("What would you like to do today?", "Que souhaites-tu faire aujourd'hui ?"),
    [FAMILY_TEXT_TM_SHOP_CATEGORY] = FAMILY_TEXT("Which kind of TM are you looking for?", "Quel genre de CT cherches-tu ?"),
    [FAMILY_TEXT_TM_SHOP_TYPE] = FAMILY_TEXT("Which move type are you looking for?", "Quel type de capacité cherches-tu ?"),
    [FAMILY_TEXT_ITEM_SHOP_WELCOME] = FAMILY_TEXT("What would you like to do today?", "Que souhaites-tu faire aujourd'hui ?"),
    [FAMILY_TEXT_ITEM_SHOP_CATEGORY] = FAMILY_TEXT("Which kind of item are you looking for?", "Quel genre d'objet cherches-tu ?"),
    [FAMILY_TEXT_ITEM_SHOP_SUBCATEGORY] = FAMILY_TEXT("Which category are you looking for?", "Quelle catégorie cherches-tu ?"),
    [FAMILY_TEXT_GYM_GUIDE_BAG_FULL] = FAMILY_TEXT("Your BAG is full. Make room and ask me again.", "Ton SAC est plein. Fais de la place et reviens me voir."),
};

#undef FAMILY_TEXT

enum FamilyLanguage FamilyLanguage_Normalize(u32 language)
{
    return language == FAMILY_LANGUAGE_FRENCH
        ? FAMILY_LANGUAGE_FRENCH
        : FAMILY_LANGUAGE_ENGLISH;
}

enum FamilyLanguage GetFamilyLanguage(void)
{
    return FamilyLanguage_Normalize(gSaveBlock3Ptr->challengeSettings.familyLanguage);
}

void SetFamilyLanguage(u32 language)
{
    gSaveBlock3Ptr->challengeSettings.familyLanguage = FamilyLanguage_Normalize(language);
}

bool32 FamilyLanguage_IsFrench(void)
{
    return GetFamilyLanguage() == FAMILY_LANGUAGE_FRENCH;
}

const u8 *FamilyLanguage_SelectFor(u32 language, const u8 *english, const u8 *french)
{
    return FamilyLanguage_Normalize(language) == FAMILY_LANGUAGE_FRENCH ? french : english;
}

const u8 *FamilyLanguage_Select(const u8 *english, const u8 *french)
{
    return FamilyLanguage_SelectFor(GetFamilyLanguage(), english, french);
}

void FamilyLanguage_SetScriptResult(void)
{
    gSpecialVar_Result = FamilyLanguage_IsFrench();
}


void FamilyLanguage_BufferText(void)
{
    u32 id = gSpecialVar_0x8000;

    if (id >= FAMILY_TEXT_COUNT)
    {
        gStringVar4[0] = EOS;
        return;
    }
    StringCopy(gStringVar4, FamilyLanguage_Select(sFamilyTexts[id].english, sFamilyTexts[id].french));
}


static void PushLocalizedChoice(const u8 *english, const u8 *french, u32 id)
{
    struct ListMenuItem item = { .name = FamilyLanguage_Select(english, french), .id = id };
    MultichoiceDynamic_PushElement(item);
}

void FamilyLanguage_BuildTmShopMainMenu(void)
{
    PushLocalizedChoice(COMPOUND_STRING("Buy"), COMPOUND_STRING("Acheter"), 0);
    PushLocalizedChoice(COMPOUND_STRING("Quit"), COMPOUND_STRING("Quitter"), 1);
}

void FamilyLanguage_BuildTmShopCategoryMenu(void)
{
    PushLocalizedChoice(COMPOUND_STRING("Support"), COMPOUND_STRING("Soutien"), 0);
    PushLocalizedChoice(COMPOUND_STRING("Weak"), COMPOUND_STRING("Faible"), 1);
    PushLocalizedChoice(COMPOUND_STRING("Powerful"), COMPOUND_STRING("Puissante"), 2);
    PushLocalizedChoice(COMPOUND_STRING("Ultimate"), COMPOUND_STRING("Ultime"), 3);
    PushLocalizedChoice(COMPOUND_STRING("Back"), COMPOUND_STRING("Retour"), 4);
}

static const u8 *const sTmTypesEnglish[] = {
    COMPOUND_STRING("Normal"), COMPOUND_STRING("Fighting"), COMPOUND_STRING("Flying"),
    COMPOUND_STRING("Poison"), COMPOUND_STRING("Ground"), COMPOUND_STRING("Rock"),
    COMPOUND_STRING("Bug"), COMPOUND_STRING("Ghost"), COMPOUND_STRING("Steel"),
    COMPOUND_STRING("Fire"), COMPOUND_STRING("Water"), COMPOUND_STRING("Grass"),
    COMPOUND_STRING("Electric"), COMPOUND_STRING("Psychic"), COMPOUND_STRING("Ice"),
    COMPOUND_STRING("Dragon"), COMPOUND_STRING("Dark"), COMPOUND_STRING("Back"),
};

static const u8 *const sTmTypesFrench[] = {
    COMPOUND_STRING("Normal"), COMPOUND_STRING("Combat"), COMPOUND_STRING("Vol"),
    COMPOUND_STRING("Poison"), COMPOUND_STRING("Sol"), COMPOUND_STRING("Roche"),
    COMPOUND_STRING("Insecte"), COMPOUND_STRING("Spectre"), COMPOUND_STRING("Acier"),
    COMPOUND_STRING("Feu"), COMPOUND_STRING("Eau"), COMPOUND_STRING("Plante"),
    COMPOUND_STRING("Électrik"), COMPOUND_STRING("Psy"), COMPOUND_STRING("Glace"),
    COMPOUND_STRING("Dragon"), COMPOUND_STRING("Ténèbres"), COMPOUND_STRING("Retour"),
};

static void BuildTmTypeMenu(const u8 *indices, u32 count)
{
    u32 i;
    for (i = 0; i < count; i++)
        PushLocalizedChoice(sTmTypesEnglish[indices[i]], sTmTypesFrench[indices[i]], i);
}

void FamilyLanguage_BuildTmShopSupportTypeMenu(void)
{
    static const u8 types[] = {0, 1, 2, 3, 5, 9, 10, 12, 13, 14, 16, 17};
    BuildTmTypeMenu(types, ARRAY_COUNT(types));
}

void FamilyLanguage_BuildTmShopWeakTypeMenu(void)
{
    static const u8 types[] = {0, 1, 2, 5, 6, 7, 8, 10, 11, 12, 14, 16, 17};
    BuildTmTypeMenu(types, ARRAY_COUNT(types));
}

void FamilyLanguage_BuildTmShopPowerfulTypeMenu(void)
{
    static const u8 types[] = {0, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17};
    BuildTmTypeMenu(types, ARRAY_COUNT(types));
}

void FamilyLanguage_BuildTmShopUltimateTypeMenu(void)
{
    static const u8 types[] = {0, 1, 8, 9, 11, 12, 14, 17};
    BuildTmTypeMenu(types, ARRAY_COUNT(types));
}

void FamilyLanguage_BuildItemShopMainMenu(void) { FamilyLanguage_BuildTmShopMainMenu(); }

void FamilyLanguage_BuildItemShopCategoryMenu(void)
{
    PushLocalizedChoice(COMPOUND_STRING("Evolution"), COMPOUND_STRING("Évolution"), 0);
    PushLocalizedChoice(COMPOUND_STRING("Strategic"), COMPOUND_STRING("Stratégie"), 1);
    PushLocalizedChoice(COMPOUND_STRING("Other"), COMPOUND_STRING("Autres"), 2);
    PushLocalizedChoice(COMPOUND_STRING("Back"), COMPOUND_STRING("Retour"), 3);
}

void FamilyLanguage_BuildItemShopEvolutionMenu(void)
{
    PushLocalizedChoice(COMPOUND_STRING("Stones"), COMPOUND_STRING("Pierres"), 0);
    PushLocalizedChoice(COMPOUND_STRING("Trade / Held"), COMPOUND_STRING("Échange / Tenu"), 1);
    PushLocalizedChoice(COMPOUND_STRING("Special / Regional"), COMPOUND_STRING("Spécial / Régional"), 2);
    PushLocalizedChoice(COMPOUND_STRING("Back"), COMPOUND_STRING("Retour"), 3);
}

void FamilyLanguage_BuildItemShopStrategicMenu(void)
{
    PushLocalizedChoice(COMPOUND_STRING("Type Boosters"), COMPOUND_STRING("Bonus de type"), 0);
    PushLocalizedChoice(COMPOUND_STRING("Choice / Offense"), COMPOUND_STRING("Choix / Attaque"), 1);
    PushLocalizedChoice(COMPOUND_STRING("Defense / Sustain"), COMPOUND_STRING("Défense / Soin"), 2);
    PushLocalizedChoice(COMPOUND_STRING("Weather / Terrain"), COMPOUND_STRING("Climat / Terrain"), 3);
    PushLocalizedChoice(COMPOUND_STRING("Activation / Utility"), COMPOUND_STRING("Activation / Utilité"), 4);
    PushLocalizedChoice(COMPOUND_STRING("Competitive Berries"), COMPOUND_STRING("Baies stratégiques"), 5);
    PushLocalizedChoice(COMPOUND_STRING("Back"), COMPOUND_STRING("Retour"), 6);
}

void FamilyLanguage_BuildItemShopOtherMenu(void)
{
    PushLocalizedChoice(COMPOUND_STRING("Training / Optimize"), COMPOUND_STRING("Training / Optimiser"), 0);
    PushLocalizedChoice(COMPOUND_STRING("Breeding / Friendship"), COMPOUND_STRING("Élevage / Bonheur"), 1);
    PushLocalizedChoice(COMPOUND_STRING("Other Useful"), COMPOUND_STRING("Autres objets utiles"), 2);
    PushLocalizedChoice(COMPOUND_STRING("Back"), COMPOUND_STRING("Retour"), 3);
}
