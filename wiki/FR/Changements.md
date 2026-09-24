[Accueil](Accueil.md) · [Guide de jeu](Guide-de-jeu.md) · [Changements](Changements.md) · [Boss & Conseils](Boss-et-Conseils.md) · [Pokédex & Localisation](Pokedex-et-Localisation.md) · [Crédits & Versions](Credits-et-Versions.md) · **[EN](../EN/Changes.md)**

# Changements

Cette page regroupe les différences principales entre Pokémon Heart & Soul et Pokémon Family Remix. L'objectif est d'éviter une navigation remplie de micro-pages.

## Sommaire

- [Systèmes](#systèmes)
- [Starters et œuf d'Orme](#starters-et-œuf-dorme)
- [Pokémon](#pokémon)
- [Évolutions et learnsets](#évolutions-et-learnsets)
- [Rencontres sauvages](#rencontres-sauvages)
- [Combats de boss](#combats-de-boss)
- [Boutiques](#boutiques)
- [Interface et confort](#interface-et-confort)

## Systèmes

Family Remix ajoute ou modifie notamment :

- HARD par défaut, NORMAL disponible ;
- Level Cap ;
- Training NPC ;
- vitesse native x1/x2/x3/x4 ;
- réglages audio indépendants ;
- nouvelle configuration de partie ;
- sauvegarde des paramètres simplifiée ;
- meilleure séparation entre difficulté, challenges et randomizer.

## Starters et œuf d'Orme

Le choix de starter n'est plus limité au trio classique. Les familles sont regroupées par type et comprennent également Évoli.

L'œuf d'Orme devient une seconde sélection Family Remix : l'espèce choisie est réellement contenue dans l'œuf et conserve son identité jusqu'à l'éclosion.

Des objets de type et d'évolution sont remis automatiquement afin que les starters choisis restent utilisables sans détour artificiel.

## Pokémon

Plusieurs Pokémon reçoivent des ajustements ciblés de type, statistiques, talents ou rôle.

Exemples déjà verrouillés dans le design V1 :

| Pokémon | Changement principal |
|---|---|
| Dracaufeu | Feu / Dragon |
| Typhlosion | Feu / Sol |
| Jungko | Plante / Dragon, orientation plus physique |
| Luxray | Électrik / Ténèbres |
| Moustillon / Mateloutre / Clamiral | Eau / Combat |
| Tranchodon | second type et profil offensif retravaillés |
| Élekable | profil offensif et vitesse retravaillés |
| Hyporoi | profil physique renforcé |

La table exhaustive sera synchronisée avec les données compilées avant la RC afin d'éviter de documenter une valeur qui aurait changé pendant l'intégration.

## Évolutions et learnsets

Certaines évolutions par objet sont soumises à un niveau minimum :

- base → stade 1 : niveau 16 ;
- base → final sans stade intermédiaire : niveau 30 ;
- stade 1 → final : niveau 36.

Des learnsets ont été étendus pour soutenir les nouveaux rôles. Deux correspondances importantes utilisées dans le projet sont :

- **Aquatacle** = `MOVE_WAVE_CRASH`
- **Eau Revoir** = `MOVE_FLIP_TURN`

## Rencontres sauvages

La distribution sauvage est repensée autour de la progression.

Principes :

- 4 espèces principales par table ;
- distribution cible 30 / 30 / 30 / 10 ;
- utilisation de l'herbe, Surf, pêche, Rock Smash, moment de la journée et autres méthodes disponibles ;
- starters sauvages rares et placés progressivement ;
- stades finaux surtout tardifs ;
- aucun légendaire/fabuleux injecté comme rencontre aléatoire ;
- espèces Safari dédiées conservées au Safari.

Les données finales comptent **409 tables normales + 53 tables Safari**.

## Combats de boss

Le mode HARD remplace la simple augmentation de niveau par une logique d'équipe :

- objets ;
- IV31 ;
- EV adaptés au rôle ;
- météo/terrain ;
- hazards ;
- screens ;
- Trick Room ;
- setup ;
- pivots ;
- win conditions.

À partir de la troisième arène, les Champions utilisent des équipes complètes de six Pokémon. Les Méga apparaissent à partir de la quatrième arène.

Les conseils et les mécaniques de chaque boss sont détaillés dans [Boss & Conseils](Boss-et-Conseils.md).

## Boutiques

Le TM Shop est organisé :

**Catégorie → Type → CT**

Catégories :

- Support
- Weak
- Powerful
- Ultimate

Le shop d'objets utilise :

**Evolution → Strategic → Other**

Les objets de soin classiques, Poké Balls, Repels, Key Items et objets de scénario ne doivent pas court-circuiter la progression des boutiques normales.

## Interface et confort

Family Remix conserve la base graphique HnS et termine une refonte légère pour la V1 :

- fenêtres ;
- menus ;
- interface de combat ;
- summary ;
- Pokédex ;
- shops ;
- palettes.

Une refonte graphique plus profonde est réservée à une future V2.
