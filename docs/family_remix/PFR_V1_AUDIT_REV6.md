> **REV8 NOTICE — historical document.** For current Family Remix V1 encounter architecture and production status, use `PFR_V1_CAHIER_DES_CHARGES_FINAL_REV8.md`, `PFR_V1_AUDIT_REV8.md` and `data/family_remix/PFR_V1_ENCOUNTERS_FINAL_REV8.json`. Any instruction below that requires inherited HnS 12/5/10-slot layouts, five-slot water tables, 9%+1% splitting or native rod probability arrays is superseded and must not be used as a Family Remix design constraint.

# Pokémon Family Remix V1 — audit REV6

Audit baseline: branch `work/native-speed-starter-egg`, checkpoint `a670dce99024439cb48b43f6e1f09b4b7e25468c`.

## Owner-locked rules

- Family Remix is a fork of HnS. Inherited HnS code/data may and must be changed when it prevents the intended Family Remix behavior. Do not spend V1 time fixing unrelated upstream debt.
- NORMAL and HARD use the same Family Remix content and rosters. NORMAL is not vanilla HnS. Difficulty-specific optimization belongs to the difficulty layer: NORMAL keeps normal/native IV-EV scaling and normal/native AI; HARD uses IV31, role-optimized legal EVs and Family Remix HARD AI.
- Rocket boss progression: each scripted Rocket boss team is resolved at previous major boss/current cap +2; that value becomes the new cap. Consecutive Rocket bosses therefore chain +2. Evolution legality still applies.
- Safari remains 53 separate curated pools. Never flatten them into one giant table. The documented fallback session rotation is authoritative unless a compatible native HnS session mechanism is reused.

## Audit status

| Area | Status | Repository finding / V1 action |
| --- | --- | --- |
| Native x1/x2/x3/x4 | DONE | Implemented and documented; automated Native tests exist. Manual hardware/emulator edge cases remain release QA, not missing implementation. |
| Audio settings | DONE | Independent volume work and label landed; Audio regression group is in CI. |
| Starter + Elm egg | DONE | Shared selector, 31 target IDs, Eevee preference/rewards, PC overflow and progression handling are implemented and tested. |
| Shiny rates | DONE | Extended through 1/100 to guaranteed; retain regression coverage. |
| Standard encounters | DONE | V3 audit records 405 standard tables integrated. Active HnS table validation is now part of `tools/validate_family_remix.py`. |
| Route 28 inherited HnS data | DONE | Historical malformed water slots were normalized before this checkpoint; current Route 28 water table has five native slots. |
| Headbutt | DONE | Four dedicated 30/30/30/10 tables integrated without dropping species #4. |
| Safari 53 pools | À FAIRE | Data is staged, but JSON still says `safari: DEFERRED_NEEDS_ROTATION_RULE`. The rule now exists in the integration note; engine implementation is still missing. |
| Custom species | DONE / verify | Integration commits landed. Known final examples are present (Charizard Fire/Dragon, Sceptile Grass/Dragon, Haxorus Dragon/Steel, Electivire custom stats/type). Run final validator/build after remaining integration. |
| Custom learnsets | DONE / verify | Integration commits landed and active data was patched. Final build/regression still required. |
| Evolution gate | DONE | Family-stage minimum-level gate and tests exist. |
| Training NPC | DONE | EXP/EV/IV services landed with tests. |
| TM / item shops | DONE | 92 active HnS TMs and 172 categorized items are enforced by validator. |
| Fixed Johto/E4/Kanto boss roster | PARTIEL | 22 owner-locked HARD blocks are present and validated (127 Pokémon). They are still appended as HARD-specific parties; the common Family Remix NORMAL/HARD roster rule has not been fully propagated into the NORMAL party layer. |
| NORMAL difficulty | À CORRIGER | Repository still falls back to the pre-existing NORMAL trainer parties. Family Remix final roster/content must also be used in NORMAL, with normal/native IV-EV scaling and normal/native AI rather than HARD optimization. |
| HARD boss AI/EV | DONE / targeted QA | Fixed blocks have IV31, legal role EVs and fair strategic AI baseline; hidden-information AI flags are forbidden by validator. Run targeted battle QA after common-roster integration. |
| Rocket teams + dynamic +2 caps | À FAIRE | Current Rocket admin parties are inherited fixed-level HnS teams (e.g. Proton/Archer/Petrel/Ariana). The final dynamic +2 rule and Family Remix Rocket roster layer are not implemented at this checkpoint. |
| Level caps | PARTIEL / À CORRIGER | Major-boss cap system/tests exist, but tests still encode inherited Proton level 15 -> next cap 18 rather than the final dynamic Rocket rule. Rework progression and tests together. |
| Gym Guide strategy/Fresh Water | DONE | Johto/Kanto guide updates and one-time flags landed. |
| UI dark theme / battle & summary | DONE / manual QA | Multiple HnS UI redesign commits landed. Visual regression still needs manual ROM QA. |
| EN/FR localization | À FAIRE | New Family strings are mixed: starter notes explicitly report English species names with French new categories/dialogue, while shops and many new strings are English. Complete the intended EN/FR pass after gameplay strings stabilize. |
| CI/data validation | PARTIEL | Family validation workflow builds HnS and runs Level Cap, Evolution, Training, Audio, Settings, Native and Family tests. Add Safari, Rocket dynamic scaling and NORMAL/HARD common-roster tests when implemented. |
| Full V1 build/manual test | À FAIRE | Must be done after Safari + Rocket + common NORMAL/HARD roster + localization integration. |

## Important audit conclusions

1. The historical Route 28 12-slot water defect is no longer an open item at this checkpoint. The repository history contains the normalization commit and the current table is five slots.
2. The biggest semantic mismatch is now difficulty handling: the final fixed Family Remix boss roster exists only in the appended HARD blocks, while NORMAL still resolves its older party data. Do not solve this by deleting NORMAL or by making NORMAL competitively optimized. Share roster/content, not optimization.
3. Rocket is not final. Existing fixed-level Rocket parties are evidence of the inherited HnS implementation, not the final Family Remix rule.
4. Safari data is complete enough to implement: 53 pools are staged. The missing piece is engine/session selection.
5. Do not rewrite already-stable features merely because they originated in HnS. Change inherited behavior only where it conflicts with Family Remix or is malformed in the playable fork.

## Production order

1. Implement common Family Remix boss roster semantics for NORMAL/HARD while preserving difficulty-specific AI/IV-EV behavior.
2. Implement Family Remix Rocket teams and dynamic +2 cap chaining; update level-cap tests.
3. Implement the 53-pool Safari session rotation without flattening pools.
4. Add/extend validators and automated tests for the three systems above.
5. Run targeted HARD AI/boss regression and evolution legality checks.
6. Complete EN/FR localization of Family Remix-added player-facing strings.
7. Run full HnS build + all Family Remix CI groups, then manual mGBA gameplay/UI regression.
