SandalineColony_Mart_MapScripts::
	.byte 0


SandalineColony_Mart_EventScript_ClerkM::
	compare VAR_MAP_SCENE_SANDALINE_COLONY_POKECENTER, 1
	goto_if_lt SandalineColony_Mart_EventScript_ClerkM_1
	lock
	faceplayer
	message Text_MayIHelpYou
	waitmessage
	pokemart Mart_StandardItems
	msgbox Text_PleaseComeAgain
	closemessage
	release
	return

SandalineColony_Mart_EventScript_ClerkM_1:
	msgbox SandalineColony_Mart_Text_ClerkM_ThatGuyIsWaitingForSomeone, MSGBOX_NPC
	return


SandalineColony_Mart_EventScript_ClerkF::
	msgbox SandalineColony_Mart_Text_ClerkF_WelcomeToThePokemonMart, MSGBOX_NPC
	return


	.align 2
Mart_StandardItems:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_REPEL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_NONE

SandalineColony_Mart_EventScript_Bugsy::
	lock
	applymovement 5, SandalineColony_Mart_Movement_Bugsy_RunInPlace
	waitmovement 5
	msgbox SandalineColony_Mart_Text_Bugsy_TookYouAWhile
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SandalineColony_Mart_Movement_Player_OutOfTheWay
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 5, SandalineColony_Mart_Movement_Bugsy_WalkToClerk
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, SandalineColony_Mart_Movement_Player_FollowBugsyToClerk
	waitmovement 5
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject 5, DIR_EAST
	msgbox SandalineColony_Mart_Text_Bugsy_ThisIsAMart
	closemessage
	applymovement 5, SandalineColony_Mart_Movement_TurnToClerk
	waitmovement 5
	msgbox SandalineColony_Mart_Text_Bugsy_IdLikeToBuyPokeBalls
	closemessage
	applymovement 1, SandalineColony_Mart_Movement_ClerkM_GivePokeBallsToBugsy
	waitmovement 1
	msgbox SandalineColony_Mart_Text_ClerkM_ThatWouldBeMoney
	closemessage
	playse SE_SHOP
	msgbox SandalineColony_Mart_Text_Scene_BugsyPays, MSGBOX_DEFAULT
	waitse
	closemessage
	msgbox SandalineColony_Mart_Text_ClerkM_YouReceiveAPremierBall
	closemessage
	msgbox SandalineColony_Mart_Text_Bugsy_ThankYou
	closemessage
	turnobject 5, DIR_EAST
	msgbox SandalineColony_Mart_Text_Bugsy_ItemsCostMoney
	closemessage
	applymovement 5, SandalineColony_Mart_Movement_Bugsy_WalkOut
	waitmovement 5
	removeobject 5
	playse SE_EXIT
	delay 120
	setvar VAR_MAP_SCENE_SANDALINE_COLONY_POKECENTER, 1
	clearflag FLAG_HIDE_BUGSY_IN_SANDALINE_POKECENTER
	release
	return


SandalineColony_Mart_Movement_Bugsy_RunInPlace:
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	step_end

SandalineColony_Mart_Movement_Player_OutOfTheWay:
	walk_down
	face_up
	step_end

SandalineColony_Mart_Movement_Bugsy_WalkToClerk:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SandalineColony_Mart_Movement_Player_FollowBugsyToClerk:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SandalineColony_Mart_Movement_TurnToClerk:
	walk_in_place_left
	step_end

SandalineColony_Mart_Movement_ClerkM_GivePokeBallsToBugsy:
	walk_in_place_slow_right
	step_end

SandalineColony_Mart_Movement_Bugsy_WalkOut:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_down
	step_end
