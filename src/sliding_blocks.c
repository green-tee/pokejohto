#include "main.h"
#include "malloc.h"
#include "global.h"
#include "constants/field_weather.h"
#include "field_weather.h"
#include "task.h"
#include "gba/gba.h"
#include "palette.h"

struct SlidingBlocksState
{
    MainCallback savedCallback;
    u8 state;
    u8 taskId;
    u8 layoutId;
};

static EWRAM_DATA bool8 (*sStartMenuCallback)(void) = NULL;
static EWRAM_DATA struct SlidingBlocksState *sSlidingBlocksState = NULL;

static void InitSlidingBlocksState(struct SlidingBlocksState *ptr);
static void CB2_InitSlidingBlocks(void);
static void MainTask_SlidingBlocksGameLoop(u8 taskId);
static void CB2_RunSlidingBlocks(void);

void PlaySlidingBlocks(u8 puzzleId, MainCallback savedCallback)
{
    ResetTasks();
    sSlidingBlocksState = Alloc(sizeof(*sSlidingBlocksState));
    if (sSlidingBlocksState == NULL)
        SetMainCallback2(savedCallback);
    else
    {
        sSlidingBlocksState->layoutId = puzzleId;
        sSlidingBlocksState->savedCallback = savedCallback;
        InitSlidingBlocksState(sSlidingBlocksState);
        FadeScreen(FADE_TO_BLACK, 0);
        SetMainCallback2(CB2_InitSlidingBlocks);
    }
}

static void InitSlidingBlocksState(struct SlidingBlocksState *ptr)
{
    // TODO: Define fields of struct SlidingBlocksState and initialize them here.
    u8 state = 0;
}

static void CB2_InitSlidingBlocks(void)
{
    // TODO: Figure out what is supposed to be done here and do it.
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();

    if (!gPaletteFade.active) {
        // Set main callback 2 to next step.
        sSlidingBlocksState->taskId = CreateTask(MainTask_SlidingBlocksGameLoop, 0);
        SetMainCallback2(CB2_RunSlidingBlocks);
    }
}

static void MainTask_SlidingBlocksGameLoop(u8 taskId) {
    if (JOY_NEW(B_BUTTON)) {
        DestroyTask(taskId);
        SetMainCallback2(sSlidingBlocksState->savedCallback);
        Free(sSlidingBlocksState);
    }
}

static void CB2_RunSlidingBlocks(void) {
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}
