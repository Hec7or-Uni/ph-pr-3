#ifndef COLA_ASYNC_H
#define COLA_ASYNC_H
#include <inttypes.h>

#include "eventos.h"
#include "msg.h"
#include "semaforo_interrupciones.h"
#include "utils.h"

enum { COLA_EVENTOS_SIZE = 32 };

typedef struct evento_t {
  uint32_t veces;
  uint32_t auxData;
  uint8_t ID_evento;
} evento_t;

/**
 * @brief  Función que encola un evento a la cola de eventos
 * @param ID_msg Identificador único del evento
 * @param veces Número de veces que ha aparecido un evento
 * @param auxData Información extra sobre el evento
 */
void cola_encolar_eventos(uint8_t ID_evento, uint32_t veces, uint32_t auxData);

/**
 * @brief  Función que desencola un evento de la cola de eventos
 * @return Evento desencolado
 */
evento_t cola_desencolar_eventos(void);

/**
 * @brief  Función que comprueba si hay eventos
 * @return Número de eventos
 */
int cola_hay_eventos(void);

#endif
