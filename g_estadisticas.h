#ifndef G_ESTADISTICAS_H
#define G_ESTADISTICAS_H

#include "cola_msg.h"
#include "msg.h"
#include "contadores.h"
#include "llamadas_sistema.h"

/**
 * @brief Escribe por pantalla el tiempo total jugado.
 * @param opcion 0 para mostrar los minutos; 1 para mostrar los segundos
 */
void g_estadisticas_tiempo_jugado(int opcion);

/**
 * @brief Escribe por pantalla la calidad de servicio en la gestión de mensajes.
 *        Muestra el tiempo medio que le cuesta al planificador procesar los
 *        mensajes desde que son enviados.
 * @param tiempo Tiempo medio desde que es lanzado un mensaje hasta que finaliza
 *        su gestión
 */
void g_estadisticas_calidad_servicio(int tiempo);

/**
 * @brief Tratamiento de mensajes del módulo del gestor de estadísticas
 * @param mensaje Mensaje a tratar
 */
void g_estadisticas_tratar_mensaje(msg_t mensaje);

#endif
