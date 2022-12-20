/**
 * @file g_estadisticas.h
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Definición de funciones para el manejo de las estadísticas
 */

#ifndef G_ESTADISTICAS_H
#define G_ESTADISTICAS_H

#include "cola_msg.h"
#include "contadores.h"
#include "msg.h"
#include "temporizador.h"

enum {
  G_ESTADISTICAS_INACTIVO,
  G_ESTADISTICAS_ACTIVO,
  G_ESTADISTICAS_ESPERANDO
};

/**
 * @brief Tratamiento de mensajes del módulo del gestor de estadísticas
 * @param mensaje Mensaje a tratar
 */
void g_estadisticas_tratar_mensaje(msg_t mensaje);

#endif
