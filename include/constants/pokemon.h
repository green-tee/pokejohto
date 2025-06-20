#ifndef GUARD_CONSTANTS_POKEMON_H
#define GUARD_CONSTANTS_POKEMON_H

// For (Set|Get)(Box)?MonData
#define MON_DATA_PERSONALITY         0
#define MON_DATA_OT_ID               1
#define MON_DATA_NICKNAME            3
#define MON_DATA_LANGUAGE            4
#define MON_DATA_SANITY_IS_BAD_EGG   5
#define MON_DATA_SANITY_HAS_SPECIES  6
#define MON_DATA_SANITY_IS_EGG       7
#define MON_DATA_IS_SHINY            8
#define MON_DATA_OT_NAME             9
#define MON_DATA_MARKINGS           10
#define MON_DATA_CHECKSUM           11
#define MON_DATA_ENCRYPT_SEPARATOR  12
#define MON_DATA_SPECIES            13
#define MON_DATA_HELD_ITEM          14
#define MON_DATA_MOVE1              15
#define MON_DATA_MOVE2              16
#define MON_DATA_MOVE3              17
#define MON_DATA_MOVE4              18
#define MON_DATA_PP1                19
#define MON_DATA_PP2                20
#define MON_DATA_PP3                21
#define MON_DATA_PP4                22
#define MON_DATA_PP_BONUSES         23
#define MON_DATA_COOL               24
#define MON_DATA_BEAUTY             25
#define MON_DATA_CUTE               26
#define MON_DATA_EXP                27
#define MON_DATA_HP_EV              28
#define MON_DATA_ATK_EV             29
#define MON_DATA_DEF_EV             30
#define MON_DATA_SPEED_EV           31
#define MON_DATA_SPATK_EV           32
#define MON_DATA_SPDEF_EV           33
#define MON_DATA_FRIENDSHIP         34
#define MON_DATA_SMART              35
#define MON_DATA_POKERUS            36
#define MON_DATA_MET_LOCATION       37
#define MON_DATA_MET_LEVEL          38
#define MON_DATA_MET_GAME           39
#define MON_DATA_POKEBALL           40
#define MON_DATA_HP_IV              41
#define MON_DATA_ATK_IV             42
#define MON_DATA_DEF_IV             43
#define MON_DATA_SPEED_IV           44
#define MON_DATA_SPATK_IV           45
#define MON_DATA_SPDEF_IV           46
#define MON_DATA_IS_EGG             47
#define MON_DATA_ABILITY_NUM        48
#define MON_DATA_TOUGH              49
#define MON_DATA_SHEEN              50
#define MON_DATA_OT_GENDER          51
#define MON_DATA_COOL_RIBBON        52
#define MON_DATA_BEAUTY_RIBBON      53
#define MON_DATA_CUTE_RIBBON        54
#define MON_DATA_SMART_RIBBON       55
#define MON_DATA_TOUGH_RIBBON       56
#define MON_DATA_STATUS             57
#define MON_DATA_LEVEL              58
#define MON_DATA_HP                 59
#define MON_DATA_MAX_HP             60
#define MON_DATA_ATK                61
#define MON_DATA_DEF                62
#define MON_DATA_SPEED              63
#define MON_DATA_SPATK              64
#define MON_DATA_SPDEF              65
#define MON_DATA_MAIL               66
#define MON_DATA_SPECIES2           67
#define MON_DATA_IVS                68
#define MON_DATA_CHAMPION_RIBBON    69
#define MON_DATA_WINNING_RIBBON     70
#define MON_DATA_VICTORY_RIBBON     71
#define MON_DATA_ARTIST_RIBBON      72
#define MON_DATA_EFFORT_RIBBON      73
#define MON_DATA_MARINE_RIBBON      74
#define MON_DATA_LAND_RIBBON        75
#define MON_DATA_SKY_RIBBON         76
#define MON_DATA_COUNTRY_RIBBON     77
#define MON_DATA_NATIONAL_RIBBON    78
#define MON_DATA_EARTH_RIBBON       79
#define MON_DATA_WORLD_RIBBON       80
#define MON_DATA_UNUSED_RIBBONS     81
#define MON_DATA_EVENT_LEGAL        82
#define MON_DATA_KNOWN_MOVES        83
#define MON_DATA_RIBBON_COUNT       84
#define MON_DATA_RIBBONS            85
#define MON_DATA_ATK2               86
#define MON_DATA_DEF2               87
#define MON_DATA_SPEED2             88
#define MON_DATA_SPATK2             89
#define MON_DATA_SPDEF2             90

// Pokemon types
#define TYPE_NONE           255
#define TYPE_NORMAL         0
#define TYPE_FIGHTING       1
#define TYPE_FLYING         2
#define TYPE_POISON         3
#define TYPE_GROUND         4
#define TYPE_ROCK           5
#define TYPE_BUG            6
#define TYPE_GHOST          7
#define TYPE_STEEL          8
#define TYPE_MYSTERY        9
#define TYPE_FIRE           10
#define TYPE_WATER          11
#define TYPE_GRASS          12
#define TYPE_ELECTRIC       13
#define TYPE_PSYCHIC        14
#define TYPE_ICE            15
#define TYPE_DRAGON         16
#define TYPE_DARK           17
#define NUMBER_OF_MON_TYPES 18

// Pokemon egg groups
#define EGG_GROUP_NONE 0
#define EGG_GROUP_MONSTER 1
#define EGG_GROUP_WATER_1 2
#define EGG_GROUP_BUG 3
#define EGG_GROUP_FLYING 4
#define EGG_GROUP_FIELD 5
#define EGG_GROUP_FAIRY 6
#define EGG_GROUP_GRASS 7
#define EGG_GROUP_HUMAN_LIKE 8
#define EGG_GROUP_WATER_3 9
#define EGG_GROUP_MINERAL 10
#define EGG_GROUP_AMORPHOUS 11
#define EGG_GROUP_WATER_2 12
#define EGG_GROUP_DITTO 13
#define EGG_GROUP_DRAGON 14
#define EGG_GROUP_UNDISCOVERED 15

#define EGG_GROUPS_PER_MON      2

// Pokemon natures
#define NATURE_HARDY    0
#define NATURE_LONELY   1
#define NATURE_BRAVE    2
#define NATURE_ADAMANT  3
#define NATURE_NAUGHTY  4
#define NATURE_BOLD     5
#define NATURE_DOCILE   6
#define NATURE_RELAXED  7
#define NATURE_IMPISH   8
#define NATURE_LAX      9
#define NATURE_TIMID    10
#define NATURE_HASTY    11
#define NATURE_SERIOUS  12
#define NATURE_JOLLY    13
#define NATURE_NAIVE    14
#define NATURE_MODEST   15
#define NATURE_MILD     16
#define NATURE_QUIET    17
#define NATURE_BASHFUL  18
#define NATURE_RASH     19
#define NATURE_CALM     20
#define NATURE_GENTLE   21
#define NATURE_SASSY    22
#define NATURE_CAREFUL  23
#define NATURE_QUIRKY   24
#define NUM_NATURES     25

// Pokemon Stats
#define STAT_HP      0
#define STAT_ATK     1
#define STAT_DEF     2
#define STAT_SPEED   3
#define STAT_SPATK   4
#define STAT_SPDEF   5
#define NUM_STATS    6

#define STAT_ACC     6 // Only in battles.
#define STAT_EVASION 7 // Only in battles.

#define NUM_NATURE_STATS (NUM_STATS - 1) // excludes HP
#define NUM_BATTLE_STATS (NUM_STATS + 2) // includes Accuracy and Evasion

#define MIN_STAT_STAGE     0
#define DEFAULT_STAT_STAGE 6
#define MAX_STAT_STAGE    12

// Shiny odds
#define SHINY_ODDS_OBSOLETE 8 // Actual probability is SHINY_ODDS_OBSOLETE/65536
// SHINY_ODDS_OBSOLETE is not used anymore. Probability is now SHINY_ODDS_NUMERATOR / SHINY_ODDS_DENOMINATOR
#define SHINY_ODDS_NUMERATOR   0x00010
#define SHINY_ODDS_DENOMINATOR 0x10000

// Learning moves
#define MON_ALREADY_KNOWS_MOVE 0xFFFE
#define MON_HAS_MAX_MOVES      0xFFFF

#define PLAYER_HAS_TWO_USABLE_MONS              0x0
#define PLAYER_HAS_ONE_MON                      0x1
#define PLAYER_HAS_ONE_USABLE_MON               0x2

#define MAX_LEVEL 100

#define OT_ID_RANDOM 2
#define OT_ID_PRESET 1
#define OT_ID_PLAYER_ID 0

#define MON_GIVEN_TO_PARTY      0x0
#define MON_GIVEN_TO_PC         0x1
#define MON_CANT_GIVE           0x2

#define MON_MALE       0x00
#define MON_FEMALE     0xFE
#define MON_GENDERLESS 0xFF

#define FRIENDSHIP_EVENT_GROW_LEVEL           0
#define FRIENDSHIP_EVENT_VITAMIN              1
#define FRIENDSHIP_EVENT_BATTLE_ITEM          2
#define FRIENDSHIP_EVENT_LEAGUE_BATTLE        3
#define FRIENDSHIP_EVENT_LEARN_TMHM           4
#define FRIENDSHIP_EVENT_WALKING              5
#define FRIENDSHIP_EVENT_MASSAGE              6
#define FRIENDSHIP_EVENT_FAINT_SMALL          7
#define FRIENDSHIP_EVENT_FAINT_OUTSIDE_BATTLE 8
#define FRIENDSHIP_EVENT_FAINT_LARGE          9

#define MAX_PER_STAT_IVS 31
#define MAX_IV_MASK 31
#define USE_RANDOM_IVS (MAX_PER_STAT_IVS + 1)
#define MAX_PER_STAT_EVS 255
#define MAX_TOTAL_EVS 510
#define EV_ITEM_RAISE_LIMIT 100

#define PARTY_SIZE 6
#define BOX_NAME_LENGTH 8

#define EVO_MODE_NORMAL     0
#define EVO_MODE_TRADE      1
#define EVO_MODE_ITEM_USE   2
#define EVO_MODE_ITEM_CHECK 3 // If an Everstone is being held, still want to show that the stone *could* be used on that Pokémon to evolve

#define MON_PIC_WIDTH 64
#define MON_PIC_HEIGHT 64
#define MON_PIC_SIZE (MON_PIC_WIDTH * MON_PIC_HEIGHT / 2)

// used by ShouldIgnoreDeoxysForm
#define DEOXYS_CHECK_BATTLE_SPRITE      1
#define DEOXYS_CHECK_TRADE_MAIN         3
#define DEOXYS_CHECK_BATTLE_ANIM        5

#endif // GUARD_CONSTANTS_POKEMON_H
