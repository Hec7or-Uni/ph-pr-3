#ifndef GESTOR_IO_H
#define GESTOR_IO_H

#include <LPC210x.H> /* LPC210x definitions */
#include <inttypes.h>

#include "cola_asyn.h"
#include "cola_msg.h"
#include "g_alarmas.h"
#include "gpio.h"
#include "utils.h"

enum { G_IO_FIN_BLOQUEADO, G_IO_FIN_LIBRE };

/**
 * @brief Inicializa el gestor de IO.
 */
void g_io_iniciar(void);

/**
 * @brief Indicar que la jugada ha sido realizada.
 */
void g_io_encender_realizada(void);

/**
 * @brief Apagar indicador de jugada realizada.
 */
void g_io_apagar_realizada(void);

/**
 * @brief Indicar jugada no válida.
 */
void g_io_mostrar_invalido(void);

/**
 * @brief Apagar indicador de jugada no válida.
 */
void g_io_apagar_invalido(void);

void g_io_mostrar_fin(void);

void g_io_apagar_fin(void);

/**
 * @brief Indicar overflow
 */
void g_io_overflow(void);

/**
 * @brief Alternar led indicador de modo idle
 */
void g_io_latido(void);

/**
 * @brief Apagar indicador de modo idle
 */
void g_io_apagar_latido(void);

/**
 * @brief Tratamiento de eventos del módulo del gestor de entrada y salida
 * @param evento Evento a tratar
 */
void g_io_tratar_evento(evento_t evento);

/**
 * @brief Tratamiento de mensajes del módulo del gestor de entrada y salida
 * @param mensaje Mensaje a tratar
 */
void g_io_tratar_mensaje(msg_t mensaje);

#endif
