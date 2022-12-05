#include "contadores.h"

// ----- REAL TIME CLOCK -----

void RTC_init(void) {
  CCR = CCR | 3;   // 60E6 Hz
  PREINT = 1830;   // PREINT = int (PCLK / 32768) - 1 = 1830
  PREFRAC = 1792;  // EFRAC = PCLK - ([PREINT + 1] * 32768) = 1792

  CCR = CCR | 3;  //  Reset and enable  CCR = CCR & ~2; // Empieza a contar
}

void RTC_leer(uint32_t* minutos, uint32_t* segundos) {
  uint32_t time = clock_gettime(minutos, segundos);
  *minutos = (CTIME0 & 0x3F00) >> 8;
  *segundos = (CTIME0 & 0x1F);
}

// --- WATCHDOG TIMER -----

void WD_init(int sec)  {
  TC = sec * 1000;    // Set tiempo de watchdog
  WDMOD = WDMOD | 3;  // Reset y watchdog
}

void WD_feed() {
  disable_irq_fiq();
  FEED = 0xAA;
  WDFEED = 0x55;
  enable_irq_fiq();
}
