# Wiki V1 production status

Updated: 2026-09-24

| Block | Status | Result |
|---|---|---|
| GitHub Pages publishing | DONE | Public source is `wiki/family-remix-v1:/docs`; site is pre-rendered static HTML. |
| Visual system | DONE | Family Remix dark theme, cyan/violet/pink accents, responsive navigation, cards, tables and boss panels. |
| Landing page | DONE | FR/EN entry points and graphical navigation cards. |
| French wiki | DONE | Accueil, Guide, Changements, Boss & Conseils, Pokédex & Localisation, Crédits & Versions are graphically visitable. |
| English wiki | DONE | Home, Game Guide, Changes, Bosses & Tips, Pokédex & Locations, Credits & Versions are graphically visitable. |
| Boss presentation | DONE | Boss sections rendered as dedicated visual cards. |
| Encounter presentation | DONE | Large encounter/Safari tables rendered in scrollable responsive containers. |
| Mobile/responsive pass | DONE | Responsive navigation, content spacing and tables. |
| Content synchronization with final ROM | ALMOST DONE | Wiki contains the current authored V1 data; final ROM integration/playthrough can still change data before release. |
| Final visual approval | BLOCKED, need user | Requires creator review of the published design. |

## Publishing model

- `wiki/` remains the editable source/reference content.
- `docs/` is the GitHub Pages publication tree.
- Public pages are pre-rendered `.html` files to avoid raw Markdown/Jekyll rendering failures.
- `docs/.nojekyll` intentionally disables Jekyll processing for the public tree.

## Release rule

Before declaring the wiki release-final, synchronize boss/encounter/progression facts against the final V1 ROM after Codex integration and the final playthrough.
