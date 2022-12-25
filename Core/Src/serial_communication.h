#ifndef __SERIAL_COMMUNICATION__
#define __SERIAL_COMMUNICATION__

typedef union {
    struct {
       uint8_t major;
       uint8_t minor;
       uint16_t data;
    } bytes;
    uint32_t dword;
} Opcode;

Opcode GetAdress = { .dword = 0x30300000 };

#endif //__SERIAL_COMMUNICATION__