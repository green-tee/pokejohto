AzaleaTown_House3_MapScripts::
	.byte 0

AzaleaTown_House3_EventScript_OldWoman::
	msgbox AzaleaTown_House3_Text_PleaseTradeWithMyHusband, MSGBOX_NPC
	end

AzaleaTown_House3_EventScript_Dontae::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_JYNX
	call EventScript_GetInGameTradeSpeciesInfo
	goto_if_set FLAG_DID_ZYNX_TRADE, AzaleaTown_House3_EventScript_AlreadyTraded
	msgbox Trade_Text_DoYouHaveMonWouldYouTradeForMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AzaleaTown_House3_EventScript_DeclineTrade
	call EventScript_ChooseMonForInGameTrade
	goto_if_ge VAR_0x8004, PARTY_SIZE, AzaleaTown_House3_EventScript_DeclineTrade
	call EventScript_GetInGameTradeSpecies
	goto_if_ne VAR_RESULT, VAR_0x8009, AzaleaTown_House3_EventScript_NotRequestedMon
	call EventScript_DoInGameTrade
	msgbox Trade_Text_Thanks
	setflag FLAG_DID_ZYNX_TRADE
	release
	end

AzaleaTown_House3_EventScript_DeclineTrade::
	msgbox Trade_Text_WellIfYouDontWantTo
	release
	end

AzaleaTown_House3_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox Trade_Text_ThisIsntMon
	release
	end

AzaleaTown_House3_EventScript_AlreadyTraded::
	msgbox Trade_Text_HasTradedMonGrownStronger
	release
	end
