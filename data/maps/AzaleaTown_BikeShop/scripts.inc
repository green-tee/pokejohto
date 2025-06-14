AzaleaTown_BikeShop_MapScripts::
	.byte 0

AzaleaTown_BikeShop_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BICYCLE, AzaleaTown_BikeShop_EventScript_AlreadyGotBicycle
	goto_if_set FLAG_GOT_BIKE_VOUCHER, AzaleaTown_BikeShop_EventScript_ExchangeBikeVoucher
	showmoneybox 0, 0
	message AzaleaTown_BikeShop_Text_WelcomeToBikeShop
	waitmessage
	multichoice 11, 0, MULTICHOICE_BIKE_SHOP, FALSE
	switch VAR_RESULT
	case 0, AzaleaTown_BikeShop_EventScript_TryPurchaseBicycle
	case 1, AzaleaTown_BikeShop_EventScript_ClerkGoodbye
	case 127, AzaleaTown_BikeShop_EventScript_ClerkGoodbye
	end

@ The Bicycle price / players money is never actually checked
AzaleaTown_BikeShop_EventScript_TryPurchaseBicycle::
	msgbox AzaleaTown_BikeShop_Text_SorryYouCantAffordIt
	goto AzaleaTown_BikeShop_EventScript_ClerkGoodbye
	end

AzaleaTown_BikeShop_EventScript_ClerkGoodbye::
	msgbox AzaleaTown_BikeShop_Text_ThankYouComeAgain
	hidemoneybox
	release
	end

AzaleaTown_BikeShop_EventScript_ExchangeBikeVoucher::
	msgbox AzaleaTown_BikeShop_Text_OhBikeVoucherHereYouGo
	msgreceiveditem AzaleaTown_BikeShop_Text_ExchangedVoucherForBicycle, ITEM_BICYCLE, 1, MUS_OBTAIN_KEY_ITEM
	setflag FLAG_GOT_BICYCLE
	additem ITEM_BICYCLE
	removeitem ITEM_BIKE_VOUCHER
	msgbox AzaleaTown_BikeShop_Text_ThankYouComeAgain
	release
	end

AzaleaTown_BikeShop_EventScript_AlreadyGotBicycle::
	msgbox AzaleaTown_BikeShop_Text_HowDoYouLikeNewBicycle
	release
	end

@ Unused
AzaleaTown_BikeShop_EventScript_NoRoomForBicycle::
	msgbox AzaleaTown_BikeShop_Text_MakeRoomForBicycle
	release
	end

AzaleaTown_BikeShop_EventScript_Woman::
	msgbox AzaleaTown_BikeShop_Text_CityBikeGoodEnoughForMe, MSGBOX_NPC
	end

AzaleaTown_BikeShop_EventScript_Youngster::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BICYCLE, AzaleaTown_BikeShop_EventScript_YoungsterHaveBike
	msgbox AzaleaTown_BikeShop_Text_BikesCoolButExpensive
	release
	end

AzaleaTown_BikeShop_EventScript_YoungsterHaveBike::
	msgbox AzaleaTown_BikeShop_Text_WowYourBikeIsCool
	release
	end

AzaleaTown_BikeShop_EventScript_Bicycle::
	msgbox AzaleaTown_BikeShop_Text_ShinyNewBicycle, MSGBOX_SIGN
	end
