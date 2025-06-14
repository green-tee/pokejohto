.set LOCALID_POLICEMAN, 1
.set LOCALID_GRUNT,     2
.set LOCALID_SLOWBRO,   5
.set LOCALID_LASS,      6
.set LOCALID_RIVAL,     8
.set LOCALID_WOMAN,     11

AzaleaTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_OnTransition
	.byte 0

AzaleaTown_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_AZALEA_TOWN
	call_if_unset FLAG_GOT_SS_TICKET, AzaleaTown_EventScript_BlockExits
	end

AzaleaTown_EventScript_BlockExits::
	setobjectxyperm LOCALID_POLICEMAN, 30, 12
	setobjectxyperm LOCALID_SLOWBRO, 26, 31
	setobjectxyperm LOCALID_LASS, 27, 31
	return

AzaleaTown_EventScript_RivalTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto AzaleaTown_EventScript_Rival
	end

AzaleaTown_EventScript_RivalTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	setobjectxyperm LOCALID_RIVAL, 23, 0
	goto AzaleaTown_EventScript_Rival
	end

AzaleaTown_EventScript_RivalTriggerRight::
	lockall
	setvar VAR_TEMP_1, 2
	setobjectxyperm LOCALID_RIVAL, 24, 0
	goto AzaleaTown_EventScript_Rival
	end

AzaleaTown_EventScript_Rival::
	textcolor NPC_TEXT_COLOR_MALE
	setvar VAR_MAP_SCENE_ROUTE22, 2
	playbgm MUS_ENCOUNTER_RIVAL, 0
	addobject LOCALID_RIVAL
	applymovement LOCALID_RIVAL, AzaleaTown_Movement_RivalEnter
	waitmovement 0
	msgbox AzaleaTown_Text_RivalIntro
	setvar VAR_LAST_TALKED, LOCALID_RIVAL
	call_if_eq VAR_STARTER_MON, 2, AzaleaTown_EventScript_RivalSquirtle
	call_if_eq VAR_STARTER_MON, 1, AzaleaTown_EventScript_RivalBulbasaur
	call_if_eq VAR_STARTER_MON, 0, AzaleaTown_EventScript_RivalCharmander
	famechecker FAMECHECKER_BILL, 0
	msgbox AzaleaTown_Text_RivalPostBattle
	closemessage
	playbgm MUS_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, AzaleaTown_EventScript_RivalStartExit
	call_if_eq VAR_TEMP_1, 1, AzaleaTown_EventScript_RivalStartExit
	call_if_eq VAR_TEMP_1, 2, AzaleaTown_EventScript_RivalStartExitRight
	msgbox AzaleaTown_Text_OhRightLittlePresentAsFavor
	setvar VAR_MAP_SCENE_ROUTE33, 1
	setflag FLAG_GOT_FAME_CHECKER
	giveitem ITEM_FAME_CHECKER
	msgbox AzaleaTown_Text_ExplainFameCheckerSmellYa
	closemessage
	applymovement LOCALID_RIVAL, AzaleaTown_Movement_RivalExit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_RIVAL
	releaseall
	end

AzaleaTown_EventScript_RivalSquirtle::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_SQUIRTLE, AzaleaTown_Text_RivalDefeat
	return

AzaleaTown_EventScript_RivalBulbasaur::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_BULBASAUR, AzaleaTown_Text_RivalDefeat
	return

AzaleaTown_EventScript_RivalCharmander::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_CHARMANDER, AzaleaTown_Text_RivalDefeat
	return

AzaleaTown_EventScript_RivalStartExit::
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Movement_PlayerWatchRivalExit
	applymovement LOCALID_RIVAL, AzaleaTown_Movement_RivalStartExit
	waitmovement 0
	return

AzaleaTown_EventScript_RivalStartExitRight::
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Movement_PlayerWatchRivalExitRight
	applymovement LOCALID_RIVAL, AzaleaTown_Movement_RivalStartExitRight
	waitmovement 0
	return

AzaleaTown_Movement_PlayerWatchRivalExit::
	delay_16
	delay_8
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_down
	step_end

AzaleaTown_Movement_PlayerWatchRivalExitRight::
	delay_16
	delay_8
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

AzaleaTown_Movement_RivalEnter::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

AzaleaTown_Movement_RivalStartExit::
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	delay_16
	delay_16
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

AzaleaTown_Movement_RivalStartExitRight::
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	delay_16
	delay_16
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

AzaleaTown_Movement_RivalExit::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

AzaleaTown_EventScript_Grunt::
	lock
	faceplayer
	goto_if_defeated TRAINER_TEAM_ROCKET_GRUNT_5, AzaleaTown_EventScript_GruntDefeated
	message AzaleaTown_Text_GruntIntro
	waitmessage
	playbgm MUS_ENCOUNTER_ROCKET, 0
	waitbuttonpress
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_5, AzaleaTown_Text_GruntDefeat
	setvar VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 1
	goto AzaleaTown_EventScript_GruntDefeated
	end

AzaleaTown_EventScript_GruntDefeated::
	msgbox AzaleaTown_Text_OkayIllReturnStolenTM
	checkitemspace ITEM_TM28
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_EventScript_NoRoomForTM28
	giveitem_msg AzaleaTown_Text_RecoveredTM28FromGrunt, ITEM_TM28
	msgbox AzaleaTown_Text_BetterGetMovingBye
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_GRUNT
	fadescreen FADE_FROM_BLACK
	setflag FLAG_GOT_TM28_FROM_ROCKET
	release
	end

AzaleaTown_EventScript_NoRoomForTM28::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox AzaleaTown_Text_MakeRoomForThisCantRun
	release
	end

AzaleaTown_EventScript_GruntTriggerTop::
	lockall
	setvar VAR_TEMP_1, 0
	applymovement LOCALID_GRUNT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	goto AzaleaTown_EventScript_GruntTrigger
	end

AzaleaTown_EventScript_GruntTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 1
	applymovement LOCALID_GRUNT, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto AzaleaTown_EventScript_GruntTrigger
	end

AzaleaTown_EventScript_GruntTrigger::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox AzaleaTown_Text_GruntIntro
	setvar VAR_LAST_TALKED, LOCALID_GRUNT
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_5, AzaleaTown_Text_GruntDefeat
	setvar VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 1
	goto AzaleaTown_EventScript_GruntDefeated
	end

AzaleaTown_EventScript_Policeman::
	lock
	faceplayer
	msgbox AzaleaTown_Text_PeopleHereWereRobbed
	closemessage
	applymovement LOCALID_POLICEMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AzaleaTown_EventScript_LittleBoy::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SS_TICKET, AzaleaTown_EventScript_LittleBoySlowbroMoved
	msgbox AzaleaTown_Text_IfSlowbroWasntThereCouldCutTree
	release
	end

AzaleaTown_EventScript_LittleBoySlowbroMoved::
	msgbox AzaleaTown_Text_YouCanCutDownSmallTrees
	release
	end

AzaleaTown_EventScript_BaldingMan::
	msgbox AzaleaTown_Text_PokemonEncyclopediaAmusing, MSGBOX_NPC
	end

AzaleaTown_EventScript_Youngster::
	msgbox AzaleaTown_Text_TrainerLifeIsToughIsntIt, MSGBOX_NPC
	end

AzaleaTown_EventScript_CeruleanCaveGuard::
	msgbox AzaleaTown_Text_ThisIsCeruleanCave, MSGBOX_NPC
	end

AzaleaTown_EventScript_Woman::
	lock
	faceplayer
	msgbox AzaleaTown_Text_WantBrightRedBicycle
	closemessage
	applymovement LOCALID_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AzaleaTown_EventScript_Lass::
	lock
	random 3
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, 0, AzaleaTown_EventScript_SlowbroCommand1
	call_if_eq VAR_0x8008, 1, AzaleaTown_EventScript_SlowbroCommand2
	call_if_eq VAR_0x8008, 2, AzaleaTown_EventScript_SlowbroCommand3
	waitmessage
	delay 40
	playse SE_PIN
	applymovement LOCALID_SLOWBRO, Common_Movement_QuestionMark
	waitmovement 0
	delay 30
	call_if_eq VAR_0x8008, 0, AzaleaTown_EventScript_SlowbroFailed1
	call_if_eq VAR_0x8008, 1, AzaleaTown_EventScript_SlowbroFailed2
	call_if_eq VAR_0x8008, 2, AzaleaTown_EventScript_SlowbroFailed3
	release
	end

AzaleaTown_EventScript_SlowbroCommand1::
	message AzaleaTown_Text_SlowbroUseSonicboom
	return

AzaleaTown_EventScript_SlowbroCommand2::
	message AzaleaTown_Text_SlowbroPunch
	return

AzaleaTown_EventScript_SlowbroCommand3::
	message AzaleaTown_Text_SlowbroWithdraw
	return

AzaleaTown_EventScript_SlowbroFailed1::
	msgbox AzaleaTown_Text_SlowbroPayAttention
	return

AzaleaTown_EventScript_SlowbroFailed2::
	msgbox AzaleaTown_Text_NoYouBlewItAgain
	return

AzaleaTown_EventScript_SlowbroFailed3::
	msgbox AzaleaTown_Text_HardToControlMonsObedience
	return

AzaleaTown_EventScript_Slowbro::
	lock
	random 4
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, 0, AzaleaTown_EventScript_SlowbroText1
	call_if_eq VAR_0x8008, 1, AzaleaTown_EventScript_SlowbroText2
	call_if_eq VAR_0x8008, 2, AzaleaTown_EventScript_SlowbroText3
	call_if_eq VAR_0x8008, 3, AzaleaTown_EventScript_SlowbroText4
	release
	end

AzaleaTown_EventScript_SlowbroText1::
	msgbox AzaleaTown_Text_SlowbroTookSnooze
	return

AzaleaTown_EventScript_SlowbroText2::
	msgbox AzaleaTown_Text_SlowbroLoafingAround
	return

AzaleaTown_EventScript_SlowbroText3::
	msgbox AzaleaTown_Text_SlowbroTurnedAway
	return

AzaleaTown_EventScript_SlowbroText4::
	msgbox AzaleaTown_Text_SlowbroIgnoredOrders
	return

AzaleaTown_EventScript_CitySign::
	msgbox AzaleaTown_Text_CitySign, MSGBOX_SIGN
	end

AzaleaTown_EventScript_TrainerTips::
	msgbox AzaleaTown_Text_TrainerTipsHeldItems, MSGBOX_SIGN
	end

AzaleaTown_EventScript_BikeShopSign::
	msgbox AzaleaTown_Text_BikeShopSign, MSGBOX_SIGN
	end

AzaleaTown_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_MISTY, 0
	msgbox AzaleaTown_Text_GymSign
	releaseall
	end
