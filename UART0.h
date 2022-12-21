/**
 * @file UART0.h
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Definicion de funciones para el manejo de la UART0
 */

#ifndef UART_ZERO_H
#define UART_ZERO_H

#include <LPC210X.H>
#include <inttypes.h>

#include "cola_asyn.h"
#include "utils.h"

enum { BUFFER_ENVIO_SIZE = 32 };

/**
 * @brief Configura el envío de caracteres a través del periférico UART0.
 */
void uart0_iniciar(void);

/**
 * @brief Inicia el envío de una cadena de caracteres tipo C, enviando el
 *        primer caracter.
 * @param array Cadena a enviar.
 */
void uart0_enviar_array(const char* array);

/**
 * @brief Envía el siguiente caracter de la cadena.
 * @return true si quedaban caracteres por enviar.
 */
int uart0_continuar_envio(void);

#endif
