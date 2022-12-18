#ifndef G_SERIE_H
#define G_SERIE_H

#include <LPC210X.H>
#include <inttypes.h>

#include "UART0.h"
#include "celda.h"
#include "cola_asyn.h"
#include "cola_msg.h"
#include "conecta4_2022.h"
#include "eventos.h"
#include "msg.h"
#include "utils.h"

#define BUFFER_SIZE 3
#define NUM_COMANDOS 3

void g_serie_encolar_cadena(uint8_t cadena);

void g_serie_desencolar_cadena(void);

int g_serie_ejecutar_cmd(char buffer[BUFFER_SIZE]);

void clean_buffer(char buffer[BUFFER_SIZE]);

void g_serie_caracter_recibido(char c);

char g_serie_codificar_jugador(CELDA celda);

void g_serie_mostrar_fila(uint32_t datosFila);

void g_serie_tratar_evento(evento_t evento);

void g_serie_tratar_mensaje(msg_t mensaje);

void g_serie_mostrar_cadena(uint8_t cadena);

void g_serie_iniciar(void);

#endif
