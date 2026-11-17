#ifndef __MOTOR_FAILURE_H
#define __MOTOR_FAILURE_H

#include <stdint.h>
#include <stdbool.h>
#include "lvgl.h"

typedef struct
{
    lv_obj_t *screen;
    bool screen_del;
    lv_obj_t *screen_cont_up;
    lv_obj_t *screen_cont_down;
    lv_obj_t *screen_cont_left;
    lv_obj_t *screen_cont_right;
    lv_obj_t *screen_cont_1;
    lv_obj_t *screen_img_1;
    lv_obj_t *screen_arc_1;
    lv_obj_t *screen_1;
} lv_ui;

#endif /* __MOTOR_FAILURE_H */
