PalletTown_MapScripts::
	.byte 0


PalletTown_EventScript_FatMan::
	lockall
	faceplayer
	goto_if_set FLAG_SYS_POKEMON_GET, PalletTown_EventScript_FatMan_2
	msgbox PalletTown_Text_FatManPlayerHasNoPokemon
	givemon SPECIES_ABSOL, 5, ITEM_NONE
	playfanfare MUS_OBTAIN_ITEM
	msgbox PalletTown_EventScript_FatMan_Text_0
	waitfanfare
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_SYS_POKEDEX_GET
	msgbox PalletTown_Text_FatManJustGavePokemon
PalletTown_EventScript_FatMan_1:
	releaseall
	return

PalletTown_EventScript_FatMan_2:
	msgbox PalletTown_Text_FatManPlayerHasPokemon
	goto PalletTown_EventScript_FatMan_1


PalletTown_EventScript_FatMan_Text_0:
	.string "Absol obtained!$"

PalletTown_Text_FatManPlayerHasNoPokemon::
	.string "Hey there! You have no Pokémon with\n"
	.string "you, am I right?\p"
	.string "Here, take this one!$"

PalletTown_Text_FatManJustGavePokemon::
	.string "Don't mention it! Stay safe out there!$"

PalletTown_Text_FatManPlayerHasPokemon::
	.string "Technology is incredible! Some guys\n"
	.string "managed to reverse-engineer old\l"
	.string "Pokémon games for the GBA!\p"
	.string "I… I can't even fathom.$"
