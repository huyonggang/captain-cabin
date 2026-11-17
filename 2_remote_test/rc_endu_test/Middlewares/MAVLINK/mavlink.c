#include "usart.h"
#include "joystick.h"
#include "my_mavlink.h"
#include "stdint.h"
#include "delay.h"
#include "led.h"
#include <stdbool.h>
#include "main_ui.h"
#include "Time.h"
#include "app_mavlink.h"
#include "display.h"
#include "main.h"

/*FreeRtos includes*/
#include "FreeRTOS.h"
#include "task.h"
#include <math.h>

uint8_t mavlink_type = 1; // 默认加密
uint8_t setparmFlag = 0;
uint8_t paranamebuf[16];

#define FileFifoBufSize 2048
#define BOOT_FIRMWARE_START_ADDR 0x8000000
#define WRITE_FLASH_SIZE 1024

S_FileInfo FileInfo;
uint8_t flash_file_buf[WRITE_FLASH_SIZE]; // 1KB
uint32_t flash_offset = 0;
s_cycle_buffer FileFifo;
uint8_t FileFifoBuf[FileFifoBufSize];

typedef struct
{
    int8_t activeFlag;   /* 1 = waiting for ACK of pendingCmd, 0 = fresh ACK stored in CmdACK */
    uint16_t pendingCmd; /* [rc-0001] command id we are waiting for */
    mavlink_command_ack_t CmdACK;
} MAVLINKCOMMANDACK;


volatile GLOBE_STATE globeState; // 全局状态全局变量
volatile MAVLINKCOMMANDACK mavLinkCmdAck;
extern volatile uint8_t g_rth_arrival_done; /* [rc-0001] defined in main_ui.c */
/* [rc-0001] arm ACK wait before sending: drop any stale ACK */
static void cmd_ack_arm(uint16_t mav_cmd)
{
    mavLinkCmdAck.CmdACK.command = 0xFFFF;
    mavLinkCmdAck.CmdACK.result = 0xFF;
    mavLinkCmdAck.pendingCmd = mav_cmd;
    mavLinkCmdAck.activeFlag = 1;
}

mavlink_system_t mavlink_system;
mavlink_system_t target_system;
MISSIONSTATE missionCurrState;
TaskHandle_t ParseBoatMavTaskHandle;
SemaphoreHandle_t MavRecBinary;
TaskHandle_t JoystickSendHandle;
TaskHandle_t ParseAppMavTaskHandle;
SemaphoreHandle_t WiFiRecBinary;
mavlink_rc_channels_t rc_channels;
mavlink_mission_item_int_t missionItem[20];
static const uint32_t crc32_table[256] = {
    0x00000000,
    0x77073096,
    0xEE0E612C,
    0x990951BA,
    0x76DC419,
    0x706AF48F,
    0xE963A535,
    0x9E6495A3,
    0xEDB8832,
    0x79DCB8A4,
    0xE0D5E91E,
    0x97D2D988,
    0x9B64C2B,
    0x7EB17CBD,
    0xE7B82D07,
    0x90BF1D91,
    0x1DB71064,
    0x6AB020F2,
    0xF3B97148,
    0x84BE41DE,
    0x1ADAD47D,
    0x6DDDE4EB,
    0xF4D4B551,
    0x83D385C7,
    0x136C9856,
    0x646BA8C0,
    0xFD62F97A,
    0x8A65C9EC,
    0x14015C4F,
    0x63066CD9,
    0xFA0F3D63,
    0x8D080DF5,
    0x3B6E20C8,
    0x4C69105E,
    0xD56041E4,
    0xA2677172,
    0x3C03E4D1,
    0x4B04D447,
    0xD20D85FD,
    0xA50AB56B,
    0x35B5A8FA,
    0x42B2986C,
    0xDBBBC9D6,
    0xACBCF940,
    0x32D86CE3,
    0x45DF5C75,
    0xDCD60DCF,
    0xABD13D59,
    0x26D930AC,
    0x51DE003A,
    0xC8D75180,
    0xBFD06116,
    0x21B4F4B5,
    0x56B3C423,
    0xCFBA9599,
    0xB8BDA50F,
    0x2802B89E,
    0x5F058808,
    0xC60CD9B2,
    0xB10BE924,
    0x2F6F7C87,
    0x58684C11,
    0xC1611DAB,
    0xB6662D3D,
    0x76DC4190,
    0x1DB7106,
    0x98D220BC,
    0xEFD5102A,
    0x71B18589,
    0x6B6B51F,
    0x9FBFE4A5,
    0xE8B8D433,
    0x7807C9A2,
    0xF00F934,
    0x9609A88E,
    0xE10E9818,
    0x7F6A0DBB,
    0x86D3D2D,
    0x91646C97,
    0xE6635C01,
    0x6B6B51F4,
    0x1C6C6162,
    0x856530D8,
    0xF262004E,
    0x6C0695ED,
    0x1B01A57B,
    0x8208F4C1,
    0xF50FC457,
    0x65B0D9C6,
    0x12B7E950,
    0x8BBEB8EA,
    0xFCB9887C,
    0x62DD1DDF,
    0x15DA2D49,
    0x8CD37CF3,
    0xFBD44C65,
    0x4DB26158,
    0x3AB551CE,
    0xA3BC0074,
    0xD4BB30E2,
    0x4ADFA541,
    0x3DD895D7,
    0xA4D1C46D,
    0xD3D6F4FB,
    0x4369E96A,
    0x346ED9FC,
    0xAD678846,
    0xDA60B8D0,
    0x44042D73,
    0x33031DE5,
    0xAA0A4C5F,
    0xDD0D7CC9,
    0x5005713C,
    0x270241AA,
    0xBE0B1010,
    0xC90C2086,
    0x5768B525,
    0x206F85B3,
    0xB966D409,
    0xCE61E49F,
    0x5EDEF90E,
    0x29D9C998,
    0xB0D09822,
    0xC7D7A8B4,
    0x59B33D17,
    0x2EB40D81,
    0xB7BD5C3B,
    0xC0BA6CAD,
    0xEDB88320,
    0x9ABFB3B6,
    0x3B6E20C,
    0x74B1D29A,
    0xEAD54739,
    0x9DD277AF,
    0x4DB2615,
    0x73DC1683,
    0xE3630B12,
    0x94643B84,
    0xD6D6A3E,
    0x7A6A5AA8,
    0xE40ECF0B,
    0x9309FF9D,
    0xA00AE27,
    0x7D079EB1,
    0xF00F9344,
    0x8708A3D2,
    0x1E01F268,
    0x6906C2FE,
    0xF762575D,
    0x806567CB,
    0x196C3671,
    0x6E6B06E7,
    0xFED41B76,
    0x89D32BE0,
    0x10DA7A5A,
    0x67DD4ACC,
    0xF9B9DF6F,
    0x8EBEEFF9,
    0x17B7BE43,
    0x60B08ED5,
    0xD6D6A3E8,
    0xA1D1937E,
    0x38D8C2C4,
    0x4FDFF252,
    0xD1BB67F1,
    0xA6BC5767,
    0x3FB506DD,
    0x48B2364B,
    0xD80D2BDA,
    0xAF0A1B4C,
    0x36034AF6,
    0x41047A60,
    0xDF60EFC3,
    0xA867DF55,
    0x316E8EEF,
    0x4669BE79,
    0xCB61B38C,
    0xBC66831A,
    0x256FD2A0,
    0x5268E236,
    0xCC0C7795,
    0xBB0B4703,
    0x220216B9,
    0x5505262F,
    0xC5BA3BBE,
    0xB2BD0B28,
    0x2BB45A92,
    0x5CB36A04,
    0xC2D7FFA7,
    0xB5D0CF31,
    0x2CD99E8B,
    0x5BDEAE1D,
    0x9B64C2B0,
    0xEC63F226,
    0x756AA39C,
    0x26D930A,
    0x9C0906A9,
    0xEB0E363F,
    0x72076785,
    0x5005713,
    0x95BF4A82,
    0xE2B87A14,
    0x7BB12BAE,
    0xCB61B38,
    0x92D28E9B,
    0xE5D5BE0D,
    0x7CDCEFB7,
    0xBDBDF21,
    0x86D3D2D4,
    0xF1D4E242,
    0x68DDB3F8,
    0x1FDA836E,
    0x81BE16CD,
    0xF6B9265B,
    0x6FB077E1,
    0x18B74777,
    0x88085AE6,
    0xFF0F6A70,
    0x66063BCA,
    0x11010B5C,
    0x8F659EFF,
    0xF862AE69,
    0x616BFFD3,
    0x166CCF45,
    0xA00AE278,
    0xD70DD2EE,
    0x4E048354,
    0x3903B3C2,
    0xA7672661,
    0xD06016F7,
    0x4969474D,
    0x3E6E77DB,
    0xAED16A4A,
    0xD9D65ADC,
    0x40DF0B66,
    0x37D83BF0,
    0xA9BCAE53,
    0xDEBB9EC5,
    0x47B2CF7F,
    0x30B5FFE9,
    0xBDBDF21C,
    0xCABAC28A,
    0x53B39330,
    0x24B4A3A6,
    0xBAD03605,
    0xCDD70693,
    0x54DE5729,
    0x23D967BF,
    0xB3667A2E,
    0xC4614AB8,
    0x5D681B02,
    0x2A6F2B94,
    0xB40BBE37,
    0xC30C8EA1,
    0x5A05DF1B,
    0x2D02EF8D, //
}; // CRC32 查找表
static int signal = 0;

uint32_t crc32(const void *data, size_t len) // 计算 CRC32 校验和
{
    const uint8_t *bytes = data;
    uint32_t crc = 0xFFFFFFFFUL;
    IWDG_Feed();
    for (size_t i = 0; i < len; i++)
    {
        // IWDT->KEY = IWDT_KEYWORD_RELOAD; // 如果需要，保持看门狗重载
        crc = (crc >> 8) ^ crc32_table[(crc ^ bytes[i]) & 0xFF];
    }
    IWDG_Feed();
    return ~crc; // 取反操作得到最终结果
}

uint8_t setWPAsync(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint16_t seq, uint8_t frame, uint16_t command,
                   uint8_t current, uint8_t autocontinue, float param1, float param2, float param3, float param4, int32_t x, int32_t y, float z)
{
    int retrys = 10;
    uint32_t startTime;
    uint16_t res_seq;

    mavlink_msg_mission_item_int_send(chan, target_system, target_component, seq, frame, command, current,
                                      autocontinue, param1, param2, param3, param4, x, y, z);
    startTime = GetSysTick();
    Debug("seq = %d", seq);
    while (retrys > 0)
    {
        if (!(startTime + 300 > GetSysTick())) // 己经过了450ms
        {
            if (retrys > 0)
            {
                mavlink_msg_mission_item_int_send(chan, target_system, target_component, seq, frame, command, current,
                                                  autocontinue, param1, param2, param3, param4, x, y, z);
                startTime = GetSysTick();
                retrys--;
                continue;
            }
        }

        if (1 == missionCurrState.activeFlag)
        {
            missionCurrState.activeFlag = 0;
            if (missionCurrState.msgid == MAVLINK_MSG_ID_MISSION_ACK)
            {
                return missionCurrState.ACKtype;
            }

            else if (missionCurrState.msgid == MAVLINK_MSG_ID_MISSION_REQUEST_INT || missionCurrState.msgid == MAVLINK_MSG_ID_MISSION_REQUEST)
            {
                res_seq = missionCurrState.seq;
                Debug("res_seq = %d", res_seq);
                if (res_seq == seq + 1)
                {
                    return MAV_MISSION_ACCEPTED;
                }
                else
                {
                    startTime = 0; // resend point now
                }
            }
        }
        delay_ms(10);
    }
    return MAV_MISSION_RESULT_ENUM_END; // 遥控收飞控timeout
}

uint8_t getRequestedWPNoAsync(uint16_t *res_seq)
{
    uint32_t startTime = GetSysTick();

    while (true)
    {
        if (!(startTime + 1000 > GetSysTick()))
        {
            return 1;
        }
        // res = getMAVLinkData (&msg, &status);
        if (1 == missionCurrState.activeFlag)
        {
            missionCurrState.activeFlag = 0;
            if (missionCurrState.msgid == MAVLINK_MSG_ID_MISSION_REQUEST_INT || missionCurrState.msgid == MAVLINK_MSG_ID_MISSION_REQUEST)
            {
                *res_seq = missionCurrState.seq;
                return 0;
            }
        }
        delay_ms(10);
    }
}

/* 发关任务count只有两种结果，一个是收到seq，一个是超时 */
uint8_t setWPTotalAsync(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint16_t count)
{
    int retrys = 10;
    uint32_t startTime;
    uint16_t res_seq;

    Debug("count: %d", count);

    mavlink_msg_mission_count_send(chan, target_system, target_component, count);
    startTime = GetSysTick();

    while (retrys > 0)
    {
        if (!(startTime + 300 > GetSysTick()))
        {
            if (retrys > 0)
            {
                mavlink_msg_mission_count_send(chan, target_system, target_component, count); // 航点数,这里不包含home点
                startTime = GetSysTick();
                retrys--;
                continue;
            }
        }
        if (1 == missionCurrState.activeFlag)
        {
            missionCurrState.activeFlag = 0;
            if (missionCurrState.msgid == MAVLINK_MSG_ID_MISSION_REQUEST_INT || missionCurrState.msgid == MAVLINK_MSG_ID_MISSION_REQUEST)
            {
                res_seq = missionCurrState.seq;
                if (res_seq == 0 || res_seq == 1)
                {
                    Debug("cnt seq = %d", res_seq);
                    return MAV_MISSION_ACCEPTED;
                }
            }
        }
        delay_ms(10);
    }
    return MAV_MISSION_RESULT_ENUM_END;
}

/// <summary>
/// Set parameter on apm
/// </summary>
/// <param name="paramname">name as a string</param>
/// <param name="value"></param>
bool setParamAsync(char *paramname, float param_value)
{
    uint32_t startTime;
    uint8_t retrys = 10;
    char tmpname[16];
    memset(tmpname, 0, sizeof(tmpname));
    strncpy(tmpname, paramname, strlen(paramname));

    mavlink_msg_param_set_send(MAVLINK_COMM_0, target_system.sysid, target_system.compid, tmpname, param_value, MAV_PARAM_TYPE_REAL32);

    startTime = GetSysTick();

    while (retrys)
    {
        if (!(startTime + 300 > GetSysTick()))
        {
            if (retrys > 0)
            {
                mavlink_msg_param_set_send(MAVLINK_COMM_0, target_system.sysid, target_system.compid, tmpname, param_value, MAV_PARAM_TYPE_REAL32);

                startTime = GetSysTick();
                retrys--;
                continue;
            }
        }

        if (setparmFlag == 1)
        {
            setparmFlag = 0;
            if (!strncmp(paramname, (char *)paranamebuf, strlen(paramname)))
                return true;
            else
                continue;
        }
        delay_ms(10);
    }
    return false;
}

uint8_t upload(mavlink_mission_item_int_t *missionItem, uint16_t itemCount, uint8_t barCurr, uint8_t barTotal, uint8_t need_bar)
{
    int a;
    int uploadwpno;
    uint8_t ans;
    int value;
    char str[15];

    mavlink_mission_item_int_t *tmpMissionItem;
    Debug("---------- itemCount: %d ----------", itemCount);
    /* GCS的代码并没有做上传mission item数目的命令的返回做判断，GCS认为这个命令一定时成功的 */
    if (setWPTotalAsync(MAVLINK_COMM_0, 1, 1, itemCount) == MAV_MISSION_RESULT_ENUM_END)
    {
        return MAV_MISSION_RESULT_ENUM_END;
    }
    else
    {
        if (need_bar)
        {
            value = (float)(++barCurr) / (float)barTotal * 100.0f;
            TaskUpProgSendApp(value);
            lv_bar_set_value(globePopUp.bar, value, LV_ANIM_ON); /* 设置进度条当前值 */
            sprintf(str, "%d%%", value);
            lv_label_set_text(globePopUp.label_3, str);
            Debug("----- %d%% -----", value);
            if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
            {
                lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
                // lv_obj_move_foreground(globeGUI.light_img);
            }
            lvgl_force_refresh();
        }
    }

    for (a = 0; a < itemCount; ++a)
    {
        uploadwpno = a;
        tmpMissionItem = missionItem + uploadwpno;

        ans = setWPAsync(
            MAVLINK_COMM_0,
            tmpMissionItem->target_system,
            tmpMissionItem->target_component,
            // tmpMissionItem->seq, 				//航点序号
            uploadwpno,
            tmpMissionItem->frame,
            tmpMissionItem->command,
            tmpMissionItem->current,
            tmpMissionItem->autocontinue, // 自动走到下一个航点
            tmpMissionItem->param1,       // 在一个点位停留10s钟
            tmpMissionItem->param2,       // 在航点0.5m范围内都算是到达了航点
            tmpMissionItem->param3,       // Pass Radius
            tmpMissionItem->param4,       // Yaw
            tmpMissionItem->x,
            tmpMissionItem->y,
            // missionMenu[missionACKsta.seq]->position.alt_mm/1000.0
            tmpMissionItem->z); // 最后一个参数莫名其妙的错，这里先写成1.0

        if (ans == MAV_MISSION_ERROR)
        {
            Debug("a = %d, MAV_MISSION_ERROR: %d", a, MAV_MISSION_ERROR);
            // resend for partial upload
            mavlink_msg_mission_write_partial_list_send(MAVLINK_COMM_0, mavlink_system.sysid, mavlink_system.compid, (uint16_t)(uploadwpno), itemCount);
            // reupload this point.
            ans = setWPAsync(
                MAVLINK_COMM_0,
                tmpMissionItem->target_system,
                tmpMissionItem->target_component,
                // tmpMissionItem->seq, 				//航点序号
                uploadwpno,
                tmpMissionItem->frame,
                tmpMissionItem->command,
                tmpMissionItem->current,
                tmpMissionItem->autocontinue, // 自动走到下一个航点
                tmpMissionItem->param1,       // 在一个点位停留10s钟
                tmpMissionItem->param2,       // 在航点0.5m范围内都算是到达了航点
                tmpMissionItem->param3,       // Pass Radius
                tmpMissionItem->param4,       // Yaw
                tmpMissionItem->x,
                tmpMissionItem->y,
                // missionMenu[missionACKsta.seq]->position.alt_mm/1000.0
                tmpMissionItem->z);
            Debug("ans = %d ", ans);
        }

        if (ans == MAV_MISSION_NO_SPACE)
        {
            Debug("Upload failed: MAV_MISSION_NO_SPACE");
            return MAV_MISSION_NO_SPACE;
        }
        if (ans == MAV_MISSION_INVALID)
        {
            Debug("Upload failed: MAV_MISSION_INVALID");
            return MAV_MISSION_INVALID;
        }
        if (ans == MAV_MISSION_RESULT_ENUM_END)
        {
            Debug("Upload failed: TIMEOUT");
            return MAV_MISSION_RESULT_ENUM_END;
        }
        if (ans == MAV_MISSION_INVALID_SEQUENCE)
        {
            uint16_t res_seq;
            Debug("a = %d, MAV_MISSION_INVALID_SEQUENCE: %d", a, MAV_MISSION_INVALID_SEQUENCE);
            // invalid sequence can only occur if we failed to see a response from the apm when we sent the request.
            // or there is io lag and we send 2 mission_items and get 2 responces, one valid, one a ack of the second send
            // the ans is received via mission_ack, so we dont know for certain what our current request is for. as we may have lost the mission_request
            // get requested wp no - 1;
            if (!getRequestedWPNoAsync(&res_seq))
            {
                Debug("a = %d, res_seq = %d, itemCount = %d", a, res_seq, itemCount);
                a = res_seq - 1;
            }
            else
            {
                // resend for partial upload
                Debug("a = %d, uploadwpno = %d", a, uploadwpno);
                mavlink_msg_mission_write_partial_list_send(MAVLINK_COMM_0, mavlink_system.sysid, mavlink_system.compid, (uint16_t)(uploadwpno), itemCount);
                // reupload this point.
            }
            continue;
        }
        if (ans != MAV_MISSION_ACCEPTED)
        {
            Debug("upload error: %d", ans);
            return MAV_MISSION_INVALID;
            // 其它错误完全重新传
            // mavlink_msg_mission_write_partial_list_send (MAVLINK_COMM_0, mavlink_system.sysid, mavlink_system.compid, 0, itemCount);
        }
        if (need_bar)
        {
            value = (float)(++barCurr) / (float)barTotal * 100.0f;
            TaskUpProgSendApp(value);
            lv_bar_set_value(globePopUp.bar, value, LV_ANIM_ON); /* 设置进度条当前值 */
            sprintf(str, "%d%%", value);
            lv_label_set_text(globePopUp.label_3, str);
            Debug("----- %d%% -----", value);
            if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
            {
                lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
                // lv_obj_move_foreground(globeGUI.light_img);
            }
            lvgl_force_refresh();
        }
    }
    mavlink_msg_mission_ack_send(MAVLINK_COMM_0, mavlink_system.sysid, mavlink_system.compid, MAV_MISSION_ACCEPTED);
    globeState.TaskCount = itemCount;
    return MAV_MISSION_ACCEPTED;
}

uint8_t task_mission_clear_all(void)
{
    uint32_t startTime = GetSysTick();
    int retrys = 10;

    missionCurrState.activeFlag = 0;
    missionCurrState.ACKtype = 0;
    missionCurrState.msgid = 0;
    mavlink_msg_mission_clear_all_send(MAVLINK_COMM_0, 1, 1);

    while (retrys > 0)
    {
        if (!(startTime + 300 > GetSysTick()))
        {
            if (retrys > 0)
            {
                missionCurrState.activeFlag = 0;
                missionCurrState.ACKtype = 0;
                missionCurrState.msgid = 0;
                mavlink_msg_mission_clear_all_send(MAVLINK_COMM_0, 1, 1);
                startTime = GetSysTick();
                retrys--;
                continue;
            }
        }
        if (missionCurrState.activeFlag && missionCurrState.msgid == MAVLINK_MSG_ID_MISSION_ACK && missionCurrState.ACKtype == 0)
        {
            return MAV_MISSION_ACCEPTED;
        }
        delay_ms(10);
    }
    return MAV_MISSION_RESULT_ENUM_END;
}

uint8_t Task_Uploading(S_Position TaskPosition, uint8_t take_num, uint8_t Hopper, uint8_t Home, uint8_t Hook, uint8_t need_bar)
{
    uint8_t i, ans, barCurr = 0, barTotal = 0;
    uint8_t IsOK = 0;
    uint8_t missonWPindex = 0;
    uint8_t err = 0;
    int value;
    char str[15];

    static mavlink_mission_item_int_t missionItem[10] = {0};

    do
    {
        // if (task_mission_clear_all())
        // {
        //     err = 1;
        //     break;
        // }

        mavlink_msg_mission_clear_all_send(MAVLINK_COMM_0, 1, 1);

        /* 第0个点位一定是当前船的位置点 */
        missionItem[missonWPindex].param1 = 0.0;
        missionItem[missonWPindex].param2 = 0.0;
        missionItem[missonWPindex].param3 = 0.0; // Pass Radius
        missionItem[missonWPindex].param4 = 0.0; // Yaw
        missionItem[missonWPindex].x = globeState.current_position.degE7_lat;
        missionItem[missonWPindex].y = globeState.current_position.degE7_long;
        missionItem[missonWPindex].z = 1.0;
        missionItem[missonWPindex].seq = missonWPindex;
        missionItem[missonWPindex].command = MAV_CMD_NAV_WAYPOINT; // 导航到路径点
        missionItem[missonWPindex].target_system = 1;
        missionItem[missonWPindex].target_component = 1;
        missionItem[missonWPindex].frame = MAV_FRAME_GLOBAL;
        missionItem[missonWPindex].current = 0;
        missionItem[missonWPindex].autocontinue = 1; // 自动走到下一个航点
        missonWPindex++;

        switch (take_num)
        {
        case TaskH: // Home
            // missionItem[missonWPindex].param1 = 1; // 在一个点位停留5s
            if (need_bar)
            {
                show_popup(UploadHome_IMG_ID, RTHTask_Lang_ID, NULL, 1);
                if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
                {
                    lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
                    // lv_obj_move_foreground(globeGUI.light_img);
                }
                lvgl_force_refresh();
            }
            break;
        case TaskA: // TaskA
            if (need_bar)
            {
                show_popup(UploadA_IMG_ID, UpTask_Lang_ID, NULL, 1);
                if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
                {
                    lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
                    // lv_obj_move_foreground(globeGUI.light_img);
                }
                lvgl_force_refresh();
            }
            // missionItem[missonWPindex].param1 = 2; // 在一个点位停留5s
            break;
        case TaskB: // TaskB
            if (need_bar)
            {
                show_popup(UploadB_IMG_ID, UpTask_Lang_ID, NULL, 1);
                if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
                {
                    lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
                    // lv_obj_move_foreground(globeGUI.light_img);
                }
                lvgl_force_refresh();
            }
            // missionItem[missonWPindex].param1 = 3; // 在一个点位停留5s
            break;
        case TaskC: // TaskC
            if (need_bar)
            {
                show_popup(UploadC_IMG_ID, UpTask_Lang_ID, NULL, 1);
                if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
                {
                    lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
                    // lv_obj_move_foreground(globeGUI.light_img);
                }
                lvgl_force_refresh();
            }
            break;
        case TaskD: // TaskD
            if (need_bar)
            {
                show_popup(UploadD_IMG_ID, UpTask_Lang_ID, NULL, 1);
                if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
                {
                    lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
                    // lv_obj_move_foreground(globeGUI.light_img);
                }
                lvgl_force_refresh();
            }
            break;
        case TaskApp: // TaskApp
            if (need_bar)
            {
                show_popup(TaskIcom19, UpTask_Lang_ID, NULL, 1);
                if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
                {
                    lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
                    // lv_obj_move_foreground(globeGUI.light_img);
                }
                lvgl_force_refresh();
            }
            break;
        default:
            break;
        }

        if (Hopper || Hook)
        {
            missionItem[missonWPindex].param1 = 5;
        }
        else if (Home)
        {
            missionItem[missonWPindex].param1 = 2;
        }
        else
        {
            missionItem[missonWPindex].param1 = 0;
        }
        missionItem[missonWPindex].param2 = 0.3; // 在航点0.3m范围内都算是到达了航点
        missionItem[missonWPindex].param3 = 0.0; // Pass Radius
        missionItem[missonWPindex].param4 = 0.0; // Yaw
        missionItem[missonWPindex].x = TaskPosition.degE7_lat;
        missionItem[missonWPindex].y = TaskPosition.degE7_long;
        missionItem[missonWPindex].z = 1.0;
        missionItem[missonWPindex].seq = missonWPindex;
        missionItem[missonWPindex].command = MAV_CMD_NAV_WAYPOINT; // 导航到路径点
        missionItem[missonWPindex].target_system = 1;
        missionItem[missonWPindex].target_component = 1;
        missionItem[missonWPindex].frame = MAV_FRAME_GLOBAL;
        missionItem[missonWPindex].current = 0;
        missionItem[missonWPindex].autocontinue = 0; // 自动走到下一个航点
        globeState.TaskPointCurrentItem = missonWPindex;
        missonWPindex++;

        globeState.HopperCurrentItem = 0;
        globeState.HomeCurrentItem = 0;
        globeState.HookCurrentItem = 0;

        if (Hopper)
        {
            missionItem[missonWPindex].param1 = 6;
            missionItem[missonWPindex].param2 = 1100;
            missionItem[missonWPindex].param3 = 0.0; // Pass Radius
            missionItem[missonWPindex].param4 = 0.0; // Yaw
            missionItem[missonWPindex].x = TaskPosition.degE7_lat;
            missionItem[missonWPindex].y = TaskPosition.degE7_long;
            missionItem[missonWPindex].z = 1.0;
            missionItem[missonWPindex].seq = missonWPindex;
            missionItem[missonWPindex].command = MAV_CMD_DO_SET_SERVO;
            missionItem[missonWPindex].target_system = 1;
            missionItem[missonWPindex].target_component = 1;
            missionItem[missonWPindex].frame = MAV_FRAME_GLOBAL;
            missionItem[missonWPindex].current = 0;
            missionItem[missonWPindex].autocontinue = 0; // 自动走到下一个航点
            globeState.HopperCurrentItem = missonWPindex;
            missonWPindex++;
        }
        if (Hook)
        {
            missionItem[missonWPindex].param1 = 7;
            missionItem[missonWPindex].param2 = 2000; // 在航点0.3m范围内都算是到达了航点
            missionItem[missonWPindex].param3 = 0.0;  // Pass Radius
            missionItem[missonWPindex].param4 = 0.0;  // Yaw
            missionItem[missonWPindex].x = TaskPosition.degE7_lat;
            missionItem[missonWPindex].y = TaskPosition.degE7_long;
            missionItem[missonWPindex].z = 1.0;
            missionItem[missonWPindex].seq = missonWPindex;
            missionItem[missonWPindex].command = MAV_CMD_DO_SET_SERVO;
            missionItem[missonWPindex].target_system = 1;
            missionItem[missonWPindex].target_component = 1;
            missionItem[missonWPindex].frame = MAV_FRAME_GLOBAL;
            missionItem[missonWPindex].current = 0;
            missionItem[missonWPindex].autocontinue = 0; // 自动走到下一个航点
            globeState.HookCurrentItem = missonWPindex;
            missonWPindex++;
        }
        if (Home)
        {
            missionItem[missonWPindex].param1 = 0;
            missionItem[missonWPindex].param2 = 0.3; // 在航点0.3m范围内都算是到达了航点
            missionItem[missonWPindex].param3 = 0.0; // Pass Radius
            missionItem[missonWPindex].param4 = 0.0; // Yaw
            missionItem[missonWPindex].x = globeState.home_position.degE7_lat + globeState.Reposition_Value.lat_Diff;
            missionItem[missonWPindex].y = globeState.home_position.degE7_long + globeState.Reposition_Value.long_Diff;
            missionItem[missonWPindex].z = 1.0;
            missionItem[missonWPindex].seq = missonWPindex;
            missionItem[missonWPindex].command = MAV_CMD_NAV_WAYPOINT; // 导航到路径点
            missionItem[missonWPindex].target_system = 1;
            missionItem[missonWPindex].target_component = 1;
            missionItem[missonWPindex].frame = MAV_FRAME_GLOBAL;
            missionItem[missonWPindex].current = 0;
            missionItem[missonWPindex].autocontinue = 0; // 自动走到下一个航点
            globeState.HomeCurrentItem = missonWPindex;
            missonWPindex++;
        }
        // loiter 模式
        missionItem[missonWPindex].param1 = 0;
        missionItem[missonWPindex].param2 = 0;
        missionItem[missonWPindex].param3 = 0.3; // Pass Radius
        missionItem[missonWPindex].param4 = 0.0; // Yaw
        missionItem[missonWPindex].x = TaskPosition.degE7_lat;
        missionItem[missonWPindex].y = TaskPosition.degE7_long;
        missionItem[missonWPindex].z = 1.0;
        missionItem[missonWPindex].seq = missonWPindex;
        missionItem[missonWPindex].command = MAV_CMD_NAV_LOITER_UNLIM;
        missionItem[missonWPindex].target_system = 1;
        missionItem[missonWPindex].target_component = 1;
        missionItem[missonWPindex].frame = MAV_FRAME_GLOBAL;
        missionItem[missonWPindex].current = 0;
        missionItem[missonWPindex].autocontinue = 0; // 自动走到下一个航点
        globeState.TaskCount = missonWPindex;
        missonWPindex++;

        barTotal = missonWPindex;
        barTotal++; // setParamAsync("WP_SPEED", 1.0) 这里一次
        barTotal++;

        if (ROVER_MODE_LOITER != globeState.custom_mode)
        {
            barTotal++;
        }

        float speed;
        switch (configParam.BoatSpeed)
        {
        case Speed_min:
            speed = BoatSpeed_LOW;
            break;
        case Speed_normal:
            speed = BoatSpeed_NORMA;
            break;
        case Speed_max:
            speed = BoatSpeed_HIGH;
            break;
        default:
            configParam.BoatSpeed = BoatSpeed_NORMA;
            speed = BoatSpeed_HIGH;
            break;
        }

        for (i = 0; i < 2; ++i) // 命令失败就再一次
        {
            if (setParamAsync("WP_SPEED", speed)) // 设置速度
            {
                Debug("set WPSPEED success");
                if (need_bar)
                {
                    value = (float)(++barCurr) / (float)barTotal * 100.0f;
                    TaskUpProgSendApp(value);
                    lv_bar_set_value(globePopUp.bar, value, LV_ANIM_ON); /* 设置进度条当前值 */
                    sprintf(str, "%d%%", value);
                    lv_label_set_text(globePopUp.label_3, str);
                    Debug("----- %d%% -----", value);
                    if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
                    {
                        lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
                        // lv_obj_move_foreground(globeGUI.light_img);
                    }
                    lvgl_force_refresh();
                }
                break;
            }
            else
            {
                Debug("set WPSPEED fail");
            }
        }
        if (i == 2)
        {
            err = 1;
            break;
        }

        if (ROVER_MODE_LOITER != globeState.custom_mode)
        {
            for (i = 0; i < 2; ++i) // 命令失败就再一次
            {
                if (my_mavlink_msg_command(MAV_CMD_DO_SET_MODE, CUSTOM_MODE_ENABLED, CUSTOM_LOITER, 0, 0, 0, 0, 0, 1))
                {
                    globeState.custom_mode = CUSTOM_LOITER;
                    Debug("CUSTOM_LOITER success");
                    if (need_bar)
                    {
                        value = (float)(++barCurr) / (float)barTotal * 100.0f;
                        TaskUpProgSendApp(value);
                        lv_bar_set_value(globePopUp.bar, value, LV_ANIM_ON); /* 设置进度条当前值 */
                        sprintf(str, "%d%%", value);
                        lv_label_set_text(globePopUp.label_3, str);
                        if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
                        {
                            lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
                            // lv_obj_move_foreground(globeGUI.light_img);
                        }
                        lvgl_force_refresh();
                    }
                    break;
                }
                else
                {
                    Debug("CUSTOM_LOITER fail");
                }
            }

            if (i == 2)
            {
                err = 1;
                break;
            }
        }

        Debug("missonWPindex: %d", missonWPindex);

        ans = upload(missionItem, missonWPindex, barCurr, barTotal, need_bar);

        if (ans == MAV_MISSION_ACCEPTED)
        {
            Debug("upload success");
            delay_ms(200);

            if (need_bar)
            {
                // show_popup("传输成功", NULL, NULL, NULL, 1000);
            }

            // 设置自动模式
            if (my_mavlink_msg_command(MAV_CMD_DO_SET_MODE, CUSTOM_MODE_ENABLED, CUSTOM_AUTO, 0, 0, 0, 0, 0, 1))
            {
                globeState.custom_mode = ROVER_MODE_AUTO;
                Debug("automode success");
            }
            else
            {
                Debug("automode fail");

                if (need_bar)
                {
                    // show_popup("自动任务失败", NULL, NULL, NULL, 1000);
                    if (take_num == TaskH)
                    {
                        show_popup(Fail_IMG_ID, CommandFail_Lang_ID, Invalid_Lang_ID, 0);
                    }
                    else
                    {
                        show_popup(Fail_IMG_ID, CommandFail_Lang_ID, Invalid_Lang_ID, 0);
                    }
                }
                break;
            }

            if (my_mavlink_msg_command(MAV_CMD_DO_SET_MISSION_CURRENT, 1, 0, 0, 0, 0, 0, 0, 1)) // 开始任务
            {
                Debug("setcurrent mission seq success");
                if (need_bar)
                {
                    // show_popup("自动任务成功", NULL, NULL, NULL, 1000);
                    if (take_num == TaskH)
                    {
                        show_popup(Success_IMG_ID, RTH_OK_Lang_ID, Invalid_Lang_ID, 0);
                    }
                    else
                    {
                        show_popup(Success_IMG_ID, AutoTaskOK_Lang_ID, Invalid_Lang_ID, 0);
                    }
                    if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
                    {
                        lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
                        // lv_obj_move_foreground(globeGUI.light_img);
                    }
                    lvgl_force_refresh();
                }
                globeState.missionStat = MISSION_EXEC; // 当前是任务模式
                globeState.currentItem = 0;
                IsOK = 1; // 任务成功
            }
            else
            {
                Debug("setcurrent mission seq fail");
                if (need_bar)
                {
                    // show_popup("自动任务失败", NULL, NULL, NULL, 1000);
                    if (take_num == TaskH)
                    {
                        show_popup(Fail_IMG_ID, CommandFail_Lang_ID, Invalid_Lang_ID, 0);
                    }
                    else
                    {
                        show_popup(Fail_IMG_ID, CommandFail_Lang_ID, Invalid_Lang_ID, 0);
                    }
                    if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
                    {
                        lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
                        // lv_obj_move_foreground(globeGUI.light_img);
                    }
                    lvgl_force_refresh();
                }
                break;
            }
        }
        else if (ans == MAV_MISSION_RESULT_ENUM_END)
        {
            Debug("upload time out");
            err = 1;
            break;
        }
        else
        {
            err = 1;
            break;
        }
    } while (0);

    if (err)
    {
        Debug("upload fail: %d", ans);
        globeState.HopperCurrentItem = 0;
        globeState.HomeCurrentItem = 0;
        globeState.TaskPointCurrentItem = 0;
        if (need_bar)
        {
            // show_popup("传输失败", NULL, NULL, NULL, 1000);
            if (take_num == TaskH)
            {
                show_popup(Fail_IMG_ID, CommandFail_Lang_ID, Invalid_Lang_ID, 0);
            }
            else
            {
                show_popup(Fail_IMG_ID, CommandFail_Lang_ID, Invalid_Lang_ID, 0);
            }
            if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
            {
                lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
                // lv_obj_move_foreground(globeGUI.light_img);
            }
            lvgl_force_refresh();
        }
    }
    return IsOK;
}

uint8_t my_mavlink_msg_command(MAV_CMD mav_cmd, float p1, float p2, float p3, float p4, float p5, float p6, float p7, uint8_t requireack)
{
    int retrys = 10;
    int timeout = 300;
    uint32_t startTime;

    char str[200];
    sprintf(str, "cmd: %d, p1: %f, p2: %f, p3: %f, p4: %f, p5: %f, p6: %f, p7: %f", mav_cmd, p1, p2, p3, p4, p5, p6, p7);
    Debug("%s", str);

    if (!globeState.isConnect)
    {
        return false;
    }

    cmd_ack_arm(mav_cmd); /* [rc-0001] was: activeFlag = 0 (stale ACK accepted) */

    mavlink_msg_command_long_send(MAVLINK_COMM_0, 1, 1, mav_cmd, 1, p1, p2, p3, p4, p5, p6, p7);

    if (!requireack)
    {
        return true;
    }
    // imu calib take a little while
    else if (mav_cmd == MAV_CMD_PREFLIGHT_CALIBRATION && p5 == 1)
    {
        // this is for advanced accel offsets, and blocks execution
        return true;
    }
    else if (mav_cmd == MAV_CMD_PREFLIGHT_CALIBRATION && p6 == 1)
    {
        // compassmot
        // send again just incase
        mavlink_msg_command_long_send(MAVLINK_COMM_0, 1, 1, mav_cmd, 1, p1, p2, p3, p4, p5, p6, p7);
        return true;
    }
    else if (mav_cmd == MAV_CMD_PREFLIGHT_CALIBRATION)
    {
        retrys = 1;
        timeout = 25000;
    }
    else if (mav_cmd == MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN)
    {
        mavlink_msg_command_long_send(MAVLINK_COMM_0, 1, 1, mav_cmd, 1, p1, p2, p3, p4, p5, p6, p7);
        return true;
    }
    else if (mav_cmd == MAV_CMD_COMPONENT_ARM_DISARM)
    {
        // 10 seconds as may need an imu calib
        timeout = 10000;
    }
    else if (mav_cmd == MAV_CMD_GET_HOME_POSITION)
    {
        retrys = 10;
        timeout = 300;
    }
    else if (mav_cmd == MAV_CMD_DO_SET_HOME)
    {
        retrys = 10;
        timeout = 300;
    }

    startTime = GetSysTick();

    while (retrys > 0)
    {
        if (GetTimeInterval(startTime, GetSysTick()) >= timeout)
        {
            mavlink_msg_command_long_send(MAVLINK_COMM_0, 1, 1, mav_cmd, 1, p1, p2, p3, p4, p5, p6, p7);
            startTime = GetSysTick();
            retrys--;
            continue;
        }

        if (!mavLinkCmdAck.activeFlag && mavLinkCmdAck.CmdACK.command == mav_cmd) /* [rc-0001] only fresh ACK */
        {
            if (mavLinkCmdAck.CmdACK.result == 0)
            {
                Debug("CmdACK.result = %d", mavLinkCmdAck.CmdACK.result);
                return true;
            }
            else if (mav_cmd == MAV_CMD_WAYPOINT_USER_1 || mav_cmd == MAV_CMD_WAYPOINT_USER_2 || mav_cmd == MAV_CMD_WAYPOINT_USER_3) // 这里是用来同步遥控器任务点和标记点的，实际指令无效
            {
                return true;
            }
            else
            {
                Debug("CmdACK.result = %d", mavLinkCmdAck.CmdACK.result);
                return false;
            }
        }
        delay_ms(10);
    }
    Debug("command time out");
    return false;
}

uint8_t my_mavlink_msg_int_command(MAV_CMD mav_cmd, float p1, float p2, float p3, float p4, float x, float y, float z, uint8_t requireack)
{
    int retrys = 10;
    int timeout = 300;
    uint32_t startTime = GetSysTick();

    if (!globeState.isConnect)
    {
        return false;
    }
    cmd_ack_arm(mav_cmd); /* [rc-0001] */
    mavlink_msg_command_int_send(MAVLINK_COMM_0, 1, 1, MAV_FRAME_GLOBAL, mav_cmd, 0, 0, p1, p2, p3, p4, x, y, z);
    if (!requireack)
    {
        return true;
    }
    while (retrys > 0)
    {
        if (GetTimeInterval(startTime, GetSysTick()) >= timeout)
        {
            mavlink_msg_command_int_send(MAVLINK_COMM_0, 1, 1, MAV_FRAME_GLOBAL, mav_cmd, 0, 0, p1, p2, p3, p4, x, y, z);
            startTime = GetSysTick();
            retrys--;
            continue;
        }
        if (!mavLinkCmdAck.activeFlag && mavLinkCmdAck.CmdACK.command == mav_cmd) /* [rc-0001] only fresh ACK */
        {
            if (mavLinkCmdAck.CmdACK.result == 0)
            {
                Debug("CmdACK.result = %d", mavLinkCmdAck.CmdACK.result);
                return true;
            }
            else
            {
                Debug("CmdACK.result = %d", mavLinkCmdAck.CmdACK.result);
                return false;
            }
        }
        delay_ms(10);
    }
    return false;
}

void parse_boat_mavlink_messages(mavlink_message_t *msg)
{
    static uint8_t last_custom_mode = 0;

    mavlink_heartbeat_t heartbeat;
    mavlink_global_position_int_t position;

    switch (msg->msgid)
    {
    case MAVLINK_MSG_ID_HEARTBEAT:
    {
        mavlink_msg_heartbeat_decode(msg, &heartbeat);
        target_system.compid = msg->compid;
        target_system.sysid = msg->sysid;
        globeState.connectCnt = CONNECT_CNT; // 类似喂狗
        globeState.isConnect = 1;
        // Debug ("heartbeat, compid:%d, sysid:%d", target_system.compid, target_system.sysid);

        if (ROVER_MODE_LOITER == heartbeat.custom_mode && last_custom_mode == ROVER_MODE_AUTO) // 自动任务切换了悬停
        {
            if (globeState.NowTask.TaskType <= TaskScan && globeState.IsUpTask == 0)
            {
                globeState.Recover_Task = globeState.NowTask;
                globeState.missionStat = MISSION_IDEL;
                Debug("MISSION_IDEL----->8");
                Debug("Now_TaskType: %d", globeState.Recover_Task.TaskType);
                LED_TaskB_Pin = LED_OFF;
            }
        }

        if (last_custom_mode == ROVER_MODE_LOITER && heartbeat.custom_mode == ROVER_MODE_AUTO) // 悬停切换到了自动任务
        {
            if (globeState.Recover_Task.TaskType != TaskClear && globeState.IsUpTask == 0) // 这里恢复上一次的任务
            {
                globeState.CruiseSta = 0;
                LED_Cruise_Pin = LED_OFF;
                globeState.NowTask = globeState.Recover_Task;
                globeState.NowTask.LED_Sta = globeState.boatLEDStat;
                if (globeState.NowTask.TaskType == TaskScan)
                {
                    globeState.show_main = ShowTaskScan;
                }
                else if (globeState.TaskPointCurrentItem)
                {
                    globeState.show_main = globeState.Recover_Task.TaskType;
                    globeState.missionStat = MISSION_EXEC;
                }
                else if (globeState.HopperCurrentItem)
                {
                    globeState.show_main = ShowMainLogo;
                    globeState.missionStat = MISSION_EXEC;
                }
                else if (globeState.HomeCurrentItem)
                {
                    globeState.show_main = ShowReturnHome;
                    globeState.missionStat = MISSION_EXEC;
                }
                globeState.Recover_Task.TaskType = TaskClear;
                if (globeState.NowTask.TaskType < TaskH)
                {
                    LED_TaskB_Pin = LED_ON;
                }
                else
                {
                    LED_TaskB_Pin = LED_OFF;
                }
                Debug("Recover_TaskType: %d", globeState.NowTask.TaskType);
            }
        }

        if (heartbeat.custom_mode != ROVER_MODE_RTL) /* [rc-0001] boat left RTL: re-arm arrival */
        {
            g_rth_arrival_done = 0;
        }
        globeState.custom_mode = heartbeat.custom_mode;
        last_custom_mode = globeState.custom_mode;
        // 显示的手动和自动模式
        if (heartbeat.base_mode & CUSTOM_MODE_ENABLED && heartbeat.custom_mode == 0) // mannul
        {
            globeState.FCmode = 'M';
        }
        else if (heartbeat.base_mode & CUSTOM_MODE_ENABLED && heartbeat.custom_mode != 0)
        {
            globeState.FCmode = 'A';
            globeState.IsUpTask = 0;
        }

        Debug("globeState.custom_mode: %d", globeState.custom_mode);
        break;
    }

    case MAVLINK_MSG_ID_ATTITUDE:
    {
        // mavlink_msg_attitude_decode(msg, &attitude);
        break;
    }

    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
    {
        mavlink_msg_global_position_int_decode(msg, &position);
        globeState.Angle = position.hdg / 100;
        break;
    }

    case MAVLINK_MSG_ID_GPS_RAW_INT:
    {
        // Debug("MAVLINK_MSG_ID_GPS_RAW_INT");
        globeState.currentPosRefresh = 1;
        globeState.satelliteNum = mavlink_msg_gps_raw_int_get_satellites_visible(msg);

        globeState.current_position.degE7_lat = mavlink_msg_gps_raw_int_get_lat(msg);
        globeState.current_position.degE7_long = mavlink_msg_gps_raw_int_get_lon(msg);
        globeState.current_position.alt_mm = mavlink_msg_gps_raw_int_get_alt(msg);

        globeState.speed = (float)mavlink_msg_gps_raw_int_get_vel(msg) / 100.0f;

#if 0
        if (configParam.BoatSpeed == Speed_max && globeState.NowTask.TaskType != TaskScan)
        {
            globeState.speed *= 1.12f;
        }

        if (globeState.speed > 1.1f)
        {
            globeState.speed = 1.1f;
        }
#endif

        mavlink_msg_send_to_app(BoatSpeed_Msg_ID, (const char *)&globeState.speed, sizeof(globeState.speed));
        break;
    }

    case MAVLINK_MSG_ID_HOME_POSITION:
    {
        globeState.home_position.degE7_lat = mavlink_msg_home_position_get_latitude(msg);
        globeState.home_position.degE7_long = mavlink_msg_home_position_get_longitude(msg);
        globeState.home_position.alt_mm = mavlink_msg_home_position_get_altitude(msg);
        configParam.PositionH = globeState.home_position;
        NeedSave_User_Data();
        Debug("home_position.degE7_lat: %d", globeState.home_position.degE7_lat);
        Debug("home_position.degE7_long: %d", globeState.home_position.degE7_long);
        break;
    }

    case MAVLINK_MSG_ID_MISSION_REQUEST_INT:
    {
        missionCurrState.activeFlag = 1;
        missionCurrState.msgid = msg->msgid;
        missionCurrState.seq = mavlink_msg_mission_request_get_seq(msg);
        break;
    }

    case MAVLINK_MSG_ID_MISSION_REQUEST:
    {
        missionCurrState.activeFlag = 1;
        missionCurrState.msgid = msg->msgid;
        missionCurrState.seq = mavlink_msg_mission_request_get_seq(msg);
        break;
    }

    case MAVLINK_MSG_ID_MISSION_ACK:
    {
        missionCurrState.activeFlag = 1;
        missionCurrState.msgid = msg->msgid;
        missionCurrState.ACKtype = mavlink_msg_mission_ack_get_type(msg);
        break;
    }

    case MAVLINK_MSG_ID_COMMAND_ACK:
    {
        /* [rc-0001] store ACK only if it answers the command we are waiting for */
        mavlink_command_ack_t ack;
        mavlink_msg_command_ack_decode(msg, &ack);

        if (mavLinkCmdAck.activeFlag && ack.command == mavLinkCmdAck.pendingCmd) // 这是遥控器触发的应答
        {
            mavLinkCmdAck.CmdACK = ack;
            mavLinkCmdAck.activeFlag = 0;
        }
        break;
    }

    case MAVLINK_MSG_ID_RADIO_STATUS:
    {
        Debug("radio ");
        break;
    }

    case MAVLINK_MSG_ID_BATTERY_STATUS:
    {
        // Debug("battery ");
        break;
    }

    case MAVLINK_MSG_ID_SYS_STATUS:
    {
        static uint8_t carry_out_once1 = 0;
        static uint8_t carry_out_once2 = 0;
        static uint16_t cnt = 0;
        static uint32_t sum = 0;
        static uint32_t delay = 0;

        uint16_t errors_count1 = mavlink_msg_sys_status_get_errors_count1(msg);
        uint16_t errors_count2 = mavlink_msg_sys_status_get_errors_count2(msg);

        if (errors_count1 == 0 && errors_count2 == 0)
        {
            if (globeState.motor_error_code != DETECT_STALL_NO_ERROR)
            {
                globeState.motor_error_code = DETECT_STALL_NO_ERROR;
                log_info("motor no error");
            }
        }
        else if (errors_count1 == 16 || errors_count2 == 16 ||
                 errors_count1 == 20 || errors_count2 == 20 ||
                 errors_count1 == 48 || errors_count2 == 48)
        {
            if (globeState.motor_error_code != DETECT_STALL_STARTUP_FAIL)
            {
                globeState.motor_error_code = DETECT_STALL_STARTUP_FAIL;
                globeState.motor_error_tick = 0;
                log_error("motor startup fail");
            }
        }
        else if (errors_count1 == 4 || errors_count2 == 4 || errors_count1 == 36 || errors_count2 == 36)
        {
            if (globeState.motor_error_code != DETECT_STALL_FLAG_HIGH_CUR)
            {
                globeState.motor_error_code = DETECT_STALL_FLAG_HIGH_CUR;
                globeState.motor_error_tick = 0;
                log_error("motor stall flag high current");
            }
        }

        if (delay == 0)
        {
            delay = GetSysTick() ? GetSysTick() : 1;
            globeState.boat_voltage_battery = mavlink_msg_sys_status_get_voltage_battery(msg);
            mavlink_msg_send_to_app(BoatVoltage_Msg_ID, (const char *)&globeState.boat_voltage_battery, sizeof(globeState.boat_voltage_battery));
        }
        if (GetTimeInterval(delay, GetSysTick()) >= 10000)
        {
            delay = GetSysTick();
            if (cnt)
            {
                globeState.boat_voltage_battery = sum / cnt;
                if (globeState.boat_voltage_battery > 12600)
                {
                    globeState.boat_voltage_battery = 12600;
                }
                else if (globeState.boat_voltage_battery < 10200 && !carry_out_once1)
                {
                    globeState.BoatLowPowerFlag = 1;
                    carry_out_once1 = 1;
                }
                else if (globeState.boat_voltage_battery < 10620 && !carry_out_once2)
                {
                    globeState.BoatLowPowerFlag = 1;
                    carry_out_once2 = 1;
                }
                else if (globeState.boat_voltage_battery > 11280)
                {
                    carry_out_once1 = 0;
                    carry_out_once2 = 0;
                }
                mavlink_msg_send_to_app(BoatVoltage_Msg_ID, (const char *)&globeState.boat_voltage_battery, sizeof(globeState.boat_voltage_battery));
            }
            cnt = 0;
            sum = 0;
        }
        else
        {
            sum += mavlink_msg_sys_status_get_voltage_battery(msg);
            cnt++;
        }
        globeState.FCbatPercent = mavlink_msg_sys_status_get_battery_remaining(msg);
        // globeState.boat_voltage_battery = mavlink_msg_sys_status_get_voltage_battery(msg);
        log_info("boat_voltage_battery = %d", globeState.boat_voltage_battery);
        break;
    }

    case MAVLINK_MSG_ID_MISSION_ITEM_REACHED:
    {
        // globeState.missionItemReachedFlag = 1;
        // globeState.missionItemReachedSeq = mavlink_msg_mission_item_reached_get_seq (msg);
        // Debug ("item reached %d", mavlink_msg_mission_item_reached_get_seq (msg));
        break;
    }

    case MAVLINK_MSG_ID_MISSION_CURRENT:
    {
        if (globeState.missionStat != MISSION_IDEL)
        {
            globeState.currentItem = mavlink_msg_mission_current_get_seq(msg);
            globeState.currentItemUpdataTime = GetSysTick();
            Debug("globeState.currentItem: %d", globeState.currentItem);
            // Debug("globeState.TaskCount: %d", globeState.TaskCount);
            break;
        }
    }

    case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
    {
        // globeState.rf_rssi = mavlink_msg_rc_channels_raw_get_rssi(msg);
        // Debug ("rf_rssi = %d", globeState.rf_rssi);
        break;
    }

    case MAVLINK_MSG_ID_PARAM_VALUE:
    {
        setparmFlag = 1;
        mavlink_msg_param_value_get_param_id(msg, (char *)paranamebuf);
        break;
    }

    case MAVLINK_MSG_ID_RAW_IMU:
    {
        if (globeState.cal_compass_stat)
        {
            globeState.xgyro = mavlink_msg_raw_imu_get_xgyro(msg);
            Debug("xgyro: %d", globeState.xgyro);
        }
        break;
    }

    case MAVLINK_MSG_ID_COMMAND_LONG:
    {
        uint16_t cmdid = mavlink_msg_command_long_get_command(msg);

        if (cmdid != 410)
        {
            Debug("msgid: %d  ", msg->msgid);
            Debug("cmdid = %d  ", cmdid);
            Debug("parm1 = %d", (int)mavlink_msg_command_long_get_param1(msg));
        }
        break;
    }

    case MAVLINK_MSG_ID_STATUSTEXT:
    {
        // if (globeState.BoatVersion == Unknown_Boat)
        {
            mavlink_statustext_t mavlink_statustext;
            memcpy(&mavlink_statustext, msg->payload64, sizeof(mavlink_statustext_t));
            Debug("boat version: %s", mavlink_statustext.text);
            // globeState.BoatVersion = CatchX_Ultra;
            // globeState.show_mainRefresh = Refresh;
            // break;
            int len = strlen("catchx_black.");
            if (!strncmp(mavlink_statustext.text, "catchx_black.", len))
            {
                globeState.BoatVersion = CatchX_MAX;
                globeState.show_mainRefresh = Refresh;
                if (globeState.BoatVersion != configParam.BoatVersion)
                {
                    configParam.BoatVersion = globeState.BoatVersion;
                    NeedSave_User_Data();
                }
                break;
            }
            len = strlen("catchx_rogue_max");
            if (!strncmp(mavlink_statustext.text, "catchx_rogue_max", len))
            {
                globeState.BoatVersion = Rogue_MAX;
                globeState.show_mainRefresh = Refresh;
                if (globeState.BoatVersion != configParam.BoatVersion)
                {
                    configParam.BoatVersion = globeState.BoatVersion;
                    NeedSave_User_Data();
                }
                break;
            }
            len = strlen("catchx_ultra");
            if (!strncmp(mavlink_statustext.text, "catchx_ultra", len))
            {
                globeState.BoatVersion = CatchX_Ultra;
                globeState.show_mainRefresh = Refresh;
                if (globeState.BoatVersion != configParam.BoatVersion)
                {
                    configParam.BoatVersion = globeState.BoatVersion;
                    NeedSave_User_Data();
                }
                break;
            }
        }
        break;
    }

    default:
        break;
    }
}

// 求弧度
static double radian(double d)
{
#define PI 3.1415926
#define EARTH_RADIUS 6378137 // 地球近似半径
    return d * PI / 180.0;   // 角度s = π / 180
}

// unit meter
double get_distance(double lat1, double lng1, double lat2, double lng2)
{
    double radLat1 = radian(lat1);
    double radLat2 = radian(lat2);
    double a = radLat1 - radLat2;
    double b = radian(lng1) - radian(lng2);

    double dst = 2 * asin((sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2))));

    dst = dst * EARTH_RADIUS;
    if (dst < 0)
    {
        dst = -dst;
    }
    return dst;
}

void parse_boat_mavlink_msg_task(void *param)
{
    uint16_t i;
    uint8_t c;
    // static uint16_t recSeq = 0;
    // short lastSeq = -1;

    uint16_t rx_len;

    mavlink_message_t msg;
    mavlink_status_t status;

    MavRecBinary = xSemaphoreCreateBinary();

    status.packet_rx_drop_count = 0;
    mavlink_system.sysid = 255;
    mavlink_system.compid = 190;

    for (;;)
    {
        // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        xSemaphoreTake(MavRecBinary, portMAX_DELAY);
        rx_len = getFifoLen(&Rf_Rx_Fifo);
        // Debug("rx_len: %d", rx_len);

        for (i = 0; i < rx_len; ++i)
        {
            IWDG_Feed();
            fifoGet(&Rf_Rx_Fifo, &c, 1);
            // printf("%02X ", c);
            if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status) == MAVLINK_FRAMING_OK)
            {
                // Debug("msgid: %d", msg.msgid);
                // Debug("sysid: %x", msg.sysid);
                switch (msg.sysid)
                {
                case AppSysID:
                {
                    globeState.WiFiConnect = 1;
                    parse_app_mavlink_messages(&msg);
                }
                break;
                case DTU_SONAR_SYS_ID:
                {
                    boat_dtu_return_mavlink_msg(&msg);
                }
                break;
                default:
                {
                    WiFi_Uart_Send((uint8_t *)(&msg.magic), MAVLINK_NUM_HEADER_BYTES + MAVLINK_NUM_CHECKSUM_BYTES + msg.len); // 这里是解析成功之后再转发给App
                    if (!globeState.isConnect)
                    {
                        if (signal > -67)
                            globeState.rf_rssi = 5;
                        else if (signal > -79)
                            globeState.rf_rssi = 4;
                        else if (signal > -85)
                            globeState.rf_rssi = 3;
                        else if (signal > -88)
                            globeState.rf_rssi = 2;
                        else if (signal > -90)
                            globeState.rf_rssi = 1;
                        else
                            globeState.rf_rssi = 1;
                        globeState.isConnect = 1;
                    }
                    if (globeState.BoatVersion == Init)
                    {
                        globeState.BoatVersion = Unknown_Boat;
                    }
#ifdef ENDU_TEST_BUILD
                    /* ENDU test: ACKs for the App's MAV_CMD_USER_1/2 (31010/31011) are only for the App */
                    if (!(msg.msgid == MAVLINK_MSG_ID_COMMAND_ACK &&
                          (mavlink_msg_command_ack_get_command(&msg) == 31010 || mavlink_msg_command_ack_get_command(&msg) == 31011)))
#endif
                    parse_boat_mavlink_messages(&msg);
                    Debug("msgid: %d", msg.msgid);
                }
                break;
                }
            }
        }
        // printf("\r\n");
    }
}

void joystick_value_send_to_boat(void *param)
{
    joystickFlyf_t joystick;

    for (uint8_t i = 0; i < 18; i++)
    {
        ((uint16_t *)&rc_channels.chan1_raw)[i] = 1500;
    }
    rc_channels.chancount = 18;
    rc_channels.rssi = 255;

    for (;;)
    {
        if (globeState.isConnect && configParam.JoystickChoose == 0)
        {
            rc_channels.time_boot_ms = GetSysTick();
            if (show_ui == MAIN_UI || show_ui == BOAT_TASK_PRESET_UI)
            {
                ADCtoFlyDataPercent(&joystick);
                rc_channels.chan3_raw = (uint16_t)joystick.pitch;
                rc_channels.chan4_raw = (uint16_t)joystick.roll;
                // pit 是上下
                // roll是左右
                // Debug("pitch: %d", rc_channels.chan3_raw);
                // Debug("roll: %d", rc_channels.chan4_raw);
            }
            else
            {
                rc_channels.chan3_raw = 1500;
                rc_channels.chan4_raw = 1500;
            }
            mavlink_msg_rc_channels_send_struct(MAVLINK_COMM_0, &rc_channels);
        }
        else
        {
            rc_channels.chan3_raw = 1500;
            rc_channels.chan4_raw = 1500;
        }
        IWDG_Feed();
        delay_ms(50);
    }
}

void mavlink_msg_send_to_app(uint8_t msgid, const char *packet, uint8_t length)
{
    if (!globeState.WiFiConnect)
    {
        return;
    }

    uint16_t checksum;
    uint8_t buf[MAVLINK_NUM_HEADER_BYTES];
    uint8_t ck[2];
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_1);

    switch (mavlink_type)
    {
    case 0:
        buf[0] = MAVLINK_STX0;
        break;
    case 1:
        buf[0] = MAVLINK_STX1;
        break;
    default:
        buf[0] = MAVLINK_STX1;
        break;
    }

    buf[1] = length;
    buf[2] = status->current_tx_seq;
    buf[3] = AppSysID;
    buf[4] = AppCompID;
    buf[5] = msgid;
    status->current_tx_seq++;
    checksum = crc_calculate((const uint8_t *)&buf[1], MAVLINK_CORE_HEADER_LEN);
    crc_accumulate_buffer(&checksum, packet, length);
    crc_accumulate(mavlink_message_crcs(msgid), &checksum);
    ck[0] = (uint8_t)(checksum & 0xFF);
    ck[1] = (uint8_t)(checksum >> 8);

    _mavlink_send_uart(MAVLINK_COMM_0, (const char *)buf, MAVLINK_NUM_HEADER_BYTES);
    _mavlink_send_uart(MAVLINK_COMM_0, packet, length);
    _mavlink_send_uart(MAVLINK_COMM_0, (const char *)ck, 2);
    Rf_Tx_Fifo_Uart_Send();

#if 1
    fifoPut(&WiFi_Tx_Fifo, buf, MAVLINK_NUM_HEADER_BYTES);
    fifoPut(&WiFi_Tx_Fifo, (uint8_t *)packet, length);
    fifoPut(&WiFi_Tx_Fifo, ck, 2);

    int Length = getFifoLen(&WiFi_Tx_Fifo);

    if (WiFi_Tx_Fifo.uartSendBusy)
    {
        return;
    }

    if (Length > WiFiUart4_Tx_DMA_Buf_SIZE)
    {
        fifoGet(&WiFi_Tx_Fifo, WiFiUart4_Tx_DMA_Buf, WiFiUart4_Tx_DMA_Buf_SIZE);

        DMA1_Stream4->SCFG_B.EN = 0;
        DMA_ClearStatusFlag(DMA1_Stream4, DMA_FLAG_TCIFLG4);
        DMA1_Stream4->NDATA = WiFiUart4_Tx_DMA_Buf_SIZE;
        DMA1_Stream4->SCFG_B.EN = 1;

        WiFi_Tx_Fifo.uartSendBusy = 1;
    }
    else
    {
        fifoGet(&WiFi_Tx_Fifo, WiFiUart4_Tx_DMA_Buf, Length);

        DMA1_Stream4->SCFG_B.EN = 0;
        DMA_ClearStatusFlag(DMA1_Stream4, DMA_FLAG_TCIFLG4);
        DMA1_Stream4->NDATA = Length;
        DMA1_Stream4->SCFG_B.EN = 1;

        WiFi_Tx_Fifo.uartSendBusy = 1;
    }
#endif
}

void mavlink_set_sys_msg_send_to_dtu(uint8_t SysID, uint8_t CompID, uint8_t msgid, const char *packet, uint8_t length)
{
    uint16_t checksum;
    uint8_t buf[MAVLINK_NUM_HEADER_BYTES];
    uint8_t ck[2];
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_1);

    switch (mavlink_type)
    {
    case 0:
        buf[0] = MAVLINK_STX0;
        break;
    case 1:
        buf[0] = MAVLINK_STX1;
        break;
    default:
        buf[0] = MAVLINK_STX1;
        break;
    }

    buf[1] = length;
    buf[2] = status->current_tx_seq;
    buf[3] = SysID;
    buf[4] = CompID;
    buf[5] = msgid;
    status->current_tx_seq++;
    checksum = crc_calculate((const uint8_t *)&buf[1], MAVLINK_CORE_HEADER_LEN);
    crc_accumulate_buffer(&checksum, packet, length);
    crc_accumulate(mavlink_message_crcs(msgid), &checksum);
    ck[0] = (uint8_t)(checksum & 0xFF);
    ck[1] = (uint8_t)(checksum >> 8);

    _mavlink_send_uart(MAVLINK_COMM_0, (const char *)buf, MAVLINK_NUM_HEADER_BYTES);
    _mavlink_send_uart(MAVLINK_COMM_0, packet, length);
    _mavlink_send_uart(MAVLINK_COMM_0, (const char *)ck, 2);
    Rf_Tx_Fifo_Uart_Send();

#if 0
    uint16_t checksum;
    uint8_t buf[MAVLINK_NUM_HEADER_BYTES];
    uint8_t ck[2];
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_1);

    buf[0] = MAVLINK_STX3;
    buf[1] = length;
    buf[2] = status->current_tx_seq;
    buf[3] = mavlink_system.sysid;
    buf[4] = mavlink_system.compid;
    buf[5] = msgid;
    status->current_tx_seq++;
    // checksum = crc_calculate((const uint8_t *)&buf[1], MAVLINK_CORE_HEADER_LEN);
    checksum = X25_INIT_CRC;
    crc_accumulate_buffer(&checksum, (const char *)&buf[1], MAVLINK_CORE_HEADER_LEN);
    crc_accumulate_buffer(&checksum, packet, length);
    crc_accumulate(mavlink_message_crcs(msgid), &checksum);
    ck[0] = (uint8_t)(checksum & 0xFF);
    ck[1] = (uint8_t)(checksum >> 8);

    fifoPut(&WiFi_Tx_Fifo, buf, MAVLINK_NUM_HEADER_BYTES);
    fifoPut(&WiFi_Tx_Fifo, (uint8_t *)packet, length);
    fifoPut(&WiFi_Tx_Fifo, ck, 2);

    int Length = getFifoLen(&WiFi_Tx_Fifo);

    if (WiFi_Tx_Fifo.uartSendBusy)
    {
        return;
    }

    if (Length > WiFiUart4_Tx_DMA_Buf_SIZE)
    {
        fifoGet(&WiFi_Tx_Fifo, WiFiUart4_Tx_DMA_Buf, WiFiUart4_Tx_DMA_Buf_SIZE);

        DMA1_Stream4->SCFG_B.EN = 0;
        DMA_ClearStatusFlag(DMA1_Stream4, DMA_FLAG_TCIFLG4);
        DMA1_Stream4->NDATA = WiFiUart4_Tx_DMA_Buf_SIZE;
        DMA1_Stream4->SCFG_B.EN = 1;

        WiFi_Tx_Fifo.uartSendBusy = 1;
    }
    else
    {
        fifoGet(&WiFi_Tx_Fifo, WiFiUart4_Tx_DMA_Buf, Length);

        DMA1_Stream4->SCFG_B.EN = 0;
        DMA_ClearStatusFlag(DMA1_Stream4, DMA_FLAG_TCIFLG4);
        DMA1_Stream4->NDATA = Length;
        DMA1_Stream4->SCFG_B.EN = 1;

        WiFi_Tx_Fifo.uartSendBusy = 1;
    }
#endif
}

uint8_t Set_Connect_WiFi_Name(char *deviceName)
{
    // vTaskSuspend(ParseBoatMavTaskHandle); // 挂起接收船数据的任务
    // 清除RF缓冲区数据
    Rf_Tx_Fifo.in = Rf_Tx_Fifo.out = 0;
    Rf_Tx_Fifo.lenth = 0;
    Rf_Tx_Fifo.uartSendBusy = 0;
    Rf_Rx_Fifo.in = Rf_Rx_Fifo.out = 0;
    Rf_Rx_Fifo.lenth = 0;
    Rf_Rx_Fifo.uartSendBusy = 0;

    globeState.SetNameOK = 0;
    S_SetWirelessName_Msg SetWirelessName_Msg;
    SetWirelessName_Msg.type = 2;
    strcpy(SetWirelessName_Msg.name, deviceName);
    mavlink_set_sys_msg_send_to_dtu(DTU_SONAR_SYS_ID, BOAT_DTU_COMP_ID, SetWirelessName_Msg_ID, (char *)&SetWirelessName_Msg, sizeof(S_SetWirelessName_Msg));

    for (uint8_t i = 0; i < 10; i++)
    {
        delay_ms(100);
        if (globeState.SetNameOK)
        {
            globeState.SetNameOK = 0;
            Debug("Set_Connect_WiFi_Name OK");
            // vTaskResume(ParseBoatMavTaskHandle);
            return 1;
        }
        else
        {
            mavlink_set_sys_msg_send_to_dtu(DTU_SONAR_SYS_ID, BOAT_DTU_COMP_ID, SetWirelessName_Msg_ID, (char *)&SetWirelessName_Msg, sizeof(S_SetWirelessName_Msg));
        }
        Debug("Set_Connect_WiFi_Name");
    }
    // vTaskResume(ParseBoatMavTaskHandle);

    return 0;
}

void remote_system_data_send_to_app(void)
{
    S_RemoteSysData_Msg RemoteSysData_Msg;

    RemoteSysData_Msg.CommType = 0;
    RemoteSysData_Msg.BoatAnchorEn = configParam.BoatAnchorEn;
    RemoteSysData_Msg.SoftwareVersion = SoftwareVERSION;
    RemoteSysData_Msg.HardwareVersion = HardwareVERSION;
    RemoteSysData_Msg.Bat = globeState.RemoteBat;
    RemoteSysData_Msg.PositionA = globeState.Task_Sta.PositionA;
    RemoteSysData_Msg.PositionB = globeState.Task_Sta.PositionB;
    RemoteSysData_Msg.PositionC = globeState.Task_Sta.PositionC;
    RemoteSysData_Msg.PositionD = globeState.Task_Sta.PositionD;
    RemoteSysData_Msg.AtHomeAndAbroad = globeState.AtHomeAndAbroad;
    RemoteSysData_Msg.LOG = globeState.Log;
    RemoteSysData_Msg.NowTask = globeState.NowTask;
    if (globeState.chargeStat == delay_not_charging)
    {
        RemoteSysData_Msg.chargeStat = not_charging;
    }
    else
    {
        RemoteSysData_Msg.chargeStat = globeState.chargeStat;
    }
    mavlink_msg_send_to_app(RemoteSysData_Msg_ID, (const char *)&RemoteSysData_Msg, sizeof(S_RemoteSysData_Msg));
}

void TaskUpProgSendApp(uint8_t progress)
{
    if (globeState.App_Task_Flag) // App做任务才给App发送任务上传进度
    {
        mavlink_msg_send_to_app(TaskUpProg_Msg_ID, (const char *)&progress, sizeof(progress));
    }
}

void parse_app_mavlink_messages(mavlink_message_t *msg)
{
    S_MsgAsk_Msg MsgAsk_Msg;
    static uint32_t FifoLen = 0;
    static uint8_t flag = 0;
    static uint8_t last_seq = 0;

    switch (msg->msgid)
    {
    case MsgASK_Msg_ID:
    {
        memcpy(&MsgAsk_Msg, msg->payload64, msg->len);
        if (MsgAsk_Msg.Msg_ID == Reposition_Value_Msg_ID && MsgAsk_Msg.Ask_Data == Success)
        {
            globeState.Reposition_CNT = 0;
            log_info("Reposition_Value_Msg_ID is OK");
        }
    }
    break;

    case FileInfo_Msg_ID:
    {
        memcpy(&FileInfo, msg->payload64, sizeof(S_FileInfo));
        log_info("FileType: %d", FileInfo.FileType);
        log_info("FileSize: %d", FileInfo.FileSize);
        log_info("FileCRC: %08X", FileInfo.FileCRC);
        log_info("FileName: %s", FileInfo.File_Name);

        if (FileInfo.FileSize && FileInfo.FileType == OTA_File)
        {
            ota_data.OTA_FileSize = FileInfo.FileSize;
            ota_data.OTA_FileCRC = FileInfo.FileCRC;
            WriteOTAConfigParamEeprom();
            WriteUserConfigParamEeprom();
            delay_ms(2);
            NVIC_SystemReset(); // 复位系统
            // iap_load_app(0x8000000);
        }
        else if (FileInfo.FileSize < 48 * 1024 && FileInfo.FileType == BootLoaderOTA_File)
        {
            globeState.SuspendMavRecTaskTime = GetSysTick();
            MsgAsk_Msg.Msg_ID = FileInfo_Msg_ID;
            MsgAsk_Msg.Ask_Data = Success;
            mavlink_msg_send_to_app(MsgASK_Msg_ID, (const char *)&MsgAsk_Msg, sizeof(S_MsgAsk_Msg));
            flag = 0; // 需要擦除
            flash_offset = 0;
        }
        else
        {
            MsgAsk_Msg.Msg_ID = FileInfo_Msg_ID;
            MsgAsk_Msg.Ask_Data = ErrParameter;
            mavlink_msg_send_to_app(MsgASK_Msg_ID, (const char *)&MsgAsk_Msg, sizeof(S_MsgAsk_Msg));
        }
    }
    break;

#if 1
    case FileTransmit_Msg_ID:
    {
        if (FileInfo.FileSize && globeState.SuspendMavRecTaskTime)
        {
            globeState.SuspendMavRecTaskTime = GetSysTick();
            if (last_seq == msg->seq || !flash_offset) // 这里用于过滤重传的包
            {
                fifoPut(&FileFifo, (uint8_t *)msg->payload64, msg->len);
                FifoLen = getFifoLen(&FileFifo);
                Debug("len: %d", flash_offset + FifoLen);
                if (FifoLen >= WRITE_FLASH_SIZE)
                {
                    if (!flag)
                    {
                        flag = 1;
                        BootLoader_Flash_Erasure();
                    }

                    fifoGet(&FileFifo, flash_file_buf, WRITE_FLASH_SIZE);
                    apmflash_write_buff(flash_offset + BOOT_FIRMWARE_START_ADDR, flash_file_buf, WRITE_FLASH_SIZE);
                    flash_offset += WRITE_FLASH_SIZE;
                }

                FifoLen = getFifoLen(&FileFifo);

                if (FifoLen + flash_offset == FileInfo.FileSize)
                {
                    if (FifoLen)
                    {
                        memset(&flash_file_buf[FifoLen], 0xFF, 4 - FifoLen % 4); // 这里是防止未4字节对齐把后面的数据写进flash了
                        fifoGet(&FileFifo, flash_file_buf, FifoLen);
                        apmflash_write_buff(flash_offset + BOOT_FIRMWARE_START_ADDR, flash_file_buf, FifoLen);
                        flash_offset += FifoLen;
                    }
                    log_info("transmit size: %d", flash_offset);

                    uint32_t ReadFileCRC = crc32((uint8_t *)BOOT_FIRMWARE_START_ADDR, FileInfo.FileSize);
                    log_info("Flash File CRC: %08X", ReadFileCRC);
                    log_info("Now File CRC: %08X", FileInfo.FileCRC);

                    if (FileInfo.FileCRC == ReadFileCRC)
                    {
                        MsgAsk_Msg.Msg_ID = FileTransmit_Msg_ID;
                        MsgAsk_Msg.Ask_Data = Success;
                        mavlink_msg_send_to_app(MsgASK_Msg_ID, (const char *)&MsgAsk_Msg, sizeof(S_MsgAsk_Msg)); // 应答
                        vTaskResume(ParseBoatMavTaskHandle);
                        globeState.SuspendMavRecTaskTime = 0;
                    }
                    else
                    {
                        MsgAsk_Msg.Msg_ID = FileTransmit_Msg_ID;
                        MsgAsk_Msg.Ask_Data = FirmwareCRC_ERROR;
                        mavlink_msg_send_to_app(MsgASK_Msg_ID, (const char *)&MsgAsk_Msg, sizeof(S_MsgAsk_Msg)); // 应答
                    }
                }
                MsgAsk_Msg.Ask_Data = Success;
                MsgAsk_Msg.Msg_ID = FileTransmit_Msg_ID;
                mavlink_msg_send_to_app(MsgASK_Msg_ID, (const char *)&MsgAsk_Msg, sizeof(S_MsgAsk_Msg)); // 应答
                last_seq = msg->seq;
                last_seq++;
            }
            else
            {
                MsgAsk_Msg.Ask_Data = SEQ_ERROR;
                MsgAsk_Msg.Msg_ID = FileTransmit_Msg_ID;
                mavlink_msg_send_to_app(MsgASK_Msg_ID, (const char *)&MsgAsk_Msg, sizeof(S_MsgAsk_Msg)); // 应答
                log_info("SEQ_ERROR!!!");
            }
        }
        else
        {
            MsgAsk_Msg.Ask_Data = Nonsupport;
            memset((void *)&FileInfo, 0, sizeof(S_FileInfo));
            MsgAsk_Msg.Msg_ID = FileTransmit_Msg_ID;
            mavlink_msg_send_to_app(MsgASK_Msg_ID, (const char *)&MsgAsk_Msg, sizeof(S_MsgAsk_Msg)); // 应答
        }
    }
    break;
#endif
    case SysDataRequest_Msg_ID:
    {
        S_SysDataRequest_Msg SysDataRequest_Msg;
        memcpy(&SysDataRequest_Msg, msg->payload64, sizeof(S_SysDataRequest_Msg));

        if (SysDataRequest_Msg.Request_Msg_ID == RemoteSysData_Msg_ID)
        {
            remote_system_data_send_to_app();
            mavlink_msg_send_to_app(RemoteVoltagePercent_Msg_ID, (void *)&globeState.batPercent, sizeof(globeState.batPercent));
            Debug("SysDataRequest_Msg_ID");
        }
        else if (SysDataRequest_Msg.Request_Msg_ID == HardFaultMsg_Msg_ID)
        {
            apmflash_read_buff(ADDR_FLASH_SECTOR_3, (void *)&HardFaultMsgSave, sizeof(HardFaultMsgSave));
            mavlink_msg_send_to_app(HardFaultMsg_Msg_ID, (void *)&HardFaultMsgSave, sizeof(HardFaultMsgSave));
            Debug("HardFaultMsg_Msg_ID");
        }
    }
    break;

    case Command_Msg_ID:
    {
        S_Command_Data Command_Data;
        S_ComAsk_Msg ComAsk_Msg;

        memcpy(&Command_Data, msg->payload64, sizeof(S_Command_Data));

        switch (Command_Data.Command_ID)
        {
        case BoatAnchorEn:
        {
            ComAsk_Msg.Command_ID = BoatAnchorEn;
            ComAsk_Msg.Ask_Data = Success;

            if (Command_Data.Parameter0)
            {
                if (configParam.BoatAnchorEn != ENABLE)
                {
                    configParam.BoatAnchorEn = ENABLE;
                    log_info("BoatAnchorEn ENABLE");
                    NeedSave_User_Data();
                }
            }
            else
            {
                if (configParam.BoatAnchorEn != DISABLE)
                {
                    configParam.BoatAnchorEn = DISABLE;
                    log_info("BoatAnchorEn DISABLE");
                    NeedSave_User_Data();
                }
            }
        }
        break;
        case AtHomeAndAbroad:
        {
            ComAsk_Msg.Command_ID = AtHomeAndAbroad;
            ComAsk_Msg.Ask_Data = Success;
            if (globeState.AtHomeAndAbroad != Command_Data.Parameter0)
            {
                globeState.AtHomeAndAbroad = Command_Data.Parameter0;
                // NeedSave_User_Data();
                ee_WriteBytes((uint8_t *)&globeState.AtHomeAndAbroad, AT_HOME_AND_ABROAD_ADDR, sizeof(globeState.AtHomeAndAbroad));
                globeState.show_mainRefresh = Refresh;
            }
            log_info("AtHomeAndAbroad: %d", globeState.AtHomeAndAbroad);
        }
        break;
        case LogSet:
        {
            ComAsk_Msg.Command_ID = LogSet;
            ComAsk_Msg.Ask_Data = Success;
            if (globeState.Log != Command_Data.Parameter0)
            {
                globeState.Log = Command_Data.Parameter0;
                ee_WriteBytes((uint8_t *)&globeState.Log, LOG_ADDR, sizeof(globeState.Log));
                globeState.show_mainRefresh = Refresh;
            }
            log_info("globeState.Log: %d", globeState.Log);
        }
        break;
        case Reposition_REQ:
        {
            S_Reposition_Value_Msg Reposition_Value = globeState.Reposition_Value;
            ComAsk_Msg.Command_ID = Reposition_REQ;
            Reposition_Value.RepositionState = App_Request;
            mavlink_msg_send_to_app(Reposition_Value_Msg_ID, (const char *)&Reposition_Value, sizeof(S_Reposition_Value_Msg));
            Debug("---> Reposition_REQ");
        }
        break;
        case 255:
        {
            ComAsk_Msg.Command_ID = 255;
            ComAsk_Msg.Ask_Data = Success;
            DebugGrade = Command_Data.Parameter0;
        }
        break;
        default:
        {
            ComAsk_Msg.Command_ID = Command_Data.Command_ID;
            ComAsk_Msg.Ask_Data = Nonsupport;
            log_info("Nonsupport");
        }
        break;
        }
        mavlink_msg_send_to_app(ComASK_Msg_ID, (const char *)&ComAsk_Msg, sizeof(S_ComAsk_Msg));
    }
    break;

    case ComASK_Msg_ID:
    {
        S_ComAsk_Msg ComAsk_Msg;
        memcpy(&ComAsk_Msg, msg->payload64, sizeof(S_ComAsk_Msg));
        if (ComAsk_Msg.Ask_Data == Success && ComAsk_Msg.Command_ID == Reposition_REQ)
        {
            // globeState.PopUp_Inform.PopUp_EN = 1;
            // globeState.PopUp_Inform.img_id = Reposition_IMG_ID;
            // globeState.PopUp_Inform.str1_id = RepositionOK_Lang_ID;
            // globeState.PopUp_Inform.str2_id = Invalid_Lang_ID;
            // globeState.PopUp_Inform.bar_en = 0;
            // globeState.PopUp_Inform.bar = 0;
            if (ComAsk_Msg.Ask_Data == Success)
            {
                log_info("Reposition_REQ OK\n");
                globeState.App_ASK = Success;
            }
            else
            {
                log_info("Reposition_REQ Fail\n");
                globeState.App_ASK = Fail;
            }
        }
    }
    break;

    case Reposition_Value_Msg_ID:
    {
        memcpy((void *)&globeState.Reposition_Value, msg->payload64, sizeof(S_Reposition_Value_Msg));

        MsgAsk_Msg.Msg_ID = Reposition_Value_Msg_ID;
        MsgAsk_Msg.Ask_Data = Success;
        mavlink_msg_send_to_app(MsgASK_Msg_ID, (const char *)&MsgAsk_Msg, sizeof(S_MsgAsk_Msg));

        log_info("lat_Diff: %d", globeState.Reposition_Value.lat_Diff);
        log_info("long_Diff: %d", globeState.Reposition_Value.long_Diff);
    }
    break;

    case ReferencePoint_Msg_ID:
    {
        S_Position ReferencePoint; /* 参照点 */
        memcpy((void *)&ReferencePoint, msg->payload64, sizeof(S_Position));

        MsgAsk_Msg.Msg_ID = ReferencePoint_Msg_ID;
        if (ReferencePoint.degE7_lat != globeState.ReferencePoint.degE7_lat &&
            ReferencePoint.degE7_long != globeState.ReferencePoint.degE7_long)
        {
            MsgAsk_Msg.Ask_Data = Success;
            globeState.ReferencePoint = ReferencePoint;
        }
        else
        {
            MsgAsk_Msg.Ask_Data = ErrParameter;
        }
        mavlink_msg_send_to_app(MsgASK_Msg_ID, (const char *)&MsgAsk_Msg, sizeof(S_MsgAsk_Msg));

        if (MsgAsk_Msg.Ask_Data == Success)
        {
            globeState.PopUp_Inform.PopUp_EN = 1;
            if (globeState.ReferencePoint.degE7_lat && globeState.ReferencePoint.degE7_long)
            {
                globeState.PopUp_Inform.img_id = Circle_IMG_ID;
                globeState.PopUp_Inform.str1_id = ReferencePointAcquired_Lang_ID;
            }
            else
            {
                globeState.PopUp_Inform.img_id = Trash_IMG_ID;
                globeState.PopUp_Inform.str1_id = ReferencePointCleared_Lang_ID;
            }
            globeState.PopUp_Inform.str2_id = Invalid_Lang_ID;
            globeState.PopUp_Inform.bar_en = 0;
            globeState.PopUp_Inform.bar = 0;
        }

        log_info("degE7_lat: %d", globeState.ReferencePoint.degE7_lat);
        log_info("degE7_long: %d", globeState.ReferencePoint.degE7_long);
        log_info("alt_mm: %d", globeState.ReferencePoint.alt_mm);
    }
    break;

    case App_Task_Msg_ID:
    {
        S_MsgAsk_Msg MsgAsk_Msg;
        memcpy((S_Position *)&globeState.App_Task_Msg, msg->payload64, sizeof(S_App_Task_Msg));
        log_info("TaskType: %d", globeState.App_Task_Msg.TaskType);
        log_info("Hopper: %d", globeState.App_Task_Msg.Hopper);
        log_info("TaskIcom: %d", globeState.App_Task_Msg.TaskIcom);
        log_info("LED_Sta: %d", globeState.App_Task_Msg.LED_Sta);
        log_info("Home: %d", globeState.App_Task_Msg.Home);
        log_info("Hook: %d", globeState.App_Task_Msg.Hook);
        if (globeState.App_Task_Msg.TaskType >= TaskA_Preset && globeState.App_Task_Msg.TaskType <= TaskApp_Preset)
        {
            if (globeState.custom_mode == ROVER_MODE_AUTO || globeState.custom_mode == ROVER_MODE_RTL ||
                globeState.CruiseSta || globeState.cal_compass_stat)
            {
                globeState.PopUp_Inform.PopUp_EN = 1;
                globeState.PopUp_Inform.img_id = Fail_IMG_ID;
                globeState.PopUp_Inform.str1_id = NotExecuteDuringTask_Lang_ID;
                globeState.PopUp_Inform.str2_id = Invalid_Lang_ID;
                globeState.PopUp_Inform.bar_en = 0;

                MsgAsk_Msg.Ask_Data = AppTaskInTheTask;
            }
            else if ((show_ui == MAIN_UI || show_ui == BOAT_TASK_PRESET_UI) && !(*((uint32_t *)&globeState.Task_Sta.GetPosA_En)) && !globeState.Task_Sta.SetHome_En)
            {
                globeState.App_Task_Msg.TaskType = globeState.App_Task_Msg.TaskType - TaskA_Preset;
                globeState.TaskPresetFlag = 1;
                MsgAsk_Msg.Ask_Data = AppTaskSuccess;
                globeState.App_Task_Flag = 1;
            }
            else
            {
                globeState.PopUp_Inform.PopUp_EN = 1;
                globeState.PopUp_Inform.img_id = Fail_IMG_ID;
                globeState.PopUp_Inform.str1_id = ExitAfterTaskPreset_Lang_ID;
                globeState.PopUp_Inform.str2_id = Invalid_Lang_ID;
                globeState.PopUp_Inform.bar_en = 0;

                MsgAsk_Msg.Ask_Data = AppTaskExitTheExecutable;
            }
            MsgAsk_Msg.Msg_ID = App_Task_Msg_ID;
            mavlink_msg_send_to_app(MsgASK_Msg_ID, (const char *)&MsgAsk_Msg, sizeof(S_MsgAsk_Msg));
        }
        else
        {
            if (globeState.TaskPresetFlag != 0)
            {
                globeState.TaskPresetFlag = 0;
                globeState.Cut_Show_UI = MAIN_UI;
                mavlink_msg_send_to_app(ClearTaskPreset_Msg_ID, (void *)0, 0);
            }
            globeState.App_Task_Flag = 1;
            globeState.ScanTaskRemainTime = 0;
        }
    }
    break;

    case ScanTaskRemainTime_Msg_ID:
    {
        if (globeState.NowTask.TaskType == TaskScan && globeState.custom_mode != ROVER_MODE_LOITER)
        {
            memcpy((void *)&globeState.ScanTaskRemainTime, msg->payload64, sizeof(uint16_t));
            log_info("ScanTaskRemainTime: %d", globeState.ScanTaskRemainTime);
            boat_task_init(NULL, 1, ShowTaskScan, 0, 0, 0, 0, 1);
            globeState.show_mainRefresh = Refresh;
        }
    }
    break;

    case SetPoint_Msg_ID:
    {
        E_SetPointAskParameter SetPointAskParameter;
        S_SetPoint_Msg SetPoint_Msg;

        memcpy((void *)&SetPoint_Msg, msg->payload64, sizeof(S_SetPoint_Msg));
        Debug("PointType: %d", SetPoint_Msg.PointType);

        if (SetPoint_Msg.PointType < (configParam.AB_Mode ? 4 : 2))
        {
            if ((&globeState.Task_Sta.PositionA)[SetPoint_Msg.PointType].degE7_lat &&
                (&globeState.Task_Sta.PositionA)[SetPoint_Msg.PointType].degE7_long)
            {
                SetPointAskParameter = modification;
                Debug("SetPointAskParameter = modification");
            }
            else if ((&globeState.Task_Sta.PositionA)[SetPoint_Msg.PointType].degE7_lat == 0 &&
                     (&globeState.Task_Sta.PositionA)[SetPoint_Msg.PointType].degE7_long == 0)
            {
                SetPointAskParameter = add;
                Debug("SetPointAskParameter = add");
            }
            memcpy(&((S_Position *)&globeState.Task_Sta.PositionA)[SetPoint_Msg.PointType], &SetPoint_Msg.Position, sizeof(S_Position));
            if ((&globeState.Task_Sta.PositionA)[SetPoint_Msg.PointType].degE7_lat == 0 &&
                (&globeState.Task_Sta.PositionA)[SetPoint_Msg.PointType].degE7_long == 0)
            {
                SetPointAskParameter = delete;
                Debug("SetPointAskParameter = delete");
            }
            mavlink_msg_send_to_app(SetPointASK_Msg_ID, (const char *)&SetPointAskParameter, sizeof(E_SetPointAskParameter));

            remote_system_data_send_to_app();
            if (configParam.SavePointAB)
            {
                switch (SetPoint_Msg.PointType)
                {
                case 0:
                    configParam.PositionA = globeState.Task_Sta.PositionA;
                    break;
                case 1:
                    configParam.PositionB = globeState.Task_Sta.PositionB;
                    break;
                case 2:
                    configParam.PositionC = globeState.Task_Sta.PositionC;
                    break;
                case 3:
                    configParam.PositionD = globeState.Task_Sta.PositionD;
                    break;
                }
                NeedSave_User_Data();
                Debug("degE7_lat %d: %d", SetPoint_Msg.PointType, ((S_Position *)&globeState.Task_Sta.PositionA)[SetPoint_Msg.PointType].degE7_lat);
                Debug("degE7_long %d: %d", SetPoint_Msg.PointType, ((S_Position *)&globeState.Task_Sta.PositionA)[SetPoint_Msg.PointType].degE7_long);
                Debug("alt_mm %d: %d", SetPoint_Msg.PointType, ((S_Position *)&globeState.Task_Sta.PositionA)[SetPoint_Msg.PointType].alt_mm);
            }
            ((uint8_t *)&globeState.PositionARefresh)[SetPoint_Msg.PointType] = 1;

            if (show_ui == Point_AB_setup)
            {
                globeState.Cut_Show_UI = Point_AB_setup;
            }
            else if (*((uint32_t *)&globeState.Task_Sta.GetPosA_En))
            {
                extern S_Task_Set_Animation Task_Set_Animation;
                Task_Set_Animation.item_cut = (Task_Set_Animation.item_cut - 1) & (configParam.AB_Mode ? 3 : 1);
                if (Task_Set_Animation.animation_time == NULL)
                {
                    Task_Set_Animation.last_item_cut = Task_Set_Animation.item_cut;
                    Task_Set_Animation.item_cut = (Task_Set_Animation.item_cut + 1) & (configParam.AB_Mode ? 3 : 1);
                    globeState.PopUp_Inform.PopUp_EN = 1;
                    globeState.PopUp_Inform.img_id = SetPointA_IMG_ID + Task_Set_Animation.item_cut;
                    globeState.PopUp_Inform.str1_id = SetPointA_Lang_ID + Task_Set_Animation.item_cut;
                    globeState.PopUp_Inform.str2_id = Press_ENTER_Lang_ID;
                    globeState.PopUp_Inform.bar_en = 0;
                }
            }
        }
        else
        {
            SetPointAskParameter = ErrorParameter;
            mavlink_msg_send_to_app(SetPointASK_Msg_ID, (const char *)&SetPointAskParameter, sizeof(E_SetPointAskParameter));
            Debug("SetPointAskParameter = ErrorParameter");
        }
    }
    break;
    }
}

/*
50m  -> -54dB
100m -> -66dB   -68dB
150m -> -73dB   -71dB
200m -> -83dB   -76dB
250m -> -85dB   -80dB
300m -> -85dB   -85dB
350m -> -86dB   -87dB
400m -> -87dB   -88dB
450m -> -90dB   -89dB
500m -> -91dB   -90dB

        signal > -45    5
-45 >=  signal > -55    4
-55 >=  signal > -65    3
-65 >=  signal > -75    2
-75 >=  signal > -85    1
*/
void boat_dtu_return_mavlink_msg(mavlink_message_t *msg)
{
    switch (msg->msgid)
    {
    case MsgASK_Msg_ID:
    {
        S_MsgAsk_Msg MsgAsk_Msg;
        memcpy(&MsgAsk_Msg, msg->payload64, msg->len);
        Debug("MsgAsk_Msg.Msg_ID: %d", MsgAsk_Msg.Msg_ID);
        Debug("MsgAsk_Msg.Ask_Data: %d", MsgAsk_Msg.Ask_Data);

        if (MsgAsk_Msg.Msg_ID == SetWirelessMode_Msg_ID)
        {
            if (MsgAsk_Msg.Ask_Data == Success)
            {
                globeState.SetCommModeOK = 1;
                Debug("SetCommModeOK");
            }
        }
        else if (MsgAsk_Msg.Msg_ID == SetWirelessName_Msg_ID)
        {
            if (MsgAsk_Msg.Ask_Data == Success)
            {
                globeState.SetNameOK = 1;
                Debug("SetNameOK");
            }
        }
    }
    break;
    case BoatWiFiSignal_Msg_ID:
    {
        memcpy(&signal, msg->payload64, msg->len);
        Debug("signal: %d", signal);

        if (signal > -67)
            globeState.rf_rssi = 5;
        else if (signal > -79)
            globeState.rf_rssi = 4;
        else if (signal > -85)
            globeState.rf_rssi = 3;
        else if (signal > -88)
            globeState.rf_rssi = 2;
        else if (signal > -90)
            globeState.rf_rssi = 1;
        else
            globeState.rf_rssi = 1;
#ifdef SHOW_RSSI_DB
        globeState.rf_rssi = signal;
#endif
    }
    break;
    case AskLinuxCommand_Msg_ID:
    {
        if (msg->compid == REMOTE_DTU_COMP_ID)
        {
            char buffer[255];
            memcpy(buffer, msg->payload64, msg->len);
            buffer[msg->len] = '\0';
            char *p = NULL;
            p = strstr(buffer, "ssid=");
            if (p)
            {
                p = strstr(buffer, "_");
                if (p)
                {
                    uint32_t number = (uint32_t)strtoul(p + 1, NULL, 16); // 将字符串转换为十六进制数
                    Debug("Extracted number: %08x", number);
                    globeState.read_pair_id_flag = 1;
                    if (globeState.set_id != number)
                    {
                        globeState.set_id = number;
                        NeedSave_User_Data();
                    }
                }
            }
        }
        else if (msg->compid == BOAT_DTU_COMP_ID)
        {
        }
    }
    break;
    }
}

#if 1

#if 0
uint8_t Cut_WiFi_BT_Mode(uint8_t mode)
{
    uint8_t c;

    vTaskSuspend(ParseBoatMavTaskHandle);   // 挂起接收船数据的任务
    while (getFifoLen(&WiFi_Tx_Fifo)) // 清空发送给WiFi模块的数据
    {
        fifoGet(&WiFi_Tx_Fifo, &c, 1);
    }

    S_SetWirelessMode_Msg SetWirelessMode;
    SetWirelessMode.mode = mode;
    globeState.SetCommModeOK = 0;
    mavlink_set_sys_msg_send_to_dtu(SetWirelessMode_Msg_ID, (char *)&SetWirelessMode, sizeof(S_SetWirelessMode_Msg));

    for (uint8_t i = 0; i < 50; i++)
    {
        delay_ms(50);
        if (globeState.SetCommModeOK)
        {
            globeState.SetCommModeOK = 0;
            vTaskResume(ParseBoatMavTaskHandle);
            return 1;
        }
        else
        {
            mavlink_set_sys_msg_send_to_dtu(SetWirelessMode_Msg_ID, (char *)&SetWirelessMode, sizeof(S_SetWirelessMode_Msg));
        }
        Debug("Cut_WiFi_BT_Mode");
    }
    vTaskResume(ParseBoatMavTaskHandle);
    return 0;
}
#endif

void parse_app_mavlink_msg_task(void *param)
{
    uint16_t i;
    uint8_t c;
    static uint16_t recSeq = 0;
    short lastSeq = -1;
    uint16_t rx_len;
    mavlink_message_t msg;
    mavlink_status_t status;
    WiFiRecBinary = xSemaphoreCreateBinary();

    status.packet_rx_drop_count = 0;

    initFifo(&FileFifo, FileFifoBuf, FileFifoBufSize);

    for (;;)
    {
        // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        xSemaphoreTake(WiFiRecBinary, portMAX_DELAY);
        rx_len = getFifoLen(&WiFi_Rx_Fifo);
        // Debug("rx_len: %d", rx_len);
        for (i = 0; i < rx_len; ++i)
        {
            fifoGet(&WiFi_Rx_Fifo, &c, 1);
            // Debug("%02X", c);
            if (mavlink_parse_char(MAVLINK_COMM_1, c, &msg, &status) == MAVLINK_FRAMING_OK)
            {
                switch (msg.magic)
                {
                case MAVLINK_STX0:
                case MAVLINK_STX1:
                {
                    Debug("msg.msgid: %d", msg.msgid);
                    Debug("msg.sysid: %d", msg.sysid);
                    switch (msg.sysid)
                    {
                    case AppSysID:
                    {
                        globeState.WiFiConnect = 1;
                        parse_app_mavlink_messages(&msg);
                    }
                    break;
#ifdef ENDU_TEST_BUILD
                    case ENDU_APP_SYSID: /* ENDU test App: PARAM_SET/REQUEST_READ, COMMAND_LONG (USER_1/USER_2 RT throttle, DO_SET_MODE), HEARTBEAT -> boat, byte-for-byte */
                    {
                        Rf_Uart_Send((uint8_t *)(&msg.magic), MAVLINK_NUM_HEADER_BYTES + MAVLINK_NUM_CHECKSUM_BYTES + msg.len);
                        globeState.WiFiConnect = 1;
                    }
                    break;
#endif
                    default:
                    {
                        Rf_Uart_Send((uint8_t *)(&msg.magic), MAVLINK_NUM_HEADER_BYTES + MAVLINK_NUM_CHECKSUM_BYTES + msg.len); // 这里是解析成功之后再转发给船
                        recSeq++;
                        if (status.current_rx_seq < lastSeq)
                        {
                            globeState.wifi_rssi = recSeq * 100 / 256;
                            recSeq = 0;
                        }
                        lastSeq = status.current_rx_seq;
                        globeState.WiFiConnect = 1;
                    }
                    break;
                    }
                }
                break;
                default:
                    break;
                }
            }
        }
        // Debug("");
    }
}
#endif
