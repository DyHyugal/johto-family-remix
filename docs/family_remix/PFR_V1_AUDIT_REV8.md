# Pokémon Family Remix — Audit REV8 : prévu vs GitHub vs reste à faire

Baseline auditée :
- production : `work/native-speed-starter-egg` @ `e5c7191d66a798b3081fd81f95e9155086772c15`
- wiki : `wiki/family-remix-v1` @ `c44f8bde95b811ff01a12173d2392c5cd5a83a81`
- CI production observée : succès
- build/deploy wiki observés : succès

> Un état Codex non poussé n'est pas observable depuis GitHub. Le tableau ci-dessous compare donc le cahier final avec le dernier travail Codex réellement visible dans le dépôt.

| Bloc | Prévu REV8 | État GitHub | Action |
|---|---|---|---|
| Encounters standard | 405 tables logiques, 4 espèces, 30/30/30/10 direct | **À CORRIGER** : espèces encore dupliquées dans 12/5/10 slots hérités ; validateur verrouille ces tailles | Refactor moteur/data + validateur depuis le JSON REV8 |
| Headbutt | 4 tables directes 30/30/30/10 | **DONE** | Ne pas régresser |
| Safari | 53 pools, rotation de session, 4 espèces directes 30/30/30/10 | **DONE** au commit `e5c7191` | Ne pas régresser |
| Boss NORMAL/HARD | Même roster/contenu ; optimisation différente | **DONE** au commit `bef45fc` | QA ciblée |
| Rocket | roster final + niveau dynamique +2 + pré-évolutions légales | **DONE** au commit `18784da` | QA ciblée progression |
| Level caps | progression majeure + plancher Rocket | **DONE / QA** | Playthrough progression |
| Starter + œuf Orme | 30 + Évoli, deuxième choix via œuf, récompenses | **DONE** | QA UI/overflow |
| Vitesse x1-x4 | native, musique non accélérée | **DONE** automatisé | QA mGBA/hardware |
| Audio | musique/SFX indépendants | **DONE** | QA mGBA |
| Shiny rates | jusqu'à 1/100, 1/10, 1/1 | **DONE** | conserver |
| Shiny Only dans Challenges | défi visible dédié | **MANQUANT** : le 1/1 existe dans Features mais aucune ligne Shiny Only dans Challenges | Ajouter une ligne de défi réutilisant la logique existante |
| Menu | Mode / Features / Randomizer / Nuzlocke / Difficulty / Challenges | **DONE** | conserver |
| Training NPC | EXP/IV/EV/reset/nature/talent/etc. | **DONE** | QA |
| Boutiques | CT + objets catégorisés | **DONE** | QA |
| Custom species / learnsets | données finales owner-locked | **DONE / verify** | ne pas réinventer ; validator + build |
| ROM FR/EN | chaînes Family Remix cohérentes et localisées | **PARTIEL** : REV6 signalait encore du mix FR/EN et aucun commit de localisation ROM complet n'est visible après | Passe localisation après refactor encounters |
| Wiki thème | palette du jeu | **DONE** côté dernier commit CSS | revue visuelle utilisateur |
| Wiki Pokédex recherche | recherche fonctionnelle | **DONE code** : 724 cartes + JS + règle hidden | test navigateur/mobile |
| Wiki Guide | vrai guide pratique | **DONE** | relecture finale |
| Wiki Changements | inventaire + lignes Pokémon sprite/nom/type/changements | **DONE structure** | resynchroniser encounters après REV8 |
| Wiki FR officielle | noms/phrases propres | **PARTIEL** : il reste des formulations comme `injeu`, `abusers`, `meilleur réponse`, `le initiative`, `jeu défensif` | Passe FR complète |
| Wiki status | état réel | **STALE** : REV7 marque encore plusieurs blocs ALMOST DONE qui ont depuis été intégrés | Régénérer après prod REV8 |
| Full V1 QA | build + tests + playthrough | **PARTIEL** : CI verte sur l'ancien contrat encounters | refaire CI avec le nouveau contrat 4 slots + QA manuelle |

## Contraintes héritées trouvées et à retirer

1. `Pokemon_Family_Remix_Encounter_Dataset_v3.xlsx`
   - ancien README : 12 slots land / 5 Surf / 5 Rock Smash / 10 pêche ;
   - onglet `Slot_Rates` : taux natifs HnS ;
   - onglet `Encounter_Plan` : colonnes Slot / Suggested Rate héritées.
   - **À ne plus utiliser comme contrat d'implémentation.** Le contenu utile a été normalisé dans `PFR_V1_ENCOUNTERS_FINAL_REV8.json`.

2. `docs/family_remix/PFR_V1_AUDIT_REV6.md`
   - mention « Route 28 five native slots » ;
   - statuts boss/Rocket/Safari désormais dépassés.

3. `docs/family_remix/PFR_V1_CODEX_INSTRUCTIONS_REV6.md`
   - demande explicitement de valider les slots natifs HnS / Route 28 cinq slots.

4. `docs/family_remix/special_encounter_integration.md`
   - décrit le contournement 9 % + 1 % et les slots natifs ;
   - utile historiquement, mais le mapping natif n'est plus autoritaire.

5. `src/data/wild_encounters.json`
   - métadonnées audit actuelles décrivent encore 12 slots land, 5 slots water/rock et 10 slots fishing.

6. `tools/validate_family_remix.py`
   - calcule `expected_slots` depuis les arrays natifs et échoue si les tables HnS n'ont pas ces longueurs ;
   - c'est précisément le verrou qui doit disparaître.

## Remarque sur le commit d'import

Le commit `bb6ac539dc29` a modifié 631 enregistrements moteur car des tables logiques `Any` sont clonées jour/nuit et parce que les espèces sont répétées dans les layouts natifs. Après déduplication logique :
- 405 tables finales contiennent bien exactement quatre espèces ;
- un ancien cas Route 47 / Rock Smash à trois espèces n'appartient pas aux 405 finales et n'est pas repris dans la source REV8.

Le JSON REV8 est donc le contrat propre à utiliser pour la prochaine passe Codex.
