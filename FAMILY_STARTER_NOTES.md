# Starter principal et œuf d'Orme

Le sélecteur commun est dans `data/scripts/family_starter.inc` et ses adaptateurs dans `src/family_starter.c`. Les catégories sont Feu, Eau, Plante, Électrik, Sol, Glace et Évoli. Les 31 identifiants cibles existent dans cette base ; les générations 1 à 9 sont activées. Le menu vérifie les données compilées (`baseHP != 0`) et omet une espèce désactivée sans la remplacer. Les noms des espèces viennent des données existantes, actuellement en anglais ; les nouvelles catégories et répliques sont en français.

Les listes de starters historiques, données des espèces, évolutions et objets ne sont pas remplacées. Le nouveau tableau ne décrit que les entrées du menu demandé. Les trois scripts de Poké Balls conservent leurs espèces, indices et chemins historiques. Si le Randomizer des starters ou le défi monotype est actif, le starter principal garde ce parcours existant afin de ne pas contredire ces réglages. L'espèce effectivement reçue est mémorisée séparément pour les contrôles du starter et les crédits ; l'indice historique de Poké Ball reste disponible pour les autres scripts.

Le choix suit catégorie → espèce → confirmation. Non revient aux espèces ; B remonte d'un niveau et, au niveau catégorie, annule sans attribution. Pour Évoli, une seconde liste enregistre l'évolution choisie. Le sélecteur ne force jamais l'évolution lui-même, mais la confirmation prépare maintenant les récompenses Family Remix.

Les récompenses sont cumulatives et utilisent une file de trois objets maximum avec fallback Sac → PC. Chaque starter typé reçoit son booster de type (Charbon / Eau Mystique / Graine Miracle / Aimant / Sable Doux / Glace Éternelle), auquel s'ajoute l'objet d'évolution spécial prévu lorsque nécessaire. Évoli reçoit exactement trois objets : Mouchoir Soie + booster du type de l'évolition choisie + pierre d'évolution. La même logique s'applique au starter principal et à l'œuf d'Orme ; chaque objet conserve le message/fanfare standard d'obtention.

Après la présentation à Orme, l'objet de quête est converti en véritable œuf de l'espèce confirmée. Il n'est retiré qu'après une attribution réussie à l'équipe ou au PC par `ScriptGiveEgg`. Une annulation ou un stockage plein conserve l'objet ; la sélection peut être reprise chez Orme ou son assistant de Mauville. Une limite d'équipe de 1 ou une incompatibilité monotype utilise le PC, conformément au système existant. Le dialogue confirme le nom réel de l'espèce.

La réception ne peut se répéter : une variable mémorise l'espèce reçue. La personnalité et l'ID du joueur permettent à Orme de reconnaître l'œuf après éclosion, même après une évolution, sans confondre un autre Pokémon de la même espèce. Le drapeau historique de réception est réutilisé pour la barrière de la Route 32. L'assistant ne donne pas un deuxième œuf ; sa récompense existante et l'événement Kimono Girl sont conservés. Les anciennes sauvegardes sans sélection Family conservent le parcours Togepi original.

Variables HnS auparavant libres, sans agrandissement de sauvegarde :

| Adresse | Usage |
| --- | --- |
| 0x40C2 | Espèce du starter principal |
| 0x40C6 | Espèce de l'œuf confirmé |
| 0x40C9 | Préférence d'évolution du starter Évoli |
| 0x40CA | Préférence d'évolution de l'œuf Évoli |
| 0x40D8 / 0x40D9 | Personnalité de l'œuf |

Ces adresses correspondent à des événements Emerald inaccessibles dans HnS, identifiés dans `include/constants/vars_hns.h`. L'adaptation cible HnS, sans migration de sauvegardes provenant d'un autre jeu.

Validation : `make hns -j4`, `make check BUILD=hns TESTS=Family -j4`, plus groupes Native, Audio et Settings. Les tests couvrent les 31 espèces, les entrées invalides, l'attribution unique, l'identité/éclosion, l'envoi PC et l'échec quand le stockage est plein. À vérifier visuellement dans mGBA : toute la navigation A/B, les aperçus et noms longs, la suite Orme → Mauville → Route 32 et le dialogue après éclosion. L'existence de ces tests ne vaut pas résultat : voir le rapport de validation livré.
