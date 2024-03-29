/**
 * @file llamadas_sistema.h
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Definición de funciones para el manejo de las llamadas al
 * sistema
 */

#ifndef LLAMADAS_SISTEMA_H
#define LLAMADAS_SISTEMA_H

#include <LPC210x.H> /* LPC210x definitions */
#include <inttypes.h>

#include "temporizador.h"
#include "utils.h"

/**
 * @brief Devuelve el registro del real-time clock
 */
uint32_t __swi(0) clock_gettime(void);

/**
 * @brief Lee el tiempo transcurrido en microsegundos utilizando el timer 1.
 */
uint32_t __swi(1) clock_get_us(void);

/**
 * @brief Lee el bit IRQ del registro de estado para saber si las interrupciones
 *        están habilitadas o deshabilitadas
 */
uint8_t __swi(2) read_IRQ_bit(void);

/**
 * @brief Lee el bit FIQ del registro de estado para saber si las interrupciones
 *        están habilitadas o deshabilitadas
 */
uint8_t __swi(3) read_FIQ_bit(void);

/**
 * @brief Activa sólo las interrupciones fiq en el registro de estado.
 */
void __swi(0xFF) enable_fiq(void);

/**
 * @brief Desactiva sólo las interrupciones fiq en el registro de estado.
 */
void __swi(0xFE) disable_fiq(void);

/**
 * @brief Activa interrupciones y fiq en el registro de estado.
 */
void __swi(0xFD) enable_irq_fiq(void);

/**
 * @brief Desactiva interrupciones y fiq en el registro de estado.
 */
void __swi(0xFC) disable_irq_fiq(void);

/**
 * @brief Activa sólo las interrupciones irq en el registro de estado.
 */
void __swi(0xFB) enable_irq(void);

/**
 * @brief Desactiva sólo las interrupciones irq en el registro de estado.
 */
void __swi(0xFA) disable_irq(void);

#endif  // LLAMADAS_SISTEMA_H
