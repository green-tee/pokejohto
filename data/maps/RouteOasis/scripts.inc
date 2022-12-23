RouteOasis_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RouteOasis_EventScript_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, RouteOasis_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RouteOasis_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

RouteOasis_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE:
	map_script_2 VAR_MAP_SCENE_ROUTE_OASIS, 0, RouteOasis_EventScript_AdjustPlayerOnStart
	.2byte 0

RouteOasis_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_MAP_SCENE_ROUTE_OASIS, 0, RouteOasis_EventScript_BugsyIntro
	.2byte 0


RouteOasis_EventScript_OnTransition::
	compare VAR_MAP_SCENE_ROUTE_OASIS, 1
	goto_if_eq RouteOasis_EventScript_OnTransition_1
	return

RouteOasis_EventScript_OnTransition_1:
	call RouteOasis_EventScript_AdjustBugsyAndJoey
	return


RouteOasis_EventScript_AdjustPlayerOnStart::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	return


RouteOasis_EventScript_BugsyIntro::
	lockall
	call RouteOasis_EventScript_BugsyIntroSpeech
	call RouteOasis_EventScript_BugsyIntroLayPokeballs
	call RouteOasis_EventScript_BugsyIntroExplainStarters
	setvar VAR_MAP_SCENE_ROUTE_OASIS, 1
	releaseall
	return


RouteOasis_EventScript_BugsyIntroSpeech:
	msgbox RouteOasis_Text_Bugsy_YouWantToBecomeATrainer
	closemessage
	applymovement 2, Movement_FaceJoey
	waitmovement 2
	msgbox RouteOasis_Text_Bugsy_JoeyNewGymLeader
	closemessage
	applymovement 1, Movement_Surprised
	playse SE_PIN
	waitmovement 1
	delay 120
	msgbox RouteOasis_Text_Joey_BugsyDidNotNeedTo
	closemessage
	delay 30
	msgbox RouteOasis_Text_Bugsy_TheseMonsAreRare
	closemessage
	applymovement 2, Movement_FacePlayer
	waitmovement 2
	msgbox RouteOasis_Text_Bugsy_LastChallenger
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Movement_Player_OutOfTheWay
	waitmovement OBJ_EVENT_ID_PLAYER
	return


RouteOasis_EventScript_BugsyIntroLayPokeballs:
	applymovement 2, Movement_GoLayingFirstBall
	delay 60
	turnobject 1, DIR_WEST
	waitmovement 2
	addobject 3
	clearflag FLAG_HIDE_CHIKORITA_BALL
	playse SE_BALL
	waitse
	delay 30
	applymovement 2, Movement_GoLayingNextBall
	waitmovement 2
	addobject 4
	clearflag FLAG_HIDE_CYNDAQUIL_BALL
	playse SE_BALL
	waitse
	delay 30
	applymovement 2, Movement_GoLayingNextBall
	waitmovement 2
	addobject 5
	clearflag FLAG_HIDE_TOTODILE_BALL
	playse SE_BALL
	waitse
	delay 30
	return


RouteOasis_EventScript_BugsyIntroExplainStarters:
	applymovement 2, Movement_GoExplainStartersToPlayer
	waitmovement 2
	msgbox RouteOasis_Text_Bugsy_PlayerPickMon
	closemessage
	applymovement 2, Movement_Bugsy_FaceJoeyFromLeft
	waitmovement 2
	msgbox RouteOasis_Text_Bugsy_JoeyWillPickSecond
	closemessage
	applymovement 2, Movement_FacePokeballs
	waitmovement 2
	msgbox RouteOasis_Text_Bugsy_IWillPickLast
	closemessage
	applymovement 2, Movement_FacePlayerFromAbove
	waitmovement 2
	msgbox RouteOasis_Text_Bugsy_GoAheadPickOne
	closemessage
	delay 30
	applymovement 2, Movement_WaitPlayerPickStarter
	waitmovement 2
	call RouteOasis_EventScript_AdjustBugsyAndJoey
	return


RouteOasis_EventScript_AdjustBugsyAndJoey:
	setobjectxyperm 2, 23, 31
	setobjectmovementtype 2, MOVEMENT_TYPE_FACE_RIGHT
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_LEFT
	return


RouteOasis_EventScript_BugsyPreventPlayerFromGoingAway::
	lockall
	turnobject 2, DIR_SOUTH
	msgbox RouteOasis_Text_Bugsy_DoNotGoAway
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Movement_Player_WalkToPokeballsFromLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject 2, DIR_EAST
	releaseall
	return


RouteOasis_EventScript_JoeyPreventPlayerFromGoingAway::
	lockall
	turnobject 1, DIR_EAST
	msgbox RouteOasis_Text_Joey_DoNotGoAway
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Movement_Player_WalkToPokeballsFromRight
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject 1, DIR_WEST
	releaseall
	return


Movement_FaceJoey:
	walk_in_place_fast_up
	step_end

Movement_Surprised:
	emote_exclamation_mark
	step_end

Movement_FacePlayer:
	walk_in_place_left
	step_end

Movement_Player_OutOfTheWay:
	walk_down
	walk_left
	face_up
	step_end

Movement_GoLayingFirstBall:
	walk_left
	walk_left
	walk_left
	walk_in_place_fast_up
	step_end

Movement_GoLayingNextBall:
	walk_right
	walk_in_place_fast_up
	step_end

Movement_GoExplainStartersToPlayer:
	walk_left
	walk_in_place_fast_down
	step_end

Movement_Bugsy_FaceJoeyFromLeft:
	walk_in_place_right
	step_end

Movement_FacePokeballs:
	walk_in_place_slow_up
	step_end

Movement_FacePlayerFromAbove:
	walk_in_place_down
	step_end

Movement_WaitPlayerPickStarter:
	walk_left
	walk_left
	face_right
	step_end

Movement_Player_WalkToPokeballsFromLeft:
	walk_right
	walk_right
	step_end

Movement_Player_WalkToPokeballsFromRight:
	walk_left
	walk_left
	step_end

RouteOasis_EventScript_Bugsy::
	msgbox RouteOasis_Text_Bugsy_CheckOutPokeballs, MSGBOX_NPC
	return


RouteOasis_EventScript_Joey::
	msgbox RouteOasis_Text_Joey_CheckOutPokeballs, MSGBOX_NPC
	return


RouteOasis_EventScript_StarterBall::
	lockall
	call RouteOasis_EventScript_SetupInteractedStarterInfo
	compare VAR_RESULT, YES
	goto_if_eq RouteOasis_EventScript_StarterBall_2
RouteOasis_EventScript_StarterBall_1:
	textcolor NPC_TEXT_COLOR_DEFAULT
	hidemonpic
	releaseall
	return

RouteOasis_EventScript_StarterBall_2:
	call RouteOasis_EventScript_GiveStarterToPlayer
	call RouteOasis_EventScript_PositionCharactersAfterSelection
	setvar VAR_MAP_SCENE_ROUTE_OASIS, 2
	goto RouteOasis_EventScript_StarterBall_1


RouteOasis_EventScript_SetupInteractedStarterInfo:
	switch VAR_LAST_TALKED
	case 3, RouteOasis_EventScript_SetupInteractedStarterInfo_3
	case 4, RouteOasis_EventScript_SetupInteractedStarterInfo_4
	case 5, RouteOasis_EventScript_SetupInteractedStarterInfo_5
RouteOasis_EventScript_SetupInteractedStarterInfo_1:
	playmoncry VAR_TEMP_1, CRY_MODE_NORMAL
	showmonpic VAR_TEMP_1, 10, 3
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	msgbox RouteOasis_Text_Ball_WantToPickThisOne, MSGBOX_YESNO
	waitmoncry
	return

RouteOasis_EventScript_SetupInteractedStarterInfo_3:
	setvar VAR_TEMP_1, SPECIES_CHIKORITA
	bufferstring STR_VAR_2, RouteOasis_EventScript_SetupInteractedStarterInfo_Text_0
	setvar VAR_TEXT_COLOR, 6
	goto RouteOasis_EventScript_SetupInteractedStarterInfo_1

RouteOasis_EventScript_SetupInteractedStarterInfo_4:
	setvar VAR_TEMP_1, SPECIES_CYNDAQUIL
	bufferstring STR_VAR_2, RouteOasis_EventScript_SetupInteractedStarterInfo_Text_1
	setvar VAR_TEXT_COLOR, 4
	goto RouteOasis_EventScript_SetupInteractedStarterInfo_1

RouteOasis_EventScript_SetupInteractedStarterInfo_5:
	setvar VAR_TEMP_1, SPECIES_TOTODILE
	bufferstring STR_VAR_2, RouteOasis_EventScript_SetupInteractedStarterInfo_Text_2
	setvar VAR_TEXT_COLOR, 8
	goto RouteOasis_EventScript_SetupInteractedStarterInfo_1


RouteOasis_EventScript_GiveStarterToPlayer:
	givemon VAR_TEMP_1, 5
	setflag FLAG_SYS_POKEMON_GET
	msgbox RouteOasis_Text_Ball_StarterHasBecomeCompanion, MSGBOX_DEFAULT
	playmoncry VAR_TEMP_1, CRY_MODE_NORMAL
	waitmoncry
	delay 10
	playfanfare MUS_CAUGHT_INTRO
	waitfanfare
	closemessage
	return


RouteOasis_EventScript_PositionCharactersAfterSelection:
	fadescreenspeed FADE_TO_BLACK, 15
	hidemonpic
	setobjectxy OBJ_EVENT_ID_PLAYER, 24, 32
	setobjectxy 1, 25, 31
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	turnobject 1, DIR_NORTH
	removeobject VAR_LAST_TALKED
	delay 60
	fadescreenspeed FADE_FROM_BLACK, 15
	return


RouteOasis_EventScript_SetupInteractedStarterInfo_Text_0:
	.string "Grass$"

RouteOasis_EventScript_SetupInteractedStarterInfo_Text_1:
	.string "Fire$"

RouteOasis_EventScript_SetupInteractedStarterInfo_Text_2:
	.string "Water$"
