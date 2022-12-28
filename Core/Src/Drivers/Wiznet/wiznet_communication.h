#ifndef __SPI_W5500_COMMUNICATION__
#define __SPI_W5500_COMMUNICATION__

#include <stdio.h>

#define MAX_FRAME_BYTE_SIZE 7

typedef union {
   struct {
      uint8_t wiznet[3];
      uint8_t data0;
      uint8_t data1;
      uint8_t data2;
      uint8_t data3;
   } bytes;
   uint8_t dword[MAX_FRAME_BYTE_SIZE];
} Frame;

Frame SetGatewayIpFrame;
Frame SetMaskFrame;
Frame SetHardwareAddress1Frame;
Frame SetHardwareAddress2Frame;
Frame SetIpFrame;

#endif //__SPI_W5500_COMMUNICATION__