/**
 * @file cola_asyn.c
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Implementación de funciones para el manejo de la cola de
 * eventos
 */

#include "cola_asyn.h"

// Importante que las interrupciones lean exactamente el mismo que
// la ejecución en modo usuario
static volatile uint8_t first = 0, last = 0, full = FALSE;

static uint32_t colaVECES[COLA_EVENTOS_SIZE];
static uint32_t colaDATA[COLA_EVENTOS_SIZE];
static uint8_t colaID[COLA_EVENTOS_SIZE];

void cola_encolar_eventos(uint8_t ID_evento, uint32_t veces, uint32_t auxData) {
  uint32_t flags = bloquear_interrupciones(); /*LOCK*/
  cola_encolar_eventos_raw(ID_evento, veces, auxData);
  liberar_interrupciones(flags); /*UNLOCK*/
}

void cola_encolar_eventos_raw(uint8_t ID_evento, uint32_t veces,
                              uint32_t auxData) {
  if (full) {  // overflow
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
}

evento_t cola_desencolar_eventos(void) {
  evento_t evento;

  // No hace falta bloquear, porque el único evento que puede ser escrito en
  // esta posición es OVERFLOW, y solamente se sobreescribe el ID. El resto de
  // valores no pueden ser sobreescritos.
  evento.veces = colaVECES[first];
  evento.auxData = colaDATA[first];

  // La escritura ambas variables debe ser atómica, para evitar considerar que
  // la cola no está llena en caso de que una interrupción complete la cola.
  uint32_t flags = bloquear_interrupciones(); /*LOCK*/
  evento.ID_evento = colaID[first];
  first++;
  if (first == COLA_EVENTOS_SIZE) {
    first = 0;
  }
  full = FALSE;
  liberar_interrupciones(flags); /*UNLOCK*/

  return evento;
}

int cola_hay_eventos(void) {
  // Las interrupciones sólo pueden alterar el último,
  // por lo que no importa leer el primero y el último a la vez.
  return first != last || full;
}
