#include "global.h"
#include "text_window_graphics.h"

const u16 gSignpostWindow_Gfx[] = INCBIN_U16("graphics/text_window/signpost.4bpp");

static const u16 sUserFrame_Type1_Gfx[] = INCBIN_U16("graphics/text_window/type1.4bpp");
static const u16 sUserFrame_Type2_Gfx[] = INCBIN_U16("graphics/text_window/type2.4bpp");
static const u16 sUserFrame_Empty1[16] = {0};
static const u16 sUserFrame_Type3_Gfx[] = INCBIN_U16("graphics/text_window/type3.4bpp");
static const u16 sUserFrame_Type4_Gfx[] = INCBIN_U16("graphics/text_window/type4.4bpp");
static const u16 sUserFrame_Type5_Gfx[] = INCBIN_U16("graphics/text_window/type5.4bpp");
static const u16 sUserFrame_Type6_Gfx[] = INCBIN_U16("graphics/text_window/type6.4bpp");
static const u16 sUserFrame_Type7_Gfx[] = INCBIN_U16("graphics/text_window/type7.4bpp");
static const u16 sUserFrame_Type8_Gfx[] = INCBIN_U16("graphics/text_window/type8.4bpp");
static const u16 sUserFrame_Empty2[16] = {0};
static const u16 sUserFrame_Type9_Gfx[] = INCBIN_U16("graphics/text_window/type9.4bpp");
static const u16 sUserFrame_Type10_Gfx[] = INCBIN_U16("graphics/text_window/type10.4bpp");
static const u16 sUserFrame_Empty3[16] = {0};

static const u16 sUserFrame_Type1_PalLight[] = INCBIN_U16("graphics/text_window/type1.gbapal");
static const u16 sUserFrame_Type2_PalLight[] = INCBIN_U16("graphics/text_window/type2.gbapal");
static const u16 sUserFrame_Type3_PalLight[] = INCBIN_U16("graphics/text_window/type3.gbapal");
static const u16 sUserFrame_Type4_PalLight[] = INCBIN_U16("graphics/text_window/type4.gbapal");
static const u16 sUserFrame_Type5_PalLight[] = INCBIN_U16("graphics/text_window/type5.gbapal");
static const u16 sUserFrame_Type6_PalLight[] = INCBIN_U16("graphics/text_window/type6.gbapal");
static const u16 sUserFrame_Type7_PalLight[] = INCBIN_U16("graphics/text_window/type7.gbapal");
static const u16 sUserFrame_Type8_PalLight[] = INCBIN_U16("graphics/text_window/type8.gbapal");
static const u16 sUserFrame_Type9_PalLight[] = INCBIN_U16("graphics/text_window/type9.gbapal");
static const u16 sUserFrame_Type10_PalLight[] = INCBIN_U16("graphics/text_window/type10.gbapal");

static const u16 sUserFrame_Type1_PalDark[] = INCBIN_U16("graphics/text_window/type1dark.gbapal");
static const u16 sUserFrame_Type2_PalDark[] = INCBIN_U16("graphics/text_window/type2dark.gbapal");
static const u16 sUserFrame_Type3_PalDark[] = INCBIN_U16("graphics/text_window/type3dark.gbapal");
static const u16 sUserFrame_Type4_PalDark[] = INCBIN_U16("graphics/text_window/type4dark.gbapal");
static const u16 sUserFrame_Type5_PalDark[] = INCBIN_U16("graphics/text_window/type5dark.gbapal");
static const u16 sUserFrame_Type6_PalDark[] = INCBIN_U16("graphics/text_window/type6dark.gbapal");
static const u16 sUserFrame_Type7_PalDark[] = INCBIN_U16("graphics/text_window/type7dark.gbapal");
static const u16 sUserFrame_Type8_PalDark[] = INCBIN_U16("graphics/text_window/type8dark.gbapal");
static const u16 sUserFrame_Type9_PalDark[] = INCBIN_U16("graphics/text_window/type9dark.gbapal");
static const u16 sUserFrame_Type10_PalDark[] = INCBIN_U16("graphics/text_window/type10dark.gbapal");

const u16 gStdTextWindow_Gfx[] = INCBIN_U16("graphics/text_window/std.4bpp");
const u16 gQuestLogWindow_Gfx[] = INCBIN_U16("graphics/text_window/quest_log.4bpp");

const u16 gTextWindowPalettesLight[][16] = {
    INCBIN_U16("graphics/text_window/stdpal_0.gbapal"),
    INCBIN_U16("graphics/text_window/stdpal_1.gbapal"),
    INCBIN_U16("graphics/text_window/stdpal_2.gbapal"),
    INCBIN_U16("graphics/text_window/stdpal_3.gbapal"),
    INCBIN_U16("graphics/text_window/stdpal_4.gbapal")
};

const u16 gTextWindowPalettesDark[][16] = {
    INCBIN_U16("graphics/text_window/stdpaldark_0.gbapal"),
    INCBIN_U16("graphics/text_window/stdpal_1.gbapal"),
    INCBIN_U16("graphics/text_window/stdpal_2.gbapal"),
    INCBIN_U16("graphics/text_window/stdpal_3.gbapal"),
    INCBIN_U16("graphics/text_window/stdpal_4.gbapal")
};

#define USER_FRAME(i) {\
    .tiles = sUserFrame_Type ## i ## _Gfx,\
    .paletteLight = sUserFrame_Type ## i ## _PalLight,\
    .paletteDark = sUserFrame_Type ## i ## _PalDark\
}

const struct TextWindowGraphics gUserFrames[] = {
    USER_FRAME(1),
    USER_FRAME(2),
    USER_FRAME(3),
    USER_FRAME(4),
    USER_FRAME(5),
    USER_FRAME(6),
    USER_FRAME(7),
    USER_FRAME(8),
    USER_FRAME(9),
    USER_FRAME(10)
};

const struct TextWindowGraphics *GetUserWindowGraphics(u8 idx)
{
#ifdef BUGFIX
    if (idx >= ARRAY_COUNT(gUserFrames))
#else
    if (idx >= 20) // Using the RSE number of elements
#endif
        return &gUserFrames[0];
    else
        return &gUserFrames[idx];
}
