#ifndef __SEMAFORO_INTERRUPCIONES__
#define __SEMAFORO_INTERRUPCIONES__

#include <LPC210x.H>
#include <inttypes.h>

#include "llamadas_sistema.h"

static uint32_t recover;

/**
 * @brief Bloquea las interrupciones
 */
void bloquear_interrupciones(void);

/**
 * @brief Libera las interrupciones bloqueadas
 */
void liberar_interrupciones(void);

#endif
