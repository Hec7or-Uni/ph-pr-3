/**
 * @file contadores.c
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Implementación de funciones para el manejo de los contadores
 */

#include "contadores.h"

// ----- REAL TIME CLOCK -----

void RTC_init(void) {
  CCR = CCR & ~1;  
                    // PCLK = 60E6 Hz / 4 = 15E6Hz
  PREINT = 456;     // PREINT = int (PCLK / 32768) - 1 = 456
  PREFRAC = 25024;  // PREFRAC = PCLK - ([PREINT + 1] * 32768) = 25024

  CCR = CCR | 3;  // Reset y enable
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
  uint32_t flags = bloquear_interrupciones(); /*LOCK*/
  WDFEED = 0xAA;
  WDFEED = 0x55;
  liberar_interrupciones(flags); /*UNLOCK*/
}
