Route33_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route33_EventScript_OnTransition
	.byte 0


Route33_EventScript_OnTransition::
	compare VAR_MAP_SCENE_ROUTE33, 1
	goto_if_eq Route33_EventScript_OnTransition_1
	return

Route33_EventScript_OnTransition_1:
	call Route33_EventScript_PlaceJoeyForCatchingTutorial
	return


Route33_EventScript_PlaceJoeyForCatchingTutorial:
	setobjectxyperm 1, 54, 15
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_DOWN
	return


Route33_EventScript_Joey::
	compare VAR_MAP_SCENE_SANDALINE_COLONY_POKECENTER, 2
	goto_if_le Route33_EventScript_Joey_1
	msgbox Route33_Text_Joey_BringYourPokedexHere, MSGBOX_NPC
	return

Route33_EventScript_Joey_1:
	msgbox Route33_Text_Joey_BugsyIsWaiting, MSGBOX_NPC
	return


Route33_EventScript_Joey_Trigger::
	lockall
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	compare VAR_TEMP_2, 13
	goto_if_lt Route33_EventScript_Joey_Trigger_2
	turnobject 1, DIR_SOUTH
Route33_EventScript_Joey_Trigger_1:
	applymovement 1, Route33_Movement_ExclamationMark
	playse SE_PIN
	waitmovement 1
	waitse
	delay 90
	compare VAR_MAP_SCENE_SANDALINE_COLONY_POKECENTER, 2
	goto_if_le Route33_EventScript_Joey_Trigger_6
	msgbox Route33_Text_Joey_BringYourPokedexHere, MSGBOX_DEFAULT
Route33_EventScript_Joey_Trigger_5:
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route33_Movement_ForcePlayerToTheRight
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject 1, DIR_WEST
	releaseall
	return

Route33_EventScript_Joey_Trigger_2:
	turnobject 1, DIR_NORTH
	goto Route33_EventScript_Joey_Trigger_1

Route33_EventScript_Joey_Trigger_6:
	msgbox Route33_Text_Joey_BlockRoadBugsyIsWaiting, MSGBOX_DEFAULT
	goto Route33_EventScript_Joey_Trigger_5


Route33_Movement_ExclamationMark:
	emote_exclamation_mark
	step_end

Route33_Movement_ForcePlayerToTheRight:
	walk_right
	walk_right
	step_end

Route33_EventScript_CatchingTutorialScene::
	lockall
	msgbox Route33_EventScript_CatchingTutorialScene_Text_0
	closemessage
	releaseall
	return


Route33_EventScript_Sign_Ledges::
	msgbox Route33_EventScript_Sign_Ledges_Text_0
	return


Route33_EventScript_CatchingTutorialScene_Text_0:
	.string "AAAAAAAAAAAAAAAAAAAAAAAAA$"

Route33_EventScript_Sign_Ledges_Text_0:
	.string "TRAINER TIPS!\nAAAAAAAAAAAAAAAA$"
