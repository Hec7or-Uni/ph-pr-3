#include "cola_asyn.h"

static uint8_t first = 0, last = 0, full = 0;
static uint32_t colaVECES[COLA_EVENTOS_SIZE];
static uint32_t colaDATA[COLA_EVENTOS_SIZE];
static uint8_t colaID[COLA_EVENTOS_SIZE];

void cola_encolar_eventos(uint8_t ID_evento, uint32_t veces, uint32_t auxData) {
  // Hay interrupciones que pueden encolar eventos
  bloquear_interrupciones();    /*LOCK*/
  if (full) {                   // overflow
    colaID[last] = OVERFLOW_E;  // last == first
  } else {
    colaVECES[last] = veces;
    colaDATA[last] = auxData;
    colaID[last] = ID_evento;
    last++;
    if (last == COLA_EVENTOS_SIZE) {
      last = 0;
    }
    if (last == first) {
      full = TRUE;
    }
  }
  liberar_interrupciones(); /*UNLOCK*/
}

evento_t cola_desencolar_eventos(void) {
  bloquear_interrupciones(); /*LOCK*/
  evento_t evento;

  evento.veces = colaVECES[first];
  evento.auxData = colaDATA[first];
  evento.ID_evento = colaID[first];
  first++;
  if (first == COLA_EVENTOS_SIZE) {
    first = 0;
  }
  full = FALSE;
  liberar_interrupciones(); /*UNLOCK*/
  return evento;
}

int cola_hay_eventos(void) {
  bloquear_interrupciones(); /*LOCK*/
  int res = first != last || full;
  liberar_interrupciones(); /*UNLOCK*/
  return res;
}
