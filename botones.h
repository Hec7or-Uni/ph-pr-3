/**
 * @file botones.h
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Definición de funciones para el manejo de los botones
 */

#ifndef BOTONES_H
#define BOTONES_H

#include <LPC210x.H> /* LPC210x definitions */
#include <inttypes.h>

#include "cola_asyn.h"
#include "eventos.h"
#include "g_alarmas.h"
#include "msg.h"
#include "utils.h"

/**
 * @brief Prepara la configuración de las interrupciones para los
 *  botones 1 y 2.
 */
void botones_iniciar(void);

/**
 * @brief Resetea la configuracion de la interrupción para el boton 1.
 */
void boton1_reset(void);

/**
 * @brief Resetea la configuracion de la interrupción para el boton 2.
 */
void boton2_reset(void);

/**
 * @brief Indica si el boton 1 está pulsado.
 * @return true(1) si pulsado; false(0) en caso contrario.
 */
int boton1_pulsado(void);

/**
 * @brief Indica si el boton 2 está pulsado.
 * @return true(1) si pulsado; false(0) en caso contrario.
 */
int boton2_pulsado(void);

#endif
