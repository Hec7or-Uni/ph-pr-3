#ifndef UART_ZERO_H
#define UART_ZERO_H

#include <LPC210X.H>
#include <inttypes.h>

#include "cola_asyn.h"
#include "utils.h"

void uart0_iniciar(void);

void uart0_enviar_array(char* array);

int uart0_continuar_envio(void);

#endif
