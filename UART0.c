#include "UART0.h"

static char* caracter_a_enviar;

void uart0_IRC(void) __irq {
  static int veces = 0;

  int interrupcion = (U0IIR >> 0x1) & 0x03;

  if (interrupcion == 0x02 && (U0LSR & 0x01) != 0) {  // BRB
    cola_encolar_eventos(CARACTER_RECIBIDO, ++veces, U0RBR);
  } else if (interrupcion == 0x01 && (U0LSR & 0x20) != 0) {  // THRE
    cola_encolar_eventos(CARACTER_ENVIADO, ++veces, 0);
  }

  VICVectAddr = 0;
}

void uart0_iniciar() {
  PINSEL0 = PINSEL0 | 0x5;  // Habilita RxD0 y TxD0 (UART 0)

  U0LCR = 0x80; //DLAB = 1, para modificar la tasa de baudios

  // Para conseguir el estándar de 9600bd con PCLK =  15MHz
  U0DLM = 0;
  U0DLL = 97;
  // Cálculo:
  // Rs = PCLK / (16 * (256 * U0DLM) + U0DLL) = 15E6 / (16 * 97) = 9.664bd
 
  U0LCR = 0x03;  // 8 bits, sin paridad, 1 Stop bit, DLAB = 0

  // Habilita FIFO + Interrupciones al recibir 1 único caracter
  U0FCR = (U0FCR | 0x1) & ~0xC0; //U0FCR =  '11xx xxx1'
  U0IER = U0IER | 0x3;  // Habilita interrupciones RBR y THRE

  VICVectAddr3 = (unsigned long)uart0_IRC;  // set interrupt vector in 4

  // 0x20 bit 5 enables vectored IRQs.
  // 6 is the number of the interrupt assigned. Number 6 is the UART0
  VICVectCntl3 = VICVectCntl3 | 0x26;
  VICIntEnable = VICIntEnable | 0x40;  // Enable UART0 Interrupt (bit 6)
}

void uart0_enviar_array(char* array) {
  caracter_a_enviar = array;
  U0THR = *caracter_a_enviar;
  caracter_a_enviar++;
}

int uart0_continuar_envio(void) {
  if (*caracter_a_enviar != 0) {
    U0THR = *caracter_a_enviar;
    caracter_a_enviar++;
    return 1;
  }
  return 0;
}
