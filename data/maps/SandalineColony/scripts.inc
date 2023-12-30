SandalineColony_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SandalineColony_OnTransition
	.byte 0


SandalineColony_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SANDALINE_COLONY
	return


SandalineColony_EventScript_RadiosaHostelSign::
	msgbox SandalineColony_Text_RadiosaHostel, MSGBOX_SIGN
	return

