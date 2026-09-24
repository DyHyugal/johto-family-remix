> **REV8 NOTICE — historical document.** For current Family Remix V1 encounter architecture and production status, use `PFR_V1_CAHIER_DES_CHARGES_FINAL_REV8.md`, `PFR_V1_AUDIT_REV8.md` and `data/family_remix/PFR_V1_ENCOUNTERS_FINAL_REV8.json`. Any instruction below that requires inherited HnS 12/5/10-slot layouts, five-slot water tables, 9%+1% splitting or native rod probability arrays is superseded and must not be used as a Family Remix design constraint.

# Family Remix special encounters — integration notes

This file documents the 57 encounter tables intentionally **not** flattened into `src/data/wild_encounters.json`.

Source data:
- `data/family_remix/special_encounter_pools.json`
- 4 Headbutt tables
- 53 Safari rotation pools
- every pool keeps the validated 30/30/30/10 design.

## Headbutt

The current engine exposes `hiddenMonsInfo` / `HIDDEN_WILD_COUNT = 3`, while the Family Remix design has four species per Headbutt table.

Do **not** silently drop the fourth species.

Preferred implementation:
1. either extend the hidden/headbutt table to four logical species with weights 30/30/30/10;
2. or add a dedicated HnS Headbutt selector that reads the four-species pool directly.

Maps concerned are listed in the JSON.

## Safari

The Family Remix Safari design is integrated through `src/family_safari.c` and the generated
`src/data/family_remix_safari.h`. It is not a single static wild table per map. Each Safari sector has multiple curated pools (`safari_pool_a` ... `safari_pool_f`) that must remain individually selectable/rotatable.

Do **not** merge all pools into one giant land table.

Implemented session rule:
- Family Remix provides one session rotation counter; start a Safari session on pool A, then advance the active pool after each Safari wild encounter; wrap A→E on Johto sectors and A→F on Kanto sectors;
- use one session-level rotation counter and apply modulo the pool count of the current sector; resetting a new Safari admission to pool A is acceptable;
- active pool exposes exactly four species at 30/30/30/10;
- changing sector must not discard or merge curated pools;
- preserve the validated Johto level range 37–44;
- preserve the validated Kanto level range 68–76;
- do not duplicate the V3 Safari dataset during import.

This fallback is a Family Remix behavior. It may require changing native HnS Safari/encounter code in this fork; that is allowed when needed to make the Family Remix ROM correct.

## Standard encounters already integrated

The 405 standard Land / Surf / Rock Smash / Fishing tables have already been imported into `src/data/wild_encounters.json`.

Fishing slot policy:
- Old Rod: first two species, 70/30;
- Good Rod: first three species, 40/30/30;
- Super Rod: four species, 30/30/30/10.

Surf/Rock Smash use five native slots with weights 30/30/30/9/1; the fourth species occupies the final two slots to total 10%.
