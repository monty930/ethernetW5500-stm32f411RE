#include "main.h"
#include "stm32f4xx_it.h"
#include "wiznet_communication.h"
#include "serial_communication.h"
#include "command_handler.h"
#include "consts.h"
#include "tmp.h"

Opcode SetInitGateway = { .dword = { 0x30, 0x31, 0x30, 0x30, 192, 168, 0, 255 } };
Opcode SetInitMask = { .dword = { 0x30, 0x31, 0x30, 0x31, 255, 255, 255, 0 } };
Opcode SetInitHWAddress1 = { .dword = { 0x30, 0x31, 0x32, 0x30, 0x00, 0x08, 0xdc, 0x78 } };
Opcode SetInitHWAddress2 = { .dword = { 0x30, 0x31, 0x33, 0x30, 0x91, 0x71, 0, 0 } };
Opcode SetInitIp = { .dword = { 0x30, 0x31, 0x30, 0x34, 192, 168, 0, 125 } };

void MapInit(Opcode *InitOpcode, Opcode *ReceivedOpCode) {
  for (int i = 0; i < 8; i++) {
    ReceivedOpCode->dword[i] = InitOpcode->dword[i];
  }
}

void send_init_data(Opcode *ReceivedOpCode) {
  MapInit(&SetInitGateway, ReceivedOpCode);
  SetGatewayIp();

  MapInit(&SetInitMask, ReceivedOpCode);
  SetMask();
  
  MapInit(&SetInitHWAddress1, ReceivedOpCode);
  SetHardwareAddress1();
  
  MapInit(&SetInitHWAddress2, ReceivedOpCode);
  SetHardwareAddress2();
  
  MapInit(&SetInitIp, ReceivedOpCode);
  SetIp();
}

uint8_t buffRead[22];
uint8_t buffWrite_Gateway[3] = { 0b00000000, 0b00000001, 0b00000000 };

void readFromGateway() {
  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);

  HAL_Delay(100);
  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, buffWrite_Gateway, 3, HAL_MAX_DELAY);
  HAL_SPI_Receive(&hspi2, buffRead, 8, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);

  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
}