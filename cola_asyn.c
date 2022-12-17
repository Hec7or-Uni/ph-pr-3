#include "cola_asyn.h"

// Importante que las interrupciones lean exactamente el mismo que
// la ejecución en modo usuario
static volatile uint8_t first = 0, last = 0, full = 0;

static uint32_t colaVECES[COLA_EVENTOS_SIZE];
static uint32_t colaDATA[COLA_EVENTOS_SIZE];
static uint8_t colaID[COLA_EVENTOS_SIZE];

void cola_encolar_eventos(uint8_t ID_evento, uint32_t veces, uint32_t auxData) {
  // Si mientras se encola un
  bloquear_interrupciones(); /*LOCK*/
  if (full) {                // overflow
    // last == first -> escribe al comienzo de la cola
    colaID[last] = OVERFLOW_E;
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
  evento_t evento;

  // No hace falta bloquear, porque el único evento que puede ser escrito en
  // esta posición es OVERFLOW, y solamente se sobreescribe el ID. El resto de
  // valores no pueden ser sobreescritos.
  evento.veces = colaVECES[first];
  evento.auxData = colaDATA[first];
  evento.ID_evento = colaID[first];

  // La escritura ambas variables debe ser atómica, para evitar considerar que
  // la cola no está llena en caso de que una interrupción complete la cola.
  bloquear_interrupciones(); /*LOCK*/
  first++;
  if (first == COLA_EVENTOS_SIZE) {
    first = 0;
  }
  full = FALSE;
  liberar_interrupciones(); /*UNLOCK*/

  return evento;
}

int cola_hay_eventos(void) {
  // Las interrupciones sólo pueden alterar el último,
  // por lo que no importa leer el primero y el último a la vez.
  return first != last || full;
}
