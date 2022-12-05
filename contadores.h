#ifndef CONTADORES_H
#define CONTADORES_H

#include <LPC210x.H> /* LPC210x definitions */
#include <inttypes.h>

// ----- REAL TIME CLOCK -----

/**
 * @brief Inicializa el RTC, reseteando la cuenta, ajustando el reloj y 
 *        activando el enable
 */
void RTC_init(void);

/**
 * @brief Devuelve los minutos y los segundos de juego (entre 0 y 59) 
 *        en dos uint8
 * @param minutos puntero a variable dónde guardar los minutos
 * @param segundos puntero a variable dónde guardar los segundos
 */
void RTC_leer(uint32_t* minutos, uint32_t* segundos);

// ----- WATCHDOG TIMER -----

/**
 * @brief Inicializa el watchdog timer para que resetee el procesador dentro de
 *        sec segundos si no se le "alimenta".
 * @param sec segundos
 */
void WD_init(int sec); 


/**
 * @brief Alimenta al watchdog timer
 */
void WD_feed();

#endif