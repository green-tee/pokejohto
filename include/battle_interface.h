#ifndef GUARD_BATTLE_INTERFACE_H
#define GUARD_BATTLE_INTERFACE_H

#include "global.h"
#include "battle_controllers.h"

enum
{
    HP_CURRENT,
    HP_MAX
};

enum
{
    HEALTH_BAR,
    EXP_BAR
};

enum
{
    HP_BAR_EMPTY,
    HP_BAR_RED,
    HP_BAR_YELLOW,
    HP_BAR_GREEN,
    HP_BAR_FULL,
};

#define TAG_HEALTHBOX_PLAYER1_TILE      0xD6FF
#define TAG_HEALTHBOX_PLAYER2_TILE      0xD700
#define TAG_HEALTHBOX_OPPONENT1_TILE    0xD701
#define TAG_HEALTHBOX_OPPONENT2_TILE    0xD702

#define TAG_HEALTHBAR_PLAYER1_TILE      0xD704
#define TAG_HEALTHBAR_OPPONENT1_TILE    0xD705
#define TAG_HEALTHBAR_PLAYER2_TILE      0xD706
#define TAG_HEALTHBAR_OPPONENT2_TILE    0xD707

#define TAG_HEALTHBOX_SAFARI_TILE       0xD70B

#define TAG_STATUS_SUMMARY_BAR_TILE     0xD70C
#define TAG_STATUS_SUMMARY_BALLS_TILE   0xD714

#define TAG_HEALTHBOX_PAL               0xD6FF
#define TAG_HEALTHBAR_PAL               0xD704
#define TAG_STATUS_SUMMARY_BAR_PAL      0xD710
#define TAG_STATUS_SUMMARY_BALLS_PAL    0xD712

#define HEALTHBOX_PAL_TRANSPARENCY        0
#define HEALTHBOX_PAL_MARGIN              1
#define HEALTHBOX_PAL_BORDER              2
#define HEALTHBOX_PAL_BOTTOM_HALF         3
#define HEALTHBOX_PAL_SHADOW              4
#define HEALTHBOX_PAL_BORDER2             5
#define HEALTHBOX_PAL_TOP_HALF            6
#define HEALTHBOX_PAL_EXP_BAR_SHADOW      7
#define HEALTHBOX_PAL_EXP_BAR             8
#define HEALTHBOX_PAL_GENDER_FEMALE       9
#define HEALTHBOX_PAL_10                 10
#define HEALTHBOX_PAL_11                 11
#define HEALTHBOX_PAL_12                 12
#define HEALTHBOX_PAL_13                 13
#define HEALTHBOX_PAL_14                 14
#define HEALTHBOX_PAL_15                 15
#define HEALTHBOX_PAL_GENDER_MALE         HEALTHBOX_PAL_EXP_BAR

enum
{
    HEALTHBOX_ALL,
    HEALTHBOX_CURRENT_HP,
    HEALTHBOX_MAX_HP,
    HEALTHBOX_LEVEL,
    HEALTHBOX_NICK,
    HEALTHBOX_HEALTH_BAR,
    HEALTHBOX_EXP_BAR,
    HEALTHBOX_UNUSED_7,
    HEALTHBOX_UNUSED_8,
    HEALTHBOX_STATUS_ICON,
    HEALTHBOX_SAFARI_ALL_TEXT,
    HEALTHBOX_SAFARI_BALLS_TEXT
};

void Task_HidePartyStatusSummary(u8 taskId);
u8 CreateBattlerHealthboxSprites(u8 battlerId);
u8 CreateSafariPlayerHealthboxSprites(void);
void SetBattleBarStruct(u8 battlerId, u8 healthboxSpriteId, s32 maxVal, s32 currVal, s32 receivedValue);
void SetHealthboxSpriteInvisible(u8 healthboxSpriteId);
void SetHealthboxSpriteVisible(u8 healthboxSpriteId);
void DestoryHealthboxSprite(u8 healthboxSpriteId);
void DummyBattleInterfaceFunc(u8 healthboxSpriteId, bool8 isDoubleBattleBankOnly);
void UpdateOamPriorityInAllHealthboxes(u8 priority);
void InitBattlerHealthboxCoords(u8 battlerId);
void UpdateHpTextInHealthbox(u8 healthboxSpriteId, s16 value, u8 maxOrCurrent);
void SwapHpBarsWithHpText(void);
u8 CreatePartyStatusSummarySprites(u8 battlerId, struct HpAndStatus *partyInfo, u8 isSwitchingMons, bool8 isBattleStart);
void UpdateHealthboxAttribute(u8 healthboxSpriteId, struct Pokemon *mon, u8 elementId);
u8 GetScaledHPFraction(s16 hp, s16 maxhp, u8 scale);
u8 GetHPBarLevel(s16 hp, s16 maxhp);
void UpdateNickInHealthbox(u8 spriteId, struct Pokemon *mon);
void TryAddPokeballIconToHealthbox(u8 spriteId, u8);
s32 MoveBattleBar(u8 battler, u8 healthboxSpriteId, u8 whichBar, u8 arg3);

#endif // GUARD_BATTLE_INTERFACE_H
