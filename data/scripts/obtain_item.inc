Std_ObtainItem::
	copyvar VAR_PREV_TEXT_COLOR, VAR_TEXT_COLOR
	textcolor NPC_TEXT_COLOR_NEUTRAL
	additem VAR_0x8000, VAR_0x8001
	copyvar VAR_0x8007, VAR_RESULT
	call EventScript_ObtainItemMessage
	copyvar VAR_TEXT_COLOR, VAR_PREV_TEXT_COLOR
	return


EventScript_ObtainItemMessage:
	bufferitemnameplural STR_VAR_2, VAR_0x8000, VAR_0x8001
	checkitemtype VAR_0x8000
	call EventScript_BufferPocketNameTryFanfare
	compare VAR_0x8007, TRUE
	goto_if_eq EventScript_ObtainItemMessage_1
	setvar VAR_RESULT, FALSE
	return

EventScript_ObtainItemMessage_1:
	call EventScript_CorrectObtainItemMessage
	waitfanfare
	waitmessage
	msgbox Text_PutItemAway
	setvar VAR_RESULT, TRUE
	return


EventScript_BufferPocketNameTryFanfare:
	switch VAR_RESULT
	case POCKET_ITEMS, EventScript_BufferPocketNameTryFanfare_2
	case POCKET_KEY_ITEMS, EventScript_BufferPocketNameTryFanfare_3
	case POCKET_POKE_BALLS, EventScript_BufferPocketNameTryFanfare_4
	case POCKET_TM_CASE, EventScript_BufferPocketNameTryFanfare_5
	case POCKET_BERRY_POUCH, EventScript_BufferPocketNameTryFanfare_6
	return

EventScript_BufferPocketNameTryFanfare_2:
	bufferstdstring STR_VAR_3, STDSTRING_ITEMS_POCKET
	compare VAR_0x8007, TRUE
	goto_if_eq EventScript_BufferPocketNameTryFanfare_7
	return

EventScript_BufferPocketNameTryFanfare_3:
	bufferstdstring STR_VAR_3, STDSTRING_KEY_ITEMS_POCKET
	compare VAR_0x8007, TRUE
	goto_if_eq EventScript_BufferPocketNameTryFanfare_9
	return

EventScript_BufferPocketNameTryFanfare_4:
	bufferstdstring STR_VAR_3, STDSTRING_POKEBALLS_POCKET
	compare VAR_0x8007, TRUE
	goto_if_eq EventScript_BufferPocketNameTryFanfare_11
	return

EventScript_BufferPocketNameTryFanfare_5:
	bufferstdstring STR_VAR_3, STDSTRING_TM_CASE
	compare VAR_0x8007, TRUE
	goto_if_eq EventScript_BufferPocketNameTryFanfare_13
	return

EventScript_BufferPocketNameTryFanfare_6:
	bufferstdstring STR_VAR_3, STDSTRING_BERRY_POUCH
	compare VAR_0x8007, TRUE
	goto_if_eq EventScript_BufferPocketNameTryFanfare_15
	return

EventScript_BufferPocketNameTryFanfare_7:
	playfanfare MUS_OBTAIN_ITEM
	return

EventScript_BufferPocketNameTryFanfare_9:
	playfanfare MUS_OBTAIN_KEY_ITEM
	return

EventScript_BufferPocketNameTryFanfare_11:
	playfanfare MUS_OBTAIN_ITEM
	return

EventScript_BufferPocketNameTryFanfare_13:
	playfanfare MUS_OBTAIN_TMHM
	return

EventScript_BufferPocketNameTryFanfare_15:
	playfanfare MUS_OBTAIN_BERRY
	return


EventScript_CorrectObtainItemMessage:
	compare VAR_0x8001, 1
	goto_if_eq EventScript_CorrectObtainItemMessage_1
	buffernumberstring STR_VAR_1, VAR_0x8001
	message Text_ObtainedNumberX
	return

EventScript_CorrectObtainItemMessage_1:
	message Text_ObtainedTheX
	return


EventScript_RestorePrevTextColor::
	copyvar VAR_TEXT_COLOR, VAR_PREV_TEXT_COLOR
	return

Std_ObtainDecoration::
	adddecoration VAR_0x8000
	copyvar VAR_0x8007, VAR_RESULT
	call EventScript_ObtainDecorMessage
	return

EventScript_ObtainDecorMessage::
	bufferdecorationname STR_VAR_2, VAR_0x8000
	call_if_eq VAR_0x8007, TRUE, EventScript_ObtainedDecor
	call_if_eq VAR_0x8007, FALSE, EventScript_NoRoomForDecor
	return

EventScript_ObtainedDecor::
	playfanfare MUS_OBTAIN_ITEM
	message Text_ObtainedTheDecor
	waitfanfare
	waitmessage
	msgbox Text_DecorTransferredToPC
	setvar VAR_RESULT, TRUE
	return

EventScript_NoRoomForDecor::
	setvar VAR_RESULT, FALSE
	return

Std_FindItem::
	lock
	faceplayer
	waitse
	copyvar VAR_0x8004, VAR_0x8000
	copyvar VAR_0x8005, VAR_0x8001
	checkitemspace VAR_0x8000, VAR_0x8001
	copyvar VAR_0x8007, VAR_RESULT
	bufferitemname STR_VAR_2, VAR_0x8000
	checkitemtype VAR_0x8000
	call EventScript_BufferPocketNameTryFanfare
	call_if_eq VAR_0x8007, TRUE, EventScript_PickUpItem
	call_if_eq VAR_0x8007, FALSE, EventScript_NoRoomToPickUpItem
	release
	return

EventScript_PickUpItem::
	removeobject VAR_LAST_TALKED
	additem VAR_0x8004, VAR_0x8005
	specialvar VAR_RESULT, BufferTMHMMoveName
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, TRUE, EventScript_FoundTMHM
	call_if_eq VAR_0x8008, FALSE, EventScript_FoundItem
	waitfanfare
	waitmessage
	msgbox Text_PutItemAway
	return

EventScript_FoundTMHM::
	message Text_FoundTMHMContainsMove
	return

EventScript_FoundItem::
	message Text_FoundOneItem
	return

EventScript_NoRoomToPickUpItem::
	msgbox Text_ObtainedTheX
	msgbox Text_TooBadBagFull
	setvar VAR_RESULT, FALSE
	return

EventScript_HiddenItemScript::
	lockall
	textcolor NPC_TEXT_COLOR_NEUTRAL
	waitse
	goto_if_eq VAR_0x8005, 0, EventScript_TryPickUpHiddenCoins
	call EventScript_TryPickUpHiddenItem
	goto_if_eq VAR_0x8007, TRUE, EventScript_PickedUpHiddenItem
	goto_if_eq VAR_0x8007, FALSE, EventScript_NoRoomForHiddenItem
	end

EventScript_TryPickUpHiddenItem::
	additem VAR_0x8005, VAR_0x8006
	copyvar VAR_0x8007, VAR_RESULT
	bufferitemname STR_VAR_2, VAR_0x8005
	checkitemtype VAR_0x8005
	call EventScript_BufferPocketNameTryFanfare
	return

EventScript_PickedUpHiddenItem::
	call_if_eq VAR_0x8006, 1, EventScript_FoundSingleItem
	call_if_ne VAR_0x8006, 1, EventScript_FoundMultipleItems
	waitfanfare
	waitmessage
	msgbox Text_PutItemAway
	special SetHiddenItemFlag
	releaseall
	end

EventScript_FoundSingleItem::
	message Text_FoundOneItem
	return

EventScript_FoundCoins::
	buffernumberstring STR_VAR_1, VAR_0x8006
	message Text_FoundXCoins
	return

EventScript_FoundMultipleItems::
	buffernumberstring STR_VAR_1, VAR_0x8006
	message Text_FoundXItems
	return

EventScript_NoRoomForHiddenItem::
	msgbox Text_FoundOneItem
	msgbox Text_TooBadBagFull
	setvar VAR_RESULT, 0
	releaseall
	end

EventScript_TryPickUpHiddenCoins::
	goto_if_unset FLAG_GOT_COIN_CASE, EventScript_NoCaseForHiddenCoins
	checkcoins VAR_RESULT
	specialvar VAR_RESULT, CheckAddCoins
	goto_if_eq VAR_RESULT, FALSE, EventScript_HiddenCoinsButCaseIsFull
	addcoins VAR_0x8006
	bufferstdstring STR_VAR_2, STDSTRING_COINS
	playfanfare MUS_LEVEL_UP
	call EventScript_FoundCoins
	waitfanfare
	waitmessage
	msgbox Text_PutCoinsAwayInCoinCase
	special SetHiddenItemFlag
	releaseall
	end

EventScript_HiddenCoinsButCaseIsFull::
	buffernumberstring STR_VAR_1, VAR_0x8006
	bufferstdstring STR_VAR_2, STDSTRING_COINS
	msgbox Text_FoundXCoins
	msgbox Text_CoinCaseIsFull
	setvar VAR_RESULT, 0
	releaseall
	end

EventScript_NoCaseForHiddenCoins::
	buffernumberstring STR_VAR_1, VAR_0x8006
	bufferstdstring STR_VAR_2, STDSTRING_COINS
	msgbox Text_FoundXCoins
	msgbox Text_NothingToPutThemIn
	setvar VAR_RESULT, 0
	releaseall
	end
