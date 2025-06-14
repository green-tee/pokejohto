AzaleaTown_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_PokemonCenter_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

AzaleaTown_PokemonCenter_OnTransition::
	setrespawn SPAWN_AZALEA_TOWN
	end

AzaleaTown_PokemonCenter_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse
	release
	end

AzaleaTown_PokemonCenter_EventScript_Gentleman::
	msgbox AzaleaTown_PokemonCenter_Text_EveryoneCallsBillPokemaniac, MSGBOX_NPC
	end

AzaleaTown_PokemonCenter_EventScript_Rocker::
	msgbox AzaleaTown_PokemonCenter_Text_BillDoesWhateverForRareMons, MSGBOX_NPC
	end

AzaleaTown_PokemonCenter_EventScript_Youngster::
	lock
	faceplayer
	famechecker FAMECHECKER_BILL, 1
	msgbox AzaleaTown_PokemonCenter_Text_BillCollectsRareMons
	release
	end

AzaleaTown_PokemonCenter_EventScript_Lass::
	msgbox AzaleaTown_PokemonCenter_Text_TryTradingUpstairs, MSGBOX_NPC
	end
