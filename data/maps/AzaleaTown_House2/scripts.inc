AzaleaTown_House2_MapScripts::
	.byte 0

AzaleaTown_House2_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM28_FROM_ROCKET, AzaleaTown_House2_EventScript_HikerGotTM28
	msgbox AzaleaTown_House2_Text_RocketsStoleTMForDig
	release
	end

AzaleaTown_House2_EventScript_HikerGotTM28::
	msgbox AzaleaTown_House2_Text_TeachDiglettDigWithoutTM
	release
	end

AzaleaTown_House2_EventScript_Lass::
	msgbox AzaleaTown_House2_Text_TeamRocketTryingToDigIntoNoGood, MSGBOX_NPC
	end

AzaleaTown_House2_EventScript_WallHole::
	msgbox AzaleaTown_House2_Text_TeamRocketLeftWayOut, MSGBOX_SIGN
	end
