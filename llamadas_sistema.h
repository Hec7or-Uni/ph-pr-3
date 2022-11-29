#ifndef LLAMADAS_SISTEMA_H
#define LLAMADAS_SISTEMA_H

/**
 * @brief Lee el tiempo transcurrido en segundos usando el real-time clock
 */
void clock_gettime();

/**
 * @brief Lee el tiempo transcurrido en microsegundos utilizando el timer 1.
 */
void clock_get_us();

/**
 * @brief Lee el bit IRQ del registro de estado para saber si las interrupciones 
 *        están habilitadas o deshabilitadas
 */
void read_IRQ_bit();

/**
 * @brief Lee el bit FIQ del registro de estado para saber si las interrupciones
 *        están habilitadas o deshabilitadas
 */
void read_FIQ_bit();

/**
 * @brief Activa sólo las interrupciones irq en el registro de estado.
 */
void enable_irq(); 

/**
 * @brief Desactiva sólo las interrupciones irq en el registro de estado.
 */
void disable_irq();

/**
 * @brief Activa interrupciones y fiq en el registro de estado.
 */
void enable_irq_fiq();

/**
 * @brief Desactiva interrupciones y fiq en el registro de estado.
 */
void disable_irq_fiq();

#endif // LLAMADAS_SISTEMA_H