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
 * @brief Función para el cálculo de las estadísticas de la partida
 * @param minutos_total Minutos totales acumulados en la partida
 * @param segundos_total Segundos totales acumulados en la partida
 * @param minutos_dif Minutos de diferencia entre el juego actual y el anterior
 * @param segundos_dif Segundos de diferencia entre el juego actual y el
 * anterior
 */
void g_estadisticas_partida(uint32_t *minutos_total, uint32_t *segundos_total,
                            int8_t *minutos_dif, int8_t *segundos_dif);

/**
 * @brief Función para el cálculo de las estadísticas de los mensajes
 * @param tiempo_total Tiempo total acumulado en la partida
 * @param num_mensajes Número de mensajes enviados en la partida
 * @param minutos_total Minutos totales acumulados en la partida
 * @param segundos_total Segundos totales acumulados en la partida
 */
void g_estadisticas_mensaje(uint32_t *tiempo_total, uint32_t *num_mensajes,
                            uint32_t *minutos_total, uint32_t *segundos_total);

/**
 * @brief Tratamiento de mensajes del módulo del gestor de estadísticas
 * @param mensaje Mensaje a tratar
 */
void g_estadisticas_tratar_mensaje(msg_t mensaje);

#endif
