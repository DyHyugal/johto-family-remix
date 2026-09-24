# Family Remix special encounter integration — FINAL

## Contract

Every Family Remix special encounter table is represented as **four real species slots** with explicit rates:

`[30, 30, 30, 10]`

No padding, species duplication or 9%+1% split is allowed.

## Headbutt

The four authored Headbutt tables use the same four-slot contract directly.

## Safari

The 53 Safari pools remain separate curated pools. Each active pool contains exactly four species at 30/30/30/10.

Session behavior:
- entering a Safari session starts the sector on pool A;
- after each Safari wild encounter, advance to the next authored pool for that sector;
- wrap after the final pool;
- changing sector preserves the rotation concept;
- a new Safari admission may reset to pool A.

Do not flatten pools together and do not translate them through inherited HnS encounter-slot counts.

Source:
`data/family_remix/source_v1/encounters_special_final.json`
