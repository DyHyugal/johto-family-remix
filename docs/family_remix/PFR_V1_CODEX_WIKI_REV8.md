# CODEX — Family Remix Wiki follow-up REV8

Wiki branch: `wiki/family-remix-v1`
Current audited head: `c44f8bde95b811ff01a12173d2392c5cd5a83a81`

Run this phase **after** the production REV8 encounter refactor is pushed.

## Source authority

Use:
- production REV8 cahier;
- `PFR_V1_ENCOUNTERS_FINAL_REV8.json`;
- current integrated boss/species/learnset data.

Do not derive player-facing probabilities from old native HnS slot layouts.

## Required pass

1. **Localisations**
   - regenerate from the direct four-slot encounter source;
   - show rates 30/30/30/10;
   - keep day/night and method distinctions from the source;
   - do not expose native implementation slots.

2. **Pokédex**
   - keep current searchable structure;
   - verify search on desktop/mobile and with accents;
   - names FR/EN official;
   - links to Localisations remain correct.

3. **Changements**
   - keep the Pokémon presentation already added: sprite + name + type(s) + bullet list of changes;
   - ensure every final system/species/learnset/evolution/encounter/boss/convenience change is represented;
   - update encounter wording to the direct four-slot implementation, not a mapped approximation.

4. **Guide de jeu**
   - keep it as a practical playing guide, not an introduction/changelog.

5. **FR editorial pass**
   - remove mixed or broken wording still present, including examples currently visible such as `injeu`, `abusers`, `meilleur réponse`, `le initiative`, `jeu défensif`;
   - replace unnecessary English competitive jargon with natural French or explain it;
   - use official French Pokémon, move, ability and item names.

6. **Status**
   - regenerate `wiki/WIKI_V1_STATUS_REV7.md` as REV8 status;
   - reflect that boss sharing, Rocket and Safari are integrated;
   - do not leave stale ALMOST DONE entries for work already completed.

7. **Theme**
   - preserve the current in-game-matched dark/red/blue palette;
   - only adjust if visual review identifies a real mismatch.

Build/deploy and report the commit plus any remaining manual visual checks.
