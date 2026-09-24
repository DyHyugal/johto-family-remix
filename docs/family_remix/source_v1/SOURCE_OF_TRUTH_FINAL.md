# Pokémon Family Remix V1 — SOURCE OF TRUTH FINAL

Date: 2026-09-24

This file replaces ambiguous historical handoff wording. It contains design intent, not inherited HnS implementation constraints.

## 1. Repository rule

Family Remix is our HnS fork. HnS is the base, not a protected boundary. If inherited HnS code/data prevents the intended Family Remix behavior, change it in this fork. Do not spend V1 time repairing unrelated upstream debt.

## 2. Encounters — authoritative rule

- Every active encounter table uses **exactly 4 real slots**.
- Rates are always **30% / 30% / 30% / 10%**.
- This rule applies to authored Land/grass/ground, Surf/water, Rock Smash, Fishing, Headbutt and active Safari pools.
- Do **not** duplicate species to fill 12/5/10 inherited HnS slots.
- Do **not** split the 10% species into 9% + 1%.
- Do **not** keep Old/Good/Super Rod native slot-count distributions as a design constraint. Fishing consumes the authored four-slot source and the engine must be adapted around it.
- Day/Night variants exist only where the authored dataset distinguishes them; otherwise the table is Any.
- Standard source: `data/family_remix/source_v1/encounters_standard_final.json` (405 authored tables).
- Special source: `data/family_remix/source_v1/encounters_special_final.json` (Headbutt + 53 rotating Safari pools).
- Safari pools remain separate curated sets and rotate by sector/session. Never flatten the 53 pools into one giant table.
- Legendary/Mythical species are not introduced into ordinary random wild tables unless explicitly owner-authored in a special pool.

## 3. Difficulty

NORMAL and HARD use the same Family Remix content: boss species/rosters, legal evolutions, moves, items, abilities, natures, encounters, species edits, learnsets, shops and progression.

NORMAL:
- Family Remix roster/content.
- normal/native AI behavior.
- normal/native IV/EV scaling.
- no HARD-only optimization.

HARD:
- same roster/content.
- fixed major bosses use 31 IV.
- legal role-optimized EVs, max 252/stat and 510 total.
- fair strategic AI: Basic Trainer, Try To 2HKO, Smart Switching, HP Aware, PP Stall Prevention, Assumptions plus justified strategy flags.
- no hidden-information/omniscient prediction.
- bosses use at most two healing items where authored.

Family Remix defaults to HARD at new game, but NORMAL remains available.

## 4. Rocket + level caps

For each scripted Rocket boss:

`rocketLevel = previousMajorBossOrCurrentCap + 2`

- every Pokémon in that Rocket boss team uses the resolved level, subject to evolution legality;
- that value becomes the new cap/reference;
- consecutive Rocket bosses chain +2;
- do not replace owner-authored Rocket rosters with generic competitive sets.

Level caps follow major-boss progression and never decrease.

## 5. Starters + Elm egg

Starter selector categories:
- Fire: Charmander / Torchic / Chimchar / Cyndaquil / Charcadet
- Water: Mudkip / Piplup / Froakie / Oshawott / Horsea
- Grass: Bulbasaur / Treecko / Snivy / Sprigatito / Grookey
- Electric: Elekid / Magnemite / Pawmi / Wattrel / Pichu
- Ground: Gligar / Drilbur / Sandile / Golett / Sandygast
- Ice: Alolan Vulpix / Snorunt / Swinub / Galarian Darumaka / Vanillite
- Eevee + Eeveelution preference.

Elm's egg is a second selection from the same roster. Preserve no-duplicate behavior, team/PC overflow handling and the already implemented reward logic.

## 6. Settings / QoL

Target player-facing Settings structure:
- Gameplay
- Features
- Challenges
- Difficulty
- Audio
- Save & Continue

Challenges contains Nuzlocke, Shiny Only and Randomizer. Avoid redundant challenge submenus.

Native speed x1/x2/x3/x4 remains independent from audio speed/pitch. Audio has independent music and SFX volume from OFF to 100% in 20% steps; Recommended starts at 20%/20%.

Shiny rate options: 1/8192, 1/4096, 1/2048, 1/1024, 1/512, 1/100, 1/10, guaranteed.

## 7. Pokémon / evolutions / training

Use the final integrated Family Remix species and learnset data in the repository as authoritative unless an owner-locked change source says otherwise. Do not invent additional buffs during implementation.

Trade and trade+item evolutions must be obtainable solo. Item evolutions respect the Family Remix minimum-stage gates already defined. Training NPC supports EXP/EV/IV and related team preparation while respecting the current level cap.

## 8. Shops

Keep the shared categorized TM shop and categorized useful-item shop. Do not bypass normal progression for regular healing items, Balls or other progression-gated stock.

## 9. UI / visual theme

The actual in-game Family Remix interface is the visual source of truth. Web/wiki styling must derive from the real game assets/palette, not from an independently invented dark/red/gold palette. Current menu palette sources include `graphics/interface/option_menu_text_custom.pal` and the HnS Family Remix UI code.

## 10. Localization

FR pages and player-facing FR strings must use official French Pokémon terminology wherever an official localized name exists: Pokémon, moves, abilities, items, types and trainers. Do not leave English species names in FR pages (e.g. Maushold → Famignol). English pages remain English.

## 11. Wiki

- **Guide de jeu** = actual gameplay guide/progression help, not a project introduction.
- **Changements** = exhaustive player-facing list of Family Remix changes, sourced from final data.
- Pokémon changes should use one visual row/card per Pokémon: sprite + name + type + changed fields, with bullets when useful.
- **Pokédex** search must work for official FR names and English aliases.
- **Localisations** must show the authored four-slot encounter data and 30/30/30/10 rates.
- Boss pages explain strategy without becoming an automatic walkthrough.
