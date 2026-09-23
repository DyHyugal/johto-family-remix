#include "global.h"
#include "battle_setup.h"
#include "caps.h"
#include "event_data.h"
#include "pokemon.h"
#include "training_npc.h"
#include "test/test.h"

#if IS_HNS
static u32 GetTestBossLevel(u16 trainerId, bool8 useLowestLevel)
{
    switch (trainerId)
    {
    case TRAINER_RIVAL_CHIKORITA_1_HNS:
    case TRAINER_RIVAL_CYNDAQUIL_1_HNS:
    case TRAINER_RIVAL_TOTODILE_1_HNS:
        return 5;
    case TRAINER_FALKNER_1_HNS:
        return useLowestLevel ? 8 : 11;
    case TRAINER_PROTON_1_HNS:
        return useLowestLevel ? 12 : 15;
    case TRAINER_RIVAL_CHIKORITA_2_HNS:
    case TRAINER_RIVAL_CYNDAQUIL_2_HNS:
    case TRAINER_RIVAL_TOTODILE_2_HNS:
        return useLowestLevel ? 15 : 18;
    case TRAINER_BUGSY_1_HNS:
        return useLowestLevel ? 15 : 16;
    case TRAINER_WHITNEY_1_HNS:
        return useLowestLevel ? 20 : 21;
    case TRAINER_LTSURGE_HNS:
        return useLowestLevel ? 57 : 60;
    case TRAINER_RED_HNS:
        return useLowestLevel ? 77 : 93;
    default:
        return 1;
    }
}

static void SetLevelCapMode(u8 mode)
{
    SetLevelCapTrainerLevelGetterForTesting(GetTestBossLevel);
    gSaveBlock3Ptr->challengeSettings.tx_Challenges_LevelCap = mode;
}

TEST("Level cap: Falkner is the first HnS milestone")
{
    SetLevelCapMode(1);
    EXPECT_EQ(GetCurrentLevelCap(), 11);

    SetLevelCapMode(2);
    EXPECT_EQ(GetCurrentLevelCap(), 8);
}

TEST("Level cap: defeating a major fight selects the next actual boss")
{
    SetLevelCapMode(1);
    SetTrainerFlag(TRAINER_RIVAL_CYNDAQUIL_1_HNS);
    EXPECT_EQ(GetCurrentLevelCap(), 11);

    FlagSet(FLAG_DEFEATED_VIOLET_GYM);
    EXPECT_EQ(GetCurrentLevelCap(), 15);

    SetTrainerFlag(TRAINER_PROTON_1_HNS);
    EXPECT_EQ(GetCurrentLevelCap(), 18);
}

TEST("Level cap: progression never moves backwards after a stronger boss")
{
    SetLevelCapMode(1);
    SetTrainerFlag(TRAINER_RIVAL_CYNDAQUIL_1_HNS);
    FlagSet(FLAG_DEFEATED_VIOLET_GYM);
    SetTrainerFlag(TRAINER_PROTON_1_HNS);
    SetTrainerFlag(TRAINER_RIVAL_CYNDAQUIL_2_HNS);

    // Bugsy's current ace is lower than Silver's, so Silver remains the floor.
    EXPECT_EQ(GetCurrentLevelCap(), 18);
    FlagSet(FLAG_DEFEATED_AZALEA_TOWN_GYM);
    EXPECT_EQ(GetCurrentLevelCap(), 21);
}

TEST("Level cap: hard mode uses the next boss party's lowest level")
{
    SetLevelCapMode(2);
    SetTrainerFlag(TRAINER_RIVAL_CYNDAQUIL_1_HNS);
    EXPECT_EQ(GetCurrentLevelCap(), 8);

    FlagSet(FLAG_DEFEATED_VIOLET_GYM);
    EXPECT_EQ(GetCurrentLevelCap(), 12);
}

TEST("Level cap: league transitions use Kanto, Red, then the engine maximum")
{
    SetLevelCapMode(1);
    FlagSet(FLAG_IS_CHAMPION);
    EXPECT_EQ(GetCurrentLevelCap(), 60);

    FlagSet(FLAG_IS_KANTO_CHAMPION);
    EXPECT_EQ(GetCurrentLevelCap(), 93);

    FlagSet(FLAG_DEFEATED_RED);
    EXPECT_EQ(GetCurrentLevelCap(), MAX_LEVEL);
}

TEST("Level cap: EXP Training reads the live boss cap")
{
    SetLevelCapMode(1);
    ZeroPlayerPartyMons();
    CreateRandomMon(&gPlayerParty[0], SPECIES_BULBASAUR, 2);
    gPlayerPartyCount = 1;
    gSpecialVar_0x8004 = 0;
    gSpecialVar_0x8005 = TRAINING_EXP_TO_CAP;

    TrainingNpc_ApplyExp();

    EXPECT_EQ(gSpecialVar_Result, TRAINING_RESULT_SUCCESS);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 11);
}
#endif
