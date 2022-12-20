/**
 * @file g_boton.h
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Definición de funciones para el manejo de los botones
 */

#ifndef G_BOTONES_H
#define G_BOTONES_H

#include "cola_asyn.h"
#include "cola_msg.h"
#include "eventos.h"
#include "msg.h"

/**
 * @brief Tratamiento de eventos del módulo del gestor de botones.
 * @param evento Evento a tratar.
 */
void g_boton_tratar_evento(evento_t evento);

/**
 * @brief Tratamiento de mensajes del módulo del gestor de botones.
 * @param mensaje Mensaje a tratar.
 */
void g_boton_tratar_mensaje(msg_t mensaje);

/**
 * @brief Inicialización del módulo del gestor de botones.
 */
void g_boton_iniciar(void);

#endif
