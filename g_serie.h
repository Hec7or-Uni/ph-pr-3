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
 * @brief Encola el identificador de una cadena para ser mostrada.
 * @param cadena Identificador de la cadena a mostrar.
 */
void g_serie_encolar_cadena(uint8_t cadena);

/**
 * @brief Desencola el identificador de una cadena para mostrar la siguiente.
 */
void g_serie_desencolar_cadena(void);

/**
 * @brief Muestra la cadena correspondiente al identificador.
 * @param cadena Identificador de la cadena a mostrar.
 */
void g_serie_mostrar_cadena(uint8_t cadena);

/**
 * @brief Comprueba que el comando del buffer corresponde a #Cx! y en
 *        caso afirmativo lo ejecuta.
 * @param buffer Comando a ejecutar
 */
int g_serie_check_c(char buffer[BUFFER_SIZE]);

/**
 * @brief Comprueba que el comando del buffer corresponde a alguno de los
 *        disponibles y en caso afirmativo lo ejecuta.
 * @param buffer Comando a ejecutar
 */
void g_serie_ejecutar_cmd(char buffer[BUFFER_SIZE]);

/**
 * @brief Sobreescribe todos los caracteres del buffer por '\0'.
 * @param buffer Buffer de almacenamiento de comandos.
 */
void g_serie_clean_buffer(char buffer[BUFFER_SIZE]);

/**
 * @brief Función llamada cuando se recibe un caracter. Lo añade
 *        al buffer de comandos.
 * @param c Caracter recibido.
 */
void g_serie_caracter_recibido(char c);

/**
 * @brief Codifica el valor de celda como un caracter.
 * @param celda Valor de celda a codificar.
 * @return Valor codificado como caracter.
 */
char g_serie_codificar_jugador(CELDA celda);

/**
 * @brief Muestra una fila con los datos de sus celdas.
 * @param datosFila Datos de las celdas de una fila.
 */
void g_serie_mostrar_fila(uint32_t datosFila);

/**
 * @brief Escribe el numero x como caracteres de texto en el array,
 *        alineado a la derecha a partir de la posición i.
 * @param array Cadena donde se escribe el número.
 * @param i Posición final (posición de las unidades).
 * @param x Número a escribir.
 */
void g_serie_itoa(char array[], uint32_t i, uint32_t x);

/**
 * @brief Muestra la latencia media de transmisión de mensajes.
 * @param latencia Tiempo medio de transmisión de mensajes (us).
 */
void g_serie_mostrar_qos(uint32_t latencia);

/**
 * @brief Muestra los minutos transcurridos de la partida.
 * @param minutos Minutos transcurridos en la partida.
 */
void g_serie_mostrar_minutos(uint32_t minutos);

/**
 * @brief Muestra los segundos transcurridos de la partida.
 * @param segundos Segundos transcurridos en la partida.
 */
void g_serie_mostrar_segundos(uint32_t segundos);

/**
 * @brief Encola los identificadores de las cadenas que componen el tablero.
 */
void g_serie_encolar_tablero(void);

/**
 * @brief Encola los identificadores de las cadenas que componen el
 *        mensaje de inicio.
 */
void g_serie_encolar_inicio(void);

/**
 * @brief Encola los identificadores de las cadenas que componen el
 *        mensaje de comienzo.
 */
void g_serie_encolar_comenzar(void);

/**
 * @brief Inicia el funcionamiento del gestor.
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
