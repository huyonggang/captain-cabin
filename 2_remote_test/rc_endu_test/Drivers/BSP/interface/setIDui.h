#ifndef __SETIDUI_H
#define __SETIDUI_H

#include "sys.h"

enum
{
    pairFail,
    pairsuccess,
    pairing,
    pairNum
};

void SetRF_ID_UI_Init(void);
void SetRF_ID_Run(void);

#endif
