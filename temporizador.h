#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

#include <LPC210x.H> /* LPC210x definitions */
#include <inttypes.h>

#include "cola_asyn.h"
#include "eventos.h"
#include "msg.h"

/**
 * @brief Programa un contador para que pueda ser utilizado.
 */
void temporizador_iniciar(void);

/**
 * @brief Inicia la cuenta de un contador de forma indefinida.
 */
void temporizador_empezar(void);

/**
 * @brief Lee el tiempo que lleva contando el contador desde la última vez que
 * se ejecutó temporizador_empezar y lo devuelve en microsegundos (us).
 * @return Tiempo en microsegundos (us).
 */
uint32_t temporizador_leer(void);

/**
 * @brief Detiene el contador y devuelve el tiempo transcurrido desde
 * temporizador_empezar
 * @return Tiempo en microsegundos (us).
 */
uint32_t temporizador_parar(void);

/**
 * @brief Programa el reloj para que encole un evento periódicamente. El periodo
 * se indica en milisegundos (ms).
 * @param periodo Periodo en milisegundos (ms).
 */
void temporizador_reloj(int periodo);

#endif
