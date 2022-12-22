/**
 * @file semaforo_interrupciones.c
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Implementacion de funciones para el manejo de las
 * interrupciones
 */

#include "semaforo_interrupciones.h"

uint32_t bloquear_interrupciones() {
  uint32_t i_flag = read_IRQ_bit();
  uint32_t f_flag = read_FIQ_bit();

  disable_irq_fiq();
  return (i_flag << 1) | f_flag;
}

void liberar_interrupciones(uint32_t flags) {
  uint32_t i_flag = (flags & 0x2) >> 1;
  uint32_t f_flag = flags & 0x1;

  if (i_flag == 0 && f_flag == 0) {
    enable_irq_fiq();
  } else if (i_flag == 0 && f_flag == 1) {
    enable_irq();
  } else if (i_flag == 1 && f_flag == 0) {
    enable_fiq();
  }  // else {ya están desactivadas}
}
