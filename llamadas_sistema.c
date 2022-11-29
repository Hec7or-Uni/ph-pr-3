#include "llamadas_sistema.h"

uint32_t __SWI_0(void) {
  uint32_t h = (CTIME0 & 0x1F0000) >> 16;
  uint32_t m = (CTIME0 & 0x3F00) >> 8;
  uint32_t s = (CTIME0 & 0x1F);
  return times3600(h) + times60(m) + s;
}

uint32_t __SWI_1(void) { return temporizador_leer(); }
