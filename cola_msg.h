#ifndef COLA_MSG_H
#define COLA_MSG_H
#include <inttypes.h>

#include "eventos.h"
#include "msg.h"
#include "temporizador.h"
#include "utils.h"

enum { COLA_MSG_SIZE = 16 };

typedef struct msg_t {
  uint32_t timestamp;
  uint32_t auxData;
  uint8_t ID_msg;
} msg_t;

/**
 * @brief  Función que encola un mensaje a la cola de mensajes
 * @param ID_msg Identificador único del mensaje
 * @param auxData Información extra sobre el mensaje
 */
void cola_encolar_msg(uint8_t ID_msg, uint32_t auxData);

/**
 * @brief  Función que desencola un mensaje de la cola de mensajes
 * @return Mensaje desencolado
 */
msg_t cola_desencolar_msg(void);

/**
 * @brief  Función que comprueba si hay mensajes
 * @return Número de mensajes
 */
int cola_hay_msg(void);

#endif
