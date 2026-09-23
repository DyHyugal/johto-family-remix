ItemShop_EventScript::
	lock
	faceplayer
	msgbox ItemShop_Text_Welcome, MSGBOX_DEFAULT
ItemShop_MainMenu:
	closemessage
	dynmultichoice 1, 1, FALSE, 1, 0, DYN_MULTICHOICE_CB_NONE, ItemShop_Text_Buy, ItemShop_Text_Quit
	goto_if_eq VAR_RESULT, 0, ItemShop_CategoryMenu
	goto ItemShop_Exit

ItemShop_CategoryMenu:
	msgbox ItemShop_Text_ChooseCategory, MSGBOX_DEFAULT
	closemessage
	dynmultichoice 1, 1, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, ItemShop_Text_Competitive, ItemShop_Text_Evolution, ItemShop_Text_Strategic, ItemShop_Text_Back
	switch VAR_RESULT
	case 0, ItemShop_OpenCompetitive
	case 1, ItemShop_OpenEvolution
	case 2, ItemShop_OpenStrategic
	goto ItemShop_MainMenu

ItemShop_OpenCompetitive:
	pokemart ItemShop_Items_Competitive
	goto ItemShop_CategoryMenu

ItemShop_OpenEvolution:
	pokemart ItemShop_Items_Evolution
	goto ItemShop_CategoryMenu

ItemShop_OpenStrategic:
	pokemart ItemShop_Items_Strategic
	goto ItemShop_CategoryMenu

ItemShop_Exit:
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

ItemShop_Text_Welcome:
	.string "What would you like to do today?$"
ItemShop_Text_ChooseCategory:
	.string "Which kind of item are you looking for?$"
ItemShop_Text_Buy:
	.string "Buy$"
ItemShop_Text_Quit:
	.string "Quit$"
ItemShop_Text_Competitive:
	.string "Competitive$"
ItemShop_Text_Evolution:
	.string "Evolution$"
ItemShop_Text_Strategic:
	.string "Strategic$"
ItemShop_Text_Back:
	.string "Back$"

@ Provisional V1 stock derived from the existing Frontier and department-store
@ inventories. Replace only these lists when the final curated stock is supplied.
	.align 2
ItemShop_Items_Competitive:
	.2byte ITEM_LEFTOVERS
	.2byte ITEM_WHITE_HERB
	.2byte ITEM_QUICK_CLAW
	.2byte ITEM_MENTAL_HERB
	.2byte ITEM_BRIGHT_POWDER
	.2byte ITEM_CHOICE_BAND
	.2byte ITEM_KINGS_ROCK
	.2byte ITEM_FOCUS_BAND
	.2byte ITEM_SCOPE_LENS
	.2byte ITEM_MUSCLE_BAND
	.2byte ITEM_WISE_GLASSES
	.2byte ITEM_LIFE_ORB
	.2byte ITEM_CHOICE_SPECS
	.2byte ITEM_CHOICE_SCARF
	.2byte ITEM_FOCUS_SASH
	.2byte ITEM_ASSAULT_VEST
	.2byte ITEM_EVIOLITE
	.2byte ITEM_EXPERT_BELT
	.2byte ITEM_ROCKY_HELMET
	.2byte ITEM_HEAVY_DUTY_BOOTS
	.2byte ITEM_WEAKNESS_POLICY
	.2byte ITEM_AIR_BALLOON
	.2byte ITEM_RED_CARD
	.2byte ITEM_EJECT_BUTTON
	.2byte ITEM_METRONOME
	.2byte ITEM_FLAME_ORB
	.2byte ITEM_TOXIC_ORB
	.2byte ITEM_LUCKY_EGG
	.2byte ITEM_WIDE_LENS
	.2byte ITEM_ZOOM_LENS
	pokemartlistend

	.align 2
ItemShop_Items_Evolution:
	.2byte ITEM_ICE_STONE
	.2byte ITEM_METAL_COAT
	.2byte ITEM_DRAGON_SCALE
	.2byte ITEM_KINGS_ROCK
	.2byte ITEM_UP_GRADE
	.2byte ITEM_DUBIOUS_DISC
	.2byte ITEM_REAPER_CLOTH
	.2byte ITEM_PROTECTOR
	.2byte ITEM_ELECTIRIZER
	.2byte ITEM_MAGMARIZER
	.2byte ITEM_OVAL_STONE
	.2byte ITEM_RAZOR_FANG
	.2byte ITEM_RAZOR_CLAW
	.2byte ITEM_DUSK_STONE
	.2byte ITEM_DAWN_STONE
	.2byte ITEM_SHINY_STONE
	.2byte ITEM_BLACK_AUGURITE
	.2byte ITEM_PEAT_BLOCK
	.2byte ITEM_LINKING_CORD
	pokemartlistend

	.align 2
ItemShop_Items_Strategic:
	.2byte ITEM_MACHO_BRACE
	.2byte ITEM_POWER_WEIGHT
	.2byte ITEM_POWER_BRACER
	.2byte ITEM_POWER_BELT
	.2byte ITEM_POWER_LENS
	.2byte ITEM_POWER_BAND
	.2byte ITEM_POWER_ANKLET
	.2byte ITEM_PP_MAX
	.2byte ITEM_ABILITY_CAPSULE
	.2byte ITEM_ABILITY_PATCH
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	pokemartlistend
