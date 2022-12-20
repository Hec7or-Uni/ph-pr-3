/**
 * @file g_serie.h
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Definición de funciones para el manejo de la comunicación serie
 */

#ifndef G_SERIE_H
#define G_SERIE_H

#include <LPC210X.H>
#include <inttypes.h>

#include "UART0.h"
#include "cadenas.h"
#include "celda.h"
#include "cola_asyn.h"
#include "cola_msg.h"
#include "conecta4_2022.h"
#include "eventos.h"
#include "g_alarmas.h"
#include "msg.h"
#include "utils.h"

enum {
  COLA_CADENAS_SIZE = 32,

  BUFFER_SIZE = 3,
  NUM_COMANDOS = 2,

  G_SERIE_ACTIVO = 0,
  G_SERIE_INACTIVO = 1,
  G_SERIE_ESPERANDO = 2
};

/**
 * @brief
 * @param cadena
 */
void g_serie_encolar_cadena(uint8_t cadena);

/**
 * @brief
 */
void g_serie_desencolar_cadena(void);

/**
 * @brief
 * @param cadena
 */
void g_serie_mostrar_cadena(uint8_t cadena);

/**
 * @brief
 * @param buffer
 */
int g_serie_check_c(char buffer[BUFFER_SIZE]);

/**
 * @brief
 * @param buffer
 */
void g_serie_ejecutar_cmd(char buffer[BUFFER_SIZE]);

/**
 * @brief
 * @param buffer
 */
void g_serie_clean_buffer(char buffer[BUFFER_SIZE]);

/**
 * @brief
 * @param c
 */
void g_serie_caracter_recibido(char c);

/**
 * @brief
 * @param celda
 */
char g_serie_codificar_jugador(CELDA celda);

/**
 * @brief
 * @param datosFila
 */
void g_serie_mostrar_fila(uint32_t datosFila);

/**
 * @brief
 * @param array
 * @param i
 * @param x
 */
void g_serie_itoa(char array[], uint32_t i, uint32_t x);

/**
 * @brief
 * @param latencia
 */
void g_serie_mostrar_qos(uint32_t latencia);

/**
 * @brief
 * @param minutos
 */
void g_serie_mostrar_minutos(uint32_t minutos);

/**
 * @brief
 * @param segundos
 */
void g_serie_mostrar_segundos(uint32_t segundos);

/**
 * @brief
 */
void g_serie_encolar_tablero(void);

/**
 * @brief
 */
void g_serie_encolar_inicio(void);

/**
 * @brief
 */
void g_serie_encolar_comenzar(void);

/**
 * @brief
 * @param buffer
 */
void g_serie_iniciar(void);

/**
 * @brief Tratamiento de eventos del módulo del gestor serie
 * @param evento Evento a tratar
 */
void g_serie_tratar_evento(evento_t evento);

/**
 * @brief Tratamiento de mensajes del módulo del gestor serie
 * @param mensaje Mensaje a tratar
 */
void g_serie_tratar_mensaje(msg_t mensaje);

#endif
