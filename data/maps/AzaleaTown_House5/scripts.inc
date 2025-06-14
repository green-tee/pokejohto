AzaleaTown_House5_MapScripts::
	.byte 0

AzaleaTown_House5_EventScript_BerryPowderMan::
	lock
	faceplayer
	goto_if_set FLAG_GOT_POWDER_JAR, AzaleaTown_House5_EventScript_AskToExchangePowder
	msgbox AzaleaTown_House1_Text_AnyInterestInBerries, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AzaleaTown_House5_EventScript_NoInterestInBerries
	goto_if_unset FLAG_SYS_GOT_BERRY_POUCH, AzaleaTown_House5_EventScript_NoBerries
	msgbox AzaleaTown_House1_Text_HaveJustTheThing
	setflag FLAG_GOT_POWDER_JAR
	giveitem ITEM_POWDER_JAR
	goto_if_eq VAR_RESULT, FALSE, EventScript_BagIsFull
	msgbox AzaleaTown_House1_Text_GoCrushBerriesAtDirectCorner
	release
	end

AzaleaTown_House5_EventScript_NoBerries::
	msgbox AzaleaTown_House1_Text_WhyMustYouLieNoBerries
	release
	end

AzaleaTown_House5_EventScript_NoInterestInBerries::
	msgbox AzaleaTown_House1_Text_TakeInterestInAllSortsOfThings
	release
	end

AzaleaTown_House5_EventScript_AskToExchangePowder::
	special DisplayBerryPowderVendorMenu
	msgbox AzaleaTown_House1_Text_HaveYouBroughtBerryPowder
	goto AzaleaTown_House5_EventScript_ChooseExchangeItem
	end

AzaleaTown_House5_EventScript_ChooseExchangeItem::
	message AzaleaTown_House5_Text_ExchangeWithWhat
	waitmessage
	setvar VAR_0x8004, LISTMENU_BERRY_POWDER
	special ListMenu
	waitstate
	switch VAR_RESULT
	case 0, AzaleaTown_House5_EventScript_EnergyPowder
	case 1, AzaleaTown_House5_EventScript_EnergyRoot
	case 2, AzaleaTown_House5_EventScript_HealPowder
	case 3, AzaleaTown_House5_EventScript_RevivalHerb
	case 4, AzaleaTown_House5_EventScript_Protein
	case 5, AzaleaTown_House5_EventScript_Iron
	case 6, AzaleaTown_House5_EventScript_Carbos
	case 7, AzaleaTown_House5_EventScript_Calcium
	case 8, AzaleaTown_House5_EventScript_Zinc
	case 9, AzaleaTown_House5_EventScript_HPUp
	case 10, AzaleaTown_House5_EventScript_PPUp
	case 11, AzaleaTown_House5_EventScript_ExitMenu
	case 127, AzaleaTown_House5_EventScript_ExitMenu
	end

AzaleaTown_House5_EventScript_EnergyPowder::
	bufferitemname STR_VAR_1, ITEM_ENERGY_POWDER
	setvar VAR_0x8008, ITEM_ENERGY_POWDER
	setvar VAR_0x8009, 50
	goto AzaleaTown_House5_EventScript_ExchangePowderForItem
	end

AzaleaTown_House5_EventScript_EnergyRoot::
	bufferitemname STR_VAR_1, ITEM_ENERGY_ROOT
	setvar VAR_0x8008, ITEM_ENERGY_ROOT
	setvar VAR_0x8009, 80
	goto AzaleaTown_House5_EventScript_ExchangePowderForItem
	end

AzaleaTown_House5_EventScript_HealPowder::
	bufferitemname STR_VAR_1, ITEM_HEAL_POWDER
	setvar VAR_0x8008, ITEM_HEAL_POWDER
	setvar VAR_0x8009, 50
	goto AzaleaTown_House5_EventScript_ExchangePowderForItem
	end

AzaleaTown_House5_EventScript_RevivalHerb::
	bufferitemname STR_VAR_1, ITEM_REVIVAL_HERB
	setvar VAR_0x8008, ITEM_REVIVAL_HERB
	setvar VAR_0x8009, 300
	goto AzaleaTown_House5_EventScript_ExchangePowderForItem
	end

AzaleaTown_House5_EventScript_Protein::
	bufferitemname STR_VAR_1, ITEM_PROTEIN
	setvar VAR_0x8008, ITEM_PROTEIN
	setvar VAR_0x8009, 1000
	goto AzaleaTown_House5_EventScript_ExchangePowderForItem
	end

AzaleaTown_House5_EventScript_Iron::
	bufferitemname STR_VAR_1, ITEM_IRON
	setvar VAR_0x8008, ITEM_IRON
	setvar VAR_0x8009, 1000
	goto AzaleaTown_House5_EventScript_ExchangePowderForItem
	end

AzaleaTown_House5_EventScript_Carbos::
	bufferitemname STR_VAR_1, ITEM_CARBOS
	setvar VAR_0x8008, ITEM_CARBOS
	setvar VAR_0x8009, 1000
	goto AzaleaTown_House5_EventScript_ExchangePowderForItem
	end

AzaleaTown_House5_EventScript_Calcium::
	bufferitemname STR_VAR_1, ITEM_CALCIUM
	setvar VAR_0x8008, ITEM_CALCIUM
	setvar VAR_0x8009, 1000
	goto AzaleaTown_House5_EventScript_ExchangePowderForItem
	end

AzaleaTown_House5_EventScript_Zinc::
	bufferitemname STR_VAR_1, ITEM_ZINC
	setvar VAR_0x8008, ITEM_ZINC
	setvar VAR_0x8009, 1000
	goto AzaleaTown_House5_EventScript_ExchangePowderForItem
	end

AzaleaTown_House5_EventScript_HPUp::
	bufferitemname STR_VAR_1, ITEM_HP_UP
	setvar VAR_0x8008, ITEM_HP_UP
	setvar VAR_0x8009, 1000
	goto AzaleaTown_House5_EventScript_ExchangePowderForItem
	end

AzaleaTown_House5_EventScript_PPUp::
	bufferitemname STR_VAR_1, ITEM_PP_UP
	setvar VAR_0x8008, ITEM_PP_UP
	setvar VAR_0x8009, 3000
	goto AzaleaTown_House5_EventScript_ExchangePowderForItem
	end

AzaleaTown_House5_EventScript_ExitMenu::
	msgbox AzaleaTown_House1_Text_SeeMeIfYoudLikeToTradePowder
	special RemoveBerryPowderVendorMenu
	release
	end

AzaleaTown_House5_EventScript_ExchangePowderForItem::
	msgbox AzaleaTown_House1_Text_YoullExchangeBerryPowderForItem, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AzaleaTown_House5_EventScript_ChooseExchangeItem
	copyvar VAR_0x8004, VAR_0x8009
	specialvar VAR_RESULT, Script_HasEnoughBerryPowder
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_House5_EventScript_NotEnoughBerryPowder
	giveitem VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_House5_EventScript_BagIsFull
	copyvar VAR_0x8004, VAR_0x8009
	special Script_TakeBerryPowder
	special PrintPlayerBerryPowderAmount
	msgbox AzaleaTown_House1_Text_TradeMoreBerryPowder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, AzaleaTown_House5_EventScript_ChooseExchangeItem
	msgbox AzaleaTown_House1_Text_HopeToSeeYouAgain
	special RemoveBerryPowderVendorMenu
	release
	end

AzaleaTown_House5_EventScript_BagIsFull::
	msgbox Text_BagIsFull
	special RemoveBerryPowderVendorMenu
	release
	end

AzaleaTown_House5_EventScript_NotEnoughBerryPowder::
	msgbox AzaleaTown_House1_Text_DontHaveEnoughBerryPowder
	goto AzaleaTown_House5_EventScript_ChooseExchangeItem
	end

AzaleaTown_House5_EventScript_BerryCrushRankings::
	lockall
	goto_if_questlog EventScript_ReleaseEnd
	special ShowBerryCrushRankings
	waitstate
	releaseall
	end
