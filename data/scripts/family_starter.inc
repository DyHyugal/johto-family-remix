@ Shared, reversible menu flow. Results are temporary until the caller commits.
@ 8004: category, 8005: species, 8006: optional evolution preference.
FamilyStarter_Select::
	setvar VAR_0x8005, SPECIES_NONE
	setvar VAR_0x8006, SPECIES_NONE
FamilyStarter_Category::
	closemessage
	dynmultichoice 1, 1, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, FamilyStarter_Fire, FamilyStarter_Water, FamilyStarter_Grass, FamilyStarter_Electric, FamilyStarter_Ground, FamilyStarter_Ice, FamilyStarter_Eevee
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, FamilyStarter_Cancel
	copyvar VAR_0x8004, VAR_RESULT
	goto_if_eq VAR_0x8004, 6, FamilyStarter_EeveeEvolution
FamilyStarter_Species::
	callnative FamilyStarter_BuildSpeciesMenu
	dynmultistack 1, 1, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, FamilyStarter_Category
	goto_if_eq VAR_RESULT, SPECIES_NONE, FamilyStarter_Category
	copyvar VAR_0x8005, VAR_RESULT
	setvar VAR_0x8006, SPECIES_NONE
	callnative FamilyStarter_HasEvolutionChoices
	goto_if_eq VAR_RESULT, TRUE, FamilyStarter_Evolution
FamilyStarter_ConfirmChoice::
	showmonpic VAR_0x8005, 10, 3
	bufferspeciesname STR_VAR_1, VAR_0x8005
	goto_if_ne VAR_0x8006, SPECIES_NONE, FamilyStarter_ConfirmEvolution
	msgbox FamilyStarter_ConfirmSpecies, MSGBOX_YESNO
	hidemonpic
	goto_if_ne VAR_RESULT, YES, FamilyStarter_Species
FamilyStarter_Accept::
	setvar VAR_RESULT, TRUE
	return
FamilyStarter_ConfirmEvolution::
	bufferspeciesname STR_VAR_2, VAR_0x8006
	msgbox FamilyStarter_ConfirmEvolutionText, MSGBOX_YESNO
	hidemonpic
	goto_if_ne VAR_RESULT, YES, FamilyStarter_Evolution
	goto FamilyStarter_Accept
FamilyStarter_EeveeEvolution::
	setvar VAR_0x8005, SPECIES_EEVEE
	setvar VAR_0x8006, SPECIES_NONE
FamilyStarter_Evolution::
	msgbox FamilyStarter_EvolutionPrompt, MSGBOX_DEFAULT
	closemessage
	callnative FamilyStarter_BuildEvolutionMenu
	dynmultistack 1, 1, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, FamilyStarter_EvolutionBack
	copyvar VAR_0x8006, VAR_RESULT
	goto FamilyStarter_ConfirmChoice
FamilyStarter_EvolutionBack::
	goto_if_eq VAR_0x8005, SPECIES_EEVEE, FamilyStarter_Category
	goto FamilyStarter_Species
FamilyStarter_Cancel::
	setvar VAR_0x8005, SPECIES_NONE
	setvar VAR_0x8006, SPECIES_NONE
	setvar VAR_RESULT, FALSE
	return

FamilyStarter_Fire:
	.string "Feu$"
FamilyStarter_Water:
	.string "Eau$"
FamilyStarter_Grass:
	.string "Plante$"
FamilyStarter_Electric:
	.string "Électrik$"
FamilyStarter_Ground:
	.string "Sol$"
FamilyStarter_Ice:
	.string "Glace$"
FamilyStarter_Eevee:
	.string "Évoli$"
FamilyStarter_ConfirmSpecies:
	.string "Choisis-tu {STR_VAR_1} ?$"
FamilyStarter_ConfirmEvolutionText:
	.string "Choisis-tu {STR_VAR_1}\n"
	.string "avec {STR_VAR_2} prévu ?$"
FamilyStarter_EvolutionPrompt:
	.string "Quelle évolution prévois-tu ?$"
