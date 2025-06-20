@ Separate selection menus for before the Rainbow Pass is obtained
EventScript_ChooseDestFromOneIsland::
	goto_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5, EventScript_SeviiDestinationsPage1
	goto_if_ge VAR_MAP_SCENE_CINNABAR_ISLAND, 4, EventScript_ChooseDestFromOneIslandVermilionAllowed
	multichoice 19, 6, MULTICHOICE_ISLAND_23, FALSE
	switch VAR_RESULT
	case 0, EventScript_SailToTwoIsland2
	case 1, EventScript_SailToThreeIsland2
	case 2, EventScript_CancelSail
	case SCR_MENU_CANCEL, EventScript_CancelSail
	end

EventScript_ChooseDestFromOneIslandVermilionAllowed::
	multichoice 19, 5, MULTICHOICE_SEAGALLOP_V23, FALSE
	switch VAR_RESULT
	case 0, EventScript_SailToVermilion2
	case 1, EventScript_SailToTwoIsland2
	case 2, EventScript_SailToThreeIsland2
	case 3, EventScript_CancelSail
	case SCR_MENU_CANCEL, EventScript_CancelSail
	end

EventScript_ChooseDestFromTwoIsland::
	goto_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5, EventScript_SeviiDestinationsPage1
	goto_if_ge VAR_MAP_SCENE_CINNABAR_ISLAND, 4, EventScript_ChooseDestFromTwoIslandVermilionAllowed
	multichoice 19, 6, MULTICHOICE_ISLAND_13, FALSE
	switch VAR_RESULT
	case 0, EventScript_SailToOneIsland2
	case 1, EventScript_SailToThreeIsland2
	case 2, EventScript_CancelSail
	case SCR_MENU_CANCEL, EventScript_CancelSail
	end

EventScript_ChooseDestFromTwoIslandVermilionAllowed::
	multichoice 19, 5, MULTICHOICE_SEAGALLOP_V13, FALSE
	switch VAR_RESULT
	case 0, EventScript_SailToVermilion2
	case 1, EventScript_SailToOneIsland2
	case 2, EventScript_SailToThreeIsland2
	case 3, EventScript_CancelSail
	case SCR_MENU_CANCEL, EventScript_CancelSail
	end

EventScript_SailToVermilion2::
	setvar VAR_0x8006, SEAGALLOP_VERMILION_CITY
	goto EventScript_SailToDest
	end

EventScript_SailToOneIsland2::
	setvar VAR_0x8006, SEAGALLOP_ONE_ISLAND
	goto EventScript_SailToDest
	end

EventScript_SailToTwoIsland2::
	setvar VAR_0x8006, SEAGALLOP_TWO_ISLAND
	goto EventScript_SailToDest
	end

EventScript_SailToThreeIsland2::
	setvar VAR_0x8006, SEAGALLOP_THREE_ISLAND
	goto EventScript_SailToDest
	end

EventScript_ChooseDestFromIsland::
	goto_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5, EventScript_SeviiDestinationsPage1
	goto_if_ge VAR_MAP_SCENE_CINNABAR_ISLAND, 4, EventScript_ChooseDestFromIslandVermilionAllowed
	multichoice 19, 6, MULTICHOICE_ISLAND_12, FALSE
	switch VAR_RESULT
	case 0, EventScript_SailToOneIsland2
	case 1, EventScript_SailToTwoIsland2
	case 2, EventScript_CancelSail
	case SCR_MENU_CANCEL, EventScript_CancelSail
	end

EventScript_ChooseDestFromIslandVermilionAllowed::
	multichoice 19, 5, MULTICHOICE_SEAGALLOP_V12, FALSE
	switch VAR_RESULT
	case 0, EventScript_SailToVermilion2
	case 1, EventScript_SailToOneIsland2
	case 2, EventScript_SailToTwoIsland2
	case 3, EventScript_CancelSail
	case SCR_MENU_CANCEL, EventScript_CancelSail
	end

EventScript_SailToDest::
	specialvar VAR_RESULT, GetSeagallopNumber
	buffernumberstring STR_VAR_1, VAR_RESULT
	goto_if_eq VAR_0x8004, SEAGALLOP_VERMILION_CITY, EventScript_DepartingVermilion
	goto_if_ne VAR_0x8004, SEAGALLOP_VERMILION_CITY, EventScript_DepartingNotVermilion
	end

EventScript_DepartingVermilion::
	msgbox VermilionCity_Text_Seagallop7Departing
	goto EventScript_SetSail
	end

EventScript_DepartingNotVermilion::
	msgbox Text_AllAboardSeagallopNum
	goto EventScript_SetSail
	end

EventScript_SetSail::
	closemessage
	delay 20
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	fadescreen FADE_TO_BLACK
	special DoSeagallopFerryScene
	waitstate
	end

EventScript_CancelSail::
	specialvar VAR_RESULT, IsPlayerLeftOfVermilionSailor
	goto_if_eq VAR_RESULT, TRUE, VermilionCity_EventScript_WalkUpPier
	release
	end

VermilionCity_EventScript_WalkUpPier::
	closemessage
	applymovement LOCALID_FERRY_SAILOR, Common_Movement_FaceOriginalDirection
	applymovement OBJ_EVENT_ID_PLAYER, VermilionCity_Movement_WalkUp
	waitmovement 0
	releaseall
	end

VermilionCity_Movement_WalkUp::
	walk_up
	step_end

EventScript_SeviiDestinationsPage1::
	setvar VAR_0x8005, 0
	special DrawSeagallopDestinationMenu
	waitstate
	specialvar VAR_0x8006, GetSelectedSeagallopDestination
	switch VAR_0x8006
	case SEAGALLOP_VERMILION_CITY,      EventScript_SailToVermilionCity
	case SEAGALLOP_ONE_ISLAND,	        EventScript_SailToOneIsland
	case SEAGALLOP_TWO_ISLAND,	        EventScript_SailToTwoIsland
	case SEAGALLOP_THREE_ISLAND,        EventScript_SailToThreeIsland
	case SEAGALLOP_SANDALINE_COLONY,	EventScript_SailToSandalineColony
	case SEAGALLOP_MORE,		        EventScript_SeviiDestinationsPage2
	case SCR_MENU_CANCEL,		        EventScript_CancelSail
	end

EventScript_SeviiDestinationsPage2::
	setvar VAR_0x8005, 1
	special DrawSeagallopDestinationMenu
	waitstate
	specialvar VAR_0x8006, GetSelectedSeagallopDestination
	switch VAR_0x8006
	case SEAGALLOP_SANDALINE_COLONY,  EventScript_SailToSandalineColony
	case SEAGALLOP_FIVE_ISLAND,       EventScript_SailToFiveIsland
	case SEAGALLOP_SIX_ISLAND,        EventScript_SailToSixIsland
	case SEAGALLOP_SEVEN_ISLAND,      EventScript_SailToSevenIsland
	case SEAGALLOP_MORE,		      EventScript_SeviiDestinationsPage1
	case SCR_MENU_CANCEL,		      EventScript_CancelSail
	end

EventScript_SailToVermilionCity::
	setvar VAR_0x8006, SEAGALLOP_VERMILION_CITY
	goto EventScript_SailToDest
	end

EventScript_SailToOneIsland::
	setvar VAR_0x8006, SEAGALLOP_ONE_ISLAND
	goto EventScript_SailToDest
	end

EventScript_SailToTwoIsland::
	setvar VAR_0x8006, SEAGALLOP_TWO_ISLAND
	goto EventScript_SailToDest
	end

EventScript_SailToThreeIsland::
	setvar VAR_0x8006, SEAGALLOP_THREE_ISLAND
	goto EventScript_SailToDest
	end

EventScript_SailToSandalineColony::
	setvar VAR_0x8006, SEAGALLOP_SANDALINE_COLONY
	goto EventScript_SailToDest
	end

EventScript_SailToFiveIsland::
	setvar VAR_0x8006, SEAGALLOP_FIVE_ISLAND
	goto EventScript_SailToDest
	end

EventScript_SailToSixIsland::
	setvar VAR_0x8006, SEAGALLOP_SIX_ISLAND
	goto EventScript_SailToDest
	end

EventScript_SailToSevenIsland::
	setvar VAR_0x8006, SEAGALLOP_SEVEN_ISLAND
	goto EventScript_SailToDest
	end
