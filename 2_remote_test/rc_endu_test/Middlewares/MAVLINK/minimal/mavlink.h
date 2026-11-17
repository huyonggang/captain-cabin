/** @file
 *  @brief MAVLink comm protocol built from Demo.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_H
#define MAVLINK_H

#define MAVLINK_PRIMARY_XML_IDX 0

#ifndef MAVLINK_STX

#define MAVLINK_STX0 0xFE       // 这是非加密的协议包头
#define MAVLINK_STX1 0xC3       // 这是加密的协议包头
#define AppSysID 0xA5           // 遥控器与app之间的通讯系统ID
#define AppCompID 0xA5          // 遥控器与app之间的通讯组件ID
#define DTU_SONAR_SYS_ID 0xAF   // 声纳转接板、数传与app通讯系统ID
#define BOAT_DTU_COMP_ID 0xA5   // 与船的图传通讯
#define REMOTE_DTU_COMP_ID 0xAF // 与遥控器的图传通讯
#define SONAR_COMP_ID 0xAE      // 与声纳转接板通讯

#define MAVLINK_STX3 0x55 // 这是设置透传参数的私有协议包头

#endif

#ifndef MAVLINK_ENDIAN
#define MAVLINK_ENDIAN MAVLINK_LITTLE_ENDIAN
#endif

#ifndef MAVLINK_ALIGNED_FIELDS
#define MAVLINK_ALIGNED_FIELDS 1
#endif

#ifndef MAVLINK_CRC_EXTRA
#define MAVLINK_CRC_EXTRA 1
#endif

#ifndef MAVLINK_COMMAND_24BIT
#define MAVLINK_COMMAND_24BIT 0
#endif

#include "version.h"
#include "Demo.h"

#endif // MAVLINK_H
