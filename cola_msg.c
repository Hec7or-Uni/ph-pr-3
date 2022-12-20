#include "cola_msg.h"

static uint8_t first = 0, last = 0, full = FALSE;
static uint32_t colaDATA[COLA_MSG_SIZE];
static uint32_t colaTIME[COLA_MSG_SIZE];
static uint8_t colaID[COLA_MSG_SIZE];

void cola_encolar_msg(uint8_t ID_msg, uint32_t auxData) {
  if (full) {  // overflow
    colaID[last] = OVERFLOW_M;
  } else {
    colaDATA[last] = auxData;
    colaTIME[last] = temporizador_leer();
    colaID[last] = ID_msg;
    last++;
    if (last == COLA_MSG_SIZE) {
      last = 0;
    }
    if (last == first) {
      full = TRUE;
    }
  }
}

msg_t cola_desencolar_msg(void) {
  msg_t msg;

  msg.timestamp = colaTIME[first];
  msg.auxData = colaDATA[first];
  msg.ID_msg = colaID[first];
  first++;
  if (first == COLA_MSG_SIZE) {
    first = 0;
  }
  full = FALSE;
  return msg;
}

int cola_hay_msg(void) { return first != last || full; }
