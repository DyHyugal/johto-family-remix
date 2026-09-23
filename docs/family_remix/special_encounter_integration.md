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

The Family Remix Safari design is not a single static wild table per map. Each Safari sector has multiple curated pools (`safari_pool_a` ... `safari_pool_f`) that must remain individually selectable/rotatable.

Do **not** merge all pools into one giant land table.

Implementation requirement:
- choose the active pool using the existing/new Safari rotation state;
- active pool exposes exactly four species at 30/30/30/10;
- preserve the validated Johto level range 37–44;
- preserve the validated Kanto level range 68–76;
- do not duplicate the V3 Safari dataset during import.

## Standard encounters already integrated

The 405 standard Land / Surf / Rock Smash / Fishing tables have already been imported into `src/data/wild_encounters.json`.

Fishing slot policy:
- Old Rod: first two species, 70/30;
- Good Rod: first three species, 40/30/30;
- Super Rod: four species, 30/30/30/10.

Surf/Rock Smash use five native slots with weights 30/30/30/9/1; the fourth species occupies the final two slots to total 10%.
