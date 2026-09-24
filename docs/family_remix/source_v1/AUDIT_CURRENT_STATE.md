# Family Remix V1 — audit GitHub vs source of truth

Date: 2026-09-24

## Refs audited

- Production/work branch: `work/native-speed-starter-egg` @ `e5c7191d66a798b3081fd81f95e9155086772c15`
- Wiki branch: `wiki/family-remix-v1` @ `c44f8bde95b811ff01a12173d2392c5cd5a83a81`

## Status matrix

| Area | Current repo | Against FINAL source |
|---|---|---|
| Native x1/x2/x3/x4 | Implemented | DONE; keep manual QA |
| Audio independent volume | Implemented | DONE; keep manual QA |
| Starter + Elm egg | Implemented/tested | DONE, verify final menu wording/localization |
| Shiny rates | Implemented | DONE |
| Common NORMAL/HARD boss roster | Commit `bef45fcb6448` | DONE structurally; targeted gameplay QA still needed |
| HARD IV/EV/fair AI | Integrated | DONE / QA |
| Rocket rosters + dynamic +2 cap | Commit `18784da53197` | DONE structurally; gameplay/progression QA still needed |
| Safari 53-pool rotation | Commit `e5c7191d66a7` | DONE structurally; gameplay/session QA still needed |
| Standard encounters | 405 authored tables imported via native-slot mapping | **TO REFACTOR**: source data is correct but implementation must become four real slots at 30/30/30/10 |
| Headbutt | Dedicated four-species tables | KEEP, but align to common four-slot engine contract |
| Route 28 inherited-slot normalization | Validator/docs treat native slot count as a rule | **REMOVE AS DESIGN CONSTRAINT**; only four-slot Family Remix contract matters |
| Encounter validator | Validates inherited HnS slot counts and mapping metadata | **REWRITE** to validate 4 slots + [30,30,30,10] for Family Remix authored tables |
| Encounter handoff docs | Still mention native 12/5/10 slots / 9+1 / rod distributions | **REMOVE/REPLACE** |
| Custom species | Integrated | DONE / verify against final change log |
| Custom learnsets | Integrated | DONE / verify exhaustive change log |
| Evolution gate | Implemented | DONE |
| Training NPC | Implemented | DONE |
| TM/item shops | Implemented | DONE |
| Settings IA/menu structure | Current implementation predates final simplified labels/tree in places | PARTIAL; audit against final Gameplay/Features/Challenges/Difficulty/Audio/Save & Continue structure |
| EN/FR in ROM | Mixed historical/new strings remain possible | PARTIAL; official localization pass required |
| Wiki theme | Current CSS uses independently chosen night/red/gold palette | **TO CORRECT**: derive from actual game palette/assets |
| Wiki Guide | Improved but still needs full gameplay-guide framing/content audit | PARTIAL |
| Wiki Changes | Contains many changes but inventory is not locked exhaustively from final data | PARTIAL |
| Wiki Pokémon change rows | Table exists | PARTIAL; keep sprite/name/type/change presentation and ensure exhaustive data |
| Wiki Localisations | Shows 30/30/30/10 but was generated from flattened logical rows | DATA CONCEPT CORRECT; regenerate after engine/source refactor |
| Wiki Pokédex search | JS exists on current branch | VERIFY IN BROWSER; reported broken by owner |
| Wiki FR terminology | Major pass landed (Famignol etc.) | PARTIAL; run exhaustive official-name/move/item/ability pass |

## Critical correction

The historical import deliberately encoded four authored species into inherited HnS slot arrays. That is no longer an accepted implementation requirement. Refactor the engine/data interface so Family Remix authored tables are represented directly as four real entries with explicit rates [30,30,30,10].

Do not preserve native slot counts merely because the base engine originally used them.
