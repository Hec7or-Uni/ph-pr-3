/**
 * @file g_energia.h
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Definición de funciones para el manejo de la energía
 */

#ifndef GESTOR_ENERGIA_H
#define GESTOR_ENERGIA_H

#include <inttypes.h>

#include "cola_asyn.h"
#include "cola_msg.h"
#include "eventos.h"
#include "g_alarmas.h"
#include "msg.h"
#include "power.h"
#include "utils.h"

enum estados { NORMAL, IDLE, POWERDOWN };

/**
 *  @brief Inicializa el gestor de energía.
 */
void g_energia_iniciar(void);

/**
 * @brief Pone al procesador a dormir.
 * En el estado power-down los periféricos también entran en bajo consumo y
 * dejan de funcionar pero se sigue manteniendo el estado.
 */
void g_energia_power_down(void);

/**
 * @brief Pone al procesador en modo normal.
 */
void g_energia_reset(void);

/**
 * @brief Pone el procesador en modo bajo consumo.
 * En g_energia_idle el procesador se para, pero los periféricos del chip, como
 * el temporizador, siguen activos y lo pueden despertar al realizar una
 * interrupción.
 */
void g_energia_idle(void);

/**
 * @brief Tratamiento de mensajes del módulo del gestor de energía
 * @param mensaje Mensaje a tratar
 */
void g_energia_tratar_mensaje(msg_t mensaje);

#endif
