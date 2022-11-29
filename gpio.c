#include "gpio.h"

void gpio_iniciar(void) {
  // Limpiamos los pines
  IODIR = 0xFFFFFFFF;
  IOCLR = 0xFFFFFFFF;
}

int gpio_leer(int bit_inicial, int num_bits) {
  uint32_t mask = ((1 << num_bits) - 1) << bit_inicial;
  return (IOPIN & mask) >> bit_inicial;
}

void gpio_escribir(int bit_inicial, int num_bits, int valor) {
  uint32_t maskON = (valor & ((1 << num_bits) - 1)) << bit_inicial;
  uint32_t maskOFF = (~valor & ((1 << num_bits) - 1)) << bit_inicial;
  IOSET = maskON;   // escribe los 1s
  IOCLR = maskOFF;  // escribe los 0s
}

void gpio_marcar_entrada(int bit_inicial, int num_bits) {
  uint32_t mask = ((1 << num_bits) - 1) << bit_inicial;
  IODIR = IODIR & ~mask;
}

void gpio_marcar_salida(int bit_inicial, int num_bits) {
  uint32_t mask = ((1 << num_bits) - 1) << bit_inicial;
  IODIR = IODIR | mask;
}
