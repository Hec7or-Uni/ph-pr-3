#include "contadores.h"

// ----- REAL TIME CLOCK -----

void RTC_init(void) {
  CCR = CCR | 3;   // PCLK = 60E6 Hz / 4 = 15E6Hz
  PREINT = 1830;   // PREINT = int (PCLK / 32768) - 1 = 456
  PREFRAC = 1792;  // EFRAC = PCLK - ([PREINT + 1] * 32768) = 25024

  CCR = CCR | 3;  //  Reset and enable
  CCR = CCR & ~2; // Empieza a contar
}

void RTC_leer(uint32_t* minutos, uint32_t* segundos) {
  uint32_t time = clock_gettime();
  *minutos = (time & 0x3F00) >> 8;
  *segundos = (time & 0x3F);
}

// --- WATCHDOG TIMER -----

void WD_init(int sec)  {
  WDTC = sec * 3750000;  // Set tiempo de watchdog
  // x * 15E-6 s * 4 = sec <-> x = sec / (15E-6 * 4) = sec * 3750000 s^(-1)
  WDMOD = WDMOD | 3;  // Reset y watchdog)
}

void WD_feed() {
  disable_irq_fiq();
  WDFEED = 0xAA;
  WDFEED = 0x55;
  enable_irq_fiq();
}
