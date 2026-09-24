#!/usr/bin/env python3
"""Validate Family Remix data that is otherwise only checked by generators."""

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def fail(message):
    raise SystemExit(f"Family Remix validation failed: {message}")


def validate_bosses():
    text = (ROOT / "src/data/trainers_hns.party").read_text()
    marker = "/* ========== Family Remix FINAL hard boss parties ========== */"
    if text.count(marker) != 1:
        fail("missing or duplicated FINAL hard boss marker")
    hard = text.split(marker, 1)[1]
    blocks = re.findall(r"^=== ([A-Z0-9_]+) ===\n(.*?)(?=^=== |\Z)", hard, re.M | re.S)
    if len(blocks) != 22:
        fail(f"expected 22 fixed HARD boss teams, got {len(blocks)}")

    required_ai = ("Basic Trainer", "Try To 2HKO", "Smart Switching", "HP Aware",
                   "PP Stall Prevention", "Assumptions")
    mon_count = 0
    for trainer_id, block in blocks:
        header = block.split("\n\n", 1)[0]
        if "Difficulty: Hard" not in header:
            fail(f"{trainer_id} is not marked HARD")
        ai_match = re.search(r"^AI: (.+)$", header, re.M)
        if not ai_match or any(flag not in ai_match.group(1) for flag in required_ai):
            fail(f"{trainer_id} is missing the fair strategic AI baseline")
        if any(flag in ai_match.group(1) for flag in ("Smart Trainer", "Omniscient", "Prediction")):
            fail(f"{trainer_id} uses forbidden hidden-information AI")
        items_match = re.search(r"^Items: (.+)$", header, re.M)
        if items_match and len([x for x in items_match.group(1).split(" / ") if x]) > 2:
            fail(f"{trainer_id} has more than two healing items")

        levels = re.findall(r"^Level: (\d+)$", block, re.M)
        iv_lines = re.findall(r"^IVs: (.+)$", block, re.M)
        ev_lines = re.findall(r"^EVs: (.+)$", block, re.M)
        if not (len(levels) == len(iv_lines) == len(ev_lines)):
            fail(f"{trainer_id} has incomplete level/IV/EV data")
        for level in map(int, levels):
            if not 1 <= level <= 100:
                fail(f"{trainer_id} has invalid level {level}")
        for line in iv_lines:
            values = [int(x) for x in re.findall(r"(\d+) (?:HP|Atk|Def|SpA|SpD|Spe)", line)]
            if len(values) != 6 or any(value > 31 for value in values):
                fail(f"{trainer_id} has invalid IVs: {line}")
        for line in ev_lines:
            values = [int(x) for x in re.findall(r"(\d+) (?:HP|Atk|Def|SpA|SpD|Spe)", line)]
            if not values or any(value > 252 for value in values) or sum(values) > 510:
                fail(f"{trainer_id} has illegal EVs: {line}")
        mon_count += len(levels)

    if mon_count != 127:
        fail(f"expected 127 fixed-team Pokémon, got {mon_count}")

    locked = (
        "Jolteon @ Focus Sash", "Kingdra @ Scope Lens", "Honchkrow @ Life Orb",
        "Magnezone @ Choice Specs", "Exeggutor @ Choice Specs", "- Ancient Power",
    )
    for value in locked:
        if value not in hard:
            fail(f"owner-locked boss datum is missing: {value}")


def validate_encounters():
    wild = json.loads((ROOT / "src/data/wild_encounters.json").read_text())
    audit = wild.get("family_remix_encounter_audit", {})
    expected = {
        "dataset_version": 3,
        "imported_standard_tables": 405,
        "imported_headbutt_tables": 4,
        "special_tables_deferred": 53,
    }
    for key, value in expected.items():
        if audit.get(key) != value:
            fail(f"encounter audit {key}: expected {value}, got {audit.get(key)}")

    for group in wild["wild_encounter_groups"]:
        for encounter in group.get("encounters", []):
            for method in ("land_mons", "water_mons", "rock_smash_mons", "fishing_mons"):
                if method not in encounter:
                    continue
                mons = encounter[method]["mons"]
                for mon in mons:
                    if not (1 <= mon["min_level"] <= mon["max_level"] <= 100):
                        fail(f"invalid wild level range in {encounter.get('map', encounter.get('base_label'))}")
                    if not mon["species"].startswith("SPECIES_"):
                        fail("wild species constant is malformed")

    special = json.loads((ROOT / "data/family_remix/special_encounter_pools.json").read_text())
    headbutt = [table for table in special["tables"] if table["method"] == "headbutt_mons"]
    safari = [table for table in special["tables"] if table["method"] != "headbutt_mons"]
    if len(headbutt) != 4 or len(safari) != 53:
        fail(f"expected 4 Headbutt and 53 deferred Safari tables, got {len(headbutt)} and {len(safari)}")
    for table in headbutt:
        if table["rates"] != [30, 30, 30, 10] or len(table["species"]) != 4:
            fail(f"invalid Headbutt distribution for {table['map']}")

    headbutt_c = (ROOT / "src/data/family_remix_headbutt.h").read_text()
    if len(re.findall(r"\{MAP_GROUP\(MAP_", headbutt_c)) != 4:
        fail("dedicated Headbutt engine table does not contain four maps")


def parse_shop_items(path):
    return re.findall(r"^\s*\.2byte (ITEM_[A-Z0-9_]+)$", path.read_text(), re.M)


def validate_shops():
    tms = parse_shop_items(ROOT / "data/scripts/tm_shop.inc")
    if len(tms) != 92 or len(set(tms)) != 92 or any(not item.startswith("ITEM_TM_") for item in tms):
        fail("TM shop must contain each of the 92 active HnS TMs exactly once")

    items = parse_shop_items(ROOT / "data/scripts/item_shop.inc")
    if len(items) != 172 or len(set(items)) != 172:
        fail("item shop stock is incomplete or contains duplicates")
    safe_ball_names = {"ITEM_AIR_BALLOON", "ITEM_IRON_BALL", "ITEM_SMOKE_BALL"}
    forbidden_words = ("POTION", "REVIVE", "HEAL", "REPEL", "ESCAPE_ROPE")
    for item in items:
        if (any(word in item for word in forbidden_words)
         or (item.endswith("_BALL") and item not in safe_ball_names)):
            fail(f"progression-bypassing item in special shop: {item}")


def main():
    validate_bosses()
    validate_encounters()
    validate_shops()
    print("Family Remix data validation passed: bosses, EVs, encounters and shops")


if __name__ == "__main__":
    main()
