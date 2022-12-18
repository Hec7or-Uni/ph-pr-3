#include "semaforo_interrupciones.h"

static volatile uint32_t i_flag, f_flag;

void bloquear_interrupciones() {
  i_flag = read_IRQ_bit();
  f_flag = read_FIQ_bit();
  disable_irq_fiq();
}

void liberar_interrupciones() {
  if (i_flag == 0 && f_flag == 0) {
    enable_irq_fiq();
  } else if (i_flag == 0 && f_flag == 1) {
    enable_irq_fiq();
    disable_fiq();
  } else if (i_flag == 1 && f_flag == 0) {
    enable_fiq();
  }  // else {ya están desactivadas}
}
