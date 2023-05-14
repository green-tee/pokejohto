#include "global.h"
#include "gflib.h"
#include "scanline_effect.h"
#include "text_window_graphics.h"
#include "menu.h"
#include "task.h"
#include "overworld.h"
#include "help_system.h"
#include "text_window.h"
#include "strings.h"
#include "field_fadetransition.h"
#include "gba/m4a_internal.h"

// can't include the one in menu_helpers.h since Task_OptionMenu needs bool32 for matching
bool32 MenuHelpers_CallLinkSomething(void);

// Menu tabs, each tab groups items that are related to each other
enum MenuTabs
{
    MENUTAB_WINDOW = 0,
    MENUTAB_BATTLE,
    MENUTAB_MISCELLANEOUS,
    MENUTAB_COUNT
};

// Menu items
enum MenuItems
{
    MENUITEM_TEXTSPEED = 0,
    MENUITEM_BATTLESCENE,
    MENUITEM_BATTLESTYLE,
    MENUITEM_SOUND,
    MENUITEM_BUTTONMODE,
    MENUITEM_FRAMETYPE,
    MENUITEM_DIALOGMODE,
    MENUITEM_CANCEL,
    MENUITEM_COUNT
};

typedef u8 MenuItem;

// Window Ids
enum
{
    WIN_TEXT_OPTION,
    WIN_OPTIONS
};

// RAM symbols
struct OptionMenu
{
    u8 option[MENUITEM_COUNT];
    enum MenuTabs activeTab;
    u8 cursorPos;
    u8 loadState;
    u8 state;
    u8 loadPaletteState;
};

static EWRAM_DATA struct OptionMenu *sOptionMenuPtr = NULL;

//Function Declarataions
static void CB2_InitOptionMenu(void);
static void VBlankCB_OptionMenu(void);
static void OptionMenu_InitCallbacks(void);
static void OptionMenu_SetVBlankCallback(void);
static void CB2_OptionMenu(void);
static void SetOptionMenuTask(void);
static void InitOptionMenuBg(void);
static void OptionMenu_PickSwitchCancel(void);
static void OptionMenu_ResetSpriteData(void);
static bool8 LoadOptionMenuPalette(void);
static void Task_OptionMenu(u8 taskId);
static u8 OptionMenu_ProcessInput(void);
static void BufferOptionMenuString(enum MenuTabs activeTab, u8 cursorPos);
static void CloseAndSaveOptionMenu(u8 taskId);
static void PrintOptionMenuHeader(void);
static void DrawOptionMenuBg(void);
static void LoadOptionMenuItemNames(void);
static void UpdateSettingSelectionDisplay(u8 cursorPos);

// Data Definitions
static const struct WindowTemplate sOptionMenuWinTemplates[] =
{
    {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 3,
        .width = 26,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 7,
        .width = 26,
        .height = 12,
        .paletteNum = 1,
        .baseBlock = 0x36
    },
    {
        .bg = 2,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 0xF,
        .baseBlock = 0x16e
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sOptionMenuBgTemplates[] =
{
   {
       .bg = 1,
       .charBaseIndex = 1,
       .mapBaseIndex = 30,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 0,
       .baseTile = 0
   },
   {
       .bg = 0,
       .charBaseIndex = 1,
       .mapBaseIndex = 31,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
       .baseTile = 0
   },
   {
       .bg = 2,
       .charBaseIndex = 1,
       .mapBaseIndex = 29,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 2,
       .baseTile = 0
   },
};

static const u16 sOptionMenuPalette[] = INCBIN_U16("graphics/misc/unk_83cc2e4.gbapal");

#define MAX_ITEMS_PER_TAB 4

static const u16 sOptionMenuTabCounts[MENUTAB_COUNT] =
{
    [MENUTAB_WINDOW] = 4,
    [MENUTAB_BATTLE] = 3,
    [MENUTAB_MISCELLANEOUS] = 3
};

#define S_MENU_TAB_WINDOW_OPTION_ITEMS \
{\
    MENUITEM_TEXTSPEED,\
    MENUITEM_FRAMETYPE,\
    MENUITEM_DIALOGMODE,\
    MENUITEM_CANCEL\
}

#define S_MENU_TAB_BATTLE_OPTION_ITEMS \
{\
    MENUITEM_BATTLESCENE,\
    MENUITEM_BATTLESTYLE,\
    MENUITEM_CANCEL\
}

#define S_MENU_TAB_MISCELLANEOUS_OPTION_ITEMS \
{\
    MENUITEM_SOUND,\
    MENUITEM_BUTTONMODE,\
    MENUITEM_CANCEL\
}

static const MenuItem sMenuTabsOptionItems[][MAX_ITEMS_PER_TAB] =
{
    [MENUTAB_WINDOW] = S_MENU_TAB_WINDOW_OPTION_ITEMS,
    [MENUTAB_BATTLE] = S_MENU_TAB_BATTLE_OPTION_ITEMS,
    [MENUTAB_MISCELLANEOUS] = S_MENU_TAB_MISCELLANEOUS_OPTION_ITEMS
};

static const u16 sOptionMenuItemCounts[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED] = 3,
    [MENUITEM_BATTLESCENE] = 2,
    [MENUITEM_BATTLESTYLE] = 2,
    [MENUITEM_SOUND] = 2,
    [MENUITEM_BUTTONMODE] = 3,
    [MENUITEM_FRAMETYPE] = 10,
    [MENUITEM_DIALOGMODE] = 2,
    [MENUITEM_CANCEL] = 0
};

static const u8 *const sOptionMenuTabsNames[MENUTAB_COUNT] =
{
    [MENUTAB_WINDOW] = gText_TabWindow,
    [MENUTAB_BATTLE] = gText_TabBattle,
    [MENUTAB_MISCELLANEOUS] = gText_TabMiscellaneous
};

static const u8 *const sOptionMenuItemsNames[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED]   = gText_TextSpeed,
    [MENUITEM_BATTLESCENE] = gText_BattleScene,
    [MENUITEM_BATTLESTYLE] = gText_BattleStyle,
    [MENUITEM_SOUND]       = gText_Sound,
    [MENUITEM_BUTTONMODE]  = gText_ButtonMode,
    [MENUITEM_FRAMETYPE]   = gText_Frame,
    [MENUITEM_DIALOGMODE]  = gText_Dialog,
    [MENUITEM_CANCEL]      = gText_OptionMenuCancel,
};

static const u8 *const sTextSpeedOptions[] =
{
    gText_TextSpeedSlow, 
    gText_TextSpeedMid, 
    gText_TextSpeedFast
};

static const u8 *const sBattleSceneOptions[] =
{
    gText_BattleSceneOn, 
    gText_BattleSceneOff
};

static const u8 *const sBattleStyleOptions[] =
{
    gText_BattleStyleShift,
    gText_BattleStyleSet
};

static const u8 *const sSoundOptions[] =
{
    gText_SoundMono, 
    gText_SoundStereo
};

static const u8 *const sButtonTypeOptions[] =
{
    gText_ButtonTypeHelp,
	gText_ButtonTypeLR,
	gText_ButtonTypeLEqualsA
};

static const u8 *const sDialogModeOptions[] =
{
    gText_DialogModeLight,
    gText_DialogModeDark
};

static const u8 sOptionMenuPickSwitchCancelTextColor[] = {TEXT_DYNAMIC_COLOR_6, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY};
static const u8 sOptionMenuTextColor[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_RED, TEXT_COLOR_RED};

// Functions
static void CB2_InitOptionMenu(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB_OptionMenu(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_OptionsMenuFromStartMenu(void)
{
    u8 i;
    
    if (gMain.savedCallback == NULL)
        gMain.savedCallback = CB2_ReturnToFieldWithOpenMenu;
    sOptionMenuPtr = AllocZeroed(sizeof(struct OptionMenu));
    sOptionMenuPtr->loadState = 0;
    sOptionMenuPtr->loadPaletteState = 0;
    sOptionMenuPtr->state = 0;
    sOptionMenuPtr->activeTab = MENUTAB_WINDOW;
    sOptionMenuPtr->cursorPos = 0;
    sOptionMenuPtr->option[MENUITEM_TEXTSPEED] = gSaveBlock2Ptr->optionsTextSpeed;
    sOptionMenuPtr->option[MENUITEM_BATTLESCENE] = gSaveBlock2Ptr->optionsBattleSceneOff;
    sOptionMenuPtr->option[MENUITEM_BATTLESTYLE] = gSaveBlock2Ptr->optionsBattleStyle;
    sOptionMenuPtr->option[MENUITEM_SOUND] = gSaveBlock2Ptr->optionsSound;
    sOptionMenuPtr->option[MENUITEM_BUTTONMODE] = gSaveBlock2Ptr->optionsButtonMode;
    sOptionMenuPtr->option[MENUITEM_FRAMETYPE] = gSaveBlock2Ptr->optionsWindowFrameType;
    sOptionMenuPtr->option[MENUITEM_DIALOGMODE] = gSaveBlock2Ptr->optionsWindowDialogMode;
    
    for (i = 0; i < MENUITEM_COUNT - 1; i++)
    {
        if (sOptionMenuPtr->option[i] > (sOptionMenuItemCounts[i]) - 1)
            sOptionMenuPtr->option[i] = 0;
    }
    SetHelpContext(HELPCONTEXT_OPTIONS);
    SetMainCallback2(CB2_OptionMenu);
}

static void OptionMenu_InitCallbacks(void)
{
    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
}

static void OptionMenu_SetVBlankCallback(void)
{
    SetVBlankCallback(VBlankCB_OptionMenu);
}

static void CB2_OptionMenu(void)
{
    u8 i;
    u8 state;
    u8 itemsInTabCount;
    state = sOptionMenuPtr->state;
    switch (state)
    {
    case 0:
        OptionMenu_InitCallbacks();
        break;
    case 1:
        InitOptionMenuBg();
        break;
    case 2:
        OptionMenu_ResetSpriteData();
        break;
    case 3:
        if (LoadOptionMenuPalette() != TRUE)
            return;
        break;
    case 4:
        PrintOptionMenuHeader();
        break;
    case 5:
        DrawOptionMenuBg();
        break;
    case 6:
        LoadOptionMenuItemNames();
        break;
    case 7:
        itemsInTabCount = sOptionMenuTabCounts[sOptionMenuPtr->activeTab];
        for (i = 1; i <= itemsInTabCount; i++)
            BufferOptionMenuString(sOptionMenuPtr->activeTab, i);
        break;
    case 8:
        UpdateSettingSelectionDisplay(sOptionMenuPtr->cursorPos);
        break;
    case 9:
        OptionMenu_PickSwitchCancel();
        break;
    default:
        SetOptionMenuTask();
		break;
    }
    sOptionMenuPtr->state++;
}

static void SetOptionMenuTask(void)
{
    CreateTask(Task_OptionMenu, 0);
    SetMainCallback2(CB2_InitOptionMenu);
}

static void InitOptionMenuBg(void)
{
    void *dest = (void *)VRAM;
    DmaClearLarge16(3, dest, VRAM_SIZE, 0x1000);    
    DmaClear32(3, (void *)OAM, OAM_SIZE);
    DmaClear16(3, (void *)PLTT, PLTT_SIZE);    
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sOptionMenuBgTemplates, NELEMS(sOptionMenuBgTemplates));
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
    InitWindows(sOptionMenuWinTemplates);
    DeactivateAllTextPrinters();
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_BLEND | BLDCNT_EFFECT_LIGHTEN);
    SetGpuReg(REG_OFFSET_BLDY, BLDCNT_TGT1_BG1);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_BG2 | WINOUT_WIN01_CLR);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON | DISPCNT_WIN0_ON);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
};

static void OptionMenu_PickSwitchCancel(void)
{
    s32 x;
    x = 0xE4 - GetStringWidth(FONT_0, gText_PickSwitchCancel, 0);
    FillWindowPixelBuffer(2, PIXEL_FILL(15)); 
    AddTextPrinterParameterized3(2, FONT_0, x, 0, sOptionMenuPickSwitchCancelTextColor, 0, gText_PickSwitchCancel);
    PutWindowTilemap(2);
    CopyWindowToVram(2, COPYWIN_FULL);
}

static void OptionMenu_ResetSpriteData(void)
{
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    ResetTasks();
    ScanlineEffect_Stop();
}

static bool8 LoadOptionMenuPalette(void)
{
    switch (sOptionMenuPtr->loadPaletteState)
    {
    case 0:
        LoadBgTiles(1, GetUserWindowGraphics(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->tiles, 0x120, 0x1AA);
        break;
    case 1:
        LoadPalette(GetUserWindowGraphics(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->palette, 0x20, 0x20);
        break;
    case 2:
        LoadPalette(sOptionMenuPalette, 0x10, 0x20);
        LoadPalette(GetTextWindowPalette(2), 0xF0, 0x20);
        break;
    case 3:
        LoadStdWindowGfxOnBg(1, 0x1B3, 0x30);
        break;
    default:
        return TRUE;
    }
    sOptionMenuPtr->loadPaletteState++;
    return FALSE;
}

static void Task_OptionMenu(u8 taskId)
{
    u8 itemsInTabCount;
    u8 i;
    switch (sOptionMenuPtr->loadState)
    {
    case 0:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);
        OptionMenu_SetVBlankCallback();
        sOptionMenuPtr->loadState++;
        break;
    case 1:
        if (gPaletteFade.active)
            return;
        sOptionMenuPtr->loadState++;
        break;
    case 2:
        if (((bool32)MenuHelpers_CallLinkSomething()) == TRUE)
            break;
        switch (OptionMenu_ProcessInput())
        {
        case 0:
            // Nothing happened
            break;
        case 1:
            // Menu is being closed
            sOptionMenuPtr->loadState++;
            break;
        case 2:
            // Window frame option was changed
            LoadBgTiles(1, GetUserWindowGraphics(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->tiles, 0x120, 0x1AA);
            LoadPalette(GetUserWindowGraphics(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->palette, 0x20, 0x20);
            BufferOptionMenuString(sOptionMenuPtr->activeTab, sOptionMenuPtr->cursorPos);
            break;
        case 3:
            // Cursor was moved up or down
            UpdateSettingSelectionDisplay(sOptionMenuPtr->cursorPos);
            break;
        case 4:
            // An option was changed, but not the window frame
            BufferOptionMenuString(sOptionMenuPtr->activeTab, sOptionMenuPtr->cursorPos);
            break;
        case 5:
            // Active tab was switched
            DrawOptionMenuBg();
            LoadOptionMenuItemNames();
            itemsInTabCount = sOptionMenuTabCounts[sOptionMenuPtr->activeTab];
            for (i = 1; i <= itemsInTabCount; i++)
                BufferOptionMenuString(sOptionMenuPtr->activeTab, i);
            UpdateSettingSelectionDisplay(sOptionMenuPtr->cursorPos);
            break;
        }
        break;
    case 3:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
        sOptionMenuPtr->loadState++;
        break;
    case 4:
        if (gPaletteFade.active)
            return;
        sOptionMenuPtr->loadState++;
        break;
    case 5:
        CloseAndSaveOptionMenu(taskId);
        break;
    }
}

static u8 OptionMenu_ProcessInput(void)
{
    enum MenuTabs currentlyActiveTab = sOptionMenuPtr->activeTab;
    const MenuItem *currentlyActiveTabItems = sMenuTabsOptionItems[currentlyActiveTab];
    MenuItem currentlySelectedItem;
    u8 itemCancelIndex = sOptionMenuTabCounts[sOptionMenuPtr->activeTab];
    u16 currentItemValueIndex;
    if (JOY_REPT(DPAD_RIGHT))
    {
        if (sOptionMenuPtr->cursorPos == 0)
        {
            // Switch active tab
            if (currentlyActiveTab == MENUTAB_COUNT - 1)
                sOptionMenuPtr->activeTab = 0;
            else
                sOptionMenuPtr->activeTab = sOptionMenuPtr->activeTab + 1;
            return 5;
        }
        else
        {
            currentlySelectedItem = currentlyActiveTabItems[sOptionMenuPtr->cursorPos - 1];
            currentItemValueIndex = sOptionMenuPtr->option[currentlySelectedItem];
            if (currentItemValueIndex == (sOptionMenuItemCounts[currentlySelectedItem] - 1))
                currentItemValueIndex = 0;
            else
                ++currentItemValueIndex;
            sOptionMenuPtr->option[currentlySelectedItem] = currentItemValueIndex;
            if (currentlySelectedItem == MENUITEM_FRAMETYPE)
                return 2;
            else
                return 4;
        }
    }
    else if (JOY_REPT(DPAD_LEFT))
    {
        if (sOptionMenuPtr->cursorPos == 0)
        {
            // Switch active tab
            if (currentlyActiveTab == 0)
                sOptionMenuPtr->activeTab = MENUTAB_COUNT - 1;
            else
                sOptionMenuPtr->activeTab = sOptionMenuPtr->activeTab - 1;
            return 5;
        }
        else
        {
            currentlySelectedItem = currentlyActiveTabItems[sOptionMenuPtr->cursorPos - 1];
            currentItemValueIndex = sOptionMenuPtr->option[currentlySelectedItem];
            if (currentItemValueIndex == 0)
                currentItemValueIndex = sOptionMenuItemCounts[currentlySelectedItem] - 1;
            else
                --currentItemValueIndex;
            sOptionMenuPtr->option[currentlySelectedItem] = currentItemValueIndex;
            if (currentlySelectedItem == MENUITEM_FRAMETYPE)
                return 2;
            else
                return 4;
        }
    }
    else if (JOY_REPT(DPAD_UP))
    {
        if (sOptionMenuPtr->cursorPos == 0)
        {
            // Cursor is at the top of the screen.
            // Cursor should be moved to CANCEL, which is the last menu item.
            // The index of CANCEL depends on which tab is currently active
            sOptionMenuPtr->cursorPos = itemCancelIndex;
        }
        else
            sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos - 1;
        return 3;        
    }
    else if (JOY_REPT(DPAD_DOWN))
    {
        // Check if cursor is on CANCEL. If it is, it should be moved to the top of the screen.
        if (sOptionMenuPtr->cursorPos == itemCancelIndex)
            sOptionMenuPtr->cursorPos = 0;
        else
            sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos + 1;
        return 3;
    }
    else if (JOY_NEW(B_BUTTON) || JOY_NEW(A_BUTTON))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static void BufferOptionMenuString(enum MenuTabs activeTab, u8 cursorPos)
{
    u8 str[20];
    u8 buf[12];
    u8 dst[3];
    u8 x, y;
    MenuItem selection;
    
    memcpy(dst, sOptionMenuTextColor, 3);
    x = 0x82;
    y = ((GetFontAttribute(FONT_2, FONTATTR_MAX_LETTER_HEIGHT) - 1) * cursorPos) + 2;
    FillWindowPixelRect(1, 1, x, y, 0x46, GetFontAttribute(FONT_2, FONTATTR_MAX_LETTER_HEIGHT));
    selection = sMenuTabsOptionItems[sOptionMenuPtr->activeTab][cursorPos - 1];

    switch (selection)
    {
    case MENUITEM_TEXTSPEED:
        AddTextPrinterParameterized3(1, FONT_2, x, y, dst, -1, sTextSpeedOptions[sOptionMenuPtr->option[selection]]);
        break;
    case MENUITEM_BATTLESCENE:
        AddTextPrinterParameterized3(1, FONT_2, x, y, dst, -1, sBattleSceneOptions[sOptionMenuPtr->option[selection]]);
        break;
    case MENUITEM_BATTLESTYLE:
        AddTextPrinterParameterized3(1, FONT_2, x, y, dst, -1, sBattleStyleOptions[sOptionMenuPtr->option[selection]]);
        break;
    case MENUITEM_SOUND:
        AddTextPrinterParameterized3(1, FONT_2, x, y, dst, -1, sSoundOptions[sOptionMenuPtr->option[selection]]);
        break;
    case MENUITEM_BUTTONMODE:
        AddTextPrinterParameterized3(1, FONT_2, x, y, dst, -1, sButtonTypeOptions[sOptionMenuPtr->option[selection]]);
        break;
    case MENUITEM_FRAMETYPE:
        StringCopy(str, gText_FrameType);
        ConvertIntToDecimalStringN(buf, sOptionMenuPtr->option[selection] + 1, 1, 2);
        StringAppendN(str, buf, 3);
        AddTextPrinterParameterized3(1, FONT_2, x, y, dst, -1, str);
        break;
    case MENUITEM_DIALOGMODE:
        AddTextPrinterParameterized3(1, FONT_2, x, y, dst, -1, sDialogModeOptions[sOptionMenuPtr->option[selection]]);
        break;
    default:
        break;
    }
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_FULL);
}

static void CloseAndSaveOptionMenu(u8 taskId)
{
    gFieldCallback = FieldCB_DefaultWarpExit;
    SetMainCallback2(gMain.savedCallback);
    FreeAllWindowBuffers();
    gSaveBlock2Ptr->optionsTextSpeed = sOptionMenuPtr->option[MENUITEM_TEXTSPEED];
    gSaveBlock2Ptr->optionsBattleSceneOff = sOptionMenuPtr->option[MENUITEM_BATTLESCENE];
    gSaveBlock2Ptr->optionsBattleStyle = sOptionMenuPtr->option[MENUITEM_BATTLESTYLE];
    gSaveBlock2Ptr->optionsSound = sOptionMenuPtr->option[MENUITEM_SOUND];
    gSaveBlock2Ptr->optionsButtonMode = sOptionMenuPtr->option[MENUITEM_BUTTONMODE];
    gSaveBlock2Ptr->optionsWindowFrameType = sOptionMenuPtr->option[MENUITEM_FRAMETYPE];
    gSaveBlock2Ptr->optionsWindowDialogMode = sOptionMenuPtr->option[MENUITEM_DIALOGMODE];
    SetPokemonCryStereo(gSaveBlock2Ptr->optionsSound);
    FREE_AND_SET_NULL(sOptionMenuPtr);
    DestroyTask(taskId);
}

static void PrintOptionMenuHeader(void)
{
    FillWindowPixelBuffer(0, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_TEXT_OPTION, FONT_2, gText_Option, 8, 1, TEXT_SKIP_DRAW, NULL);
    PutWindowTilemap(0);
    CopyWindowToVram(0, COPYWIN_FULL);
}

static void DrawOptionMenuBg(void)
{
    u8 h;
    h = 2;
    
    FillBgTilemapBufferRect(1, 0x1B3, 1, 2, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1B4, 2, 2, 0x1B, 1, 3);
    FillBgTilemapBufferRect(1, 0x1B5, 0x1C, 2, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1B6, 1, 3, 1, h, 3);
    FillBgTilemapBufferRect(1, 0x1B8, 0x1C, 3, 1, h, 3);
    FillBgTilemapBufferRect(1, 0x1B9, 1, 5, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1BA, 2, 5, 0x1B, 1, 3);
    FillBgTilemapBufferRect(1, 0x1BB, 0x1C, 5, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1AA, 1, 6, 1, 1, h);
    FillBgTilemapBufferRect(1, 0x1AB, 2, 6, 0x1A, 1, h);
    FillBgTilemapBufferRect(1, 0x1AC, 0x1C, 6, 1, 1, h);
    FillBgTilemapBufferRect(1, 0x1AD, 1, 7, 1, 0x10, h);
    FillBgTilemapBufferRect(1, 0x1AF, 0x1C, 7, 1, 0x10, h);
    FillBgTilemapBufferRect(1, 0x1B0, 1, 0x13, 1, 1, h);
    FillBgTilemapBufferRect(1, 0x1B1, 2, 0x13, 0x1A, 1, h);
    FillBgTilemapBufferRect(1, 0x1B2, 0x1C, 0x13, 1, 1, h);
    CopyBgTilemapBufferToVram(1);
}

static void LoadOptionMenuItemNames(void)
{
    u8 i;
    enum MenuTabs activeTab = sOptionMenuPtr->activeTab;
    const MenuItem *itemsInActiveTab = sMenuTabsOptionItems[sOptionMenuPtr->activeTab];
    u8 itemsInTabCount = sOptionMenuTabCounts[sOptionMenuPtr->activeTab];
    
    FillWindowPixelBuffer(1, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_2, sOptionMenuTabsNames[activeTab], 32, 2, TEXT_SKIP_DRAW, NULL);
    for (i = 1; i <= itemsInTabCount; i++)
    {
        AddTextPrinterParameterized(WIN_OPTIONS, FONT_2, sOptionMenuItemsNames[itemsInActiveTab[i - 1]], 8, (u8)((i * (GetFontAttribute(FONT_2, FONTATTR_MAX_LETTER_HEIGHT))) + 2) - i, TEXT_SKIP_DRAW, NULL);    
    }
}

static void UpdateSettingSelectionDisplay(u8 cursorPos)
{
    u16 maxLetterHeight, y;
    
    maxLetterHeight = GetFontAttribute(FONT_2, FONTATTR_MAX_LETTER_HEIGHT);
    y = cursorPos * (maxLetterHeight - 1) + 0x3A;
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(y, y + maxLetterHeight));
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(0x10, 0xE0));
}
