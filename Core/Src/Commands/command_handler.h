#ifndef __COMMAND_HANDLER__
#define __COMMAND_HANDLER__

#include <stdio.h>
#include "serial_communication.h"

#define GET_FW_INFO 0x3030
#define GET_FW_VERSION 0x3030

#define SET_ETH_DATA 0x3031
#define SET_GATEWAY_IP 0x3030
#define SET_MASK 0x3031
#define SET_HARDWARE_ADDRESS_1 0x3032
#define SET_HARDWARE_ADDRESS_2 0x3033
#define SET_IP 0x3034

// WORK IN PROGRESS
// to be changed
UART_HandleTypeDef huart2;
Opcode ReceivedOpCode;
SPI_HandleTypeDef hspi2;

// TBD
void setDataTmp(UART_HandleTypeDef *huart, Opcode *opcode, SPI_HandleTypeDef *hspi);

// TBD
void SetGatewayIp();
void SetMask();
void SetHardwareAddress1();
void SetHardwareAddress2();
void SetIp();

Opcode ReceivedOpCode;

void handleInstr();

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif //__COMMAND_HANDLER__