> **REV8 NOTICE — historical document.** For current Family Remix V1 encounter architecture and production status, use `PFR_V1_CAHIER_DES_CHARGES_FINAL_REV8.md`, `PFR_V1_AUDIT_REV8.md` and `data/family_remix/PFR_V1_ENCOUNTERS_FINAL_REV8.json`. Any instruction below that requires inherited HnS 12/5/10-slot layouts, five-slot water tables, 9%+1% splitting or native rod probability arrays is superseded and must not be used as a Family Remix design constraint.

# Family Remix V1 — handoff REV6

Baseline audited branch: `work/native-speed-starter-egg` at `a670dce99024439cb48b43f6e1f09b4b7e25468c`.

REV6 is repository-native: the production data already lives in the branch. These documents define what is final, what is still missing, and the exact next production pass.

## Files

- `PFR_V1_AUDIT_REV6.md`: exact audited state and DONE/PARTIEL/À CORRIGER/À FAIRE matrix.
- `PFR_V1_DIFFICULTY_RULES_FINAL.md`: authoritative NORMAL/HARD and Rocket semantics.
- `PFR_V1_CODEX_INSTRUCTIONS_REV6.md`: executable production instructions for Codex.
- Existing live data remains authoritative where already integrated, especially `src/data/trainers_hns.party`, `src/data/wild_encounters.json`, `data/family_remix/special_encounter_pools.json`, species/learnset sources and shop scripts.

## Main deltas from REV5

- Confirms the historical Route 28 malformed water table is already fixed at the audited checkpoint.
- Identifies the real remaining difficulty mismatch: final Family Remix fixed boss rosters exist in HARD blocks but NORMAL still uses inherited party content.
- Identifies Rocket fixed HnS parties/tests as obsolete relative to the final +2 dynamic rule.
- Confirms Safari has complete staged data (53 pools) and a documented fallback rotation, but no engine integration yet.
- Keeps already integrated V1 work intact rather than asking Codex to regenerate it.

Do not interpret historical filenames containing “Hard” as meaning the roster is HARD-exclusive. The roster/content is shared; optimization is difficulty-specific.
