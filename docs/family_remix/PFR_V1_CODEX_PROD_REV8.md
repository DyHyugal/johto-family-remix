# CODEX — Family Remix V1 production continuation REV8

Repository: `DyHyugal/johto-family-remix`
Production branch: `work/native-speed-starter-egg`
Audited baseline: `e5c7191d66a798b3081fd81f95e9155086772c15`

Read first:
- `docs/family_remix/PFR_V1_CAHIER_DES_CHARGES_FINAL_REV8.md`
- `docs/family_remix/PFR_V1_AUDIT_REV8.md`
- `data/family_remix/PFR_V1_ENCOUNTERS_FINAL_REV8.json`

## Authority

REV8 supersedes REV6 for encounter architecture and current status. Do not restore native HnS encounter-slot constraints from older notes.

Family Remix is the HnS fork. If inherited engine structure conflicts with Family Remix design, change the fork.

## Task 1 — standard encounters: direct four-slot model

Current problem:
- the 405 standard Family Remix tables are logically 30/30/30/10 but are physically expanded into HnS 12/5/10-slot layouts;
- `tools/validate_family_remix.py` currently enforces those inherited lengths;
- `wild_encounters.json` audit metadata documents that workaround.

Required result:
- every Family Remix standard Land / Surf / Rock Smash / Fishing table is represented and selected as **exactly four logical species**;
- weights are **30, 30, 30, 10** directly;
- no species duplication to emulate old native weights;
- no 9+1 split;
- no Old/Good/Super Rod probability arrays as a Family Remix probability contract;
- use `PFR_V1_ENCOUNTERS_FINAL_REV8.json` as the source of truth.

Implementation freedom:
- adapt the HnS-specific encounter generator/group/selector as needed;
- preserve compilation for codepaths that still need non-HnS layouts;
- do not distort Family Remix data just to reuse inherited constants.

Fishing:
- preserve the authored four-species pool and 30/30/30/10;
- rods may still gate access/progression if required by gameplay, but may not change the authored Family Remix probabilities or require duplicate physical slots;
- do not invent new rod-specific species pools absent from REV8 data.

Update:
- encounter data;
- generated constants/structures if required;
- `tools/validate_family_remix.py`: validate exactly 4 slots and [30,30,30,10] for Family Remix logical tables, not native slot counts;
- audit metadata in `wild_encounters.json`;
- tests proving boundary rolls 0–29 / 30–59 / 60–89 / 90–99 for representative standard methods;
- tests that the 405 standard tables from REV8 are all represented exactly once logically.

Do not change the 53 Safari pools or 4 Headbutt tables except where interfaces must be unified. They already use the desired direct four-slot model.

## Task 2 — preserve completed REV6 production work

Do not regress:
- shared NORMAL/HARD Family Remix boss rosters;
- HARD IV31 + role EVs + fair strategic AI;
- NORMAL without HARD EV/AI optimization;
- Rocket final rosters + dynamic +2 levels + legal pre-evolutions;
- dynamic level caps;
- starter + Elm egg selector/rewards;
- native x1/x2/x3/x4;
- independent music/SFX;
- shiny rate choices through 1/1;
- Training NPC;
- TM/item shops;
- Gym Guide/Fresh Water;
- UI work.

## Task 3 — missing Shiny Only challenge

The final menu structure remains:
`Mode / Features / Randomizer / Nuzlocke / Difficulty / Challenges`.

Add a visible **SHINY ONLY** row in `Challenges`.
- Reuse the existing guaranteed-shiny logic when enabled; do not create a second independent shiny-generation system.
- Its state must save/load correctly.
- Avoid nested challenge submenus.
- Define interaction with the Features shiny-rate selector deterministically: when Shiny Only is ON, generated Pokémon are guaranteed shiny; turning it OFF returns control to the selected shiny-rate setting.
- Add tests for save/load and interaction with 1/1 / non-1/1 rates.

## Task 4 — localization cleanup in ROM

After gameplay code is stable:
- audit Family Remix-added player-facing strings;
- FR must use official French Pokémon/move/ability/item names where available;
- EN uses official English terminology;
- remove accidental mixed-language strings;
- do not fork gameplay behavior by language.

## Validation

At minimum:
- `python3 tools/validate_family_remix.py`
- `make hns -j4`
- existing Level Cap / Evolution / Training / Audio / Settings / Native / Family tests
- boss shared-roster tests
- Rocket tests
- Safari tests
- new standard four-slot encounter tests
- new Shiny Only tests

Then report:
1. commit(s);
2. exact files changed;
3. test/build results;
4. remaining manual mGBA checks;
5. any source datum that genuinely cannot be represented without changing engine code — and in that case change the engine rather than silently remapping the data.
