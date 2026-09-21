# Settings menu fixes and validation

## Audio

The user gain is applied in `TrkVolPitSet`, after the engine initializes a track,
independently of `volX`. Track starts, fades, cry ducking and battle-animation
volume commands therefore cannot reset it to full volume. The six gains are
0, 51, 102, 154, 205 and 256 out of 256. Music and SFX/cry gains are independent;
fanfares use the music gain. Muted players keep running so scripts waiting for
a sound, cry or fanfare still complete with the original timing. Music started
while muted can be made audible again without restarting the map.

Changing a slider invalidates every active PCM/PSG player, including all cry
players used in double battles. GBS applies the gain per hardware channel rather
than changing NR50, which is shared by music and effects. A zero gain disconnects
that channel from both speakers: NR50=0 alone is not silence on GBA. GBS tone and
noise amplitude is quantized to the hardware envelope resolution; wave samples
are scaled in wave RAM. Its previous full-volume attenuation is retained.

No save or assembly-visible structure was enlarged. ChallengeSettings remains
32 bytes. Uninitialized or invalid saved audio levels fall back to 20%.
Pre-new-game audio choices now survive the Oak-speech settings reset.

## Setup and later editing

During initial setup, A on RECOMMENDED, R from its first tab, or that tab's NEXT
commits the recommended defaults and returns directly to the existing new-game
continuation. No further challenge tabs or save confirmation are required.
Returning from Custom to Recommended discards challenge edits from that setup.
Custom keeps every detailed tab and its existing final save confirmation.

Options now includes CHALLENGE SETTINGS. Saving or cancelling that submenu
returns to Options, then back to its original caller. Mid-game lock policies
remain active, and editing settings no longer reseeds the trainer-ID timer.
The PC entry remains available.

## Reproduce validation

```sh
make hns -j8
make check BUILD=hns TESTS=Audio -j8
make check BUILD=hns TESTS=Settings -j8
```

The six targeted audio emulator tests pass and cover the independent volume steps, startup gain,
fade/duck composition, legacy save fallback, GBS hardware channel muting and
amplitude steps, and overlapping cries. The test runner needed its global types
included before fake_rtc.h to build on HnS. Three additional passing menu tests
exercise Recommended via A/R, resetting Custom edits, and the Options submenu
save/cancel round trip. The HnS production ROM also builds successfully.

Manual playback/UI checks still needed in mGBA:

- Open SOUND and compare all six steps for music, cursor effects and Pokédex
  cries, both with and without the GB Player. At SFX OFF, check battle effects,
  overlapping cries and healing. Music OFF must leave SFX audible and vice versa.
- Change volume during a sustained sound; change maps, hear a fanfare and a cry,
  then confirm music resumes at the chosen level. Save/reload and recheck.
- Start a fresh game with Recommended using A and R separately; verify no other
  challenge tabs appear. Explore Custom, change a challenge, return to Recommended
  and verify that challenge is not carried into the new game.
- Use Custom with Nuzlocke and Randomizer; verify all tabs and confirmation.
- In game, open Options > CHALLENGE SETTINGS, then save and cancel separately;
  check return to Options and then the field, plus existing mid-game locks.

## Native x2/x3/x4 feasibility

No speed multiplier is implemented in this change.

In `src/main.c`, AgbMain reads keys, executes the main callbacks, updates play
time and map music, then waits for VBlank. VBlankIntr performs graphics transfers,
link work, RNG advancement and m4aSoundMain; sound DMA/VSync is also tied to this
hardware cadence. Tasks, animations and many script waits count game frames.
`src/sound.c` additionally times fanfares in frames and waits for cry completion.
GBS SFX count hardware-rate ticks in `src/gbs.c`.

Repeating callbacks two to four times per VBlank would advance some timers but
not audio, interrupts or graphics transfers. It would also reuse input edges,
interfere with link synchronization and produce inconsistent audio-wait behavior.
Removing the VBlank wait or changing music tempo does not solve these problems.
Emulator fast-forward accelerates the emulated hardware clock, which ROM-side
music tempo compensation cannot generally undo for PCM samples or GBS channels.

A robust native implementation needs separate simulation, presentation and audio
clocks, explicit input-edge handling, audited script/audio waits, and exclusions
for link, saves and transitions. It also needs worst-case CPU profiling on GBA:
four simulation steps must still fit the frame budget. This is a larger engine
project, not a safe global menu toggle. Targeted walking/battle-animation speed
features could be investigated separately, with scene-specific tests; they would
not constitute a universal x2/x3/x4 mode.
