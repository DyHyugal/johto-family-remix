# CODEX — Family Remix V1 continuation after source cleanup

Repository: `DyHyugal/johto-family-remix`
Production branch to update: `work/native-speed-starter-egg`
Clean handoff branch to read: `handoff/v1-clean-source-2026-09-24`

Read first:
1. `docs/family_remix/source_v1/SOURCE_OF_TRUTH_FINAL.md`
2. `docs/family_remix/source_v1/AUDIT_CURRENT_STATE.md`
3. `data/family_remix/source_v1/encounters_standard_final.json`
4. `data/family_remix/source_v1/encounters_special_final.json`
5. existing final difficulty rules and live integrated boss/species/learnset data.

## Non-negotiable change in interpretation

The 4-species encounter tables are the real design. The old HnS slot counts are NOT constraints.

Every Family Remix authored encounter table must be represented and selected as exactly:
- slot 1 = 30%
- slot 2 = 30%
- slot 3 = 30%
- slot 4 = 10%

Do not:
- duplicate species to fill 12 land slots;
- pad water/Rock Smash into 5 slots;
- split 10% into 9% + 1%;
- preserve Old/Good/Super Rod slot-count distributions as a design requirement.

Refactor the Family Remix HnS encounter path so the four-slot source is native to this fork. Change inherited HnS code/config/constants where required. Keep unrelated Emerald/frontier encounter systems intact.

## Block A — four-slot encounter engine/data refactor

- Import the 405 standard tables directly from `encounters_standard_final.json`.
- Make Family Remix HnS Land, Water/Surf, Rock Smash and Fishing selection consume four slots with rates 30/30/30/10.
- Keep authored Day/Night distinctions only where the source has them.
- Fishing is one authored four-species table per source row; do not rebuild the previous native rod-slot mapping.
- Keep the 4 Headbutt tables and 53 Safari pools as four-slot 30/30/30/10 data.
- Preserve Safari sector/session rotation; only remove unnecessary native-slot translation.
- Remove stale encounter audit metadata that describes 12/5/10 native grouping.
- Rewrite `tools/validate_family_remix.py` to validate the Family Remix four-slot contract rather than inherited HnS slot lengths.
- Add focused tests proving exact probabilities/table shape for representative Land, Surf, Rock Smash, Fishing, Headbutt and Safari cases.
- Recheck Route 28 under the new contract; do not keep a special "five native slots" rule.

## Block B — regression after encounter refactor

Do not redo completed systems. Regress:
- common NORMAL/HARD roster semantics;
- HARD IV31/legal EV/fair AI;
- Rocket dynamic +2 caps/evolution legality;
- Safari rotation;
- starters + Elm egg;
- shiny settings;
- native speed;
- audio;
- level caps;
- Training NPC;
- shops;
- custom species/learnsets.

Fix Family Remix regressions only.

## Block C — final Settings/menu audit

Compare live menus against the owner-approved player-facing structure:
Gameplay / Features / Challenges / Difficulty / Audio / Save & Continue.

Challenges should expose Nuzlocke / Shiny Only / Randomizer without redundant submenu nesting. Preserve already-working save compatibility and settings behavior.

## Block D — localization

Run a complete FR player-facing localization audit:
- official French Pokémon names;
- official move names;
- official abilities;
- official items;
- official types/trainers where localized.
Do not machine-translate canonical Pokémon terms.
Keep ENG pages/strings English.

## Block E — wiki/data sync

On the wiki branch (or a dedicated wiki follow-up branch):
- derive CSS palette from the actual in-game Family Remix UI assets, not the independent night/red/gold palette;
- make Guide de jeu a real gameplay guide;
- make Changements exhaustive from final integrated data;
- Pokémon-change presentation = sprite + name + type + bullet list of changes;
- regenerate Localisations from the clean four-slot encounter sources;
- fix and browser-test Pokédex search (FR + EN alias matching);
- exhaustively remove remaining English canonical terms from FR pages.

## Validation

At minimum:
- `python3 tools/validate_family_remix.py`
- `make hns -j4`
- existing Level Cap, Evolution, Training, Audio, Settings, Native and Family groups
- Rocket tests
- Safari tests
- new EncounterFourSlot tests
- targeted NORMAL/HARD boss roster tests

Then manual mGBA smoke checks for encounters, rods/fishing behavior, Safari rotation, settings, audio, native speed and representative boss battles.

Commit/push each coherent block. Do not overwrite newer valid work. If the production branch advanced, reconcile instead of resetting.
