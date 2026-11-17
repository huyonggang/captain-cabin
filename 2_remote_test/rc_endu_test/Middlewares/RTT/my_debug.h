#ifndef _MY_DEBUG_H
#define _MY_DEBUG_H

#include "stdio.h"
#include "SEGGER_RTT.h"

#define DEBUG

// 定义宏打印带有颜色的日志
#define DEBUG_NONE "\033[m"
#define DEBUG_RED "\033[0;32;31m"
#define DEBUG_LIGHT_RED "\033[1;31m"
#define DEBUG_GREEN "\033[0;32;32m"
#define DEBUG_LIGHT_GREEN "\033[1;32m"
#define DEBUG_BLUE "\033[0;32;34m"
#define DEBUG_LIGHT_BLUE "\033[1;34m"
#define DEBUG_DARY_GRAY "\033[1;30m"
#define DEBUG_CYAN "\033[0;36m"
#define DEBUG_LIGHT_CYAN "\033[1;36m"
#define DEBUG_PURPLE "\033[0;35m"
#define DEBUG_LIGHT_PURPLE "\033[1;35m"
#define DEBUG_BROWN "\033[0;33m"
#define DEBUG_YELLOW "\033[1;33m"
#define DEBUG_LIGHT_GRAY "\033[0;37m"
#define DEBUG_WHITE "\033[1;37m"

// 定义日志级别  大于或等于LOG_LEVEL_SHOW 的都打印
extern int DebugGrade; /* 日志打印等级 */
#define LOG_LEVEL_SHOW DebugGrade
#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_ERROR 3
#define LOG_LEVEL_DISABLE 4

#ifdef DEBUG
// #define RTT_DEBUG
#define USART_DEBUG USART1_DEBUG
#endif

#ifdef RTT_DEBUG
#define DebugSetTerminal(x) SEGGER_RTT_SetTerminal(x)
// 定义log_info,根据LOG_LEVEL_SHOW的值来决定是否打印日志
#define log_info(fmt, ...)                \
    if (LOG_LEVEL_SHOW >= LOG_LEVEL_INFO) \
    SEGGER_RTT_printf(0, RTT_CTRL_TEXT_BRIGHT_BLUE "[DEBUG]" fmt "\r\n", ##__VA_ARGS__)
#define log_debug(fmt, ...)                \
    if (LOG_LEVEL_SHOW >= LOG_LEVEL_DEBUG) \
    SEGGER_RTT_printf(0, RTT_CTRL_TEXT_BRIGHT_GREEN "[DEBUG]" fmt "\r\n", ##__VA_ARGS__)
#define log_warn(fmt, ...)                \
    if (LOG_LEVEL_SHOW >= LOG_LEVEL_WARN) \
    SEGGER_RTT_printf(0, RTT_CTRL_TEXT_BRIGHT_YELLOW "[WARN]%s %s %d " fmt "\r\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#define log_error(fmt, ...)                \
    if (LOG_LEVEL_SHOW >= LOG_LEVEL_ERROR) \
    SEGGER_RTT_printf(0, RTT_CTRL_TEXT_BRIGHT_RED "[ERROR] %s %s %s %d " fmt "\r\n", __FILE__, __func__, __TIME__, __LINE__, ##__VA_ARGS__)
#define Debug(fmt, ...)                    \
    if (LOG_LEVEL_SHOW >= LOG_LEVEL_DEBUG) \
    SEGGER_RTT_printf(0, RTT_CTRL_TEXT_BRIGHT_GREEN "[DEBUG]" fmt "\r\n", ##__VA_ARGS__)
#endif

#ifdef USART_DEBUG
#define DebugSetTerminal(x)
// 定义log_info,根据LOG_LEVEL_SHOW的值来决定是否打印日志
#define log_info(fmt, ...)                \
    if (LOG_LEVEL_SHOW <= LOG_LEVEL_INFO) \
    printf(DEBUG_BLUE "[INFO]" fmt "\r\n", ##__VA_ARGS__)
#define log_debug(fmt, ...)                \
    if (LOG_LEVEL_SHOW <= LOG_LEVEL_DEBUG) \
    printf(DEBUG_GREEN "[DEBUG]" fmt "\r\n", ##__VA_ARGS__)
#define log_warn(fmt, ...)                \
    if (LOG_LEVEL_SHOW <= LOG_LEVEL_WARN) \
    printf(DEBUG_YELLOW "[WARN]%s %s %d " fmt "\r\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#define log_error(fmt, ...)                \
    if (LOG_LEVEL_SHOW <= LOG_LEVEL_ERROR) \
    printf(DEBUG_RED "[ERROR] %s %s %s %d " fmt "\r\n", __FILE__, __func__, __TIME__, __LINE__, ##__VA_ARGS__)
#define Debug(fmt, ...)                    \
    if (LOG_LEVEL_SHOW <= LOG_LEVEL_DEBUG) \
    printf(DEBUG_GREEN "[DEBUG]" fmt "\r\n", ##__VA_ARGS__)
#endif

#ifndef USART_DEBUG
#ifndef RTT_DEBUG
#define DebugSetTerminal(x)
#define log_info(fmt, ...)
#define log_debug(fmt, ...)
#define log_warn(fmt, ...)
#define log_error(fmt, ...)
#endif
#endif

// Debug(DEBUG_RED"["__FILE__"][Line: %d][%s]: error happened!\n", __LINE__, __func__);
// DebugSetTerminal(0);
// sprintf(debug_str, "%1.2f", 6.89);
// Debug(DEBUG_YELLOW "%s\r\n", debug_str);
// Debug(DEBUG_COLOR_RESET "%s\r\n", debug_str);

// printf 彩色输出需要用到控制命令：\033[A1;A2;A3m
// 控制命令以\033[开头，以 m 结尾，而中间则是属性码，属性代码之间使用;分隔，如\033[1;34;40m。
// A1;A2;A3 支持右侧省略原则，即只有两个参数时，默认为A1;A2 ,只有一个参数时，默认为A1。
// A1：属性；
// A2：前景色；(字体颜色)
// A3：背景色；(填充颜色)

// 属性代码(A1)
// 0	重置所有属性
// 1	高亮/加粗
// 2	暗淡
// 4	下划线
// 5	闪烁
// 7	反转
// 8	隐藏

// 前景色(A2)
// 属性代码	功能
// 30	黑色
// 31	红色
// 32	绿色
// 33	黄色
// 34	蓝色
// 35	品红
// 36	青色

// 背景色(A3)
// 属性代码	功能
// 40	黑色
// 41	红色
// 42	绿色
// 43	黄色
// 44	蓝色
// 45	品红
// 46	青色

// printf("\033[0m\033[1;31m%s\033[0m", "Hello World!");

#endif
