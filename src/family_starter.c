#include "global.h"
#include "family_starter.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "starter_choose.h"
#include "script_pokemon_util.h"
#include "script_menu.h"
#include "list_menu.h"
#include "event_data.h"
#include "string_util.h"
#include "malloc.h"
#include "item.h"
#include "challenge_menu.h"
#include "randomizer.h"
#include "constants/vars.h"
#include "constants/flags.h"
#include "constants/items.h"

// Menu specification only. Existing starter, species, evolution and item
// tables are deliberately not replaced or altered.
static const u16 sMenuSpecies[7][5] = {
    {SPECIES_CHARMANDER, SPECIES_TORCHIC, SPECIES_CHIMCHAR, SPECIES_CYNDAQUIL, SPECIES_CHARCADET},
    {SPECIES_MUDKIP, SPECIES_PIPLUP, SPECIES_FROAKIE, SPECIES_OSHAWOTT, SPECIES_HORSEA},
    {SPECIES_BULBASAUR, SPECIES_TREECKO, SPECIES_SNIVY, SPECIES_SPRIGATITO, SPECIES_GROOKEY},
    {SPECIES_ELEKID, SPECIES_MAGNEMITE, SPECIES_PAWMI, SPECIES_WATTREL, SPECIES_PICHU},
    {SPECIES_GLIGAR, SPECIES_DRILBUR, SPECIES_SANDILE, SPECIES_GOLETT, SPECIES_SANDYGAST},
    {SPECIES_VULPIX_ALOLA, SPECIES_SNORUNT, SPECIES_SWINUB, SPECIES_DARUMAKA_GALAR, SPECIES_VANILLITE},
    {SPECIES_EEVEE},
};

u16 FamilyStarter_GetCandidate(u32 category, u32 index)
{
    if (category >= ARRAY_COUNT(sMenuSpecies) || index >= ARRAY_COUNT(sMenuSpecies[0]))
        return SPECIES_NONE;
    return sMenuSpecies[category][index];
}

bool32 FamilyStarter_IsAvailable(u16 species)
{
    return species != SPECIES_NONE && species < NUM_SPECIES
        && gSpeciesInfo[species].baseHP != 0;
}

static bool32 UNUSED IsMenuSpecies(u16 species)
{
    u32 category, index;
    if (!FamilyStarter_IsAvailable(species))
        return FALSE;
    for (category = 0; category < ARRAY_COUNT(sMenuSpecies); category++)
        for (index = 0; index < ARRAY_COUNT(sMenuSpecies[0]); index++)
            if (sMenuSpecies[category][index] == species)
                return TRUE;
    return FALSE;
}

void FamilyStarter_UseMenu(void)
{
    gSpecialVar_0x8006 = SPECIES_NONE;
    gSpecialVar_Result = IS_HNS && !IsOneTypeChallengeActive();
#if RANDOMIZER_AVAILABLE
    if (RandomizerFeatureEnabled(RANDOMIZE_STARTER_AND_GIFT_MON))
        gSpecialVar_Result = FALSE;
#endif
}

static void PushChoice(const u8 *text, u16 id)
{
    struct ListMenuItem item;
    u8 *name = Alloc(StringLength(text) + 1);
    if (name == NULL)
        return;
    StringCopy(name, text);
    item.name = name;
    item.id = id;
    // The existing dynamic menu takes ownership of this copied string.
    MultichoiceDynamic_PushElement(item);
}

void FamilyStarter_BuildSpeciesMenu(void)
{
    u32 index;
    for (index = 0; index < ARRAY_COUNT(sMenuSpecies[0]); index++)
    {
        u16 species = FamilyStarter_GetCandidate(gSpecialVar_0x8004, index);
        if (FamilyStarter_IsAvailable(species))
            PushChoice(GetSpeciesName(species), species);
    }
    PushChoice(COMPOUND_STRING("Retour"), SPECIES_NONE);
}

void FamilyStarter_BuildEeveeMenu(void)
{
    const struct Evolution *evos = GetSpeciesEvolutions(SPECIES_EEVEE);
    u32 i;
    PushChoice(COMPOUND_STRING("Plus tard"), SPECIES_NONE);
    // Read existing stone evolutions. No invented mappings and no item grant.
    if (evos != NULL)
        for (i = 0; evos[i].method != EVOLUTIONS_END; i++)
            if (evos[i].method == EVO_ITEM && FamilyStarter_IsAvailable(evos[i].targetSpecies))
                PushChoice(GetSpeciesName(evos[i].targetSpecies), evos[i].targetSpecies);
}

static u16 UNUSED ValidEeveePreference(u16 species, u16 preference)
{
    const struct Evolution *evos = GetSpeciesEvolutions(SPECIES_EEVEE);
    u32 i;
    if (species == SPECIES_EEVEE && evos != NULL)
        for (i = 0; evos[i].method != EVOLUTIONS_END; i++)
            if (evos[i].method == EVO_ITEM && evos[i].targetSpecies == preference)
                return preference;
    return SPECIES_NONE;
}

// Integration hook: deliberately no item table or reward until finalized.
static void UNUSED OnStarterConfirmed(u16 species, bool32 isEgg, u16 evolutionPreference)
{
    (void)species;
    (void)isEgg;
    (void)evolutionPreference;
}

void FamilyStarter_RecordPrimary(void)
{
#if IS_HNS
    u16 species = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES);
    if (IsMenuSpecies(species))
    {
        u16 preference = ValidEeveePreference(species, gSpecialVar_0x8006);
        VarSet(VAR_FAMILY_STARTER_SPECIES, species);
        VarSet(VAR_FAMILY_STARTER_EVOLUTION, preference);
        OnStarterConfirmed(species, FALSE, preference);
    }
#endif
}

u16 FamilyStarter_GetPrimarySpecies(void)
{
#if IS_HNS
    u16 species = VarGet(VAR_FAMILY_STARTER_SPECIES);
    if (FlagGet(FLAG_SYS_POKEMON_GET) && IsMenuSpecies(species))
        return species;
#endif
    return GetStarterPokemon(VarGet(VAR_STARTER_MON));
}

void FamilyStarter_GiveEgg(void)
{
#if IS_HNS
    u16 species = gSpecialVar_0x8005;
    u16 preference = ValidEeveePreference(species, gSpecialVar_0x8006);
    u32 personality;
    u8 result;
    gSpecialVar_Result = MON_CANT_GIVE;
    if (VarGet(VAR_FAMILY_EGG_SPECIES) != SPECIES_NONE
     || !CheckBagHasItem(ITEM_MYSTERY_EGG, 1)
     || !IsMenuSpecies(species))
        return;
    result = ScriptGiveEgg(species);
    if (result == MON_CANT_GIVE)
        return;
    if (result == MON_GIVEN_TO_PC)
        personality = GetBoxMonData(GetBoxedMonPtr(gSpecialVar_MonBoxId, gSpecialVar_MonBoxPos), MON_DATA_PERSONALITY);
    else
        personality = GetMonData(&gPlayerParty[gPlayerPartyCount - 1], MON_DATA_PERSONALITY);
    // Conversion is committed only after the real egg has a party/PC slot.
    RemoveBagItem(ITEM_MYSTERY_EGG, 1);
    VarSet(VAR_FAMILY_EGG_SPECIES, species);
    VarSet(VAR_FAMILY_EGG_PERSONALITY_LO, personality);
    VarSet(VAR_FAMILY_EGG_PERSONALITY_HI, personality >> 16);
    VarSet(VAR_FAMILY_EGG_EVOLUTION, preference);
    FlagSet(FLAG_RECEIVED_TOGEPI_EGG);
    FlagClear(FLAG_HIDE_NEWBARKTOWN_LAB_AIDE);
    OnStarterConfirmed(species, TRUE, preference);
    gSpecialVar_Result = result;
#else
    gSpecialVar_Result = MON_CANT_GIVE;
#endif
}

void FamilyStarter_HasHatchedEgg(void)
{
    u32 i;
    u32 personality = VarGet(VAR_FAMILY_EGG_PERSONALITY_LO)
        | ((u32)VarGet(VAR_FAMILY_EGG_PERSONALITY_HI) << 16);
    gSpecialVar_Result = FALSE;
    if (VarGet(VAR_FAMILY_EGG_SPECIES) == SPECIES_NONE)
        return;
    for (i = 0; i < gPlayerPartyCount; i++)
        if (!GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG)
         && GetMonData(&gPlayerParty[i], MON_DATA_PERSONALITY) == personality
         && GetMonData(&gPlayerParty[i], MON_DATA_OT_ID) == READ_OTID_FROM_SAVE)
            gSpecialVar_Result = TRUE;
}
