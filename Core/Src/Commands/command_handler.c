#include <stdio.h>
#include "main.h"
#include "command_handler.h"
#include "wiznet_communication.h"

void GetFwVersion() {
  const uint8_t Data[70];
	uint16_t size = sprintf((char *)Data, "----Odebrana wiadomosc: get_fw_version\n\r");
	HAL_UART_Transmit_IT(&huart2, Data, size);
}

#define MAX_DATA_SIZE 4

void MapData(Frame *FrameTarget, int dataSize) {
  FrameTarget->bytes.data0 = ReceivedOpCode.bytes.data0;
  FrameTarget->bytes.data1 = ReceivedOpCode.bytes.data1;
  FrameTarget->bytes.data2 = ReceivedOpCode.bytes.data2;
  FrameTarget->bytes.data3 = ReceivedOpCode.bytes.data3;
}

void TransmitData(Frame *FrameTarget, int dataSize) {
  MapData(FrameTarget, dataSize);
  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, (uint8_t *)FrameTarget, MAX_FRAME_BYTE_SIZE - (MAX_DATA_SIZE - dataSize), HAL_MAX_DELAY);
  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);
}

void SetGatewayIp() {
  const uint8_t Data[70];
	uint16_t size = sprintf((char *)Data, "----Odebrana wiadomosc: SetGatewayIp\n\r");
	HAL_UART_Transmit_IT(&huart2, Data, size);

  TransmitData(&SetGatewayIpFrame, 4);
}

void SetMask() {
  const uint8_t Data[70];
	uint16_t size = sprintf((char *)Data, "----Odebrana wiadomosc: SetMask\n\r");
	HAL_UART_Transmit_IT(&huart2, Data, size);

  TransmitData(&SetMaskFrame, 4);
}

void SetHardwareAddress1() {
  const uint8_t Data[90];
	uint16_t size = sprintf((char *)Data, "----Odebrana wiadomosc: SetHardwareAddress1\n\r");
	HAL_UART_Transmit_IT(&huart2, Data, size);

  TransmitData(&SetHardwareAddress1Frame, 4);
}

void SetHardwareAddress2() {
  const uint8_t Data[90];
	uint16_t size = sprintf((char *)Data, "----Odebrana wiadomosc: SetHardwareAddress2\n\r");
	HAL_UART_Transmit_IT(&huart2, Data, size);

  TransmitData(&SetHardwareAddress2Frame, 2);
}

void SetIp() {
  const uint8_t Data[70];
	uint16_t size = sprintf((char *)Data, "----Odebrana wiadomosc: SetIp\n\r");
	HAL_UART_Transmit_IT(&huart2, Data, size);

  TransmitData(&SetIpFrame, 4);
}

void UnknownOpCode();

void UnknownOpCodeMajor() {
  UnknownOpCode();
}

void UnknownOpCode() {
  const uint8_t Data[70];
	uint16_t size = sprintf((char *)Data, "----Unknown message\n\r");
	HAL_UART_Transmit_IT(&huart2, Data, size);
}

void handleInstr() {
  switch (ReceivedOpCode.bytes.major) {
    case GET_FW_INFO:
      switch (ReceivedOpCode.bytes.minor) {
        case GET_FW_VERSION:
          GetFwVersion();
          break;
        default:
          UnknownOpCode();
          break;
      }
      break; 
    case SET_ETH_DATA:
      switch (ReceivedOpCode.bytes.minor) {
        case SET_GATEWAY_IP:
          SetGatewayIp();
          break;
        case SET_MASK:
          SetMask();
          break;
        case SET_HARDWARE_ADDRESS_1:
          SetHardwareAddress1();
          break;
        case SET_HARDWARE_ADDRESS_2:
          SetHardwareAddress2();
          break;
        case SET_IP:
          SetIp();
          break;
        default:
          UnknownOpCode();
          break;
      }
      break;
    default:
      UnknownOpCodeMajor();
      break;
  }
}

// TBD
void setDataTmp(UART_HandleTypeDef *huart, Opcode *opcode, SPI_HandleTypeDef *hspi) {
    huart2 = *huart;
    ReceivedOpCode = *opcode;
    hspi2 = *hspi;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  // TBD
  setDataTmp(&huart2, &ReceivedOpCode, &hspi2);
  handleInstr();
	HAL_UART_Receive_DMA(&huart2, (uint8_t *)&ReceivedOpCode.dword, 8);
}