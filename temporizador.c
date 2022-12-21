/**
 * @file temporizador.c
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Implementacion de funciones para el manejo del temporizador
 */

#include "temporizador.h"

void timer0_IRC(void) __irq {
  static int veces = 0;
  cola_encolar_eventos_raw(TEMPORIZADOR, ++veces, 0);
  T0IR = 1;         // Clear interrupt flag
  VICVectAddr = 0;  // Acknowledge Interrupt
}

void temporizador_iniciar() {
  T1PR = 14;           // Cuenta cada microsegundo: 15 clk = 1 us
  T1MR0 = UINT32_MAX;  // Para que cuente el máximo numero de microsegundos
                       // antes de reiniciarse

  T1MCR = 2;  // Reset on MR0

  T1TCR = T1TCR & ~0x1;
}

void temporizador_empezar() {
  T1PC = 0;
  T1TC = 0;
  T1TCR = T1TCR | 0x1;  // comienza a contar
}

uint32_t temporizador_leer() { return clock_get_us(); }

uint32_t temporizador_parar() {
  uint32_t time = T1TC;
  T1TCR = T1TCR & ~0x1;  // detiene el contador
  return time;
}

void temporizador_reloj(int periodo) {
  T0PR = 14999;  // Cuenta cada milisegundo: 15000 clk = 1 ms;
  T0MR0 = periodo - 1;

  T0MCR = 3;  // Interrumpe cada MR0 y resetea el contador

  VICIntSelect = VICIntSelect | 0x00000010;  // FIQ
  VICIntEnable = VICIntEnable | 0x00000010;  // Enable Timer0 Interrupt.

  T0TCR = T0TCR & ~0x1;
  T0PC = 0;
  T0TC = 0;
  T0TCR = T0TCR | 0x1;  // comienza a contar
}
