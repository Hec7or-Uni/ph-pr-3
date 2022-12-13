#ifndef G_SERIE_H
#define G_SERIE_H

#include <LPC210X.H>
#include <inttypes.h>

static char* caracter_a_enviar;

void uart0_IRC(void) __irq {
  static int veces = 0;

  int interrupcion = (U0IIR >> 0x1) & 0x03;

  if (interrupt == 0x02 && (U0LSR & 0x01) != 0) {  // BRB intrruption
    cola_encolar_eventos(CARACTER_RECIBIDO, ++veces, U0RBR);
  } else if (interrupt == 0x01 && (U0LSR & 0x20) != 0) {  // THRE Interruption
    cola_encolar_eventos(CARACTER_ENVIADO, ++veces, 0);
  }

  VICVectAddr = 0;
}

void uart_init()  // Initialize Serial Interface
{
  PINSEL0 = PINSEL0 | 0x5;  // Enable RxD0 and TxD0 (UART 0)
  // U0DLL = 97;               // 9600 Baud Rate @ 15MHz VPB Clock
  U0LCR = 0x03;  // 8 bits, sin paridad, 1 Stop bit, sin divisor latches
  U0FCR =
      (U0FCR | 0x1) &
      ~0x11000000;  // Enable FIFO + Interrupciones al recibir 1 único caracter
  U0IER = U0IER | 0x3;  // RBR and THRE interrupts enabled

  VICVectAddr3 = (unsigned long)uart0_IRC;  // set interrupt vector in 4

  // 0x20 bit 5 enables vectored IRQs.
  // 6 is the number of the interrupt assigned. Number 6 is the UART0
  VICVectCntl4 = VICVectCntl4 | 0x26;
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

#endif