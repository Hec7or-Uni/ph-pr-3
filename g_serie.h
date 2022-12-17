#ifndef G_SERIE_H
#define G_SERIE_H

#include <LPC210X.H>
#include <inttypes.h>

#include "UART0.h"
#include "cola_asyn.h"
#include "cola_msg.h"

void g_serie_tratar_evento(evento_t evento);

void g_serie_tratar_mensaje(msg_t mensaje);

void g_serie_iniciar(void);

#endif
