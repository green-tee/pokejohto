AzaleaTown_House1_MapScripts::
	.byte 0

AzaleaTown_House1_EventScript_BadgeGuy::
	lock
	faceplayer
	msgbox AzaleaTown_House1_Text_BadgesHaveAmazingSecrets
	message AzaleaTown_House1_Text_DescribeWhichBadge
	waitmessage
	setvar VAR_0x8004, LISTMENU_BADGES
	special ListMenu
	waitstate
	switch VAR_RESULT
	case 0, AzaleaTown_House1_EventScript_DescribeBoulderBadge
	case 1, AzaleaTown_House1_EventScript_DescribeCascadeBadge
	case 2, AzaleaTown_House1_EventScript_DescribeThunderBadge
	case 3, AzaleaTown_House1_EventScript_DescribeRainbowBadge
	case 4, AzaleaTown_House1_EventScript_DescribeSoulBadge
	case 5, AzaleaTown_House1_EventScript_DescribeMarshBadge
	case 6, AzaleaTown_House1_EventScript_DescribeVolcanoBadge
	case 7, AzaleaTown_House1_EventScript_DescribeEarthBadge
	case 8, AzaleaTown_House1_EventScript_StopDescribingBadges
	case 127, AzaleaTown_House1_EventScript_StopDescribingBadges
	end

AzaleaTown_House1_EventScript_DescribeAnotherBadge::
	message AzaleaTown_House1_Text_DescribeWhichBadge
	waitmessage
	special ReturnToListMenu
	waitstate
	switch VAR_RESULT
	case 0, AzaleaTown_House1_EventScript_DescribeBoulderBadge
	case 1, AzaleaTown_House1_EventScript_DescribeCascadeBadge
	case 2, AzaleaTown_House1_EventScript_DescribeThunderBadge
	case 3, AzaleaTown_House1_EventScript_DescribeRainbowBadge
	case 4, AzaleaTown_House1_EventScript_DescribeSoulBadge
	case 5, AzaleaTown_House1_EventScript_DescribeMarshBadge
	case 6, AzaleaTown_House1_EventScript_DescribeVolcanoBadge
	case 7, AzaleaTown_House1_EventScript_DescribeEarthBadge
	case 8, AzaleaTown_House1_EventScript_StopDescribingBadges
	case 127, AzaleaTown_House1_EventScript_StopDescribingBadges
	end

AzaleaTown_House1_EventScript_DescribeBoulderBadge::
	msgbox AzaleaTown_House1_Text_AttackStatFlash
	goto AzaleaTown_House1_EventScript_DescribeAnotherBadge
	end

AzaleaTown_House1_EventScript_DescribeCascadeBadge::
	msgbox AzaleaTown_House1_Text_ObeyLv30Cut
	goto AzaleaTown_House1_EventScript_DescribeAnotherBadge
	end

AzaleaTown_House1_EventScript_DescribeThunderBadge::
	msgbox AzaleaTown_House1_Text_SpeedStatFly
	goto AzaleaTown_House1_EventScript_DescribeAnotherBadge
	end

AzaleaTown_House1_EventScript_DescribeRainbowBadge::
	msgbox AzaleaTown_House1_Text_ObeyLv50Strength
	goto AzaleaTown_House1_EventScript_DescribeAnotherBadge
	end

AzaleaTown_House1_EventScript_DescribeSoulBadge::
	msgbox AzaleaTown_House1_Text_DefenseStatSurf
	goto AzaleaTown_House1_EventScript_DescribeAnotherBadge
	end

AzaleaTown_House1_EventScript_DescribeMarshBadge::
	msgbox AzaleaTown_House1_Text_ObeyLv70RockSmash
	goto AzaleaTown_House1_EventScript_DescribeAnotherBadge
	end

AzaleaTown_House1_EventScript_DescribeVolcanoBadge::
	msgbox AzaleaTown_House1_Text_SpStatsWaterfall
	goto AzaleaTown_House1_EventScript_DescribeAnotherBadge
	end

AzaleaTown_House1_EventScript_DescribeEarthBadge::
	msgbox AzaleaTown_House1_Text_AllMonsWillObeyYou
	goto AzaleaTown_House1_EventScript_DescribeAnotherBadge
	end

AzaleaTown_House1_EventScript_StopDescribingBadges::
	msgbox AzaleaTown_House1_Text_ComeVisitAnytime
	release
	end
