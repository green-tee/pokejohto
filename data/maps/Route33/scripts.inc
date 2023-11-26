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
	fadescreenspeed FADE_TO_BLACK, 10
	call Route33_EventScript_NormalizeCameraAndPlayer
	fadescreenspeed FADE_FROM_BLACK, 10
	bufferspeciesname STR_VAR_1, VAR_STARTER_MON
	msgbox Route33_Text_Joey_YouWantToGoToBugsysGym
	closemessage
	delay 30
	applymovement 1, Route33_Movement_TurnToGeodude
	waitmovement 1
	msgbox Route33_Text_Joey_ThereIsAGeodude
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route33_Movement_TurnToGeodude
	waitmovement OBJ_EVENT_ID_PLAYER
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, Route33_Movement_PadCameraToGeodude
	waitmovement OBJ_EVENT_ID_CAMERA
	special RemoveCameraObject
	applymovement 1, Route33_Movement_Joey_TurnToPlayer
	waitmovement 1
	msgbox Route33_Text_Joey_JustWatch
	closemessage
	turnobject 1, DIR_SOUTH
	fadeoutbgm 4
	playse SE_SUPER_EFFECTIVE
	msgbox Route33_Text_Joey_Yell
	waitse
	closemessage
	setobjectmovementtype 2, MOVEMENT_TYPE_FACE_UP
	playse SE_PIN
	applymovement 2, Route33_Movement_Geodude_Surprise
	waitse
	waitmovement 2
	delay 30
	playmoncry SPECIES_GEODUDE, CRY_MODE_NORMAL
	waitmoncry
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, Route33_Movement_PadCameraBackFromGeodude
	applymovement 2, Route33_Movement_Geodude_Attack
	waitmovement 2
	waitmovement OBJ_EVENT_ID_CAMERA
	special RemoveCameraObject
	special StartCatchingTutorialBattle
	waitstate
	turnobject 1, DIR_EAST
	delay 6
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox Route33_Text_Joey_ThisIsHowYouCatch
	closemessage
	msgbox Route33_Text_CatchEasierExplanation
	closemessage
	releaseall
	return


Route33_EventScript_NormalizeCameraAndPlayer:
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	setobjectxy OBJ_EVENT_ID_PLAYER, 55, 15
	special SpawnCameraObject
	compare VAR_TEMP_1, 55
	goto_if_lt Route33_EventScript_NormalizeCameraAndPlayer_2
	applymovement OBJ_EVENT_ID_CAMERA, Route33_Movement_FixCameraDown
Route33_EventScript_NormalizeCameraAndPlayer_1:
	waitmovement OBJ_EVENT_ID_CAMERA
	special RemoveCameraObject
	turnobject 1, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	return

Route33_EventScript_NormalizeCameraAndPlayer_2:
	applymovement OBJ_EVENT_ID_CAMERA, Route33_Movement_FixCameraDownRight
	goto Route33_EventScript_NormalizeCameraAndPlayer_1


Route33_Movement_FixCameraDown:
	walk_faster_down
	step_end

Route33_Movement_FixCameraDownRight:
	walk_faster_right
	walk_faster_down
	step_end

Route33_Movement_TurnToGeodude:
	walk_in_place_slow_down
	step_end

Route33_Movement_PadCameraToGeodude:
	walk_slower_down
	walk_slower_down
	walk_slower_down
	step_end

Route33_Movement_Joey_TurnToPlayer:
	walk_slow_right
	step_end

Route33_Movement_Geodude_Surprise:
	face_up_fast
	emote_exclamation_mark
	step_end

Route33_Movement_Geodude_Attack:
	walk_faster_up
	walk_faster_up
	step_end

Route33_Movement_PadCameraBackFromGeodude:
	walk_faster_up
	walk_faster_up
	walk_faster_up
	step_end

Route33_EventScript_Sign_Ledges::
	msgbox Route33_Text_TrainerTipsLedges, MSGBOX_SIGN
	return

