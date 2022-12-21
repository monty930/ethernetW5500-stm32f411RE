#ifndef __SERIAL_COMMUNICATION__
#define __SERIAL_COMMUNICATION__

struct Opcode {
   uint8_t B0;
   uint8_t B1;
   uint8_t B2;
   uint8_t B3;
};

const struct Opcode GetAdress = { B0 : 0x30, B1 : 0x30, B2 : 0x30, B3 : 0x30 };

#endif //__SERIAL_COMMUNICATION__