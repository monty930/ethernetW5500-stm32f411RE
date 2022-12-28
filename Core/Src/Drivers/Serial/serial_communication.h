#ifndef __SERIAL_COMMUNICATION__
#define __SERIAL_COMMUNICATION__

typedef union {
   struct {
      uint16_t major;
      uint16_t minor;
      uint8_t data0;
      uint8_t data1;
      uint8_t data2;
      uint8_t data3;
   } bytes;
   uint8_t dword[8];
} Opcode;

#endif //__SERIAL_COMMUNICATION__