# Cahier des charges Wiki V1 — REV7

## Objectif
Le wiki public est une documentation **joueur**. Il doit être simple à lire, agréable, bilingue et utile sans exposer les consignes internes de conception, les tags de travail ou les notes de production.

## Règles éditoriales
- FR : français uniquement dans l'interface et les explications. Un terme stratégique anglais n'est utilisé que s'il est indispensable, entre guillemets, avec une définition accessible dans le glossaire.
- EN : anglais uniquement.
- Toujours écrire **mode Normal / mode Difficile** en FR et **Normal mode / Hard mode** en EN.
- Préférer une phrase simple à un terme de stratégie. Expliquer la mécanique avant le jargon.
- Ne jamais recopier comme texte joueur une consigne de production, une règle de génération de données, un tag interne ou un commentaire du propriétaire.
- Pas de blocs visuels de type code pour des noms de projets, moteurs ou dépendances.
- Les informations non utiles au joueur (ex. tag interne « Progression ») restent dans les données sources mais sont exclues du wiki.
- Le wiki décrit ce qui est réellement présent dans Family Remix. Les listes de changements doivent être exhaustives lorsqu'une source finale fiable existe ; ne pas inventer les éléments manquants.

## Navigation
Onglets publics : Accueil, Guide de jeu, Changements, Boss & Conseils, Pokédex, Localisations, Crédits, Vocabulaire.
Deux boutons de langue permanents : **FR** et **ENG**.

## Pokédex
- Pokédex et Localisations sont deux pages distinctes.
- Pokédex : visuel du Pokémon près de son nom, informations utiles sur les modifications Family Remix et accès rapide à sa localisation.
- Ne jamais afficher le champ interne « Progression ».

## Localisations
Afficher : **Zone, Pokémon, taux d'apparition, niveau, méthode**.
- Les noms de zones et méthodes suivent la langue choisie.
- Headbutt/Safari sont présentés comme des mécaniques joueur, jamais comme des règles de génération.
- Un taux exact n'est publié que lorsqu'il est vérifiable dans la donnée finale ; ne pas fabriquer un pourcentage.

## Changements
La page doit documenter réellement :
- systèmes et confort ;
- starters et œuf ;
- Pokémon modifiés (types/statistiques/talents) ;
- évolutions simplifiées, notamment les évolutions par échange ou échange + objet ;
- capacités apprises par niveau réellement modifiées ;
- rencontres sauvages ;
- boutiques et PNJ, avec emplacement/rôle quand connu ;
- Level Cap, Training NPC et autres systèmes que le joueur doit connaître.
Élekable est explicitement **Électrik / Combat**, comme Élektek dans Family Remix.

## Boss & Conseils
- Conserver l'approche actuelle, mais vulgariser le vocabulaire.
- Ajouter les compositions d'équipes lorsqu'elles sont finalisées.
- Ajouter un portrait/sprite du Champion ou boss quand une ressource stable est disponible.
- Les conseils expliquent le plan adverse sans devenir une solution tour par tour.

## Direction visuelle
- Conserver l'esprit sombre de la ROM, mais utiliser une palette inspirée du projet : noir/bleu nuit, or chaud, rouge profond et crème.
- Cartes lisibles, peu d'encadrés décoratifs inutiles.
- Pas de rendu « terminal », pas de Markdown brut.
- Responsive desktop/mobile.
- Sprites Pokémon intégrés visuellement près des noms, sans colonne « image » dédiée.

## Publication
- Branche : `wiki/family-remix-v1`.
- GitHub Pages : `/docs`.
- `wiki/` = sources/références éditoriales.
- `docs/` = site statique public.
