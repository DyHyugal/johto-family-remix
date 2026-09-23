TmShop_EventScript::
	lock
	faceplayer
	msgbox TmShop_Text_Welcome, MSGBOX_DEFAULT
TmShop_MainMenu:
	closemessage
	dynmultichoice 1, 1, FALSE, 1, 0, DYN_MULTICHOICE_CB_NONE, TmShop_Text_Buy, TmShop_Text_Quit
	goto_if_eq VAR_RESULT, 0, TmShop_CategoryMenu
	goto TmShop_Exit

TmShop_CategoryMenu:
	msgbox TmShop_Text_ChooseCategory, MSGBOX_DEFAULT
	closemessage
	dynmultichoice 1, 1, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TmShop_Text_Support, TmShop_Text_WeakAttacks, TmShop_Text_PowerfulAttacks, TmShop_Text_UltimateAttacks, TmShop_Text_Back
	switch VAR_RESULT
	case 0, TmShop_OpenSupport
	case 1, TmShop_OpenWeakAttacks
	case 2, TmShop_OpenPowerfulAttacks
	case 3, TmShop_OpenUltimateAttacks
	goto TmShop_MainMenu

TmShop_OpenSupport:
	pokemart TmShop_Items_Support
	goto TmShop_CategoryMenu

TmShop_OpenWeakAttacks:
	pokemart TmShop_Items_WeakAttacks
	goto TmShop_CategoryMenu

TmShop_OpenPowerfulAttacks:
	pokemart TmShop_Items_PowerfulAttacks
	goto TmShop_CategoryMenu

TmShop_OpenUltimateAttacks:
	pokemart TmShop_Items_UltimateAttacks
	goto TmShop_CategoryMenu

TmShop_Exit:
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

TmShop_Text_Welcome:
	.string "What would you like to do today?$"
TmShop_Text_ChooseCategory:
	.string "Which kind of TM are you looking for?$"
TmShop_Text_Buy:
	.string "Buy$"
TmShop_Text_Quit:
	.string "Quit$"
TmShop_Text_Support:
	.string "Support$"
TmShop_Text_WeakAttacks:
	.string "Weak Attacks$"
TmShop_Text_PowerfulAttacks:
	.string "Powerful Attacks$"
TmShop_Text_UltimateAttacks:
	.string "Ultimate Attacks$"
TmShop_Text_Back:
	.string "Back$"

@ Provisional V1 stock: this preserves every TM from the two former counters.
@ Replace only these four lists when the final curated categories are supplied.
	.align 2
TmShop_Items_Support:
	.2byte ITEM_TM_LIGHT_SCREEN
	.2byte ITEM_TM_PROTECT
	.2byte ITEM_TM_REFLECT
	.2byte ITEM_TM_SAFEGUARD
	.2byte ITEM_TM_CAPTIVATE
	.2byte ITEM_TM_STEALTH_ROCK
	.2byte ITEM_TM_DREAM_EATER
	.2byte ITEM_TM_ENDURE
	pokemartlistend

	.align 2
TmShop_Items_WeakAttacks:
	.2byte ITEM_TM_NATURAL_GIFT
	.2byte ITEM_TM_BRINE
	.2byte ITEM_TM_AVALANCHE
	.2byte ITEM_TM_DARK_PULSE
	.2byte ITEM_TM_GYRO_BALL
	pokemartlistend

	.align 2
TmShop_Items_PowerfulAttacks:
	.2byte ITEM_TM_BLIZZARD
	.2byte ITEM_TM_SOLAR_BEAM
	.2byte ITEM_TM_THUNDER
	.2byte ITEM_TM_FIRE_BLAST
	.2byte ITEM_TM_FOCUS_BLAST
	pokemartlistend

	.align 2
TmShop_Items_UltimateAttacks:
	.2byte ITEM_TM_HYPER_BEAM
	.2byte ITEM_TM_GIGA_IMPACT
	pokemartlistend
