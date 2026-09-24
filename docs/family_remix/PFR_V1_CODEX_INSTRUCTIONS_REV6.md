# CODEX — Family Remix V1 production continuation REV6

Work only on repository `DyHyugal/johto-family-remix`, branch `work/native-speed-starter-egg`.

Baseline audited checkpoint: `a670dce99024439cb48b43f6e1f09b4b7e25468c`.

Before editing, fetch/pull and verify the current branch tip. If the branch advanced after the audited checkpoint, preserve newer valid work and reconcile it with these instructions instead of resetting it.

Read first:
- `docs/family_remix/PFR_V1_AUDIT_REV6.md`
- `docs/family_remix/PFR_V1_DIFFICULTY_RULES_FINAL.md`
- `docs/family_remix/special_encounter_integration.md`
- `data/family_remix/special_encounter_pools.json`
- `tools/validate_family_remix.py`
- `FAMILY_STARTER_NOTES.md`
- `NATIVE_SPEED_NOTES.md`

## Non-negotiable interpretation

Family Remix is our HnS fork. HnS is the base, not a protected upstream boundary. If inherited HnS code/data makes the Family Remix ROM wrong, modify it in this fork. Do not spend V1 time repairing unrelated upstream debt.

NORMAL and HARD must use the SAME Family Remix content/rosters. NORMAL is not vanilla HnS. Keep the authored Family Remix species, roster, moves, held items, abilities and natures in both modes. Difficulty is primarily the optimization layer:
- NORMAL = Family Remix roster/content + normal/native AI + normal/native IV/EV scaling.
- HARD = same roster/content + IV31 + role-optimized legal EVs + Family Remix fair strategic AI.

Do not copy HARD optimized EVs/AI into NORMAL just to make roster sharing easy.

## Block A — fix common boss roster semantics

The audited checkpoint has 22 final fixed Family Remix boss blocks appended as HARD parties, while NORMAL still resolves inherited/older party data.

Refactor/integrate so the 22 fixed Family Remix boss rosters are the content source for BOTH NORMAL and HARD. Preserve the intended difficulty-specific IV/EV and AI behavior.

Do not change owner-locked roster choices opportunistically. Existing validator locks such as Jolteon @ Focus Sash, Kingdra @ Scope Lens, Honchkrow @ Life Orb, Magnezone @ Choice Specs, Exeggutor @ Choice Specs and Ancient Power must remain consistent with the final data.

Add validation/tests proving at least:
1. representative NORMAL and HARD boss encounters resolve the same species roster;
2. NORMAL does not receive HARD optimized EV/AI behavior;
3. HARD retains IV31/legal optimized EVs and fair strategic AI.

## Block B — Rocket + dynamic caps

Current Rocket admins are inherited fixed-level HnS parties and are NOT final.

Implement the final Family Remix Rocket teams from the owner-locked handoff/data available in the repository/history. Do not invent a replacement roster if an authored final roster exists.

For every scripted Rocket boss encounter:
- derive one team level from previous major boss/current cap +2;
- assign that level to the whole Rocket boss team;
- that level becomes the new cap/reference;
- consecutive Rocket bosses chain +2;
- enforce legal evolution stages at the resolved level.

Update `test/level_caps.c`: the current inherited Proton 12–15 assumptions and “Proton defeated -> cap 18” behavior are obsolete under the final rule.

Add focused tests for first Rocket escalation, consecutive Rocket escalation, new cap persistence, and evolution legality.

## Block C — Safari 53 pools

Implement the staged 53 Safari pools from `data/family_remix/special_encounter_pools.json`.

Never flatten them into a giant static encounter table.

Prefer a compatible native HnS Safari session state if one exists. Otherwise implement the already documented Family Remix fallback in `docs/family_remix/special_encounter_integration.md`:
- session begins on pool A;
- after each Safari wild encounter advance the session pool counter;
- wrap modulo the number of pools for the current sector;
- Johto sectors use their authored A-E sets; Kanto sectors may use A-F where authored;
- changing sector must preserve the session rotation concept and never merge curated pools;
- active pool exposes exactly four species with 30/30/30/10;
- preserve authored levels (Johto 37–44, Kanto 68–76);
- reset to A on a new Safari admission is acceptable.

After implementation update the special encounter JSON status from deferred to integrated and extend `tools/validate_family_remix.py` + CI tests accordingly.

## Block D — regression of integrated V1 data

Do not redo working systems. Verify them after A-C:
- 405 standard encounter tables;
- 4 Headbutt tables;
- active HnS encounter slot validation, including Route 28 five-slot water data;
- custom species and custom learnsets;
- evolution gate;
- Training NPC;
- categorized TM shop (92 unique active HnS TMs);
- categorized item shop (172 unique entries, no progression-bypass medicine/balls);
- starter + Elm egg flow;
- shiny rate settings;
- native x1/x2/x3/x4;
- independent audio settings/volume label;
- Gym Guide/Fresh Water progression;
- UI changes.

Fix regressions that affect Family Remix. Do not broaden scope into unrelated HnS cleanup.

## Block E — targeted battle QA

Run automated checks first. Then inspect representative HARD teams for:
- lead/setup intent;
- weather/terrain synergy;
- legal moves/items/abilities;
- max two healing items;
- no hidden-information AI;
- no impossible evolution for the encounter level.

Keep the authored strategy unless there is a concrete legality/runtime bug.

## Block F — EN/FR localization

After gameplay strings stabilize, complete the player-facing Family Remix localization pass. The checkpoint still contains mixed new FR/EN strings (starter flow vs English shops/species display). Reuse the project's localization architecture where available; do not fork gameplay logic per language.

## Block G — validation and delivery

At minimum run:
`python3 tools/validate_family_remix.py`
`make hns -j4`
`make check BUILD=hns TESTS='*Level cap:' -j4`
`make check BUILD=hns TESTS='*Evolution requirements:' -j4`
`make check BUILD=hns TESTS='*Training NPC:' -j4`
`make check BUILD=hns TESTS=Audio -j4`
`make check BUILD=hns TESTS=Settings -j4`
`make check BUILD=hns TESTS=Native -j4`
`make check BUILD=hns TESTS=Family -j4`

Also run the new boss-common-roster, Rocket and Safari tests you add.

If a test/build fails, diagnose and fix it; do not mark the block DONE because a test file exists.

Commit in coherent blocks and push to `origin/work/native-speed-starter-egg`. Do not touch the wiki branch in this production pass.

Final report must include:
- branch and final SHA;
- commits created;
- exact tests/builds run and pass/fail;
- DONE / PARTIEL / À CORRIGER / À FAIRE table updated from REV6;
- any manual mGBA checks still required;
- any true blocker with file/function and evidence.

Do not stop after each block waiting for user confirmation. If one block is blocked, document the blocker, continue independent blocks, and return the complete report at the end.
