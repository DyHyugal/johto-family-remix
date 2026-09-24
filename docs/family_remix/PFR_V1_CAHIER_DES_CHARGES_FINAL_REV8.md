# Pokémon Family Remix — Cahier des charges final V1 REV8

Date: 2026-09-24

## Autorité des sources

REV8 remplace les consignes REV6 lorsqu'elles sont en conflit. Les anciens documents restent historiques mais ne doivent plus dicter l'implémentation des rencontres.

Ordre d'autorité :
1. décisions finales du créateur résumées dans ce document ;
2. `data/family_remix/PFR_V1_ENCOUNTERS_FINAL_REV8.json` pour les rencontres ;
3. données V1 déjà intégrées et validées dans le dépôt pour les boss, Pokémon modifiés, learnsets, boutiques et systèmes ;
4. documents REV6 uniquement pour le contexte non remplacé.

Principe global : **HnS est la base du fork, pas une contrainte de game design**. Si une structure héritée empêche le comportement Family Remix voulu, on adapte la structure dans ce fork au lieu de déformer les données Family Remix.

## Rencontres sauvages

- Une table Family Remix contient **exactement 4 espèces** : A = 30 %, B = 30 %, C = 30 %, D = 10 %.
- Cette règle s'applique directement aux tables utilisées par Family Remix : terrestre/herbe/sol, Surf, Éclate-Roc, pêche, Headbutt et pools Safari.
- **Interdit :** répliquer artificiellement les espèces dans 12, 5 ou 10 slots HnS pour reconstituer 30/30/30/10.
- **Interdit :** conserver les anciens taux natifs 20/20/10…, 30/30/30/9/1, 70/30, etc. comme contrainte Family Remix.
- Les données de la V1 définissent les quatre espèces et leurs niveaux. Le moteur doit lire ces quatre slots logiques.
- Pêche : ne pas réutiliser les tableaux de probabilités Old/Good/Super Rod hérités. Les cannes peuvent conserver leur rôle d'accès/progression si nécessaire, mais elles ne doivent ni dupliquer les slots ni modifier le 30/30/30/10 du pool Family Remix.
- Jour/nuit reste utilisé quand le dataset distingue réellement les deux ; lorsqu'une même table est identique jour et nuit, elle est logique `Any`.
- Les starters sauvages restent rares et sont placés dans le slot 10 % lorsqu'ils sont autorisés.
- Les formes finales fortes arrivent tard selon la progression.
- Aucun légendaire/fabuleux ne doit être ajouté aux rencontres sauvages ordinaires.
- Safari : conserver les 53 pools curatés et leur rotation de session déjà intégrée ; chaque pool expose directement quatre espèces 30/30/30/10.
- Headbutt : conserver les 4 tables directes déjà intégrées à quatre espèces 30/30/30/10.

## Difficultés et boss

- NORMAL et HARD utilisent le **même contenu Family Remix** : espèces, niveaux, movesets, objets tenus, talents et natures.
- NORMAL conserve l'optimisation/IA normale.
- HARD ajoute IV 31, EV légaux adaptés au rôle et IA stratégique équitable, sans information cachée.
- Maximum deux objets de soin par Champion/boss quand le combat en prévoit.
- Respect strict des niveaux d'évolution ; si un boss dynamique tombe sous le niveau d'une forme finale, utiliser la pré-évolution légale.
- Les équipes finales déjà owner-locked dans le dépôt ne doivent pas être remplacées opportunément.

## Team Rocket et Level Caps

- Les équipes Rocket finales sont partagées entre NORMAL/HARD, seule l'optimisation change.
- Niveau Rocket = dernier palier majeur/progression de référence + 2.
- Un boss Rocket successif repart du palier Rocket précédent + 2.
- Le niveau Rocket devient ensuite le nouveau plancher/référentiel de progression.
- Les formes sont automatiquement rétrogradées vers une pré-évolution légale si nécessaire.

## Starter, œuf d'Orme et évolutions

- Sélecteur : 30 starters répartis Feu/Eau/Plante/Électrik/Sol/Glace + Évoli.
- L'œuf d'Orme réutilise le même sélecteur comme deuxième choix.
- Récompenses : booster de type et objet(s) d'évolution nécessaires selon le choix.
- Évoli choisit son évolution et reçoit les objets associés.
- Les évolutions d'échange / échange + objet sont réalisables en solo.
- Les garde-fous de niveau des évolutions par objet restent actifs pour éviter les formes finales trop précoces.

## Réglages et défis

Arborescence validée : **Mode / Features / Randomizer / Nuzlocke / Difficulty / Challenges**.

- Vitesse native x1/x2/x3/x4.
- Volumes Musique et SFX indépendants.
- Shiny rate : 1/8192, 1/4096, 1/2048, 1/1024, 1/512, 1/100, 1/10, 1/1.
- **Shiny Only doit aussi exister comme défi visible dans Challenges**. Il peut s'appuyer sur la logique 1/1 existante mais ne doit pas disparaître du menu Challenges.
- Randomizer et Nuzlocke restent des fonctions configurables dans le menu prévu, sans multiplication de sous-menus inutiles.
- Le mode Difficile est le preset par défaut ; NORMAL reste sélectionnable.

## Entraînement, boutiques et confort

- Assistant centralisé : EXP jusqu'au cap, IV, EV, reset EV, nature, talent, bonheur.
- Boutique CT catégorisée à partir des CT actives du projet.
- Boutique objets pour évolution / combat / confort, sans court-circuiter les soins, Balls et progression normale.
- Guides d'arène : conseils adaptés aux nouveaux combats + Eau Fraîche selon le comportement prévu.

## Interface et localisation

- Le thème sombre Family Remix doit suivre la palette réelle du jeu (fond sombre, rouge, bleu et accents clairs), pas une palette parallèle inventée pour le wiki.
- Interface pause, combats, résumé, boutiques et écrans Family Remix doivent rester cohérents.
- FR joueur : employer les noms officiels français des Pokémon, capacités, talents, objets et personnages quand ils existent.
- EN : employer les noms officiels anglais.
- Éviter les mélanges de langue et le jargon compétitif non expliqué dans le texte joueur.

## Wiki V1

- **Guide de jeu** = guide pratique pour jouer, pas simple introduction.
- **Changements** = inventaire des changements Family Remix, avec pour les Pokémon : sprite + nom + type(s) + liste des changements.
- **Pokédex** = recherche fonctionnelle et noms localisés.
- **Localisations** = données issues de la source de rencontres finale, donc quatre slots 30/30/30/10.
- **Boss & Conseils** = compositions et explications utiles, sans solution tour par tour imposée.
- Les pages FR doivent recevoir une dernière passe éditoriale officielle avant verrouillage V1.

## Validation V1

La V1 n'est verrouillée qu'après :
- validation automatisée des données Family Remix ;
- build HnS/Family Remix réussi ;
- tests boss NORMAL/HARD, Rocket dynamique, encounters quatre slots, Safari, Headbutt, starters/œuf, évolutions, entraînement, vitesse, audio et réglages ;
- playthrough manuel mGBA représentatif, puis régression UI/localisation/wiki.
