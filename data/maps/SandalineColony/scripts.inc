SandalineColony_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SandalineColony_EventScript_OnTransition
	.byte 0


SandalineColony_EventScript_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SANDALINE_COLONY
	return

