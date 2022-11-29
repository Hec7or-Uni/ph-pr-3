#ifndef LLAMADAS_SISTEMA_H
#define LLAMADAS_SISTEMA_H

#include <LPC210x.H> /* LPC210x definitions */
#include <inttypes.h>

#include "temporizador.h"
#include "utils.h"

/**
 * @brief Lee el tiempo transcurrido en segundos usando el real-time clock
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
 * @brief Activa sólo las interrupciones irq en el registro de estado.
 */
void __swi(0xFF) enable_irq(void);

/**
 * @brief Desactiva sólo las interrupciones irq en el registro de estado.
 */
void __swi(0xFE) disable_irq(void);

/**
 * @brief Activa interrupciones y fiq en el registro de estado.
 */
void __swi(0xFD) enable_irq_fiq(void);

/**
 * @brief Desactiva interrupciones y fiq en el registro de estado.
 */
void __swi(0xFC) disable_irq_fiq(void);

#endif  // LLAMADAS_SISTEMA_H
