/**
 * @file UART0.c
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Implementacion de funciones para el manejo de la UART0
 */

#include "UART0.h"

static volatile uint8_t indice_envio = 0, longitud;
static char buffer_envio[BUFFER_ENVIO_SIZE];

void uart0_IRC(void) __irq {
  static int vecesRecibido = 0;
  static int vecesEnviado = 0;

  int iir = U0IIR;

  if (iir & 0x04) {  // BRB
    cola_encolar_eventos(CARACTER_RECIBIDO, ++vecesRecibido, U0RBR);
  }
	if (iir & 0x2) {  // THRE
    cola_encolar_eventos(CARACTER_ENVIADO, ++vecesEnviado, 0);
  }

  VICVectAddr = 0;
}

void uart0_iniciar() {
  PINSEL0 = PINSEL0 | 0x5;  // Habilita RxD0 y TxD0 (UART 0)

  U0LCR = 0x80;  // DLAB = 1, para modificar la tasa de baudios

  // Para conseguir el estándar de 9600bd con PCLK =  15MHz
  U0DLM = 0;
  U0DLL = 97;
  // Cálculo:
  // Rs = PCLK / (16 * (256 * U0DLM) + U0DLL) = 15E6 / (16 * 97) = 9.664bd

  U0LCR = 0x03;  // 8 bits, sin paridad, 1 Stop bit, DLAB = 0

  // Habilita FIFO + Interrupciones al recibir 1 único caracter
  U0FCR = (U0FCR | 0x1) & ~0xC0;  // U0FCR =  '11xx xxx1'
  U0IER = U0IER | 0x3;            // Habilita interrupciones RBR y THRE

  VICVectAddr3 = (unsigned long)uart0_IRC;

  // Habilita la interrupción 6 (UART0)
  VICVectCntl3 = VICVectCntl3 | 0x26;
  VICIntEnable = VICIntEnable | 0x40;  // Enable UART0 Interrupt (bit 6)
}

void uart0_enviar_array(const char* array) {
  if (*array == '\0') return;  // Un array vacío no se envía

  int fin = FALSE;
  for (longitud = 0; longitud < BUFFER_ENVIO_SIZE && !fin; longitud++) {
    buffer_envio[longitud] = array[longitud];

    // No almacenar el caracter final permite enviar uno extra
    fin = (array[longitud + 1] == '\0');
  }
  indice_envio = 0;
  U0THR = buffer_envio[indice_envio];
  indice_envio++;
}

int uart0_continuar_envio(void) {
  if (indice_envio < longitud) {
    U0THR = buffer_envio[indice_envio];
    indice_envio++;
    return TRUE;
  }
  return FALSE;
}
