Route33_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route33_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Route33_OnResume
	.byte 0


Route33_OnTransition::
	compare VAR_MAP_SCENE_ROUTE33, 1
	goto_if_eq Route33_OnTransition_1
	return

Route33_OnTransition_1:
	call Route33_EventScript_PlaceJoeyForCatchingTutorial
	return


Route33_EventScript_PlaceJoeyForCatchingTutorial:
	setobjectxyperm 1, 54, 15
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_DOWN
	return


Route33_OnResume::
	goto_if_set FLAG_SYS_SPECIAL_WILD_BATTLE, Route33_OnResume_1
	return

Route33_OnResume_1:
	removeobject 2
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
	applymovement 1, Movement_ExclamationMark
	playse SE_PIN
	waitmovement 1
	waitse
	delay 90
	compare VAR_MAP_SCENE_SANDALINE_COLONY_POKECENTER, 2
	goto_if_le Route33_EventScript_Joey_Trigger_6
	msgbox Route33_Text_Joey_BringYourPokedexHere, MSGBOX_DEFAULT
Route33_EventScript_Joey_Trigger_5:
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Movement_ForcePlayerToTheRight
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


Movement_ExclamationMark:
	emote_exclamation_mark
	step_end

Movement_ForcePlayerToTheRight:
	walk_right
	walk_right
	step_end

Route33_EventScript_CatchingTutorialScene::
	lockall
	fadescreenspeed FADE_TO_BLACK, 0
	call Route33_EventScript_NormalizeCameraAndPlayer
	fadescreenspeed FADE_FROM_BLACK, 0
	bufferspeciesname STR_VAR_1, VAR_STARTER_MON
	msgbox Route33_Text_Joey_YouWantToGoToBugsysGym
	closemessage
	delay 30
	applymovement 1, Movement_TurnToGeodude
	waitmovement 1
	msgbox Route33_Text_Joey_ThereIsAGeodude
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Movement_TurnToGeodude
	waitmovement OBJ_EVENT_ID_PLAYER
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, Movement_PadCameraToGeodude
	waitmovement OBJ_EVENT_ID_CAMERA
	special RemoveCameraObject
	applymovement 1, Movement_Joey_TurnToPlayer
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
	applymovement 2, Movement_Geodude_Surprise
	waitse
	waitmovement 2
	delay 30
	playmoncry SPECIES_GEODUDE, CRY_MODE_NORMAL
	waitmoncry
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, Movement_PadCameraBackFromGeodude
	applymovement 2, Movement_Geodude_Attack
	waitmovement 2
	waitmovement OBJ_EVENT_ID_CAMERA
	special RemoveCameraObject
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special StartCatchingTutorialBattle
	waitstate
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	turnobject 1, DIR_EAST
	delay 6
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox Route33_Text_Joey_ThisIsHowYouCatch
	closemessage
	msgbox Route33_Text_CatchEasierExplanation
	closemessage
	call Route33_EventScript_GiveSomePokeBallsToPlayer
	msgbox Route33_Text_Joey_YouCanBuyPokeBalls
	closemessage
	delay 30
	applymovement 1, Movement_TurnToGeodude
	waitmovement 1
	delay 30
	msgbox Route33_Text_Joey_WeAreDoneHere
	closemessage
	delay 30
	applymovement 1, Movement_Joey_TurnToPlayer
	waitmovement 1
	msgbox Route33_Text_Joey_ImGoing
	closemessage
	call Route33_EventScript_JoeyStartWalkAway
	delay 20
	msgbox Route33_Text_Joey_Dots
	closemessage
	applymovement 1, Movement_WalkBackToPlayer
	waitmovement 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	call Route33_EventScript_NicknamingStarter
	msgbox Route33_Text_Joey_NowWeAreReallyDone
	closemessage
	call Route33_EventScript_JoeyStartWalkAway
	msgbox Route33_Text_Joey_ComeUpWithEnjoey
	closemessage
	applymovement 1, Movement_FinishWalkingAway
	waitmovement 1
	removeobject 1
	setvar VAR_MAP_SCENE_ROUTE33, 2
	fadedefaultbgm
	delay 60
	releaseall
	return


Route33_EventScript_NormalizeCameraAndPlayer:
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	setobjectxy OBJ_EVENT_ID_PLAYER, 55, 15
	special SpawnCameraObject
	compare VAR_TEMP_1, 55
	goto_if_lt Route33_EventScript_NormalizeCameraAndPlayer_2
	applymovement OBJ_EVENT_ID_CAMERA, Movement_FixCameraDown
Route33_EventScript_NormalizeCameraAndPlayer_1:
	waitmovement OBJ_EVENT_ID_CAMERA
	special RemoveCameraObject
	turnobject 1, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	return

Route33_EventScript_NormalizeCameraAndPlayer_2:
	applymovement OBJ_EVENT_ID_CAMERA, Movement_FixCameraDownRight
	goto Route33_EventScript_NormalizeCameraAndPlayer_1


Movement_FixCameraDown:
	walk_faster_down
	step_end

Movement_FixCameraDownRight:
	walk_faster_right
	walk_faster_down
	step_end

Movement_TurnToGeodude:
	walk_in_place_slow_down
	step_end

Movement_PadCameraToGeodude:
	walk_slower_down
	walk_slower_down
	walk_slower_down
	step_end

Movement_Joey_TurnToPlayer:
	walk_in_place_right
	step_end

Movement_Geodude_Surprise:
	face_up_fast
	emote_exclamation_mark
	step_end

Movement_Geodude_Attack:
	walk_faster_up
	walk_faster_up
	step_end

Movement_PadCameraBackFromGeodude:
	walk_faster_up
	walk_faster_up
	walk_faster_up
	step_end

Route33_EventScript_GiveSomePokeBallsToPlayer:
	countitem ITEM_POKE_BALL, VAR_TEMP_3
	compare VAR_TEMP_3, 0
	goto_if_eq Route33_EventScript_GiveSomePokeBallsToPlayer_1
	compare VAR_TEMP_3, 15
	goto_if_lt Route33_EventScript_GiveSomePokeBallsToPlayer_2
	msgbox Route33_Text_Joey_YouHaveALotOfPokeBalls
	closemessage
	return

Route33_EventScript_GiveSomePokeBallsToPlayer_1:
	msgbox Route33_Text_Joey_YouHaveNoPokeBalls
	closemessage
	giveitem ITEM_POKE_BALL, 20
	return

Route33_EventScript_GiveSomePokeBallsToPlayer_2:
	msgbox Route33_Text_Joey_YouHaveSomePokeBalls
	closemessage
	setvar VAR_TEMP_4, 20
	subvar VAR_TEMP_4, VAR_TEMP_3
	giveitem ITEM_POKE_BALL, VAR_TEMP_4
	return


Route33_EventScript_JoeyStartWalkAway:
	applymovement OBJ_EVENT_ID_PLAYER, Movement_TurnToGeodude
	applymovement 1, Movement_WalkAwayFake
	waitmovement 1
	return


Movement_WalkAwayFake:
	walk_down
	walk_down
	step_end

Movement_WalkBackToPlayer:
	walk_up
	walk_up
	face_right
	step_end

Route33_EventScript_NicknamingStarter:
	bufferspeciesname STR_VAR_1, VAR_STARTER_MON
	msgbox Route33_Text_Joey_DoYouWantToNicknameYourPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route33_EventScript_NicknamingStarter_2
Route33_EventScript_NicknamingStarter_1:
	compare VAR_RESULT, YES
	goto_if_eq Route33_EventScript_NicknamingStarter_4
	msgbox Route33_Text_Joey_OkNevermindThen
	closemessage
	return

Route33_EventScript_NicknamingStarter_2:
	msgbox Route33_Text_Joey_AreYouSure, MSGBOX_YESNO
	goto Route33_EventScript_NicknamingStarter_1

Route33_EventScript_NicknamingStarter_4:
	setvar VAR_0x8004, 0
	call EventScript_ChangePokemonNickname
	return


Movement_FinishWalkingAway:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	step_end

Route33_EventScript_Sign_Ledges::
	msgbox Route33_Text_TrainerTipsLedges, MSGBOX_SIGN
	return

