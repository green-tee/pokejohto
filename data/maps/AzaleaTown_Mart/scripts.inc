AzaleaTown_Mart_MapScripts::
	.byte 0

AzaleaTown_Mart_EventScript_Youngster::
	msgbox AzaleaTown_Mart_Text_RepelWorksOnWeakMons, MSGBOX_NPC
	end

AzaleaTown_Mart_EventScript_Woman::
	msgbox AzaleaTown_Mart_Text_DoYouKnowAboutRareCandy, MSGBOX_NPC
	end

AzaleaTown_Mart_EventScript_Clerk::
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	message Text_MayIHelpYou
	waitmessage
	pokemart AzaleaTown_Mart_Items
	msgbox Text_PleaseComeAgain
	release
	end

	.align 2
AzaleaTown_Mart_Items::
	.2byte ITEM_POKE_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end
