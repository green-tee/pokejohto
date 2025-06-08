FourIsland_PokemonCenter_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CableClub_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, CableClub_OnWarp
	map_script MAP_SCRIPT_ON_LOAD, CableClub_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, CableClub_OnTransition
	.byte 0

@ The below 3 are unused and leftover from RS
FourIsland_PokemonCenter_2F_EventScript_Colosseum::
	call CableClub_EventScript_Colosseum
	end

FourIsland_PokemonCenter_2F_EventScript_TradeCenter::
	call CableClub_EventScript_TradeCenter
	end

FourIsland_PokemonCenter_2F_EventScript_RecordCorner::
	call CableClub_EventScript_RecordCorner
	end

FourIsland_PokemonCenter_2F_EventScript_TestCountItem::
	lock
	faceplayer
	countitem ITEM_POKE_BALL, VAR_TEMP_1
	buffernumberstring STR_VAR_1, VAR_TEMP_1
	msgbox FourIsland_PokemonCenter_2F_EventScript_TestCountItem_Text_0
	closemessage
	release
	return


FourIsland_PokemonCenter_2F_EventScript_TestSlidingBlocks::
	lock
	faceplayer
	msgbox FourIsland_PokemonCenter_2F_EventScript_TestSlidingBlocks_Text_0
	closemessage
	playbgm MUS_ROWDY_RUMBLE, 0
	playslidingblocks 0
	fadedefaultbgm
	compare VAR_RESULT, 0
	goto_if_eq FourIsland_PokemonCenter_2F_EventScript_TestSlidingBlocks_2
	msgbox FourIsland_PokemonCenter_2F_EventScript_TestSlidingBlocks_Text_2
	closemessage
FourIsland_PokemonCenter_2F_EventScript_TestSlidingBlocks_1:
	release
	return

FourIsland_PokemonCenter_2F_EventScript_TestSlidingBlocks_2:
	msgbox FourIsland_PokemonCenter_2F_EventScript_TestSlidingBlocks_Text_1
	closemessage
	goto FourIsland_PokemonCenter_2F_EventScript_TestSlidingBlocks_1


FourIsland_PokemonCenter_2F_EventScript_TestCountItem_Text_0:
	.string "You have {STR_VAR_1} Poké Balls.$"

FourIsland_PokemonCenter_2F_EventScript_TestSlidingBlocks_Text_0:
	.string "Trying sliding blocks.$"

FourIsland_PokemonCenter_2F_EventScript_TestSlidingBlocks_Text_1:
	.string "Skill issue.$"

FourIsland_PokemonCenter_2F_EventScript_TestSlidingBlocks_Text_2:
	.string "Whatever.$"
