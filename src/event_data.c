#include "global.h"
#include "event_data.h"
#include "item_menu.h"
#include "quest_log.h"

static bool8 IsFlagOrVarStoredInQuestLog(u16 idx, u8 a1);

EWRAM_DATA u16 gSpecialVar_0x8000 = 0;
EWRAM_DATA u16 gSpecialVar_0x8001 = 0;
EWRAM_DATA u16 gSpecialVar_0x8002 = 0;
EWRAM_DATA u16 gSpecialVar_0x8003 = 0;
EWRAM_DATA u16 gSpecialVar_0x8004 = 0;
EWRAM_DATA u16 gSpecialVar_0x8005 = 0;
EWRAM_DATA u16 gSpecialVar_0x8006 = 0;
EWRAM_DATA u16 gSpecialVar_0x8007 = 0;
EWRAM_DATA u16 gSpecialVar_0x8008 = 0;
EWRAM_DATA u16 gSpecialVar_0x8009 = 0;
EWRAM_DATA u16 gSpecialVar_0x800A = 0;
EWRAM_DATA u16 gSpecialVar_0x800B = 0;
EWRAM_DATA u16 gSpecialVar_Result = 0;
EWRAM_DATA u16 gSpecialVar_LastTalked = 0;
EWRAM_DATA u16 gSpecialVar_Facing = 0;
EWRAM_DATA u16 gSpecialVar_MonBoxId = 0;
EWRAM_DATA u16 gSpecialVar_MonBoxPos = 0;
EWRAM_DATA u16 gSpecialVar_TextColor = 0;
EWRAM_DATA u16 gSpecialVar_PrevTextColor = 0;
EWRAM_DATA u16 gSpecialVar_0x8014 = 0;
EWRAM_DATA u8 sSpecialFlags[SPECIAL_FLAGS_COUNT] = {};

u16 gLastQuestLogStoredFlagOrVarIdx;

extern u16 *const gSpecialVars[];

void InitEventData(void)
{
    memset(gSaveBlock1Ptr->flags, 0, NUM_FLAG_BYTES);
    memset(gSaveBlock1Ptr->vars, 0, VARS_COUNT * 2);
    memset(sSpecialFlags, 0, SPECIAL_FLAGS_COUNT);
}

void ClearTempFieldEventData(void)
{
    memset(gSaveBlock1Ptr->flags, 0, 4);
    memset(gSaveBlock1Ptr->vars, 0, 16 * 2);
    FlagClear(FLAG_SYS_WHITE_FLUTE_ACTIVE);
    FlagClear(FLAG_SYS_BLACK_FLUTE_ACTIVE);
    FlagClear(FLAG_SYS_USE_STRENGTH);
    FlagClear(FLAG_SYS_SPECIAL_WILD_BATTLE);
    FlagClear(FLAG_SYS_INFORMED_OF_LOCAL_WIRELESS_PLAYER);
}

void sub_806E168(void) // Unused
{
    u16 *ptr = GetVarPointer(VAR_0x403C);
    gSaveBlock2Ptr->pokedex.nationalMagic = 0;
    *ptr = 0;
    FlagClear(FLAG_0x838);
}

void sub_806E190(void)
{
    u16 *ptr = GetVarPointer(VAR_0x403C);
    gSaveBlock2Ptr->pokedex.nationalMagic = 0xDA;
    *ptr = 0x0302;
    FlagSet(FLAG_0x838);
}

bool32 sub_806E1C0(void) // Unused
{
    if (gSaveBlock2Ptr->pokedex.nationalMagic != 0xDA)
        return FALSE;
    if (VarGet(VAR_0x403C) != 0x0302)
        return FALSE;
    if (!FlagGet(FLAG_0x838))
        return FALSE;
    return TRUE;
}

void DisableNationalPokedex(void)
{
    u16 *nationalDexVar = GetVarPointer(VAR_NATIONAL_DEX);
    gSaveBlock2Ptr->pokedex.unknown2 = 0;
    *nationalDexVar = 0;
    FlagClear(FLAG_SYS_NATIONAL_DEX);
}

void EnableNationalPokedex(void)
{
    u16 *nationalDexVar = GetVarPointer(VAR_NATIONAL_DEX);
    gSaveBlock2Ptr->pokedex.unknown2 = 0xB9;
    *nationalDexVar = 0x6258;
    FlagSet(FLAG_SYS_NATIONAL_DEX);
}

bool32 IsNationalPokedexEnabled(void)
{
    return FlagGet(FLAG_SYS_POKEDEX_GET);
    // National Pokédex will be enabled by default.
    // I don't know what gSaveBlock2Ptr->pokedex.unknown2 and VAR_NATIONAL_DEX are for, they're used nowhere else.
    /*
    if (gSaveBlock2Ptr->pokedex.unknown2 != 0xB9)
        return FALSE;
    if (VarGet(VAR_NATIONAL_DEX) != 0x6258)
        return FALSE;
    if (!FlagGet(FLAG_SYS_NATIONAL_DEX))
        return FALSE;
    return TRUE;
    */
}

void DisableMysteryGift(void)
{
    FlagClear(FLAG_SYS_MYSTERY_GIFT_ENABLED);
}

void EnableMysteryGift(void)
{
    FlagSet(FLAG_SYS_MYSTERY_GIFT_ENABLED);
}

bool32 IsMysteryGiftEnabled(void)
{
    return FlagGet(FLAG_SYS_MYSTERY_GIFT_ENABLED);
}

void ResetMysteryEventFlags(void)
{
    FlagClear(FLAG_MYSTERY_GIFT_DONE);
    FlagClear(FLAG_MYSTERY_GIFT_1);
    FlagClear(FLAG_MYSTERY_GIFT_2);
    FlagClear(FLAG_MYSTERY_GIFT_3);
    FlagClear(FLAG_MYSTERY_GIFT_4);
    FlagClear(FLAG_MYSTERY_GIFT_5);
    FlagClear(FLAG_MYSTERY_GIFT_6);
    FlagClear(FLAG_MYSTERY_GIFT_7);
    FlagClear(FLAG_MYSTERY_GIFT_8);
    FlagClear(FLAG_MYSTERY_GIFT_9);
    FlagClear(FLAG_MYSTERY_GIFT_10);
    FlagClear(FLAG_MYSTERY_GIFT_11);
    FlagClear(FLAG_MYSTERY_GIFT_12);
    FlagClear(FLAG_MYSTERY_GIFT_13);
    FlagClear(FLAG_MYSTERY_GIFT_14);
    FlagClear(FLAG_MYSTERY_GIFT_15);
}

void ResetMysteryEventVars(void)
{
    VarSet(VAR_EVENT_PICHU_SLOT, 0);
    VarSet(VAR_MYSTERY_GIFT_1,  0);
    VarSet(VAR_MYSTERY_GIFT_2,  0);
    VarSet(VAR_MYSTERY_GIFT_3,  0);
    VarSet(VAR_MYSTERY_GIFT_4,  0);
    VarSet(VAR_MYSTERY_GIFT_5,  0);
    VarSet(VAR_MYSTERY_GIFT_6,  0);
    VarSet(VAR_MYSTERY_GIFT_7,  0);
    VarSet(VAR_ALTERING_CAVE_WILD_SET, 0);
}

void DisableResetRTC(void)
{
    VarSet(VAR_0x4032, 0);
    FlagClear(FLAG_0x837);
}

void EnableResetRTC(void)
{
    VarSet(VAR_0x4032, 0x0920);
    FlagSet(FLAG_0x837);
}

bool32 CanResetRTC(void)
{
    if (!FlagGet(FLAG_0x837))
        return FALSE;
    if (VarGet(VAR_0x4032) != 0x0920)
        return FALSE;
    return TRUE;
}

u16 *GetVarPointer(u16 idx)
{
    u16 *ptr;
    if (idx < VARS_START)
        return NULL;
    if (idx < SPECIAL_VARS_START)
    {
        switch (gQuestLogPlaybackState)
        {
        case 0:
        default:
            break;
        case 1:
            ptr = QuestLogGetFlagOrVarPtr(FALSE, idx);
            if (ptr != NULL)
                gSaveBlock1Ptr->vars[idx - VARS_START] = *ptr;
            break;
        case 2:
            if (IsFlagOrVarStoredInQuestLog(idx - VARS_START, TRUE) == TRUE)
            {
                gLastQuestLogStoredFlagOrVarIdx = idx - VARS_START;
                QuestLogSetFlagOrVar(FALSE, idx, gSaveBlock1Ptr->vars[idx - VARS_START]);
            }
            break;
        }
        return &gSaveBlock1Ptr->vars[idx - VARS_START];
    }
    return gSpecialVars[idx - SPECIAL_VARS_START];
}

static bool8 IsFlagOrVarStoredInQuestLog(u16 idx, bool8 isVar)
{
    if (!isVar)
    {
        if (idx < STORY_FLAGS_START)
            return FALSE;
        if (idx >= SYS_FLAGS && idx < PERMA_SYS_FLAGS_START)
            return FALSE;
    }
    else
    {
        if (idx < VAR_ICE_STEP_COUNT - VARS_START)
            return FALSE;
        if (idx >= VAR_MAP_SCENE_ROUTE_OASIS - VARS_START && idx < VAR_PORTHOLE - VARS_START)
            return FALSE;
    }
    return TRUE;
}

u16 VarGet(u16 idx)
{
    u16 *ptr = GetVarPointer(idx);
    if (ptr == NULL)
        return idx;
    return *ptr;
}

bool8 VarSet(u16 idx, u16 val)
{
    u16 *ptr = GetVarPointer(idx);
    if (ptr == NULL)
        return FALSE;
    *ptr = val;
    return TRUE;
}

u8 VarGetObjectEventGraphicsId(u8 idx)
{
    return VarGet(VAR_OBJ_GFX_ID_0 + idx);
}

u8 *GetFlagAddr(u16 idx)
{
    u8 *ptr;
    if (idx == 0)
        return NULL;
    if (idx < SPECIAL_FLAGS_START)
    {
        switch (gQuestLogPlaybackState)
        {
        case 0:
        default:
            break;
        case 1:
            ptr = QuestLogGetFlagOrVarPtr(TRUE, idx);
            if (ptr != NULL)
                gSaveBlock1Ptr->flags[idx >> 3] = *ptr;
            break;
        case 2:
            if (IsFlagOrVarStoredInQuestLog(idx, FALSE) == TRUE)
            {
                gLastQuestLogStoredFlagOrVarIdx = idx;
                QuestLogSetFlagOrVar(TRUE, idx, gSaveBlock1Ptr->flags[idx / 8]);
            }
            break;
        }
        return &gSaveBlock1Ptr->flags[idx / 8];
    }
    return &sSpecialFlags[(idx - SPECIAL_FLAGS_START) / 8];
}

bool8 FlagSet(u16 idx)
{
    u8 *ptr = GetFlagAddr(idx);
    if (ptr != NULL)
        *ptr |= 1 << (idx & 7);
    return FALSE;
}

bool8 FlagClear(u16 idx)
{
    u8 *ptr = GetFlagAddr(idx);
    if (ptr != NULL)
        *ptr &= ~(1 << (idx & 7));
    return FALSE;
}

bool8 FlagGet(u16 idx)
{
    u8 *ptr = GetFlagAddr(idx);
    if (ptr == NULL)
        return FALSE;
    if (!(*ptr & 1 << (idx & 7)))
        return FALSE;
    return TRUE;
}

void ResetSpecialVars(void)
{
    gSpecialVar_0x8000 = 0;
    gSpecialVar_0x8001 = 0;
    gSpecialVar_0x8002 = 0;
    gSpecialVar_0x8003 = 0;
    gSpecialVar_0x8004 = 0;
    gSpecialVar_0x8005 = 0;
    gSpecialVar_0x8006 = 0;
    gSpecialVar_0x8007 = 0;
    gSpecialVar_0x8008 = 0;
    gSpecialVar_0x8009 = 0;
    gSpecialVar_0x800A = 0;
    gSpecialVar_0x800B = 0;
    gSpecialVar_Facing = 0;
    gSpecialVar_Result = 0;
    gSpecialVar_ItemId = 0;
    gSpecialVar_LastTalked = 0;
    gSpecialVar_MonBoxId = 0;
    gSpecialVar_MonBoxPos = 0;
    gSpecialVar_TextColor = 0;
    gSpecialVar_PrevTextColor = 0;
    gSpecialVar_0x8014 = 0;
}
