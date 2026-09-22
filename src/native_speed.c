#include "global.h"
#include "native_speed.h"
#include "event_data.h"
#include "main.h"
#include "palette.h"
#include "sound.h"
#include "link.h"
#include "bg.h"
#include "task.h"
#include "constants/vars.h"

#define NATIVE_SPEED_SAVE_TAG 0x5300

u32 GetNativeGameSpeed(void)
{
#if IS_HNS
    u16 value = VarGet(VAR_NATIVE_GAME_SPEED);
    if (value >= NATIVE_SPEED_SAVE_TAG && value < NATIVE_SPEED_SAVE_TAG + 4)
        return value - NATIVE_SPEED_SAVE_TAG + 1;
#endif
    return 1;
}

void SetNativeGameSpeed(u32 multiplier)
{
#if IS_HNS
    if (multiplier < 1 || multiplier > 4)
        multiplier = 1;
    VarSet(VAR_NATIVE_GAME_SPEED, NATIVE_SPEED_SAVE_TAG + multiplier - 1);
#endif
}

bool32 NativeSpeed_CanRunExtraTick(void)
{
    // Audio keeps its real hardware clock. State machines that explicitly
    // wait for a cry or fanfare still wait, while visual work stays smooth.
    return !gLinkTransferringData && !gReceivedRemoteLinkPlayers
        && !gWirelessCommType
        && !IsDma3ManagerBusyWithBgCopy();
}

void NativeSpeed_ClearInputEdges(void)
{
    // Action buttons belong to the physical input frame. Keep held directions
    // for simulation movement, but never let one A press confirm twice.
    gMain.newKeys = 0;
    gMain.newKeysRaw = 0;
    gMain.newAndRepeatedKeys = 0;
    gMain.heldKeys &= DPAD_ANY;
    gMain.heldKeysRaw &= DPAD_ANY;
}
