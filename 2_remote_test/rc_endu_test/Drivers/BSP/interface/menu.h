#ifndef __MENU_H__
#define __MENU_H__

#include "main.h"

typedef void (*MenuFun)(void);

void main_menu_init(void);

static void joystickChooseMenuInit(void);
static void SpeedSetMenuInit(void);
static void CommTypeMenuInit(void);
static void KeyCustomMenuInit(void);
static void KeyCustomSetMenuInit1(void);
static void KeyCustomSetMenuInit2(void);
static void KeyCustomSetMenuInit3(void);
static void KeyTypeMenuInit(void);
static void PointABMenuInit(void);
static void SavePointABMenuInit(void);
static void TaskModeSelectMenuInit(void);
static void BoatAnchorEnMenuInit(void);
static void AutoCruiseEnMenuInit(void);
static void GhostModeEnMenuInit(void);
static void GhostModeEnHintMenuInit(void);
static void FontChoiceMenuInit(void);
static void languageChoiceMenuInit(void);
static void reset_ui_init(void);
static void Show_Versions_UI(void);

void change_ui_init(void);
void change_run(void);

void GUI_Set_System_Parameter(uint8_t main_item, uint8_t item);

#endif
