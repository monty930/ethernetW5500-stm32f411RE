#ifndef __SPI_W5500_COMMUNICATION__
#define __SPI_W5500_COMMUNICATION__

struct Frame {
   unsigned int OFFSET : 16;
   unsigned int BSB : 5;
   unsigned int RWB : 1;
   unsigned int OM : 2;
};

#endif //__SPI_W5500_COMMUNICATION__