#include "global.h"
#include "family_starter.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "event_data.h"
#include "item.h"
#include "daycare.h"
#include "constants/vars.h"
#include "constants/items.h"
#include "constants/flags.h"
#include "test/test.h"

#if IS_HNS
static void InitFamilyTest(void)
{
    InitEventData();
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    ClearBag();
    memset(&gSaveBlock3Ptr->challengeSettings, 0, sizeof(struct ChallengeSettings));
    // Settings stores OFF as 31; zero is TYPE_NONE, an active restriction.
    gSaveBlock3Ptr->challengeSettings.tx_Challenges_OneTypeChallenge = 31;
    CreateRandomMon(&gPlayerParty[0], SPECIES_EEVEE, 5);
    gPlayerPartyCount = 1;
    gSpecialVar_0x8005 = SPECIES_CHARCADET;
    gSpecialVar_0x8006 = SPECIES_NONE;
    AddBagItem(ITEM_MYSTERY_EGG, 1);
}

TEST("Family starter: all 31 menu entries have existing enabled species data")
{
    u32 category, index, count = 0;
    for (category = 0; category < 7; category++)
        for (index = 0; index < 5; index++)
        {
            u16 species = FamilyStarter_GetCandidate(category, index);
            if (species == SPECIES_NONE)
                continue;
            EXPECT(FamilyStarter_IsAvailable(species));
            count++;
        }
    EXPECT_EQ(count, 31);
    EXPECT_EQ(FamilyStarter_GetCandidate(7, 0), SPECIES_NONE);
    EXPECT_EQ(FamilyStarter_GetCandidate(0, 5), SPECIES_NONE);
    EXPECT(!FamilyStarter_IsAvailable(SPECIES_NONE));
    EXPECT(!FamilyStarter_IsAvailable(NUM_SPECIES));
}

TEST("Family starter: cancel or invalid choice preserves the mystery egg")
{
    InitFamilyTest();
    gSpecialVar_0x8005 = SPECIES_NONE;
    FamilyStarter_GiveEgg();
    EXPECT_EQ(gSpecialVar_Result, MON_CANT_GIVE);
    EXPECT(CheckBagHasItem(ITEM_MYSTERY_EGG, 1));
    EXPECT_EQ(gPlayerPartyCount, 1);
    EXPECT_EQ(VarGet(VAR_FAMILY_EGG_SPECIES), SPECIES_NONE);
    EXPECT(!FlagGet(FLAG_RECEIVED_TOGEPI_EGG));
}

TEST("Family starter: primary Eevee remembers only an existing stone evolution")
{
    InitFamilyTest();
    gSpecialVar_0x8006 = SPECIES_VAPOREON;
    FamilyStarter_RecordPrimary();
    FlagSet(FLAG_SYS_POKEMON_GET);
    EXPECT_EQ(FamilyStarter_GetPrimarySpecies(), SPECIES_EEVEE);
    EXPECT_EQ(VarGet(VAR_FAMILY_STARTER_EVOLUTION), SPECIES_VAPOREON);
    EXPECT(CheckBagHasItem(ITEM_WATER_STONE, 1));
    gSpecialVar_0x8006 = SPECIES_CHARCADET;
    FamilyStarter_RecordPrimary();
    EXPECT_EQ(VarGet(VAR_FAMILY_STARTER_EVOLUTION), SPECIES_NONE);
}

TEST("Family starter: Eevee egg stores its existing stone evolution preference")
{
    InitFamilyTest();
    gSpecialVar_0x8005 = SPECIES_EEVEE;
    gSpecialVar_0x8006 = SPECIES_VAPOREON;
    FamilyStarter_GiveEgg();
    EXPECT_EQ(gSpecialVar_Result, MON_GIVEN_TO_PARTY);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_SPECIES), SPECIES_EEVEE);
    EXPECT_EQ(VarGet(VAR_FAMILY_EGG_EVOLUTION), SPECIES_VAPOREON);
    EXPECT(CheckBagHasItem(ITEM_WATER_STONE, 1));
}

TEST("Family starter: Charcadet branch grants its selected stone")
{
    InitFamilyTest();
    gSpecialVar_0x8006 = SPECIES_ARMAROUGE;
    FamilyStarter_GiveEgg();
    EXPECT_EQ(gSpecialVar_Result, MON_GIVEN_TO_PARTY);
    EXPECT_EQ(VarGet(VAR_FAMILY_EGG_EVOLUTION), SPECIES_ARMAROUGE);
    EXPECT(CheckBagHasItem(ITEM_FIRE_STONE, 1));
    EXPECT(!CheckBagHasItem(ITEM_DUSK_STONE, 1));
}

TEST("Family starter: rival uses a Ground starter against Electric")
{
    u16 rival;
    InitFamilyTest();
    CreateRandomMon(&gPlayerParty[0], SPECIES_ELEKID, 5);
    FamilyStarter_RecordPrimary();
    rival = VarGet(VAR_FAMILY_RIVAL_SPECIES);
    EXPECT(rival == SPECIES_GLIGAR
        || rival == SPECIES_DRILBUR
        || rival == SPECIES_SANDILE
        || rival == SPECIES_GOLETT
        || rival == SPECIES_SANDYGAST);
    EXPECT_EQ(FamilyStarter_GetRivalSpecies(SPECIES_CHIKORITA), rival);
    EXPECT(FamilyStarter_IsAvailable(FamilyStarter_GetRivalSpecies(SPECIES_BAYLEEF)));
    VarSet(VAR_FAMILY_RIVAL_SPECIES, SPECIES_NONE);
    EXPECT_EQ(FamilyStarter_GetRivalSpecies(SPECIES_CHIKORITA), SPECIES_CHIKORITA);
}

TEST("Family starter: monotype keeps the historical rival selection")
{
    InitFamilyTest();
    gSaveBlock3Ptr->challengeSettings.tx_Challenges_OneTypeChallenge = TYPE_FIRE;
    CreateRandomMon(&gPlayerParty[0], SPECIES_CYNDAQUIL, 5);
    FamilyStarter_RecordPrimary();
    EXPECT_EQ(VarGet(VAR_FAMILY_RIVAL_SPECIES), SPECIES_NONE);
    EXPECT_EQ(FamilyStarter_GetRivalSpecies(SPECIES_CHIKORITA), SPECIES_CHIKORITA);
}

TEST("Family starter: the actual selected egg is granted exactly once")
{
    u32 isEgg = FALSE;
    InitFamilyTest();
    FamilyStarter_GiveEgg();
    EXPECT_EQ(gSpecialVar_Result, MON_GIVEN_TO_PARTY);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_SPECIES), SPECIES_CHARCADET);
    EXPECT(GetMonData(&gPlayerParty[1], MON_DATA_IS_EGG));
    EXPECT_EQ(VarGet(VAR_FAMILY_EGG_SPECIES), SPECIES_CHARCADET);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_FRIENDSHIP), 0);
    EXPECT_EQ(gSaveBlock1Ptr->daycare.stepCounter, 255);
    EXPECT(!CheckBagHasItem(ITEM_MYSTERY_EGG, 1));
    EXPECT(FlagGet(FLAG_RECEIVED_TOGEPI_EGG));
    FamilyStarter_HasHatchedEgg();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    FamilyStarter_GiveEgg();
    EXPECT_EQ(gSpecialVar_Result, MON_CANT_GIVE);
    EXPECT_EQ(gPlayerPartyCount, 2);
    SetMonData(&gPlayerParty[1], MON_DATA_IS_EGG, &isEgg);
    FamilyStarter_HasHatchedEgg();
    EXPECT_EQ(gSpecialVar_Result, TRUE);
}

TEST("Family starter: selected party egg is ready to hatch on the next step")
{
    InitFamilyTest();
    FamilyStarter_GiveEgg();
    EXPECT(ShouldEggHatch());
    EXPECT_EQ(gSpecialVar_0x8004, 1);
}

TEST("Family starter: party limit one sends the egg to the PC")
{
    struct BoxPokemon *egg;
    InitFamilyTest();
    gSaveBlock3Ptr->challengeSettings.tx_Challenges_PartyLimit = 5;
    FamilyStarter_GiveEgg();
    EXPECT_EQ(gSpecialVar_Result, MON_GIVEN_TO_PC);
    EXPECT_EQ(gPlayerPartyCount, 1);
    egg = GetBoxedMonPtr(gSpecialVar_MonBoxId, gSpecialVar_MonBoxPos);
    EXPECT_EQ(GetBoxMonData(egg, MON_DATA_SPECIES), SPECIES_CHARCADET);
    EXPECT(GetBoxMonData(egg, MON_DATA_IS_EGG));
    EXPECT_EQ(GetBoxMonData(egg, MON_DATA_FRIENDSHIP), 0);
}

TEST("Family starter: monotype restriction sends an incompatible egg to the PC")
{
    InitFamilyTest();
    gSaveBlock3Ptr->challengeSettings.tx_Challenges_OneTypeChallenge = TYPE_WATER;
    FamilyStarter_GiveEgg();
    EXPECT_EQ(gSpecialVar_Result, MON_GIVEN_TO_PC);
    EXPECT_EQ(gPlayerPartyCount, 1);
    EXPECT_EQ(VarGet(VAR_FAMILY_EGG_SPECIES), SPECIES_CHARCADET);
}

TEST("Family starter: full party and PC leave the egg and progression unchanged")
{
    u32 box, slot;
    InitFamilyTest();
    gSaveBlock3Ptr->challengeSettings.tx_Challenges_PartyLimit = 5;
    for (box = 0; box < TOTAL_BOXES_COUNT; box++)
        for (slot = 0; slot < IN_BOX_COUNT; slot++)
            *GetBoxedMonPtr(box, slot) = gPlayerParty[0].box;
    FamilyStarter_GiveEgg();
    EXPECT_EQ(gSpecialVar_Result, MON_CANT_GIVE);
    EXPECT(CheckBagHasItem(ITEM_MYSTERY_EGG, 1));
    EXPECT_EQ(VarGet(VAR_FAMILY_EGG_SPECIES), SPECIES_NONE);
    EXPECT(!FlagGet(FLAG_RECEIVED_TOGEPI_EGG));
}
#endif
