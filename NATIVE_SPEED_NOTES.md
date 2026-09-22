# Native speed investigation and validation

Base: feature/settings-menu, 129f5d487ed610f656aabe4d8d17c01aaa75d280.

Primary sources inspected on 2026-09-22:

- https://github.com/Eemeliri/soulgold/blob/master/README.md credits HashtagMarky for overworld speedup and Pokeabbie for battle speedup.
- https://github.com/Eemeliri/soulgold/blob/master/src/overworld.c repeats sprite/camera updates, excluding locked field controls. This is not a global hardware speed change.
- https://github.com/Eemeliri/soulgold/blob/master/src/battle_main.c repeats software battle ticks with callback, link and palette safeguards.
- https://github.com/Eemeliri/soulgold/blob/master/src/main.c keeps m4aSoundMain in VBlank and m4aSoundVSync in VCount. This establishes the software/audio clock separation in code; no claim is made about an official SoulSilver setting.

This implementation adapts the guarded logical-tick approach to HnS. It does not copy species, trainer, starter or item tables. GAME SPEED is a new Features row; the six Settings tabs and audio gain implementation are retained. Values are x1/x2/x3/x4, encoded in unused HnS variable 0x40E5 without enlarging the save. Old/invalid values default to x1. New-game initialization preserves the confirmed choice.

Extra ticks are restricted to the regular overworld and battle callbacks. They stop on callback transitions, a new physical frame, pending background transfers, fades, link activity, fanfares or cries. Field scripts/menus and recorded/frontier/link battles remain x1. Held battle inputs suspend acceleration. Input edges and repeats are consumed once per physical frame. The audio interrupt handlers, mixer and hardware clock are untouched.

Limits: x2/x3/x4 are maximum logical ticks per presented frame, not a guarantee of hardware throughput or a universal multiplier for every scene. Worst-case GBA CPU load, moving-map DMA behavior, capture effects, weather, followers, warp/encounter boundaries and real audio playback still require emulator/hardware validation. RNG continues to advance at the existing interrupt cadence; outcomes are not promised identical across speed settings.

Validation commands: `make hns -j2`; `make check BUILD=hns TESTS=Native -j2`; existing Audio and Settings tests. Windows session initially has no WSL, make or ARM toolchain. The dedicated validation workflow builds HnS and runs these test groups. A workflow definition or an unrun test is not a successful validation.
