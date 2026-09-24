# Family Remix V1 — difficulty rules FINAL

This file is authoritative for Family Remix difficulty semantics.

## Shared content

NORMAL and HARD are both Family Remix. They share the Family Remix gameplay/content layer: boss species/rosters, legal evolutions, movesets, held items, abilities, natures, encounters, species edits, learnsets, shops, progression and Family Remix features.

NORMAL must never silently fall back to a vanilla/inherited HnS boss roster merely because the final roster was first authored in a file/section historically named “Hard”.

## NORMAL

- Family Remix roster/content.
- Normal/native HnS difficulty behavior for AI.
- Normal/native IV/EV scaling/assignment rather than the competitive HARD optimization.
- No HARD-only omniscience/prediction behavior.

## HARD

- Same Family Remix roster/content.
- 31 IVs for fixed V1 bosses.
- Legal role-optimized EVs (max 252/stat, 510 total).
- Family Remix fair strategic AI baseline: Basic Trainer, Try To 2HKO, Smart Switching, HP Aware, PP Stall Prevention and Assumptions, plus strategy flags when justified by the team.
- Do not enable hidden-information/omniscient/prediction AI merely to increase difficulty.

## Healing items

Bosses use at most two healing items where the authored team provides them.

## Rocket and caps

Rocket boss level is not a static authored number. At each scripted Rocket boss encounter:

`rocketLevel = previousMajorBossOrCurrentCap + 2`

Every Pokémon on that Rocket boss team uses `rocketLevel`, subject to evolution legality. After that encounter is introduced into progression, `rocketLevel` becomes the new level cap/reference. Consecutive Rocket bosses therefore chain upward by +2.

Data may represent unresolved Rocket levels as dynamic/null. That is intentional and must not be treated as missing design data.
