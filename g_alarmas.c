#include "g_alarmas.h"

// Vector de alarmas
static alarma_t alarmas[NUM_ALARMAS];
static uint32_t tiempo[NUM_ALARMAS];

alarma_t g_alarma_borrar(uint8_t ID_msg) {
  return ID_msg << 24;  // El resto de campos a 0 para borrarla
}

alarma_t g_alarma_crear(uint8_t ID_msg, int esPeriodica, uint32_t retardo) {
  alarma_t alarma =
      ID_msg << 24;   // Los 8 bits más significativos son el msg asociado
  if (esPeriodica) {  // Activar bit 23
    alarma = alarma | 0x800000;
  }
  alarma = alarma | (retardo & 0x7FFFFF);
  return alarma;
}

alarma_t g_alarma_retardo(alarma_t alarma) { return alarma & 0x7FFFFF; }

int g_alarma_es_periodica(alarma_t alarma) { return (alarma & 0x800000) != 0; }

uint8_t g_alarma_id_msg(alarma_t alarma) { return alarma >> 24; }

void g_alarma_iniciar() {
  temporizador_reloj(1);
  temporizador_iniciar();
  temporizador_empezar();
}

void g_alarma_programar(alarma_t alarma) {
  // Buscar si hay que reprogramarla
  for (int i = 0; i < NUM_ALARMAS; i++) {
    if (alarmas[i] == 0)
      continue;
    else if ((g_alarma_id_msg(alarmas[i]) == g_alarma_id_msg(alarma))) {
      if (g_alarma_retardo(alarma) == 0) {
        alarmas[i] = 0;
        return;
      } else {
        alarmas[i] = alarma;
        tiempo[i] = g_alarma_retardo(alarma);
        return;
      }
    }
  }

  if (g_alarma_retardo(alarma) == 0) return;

  // Buscar el primer hueco libre
  for (int i = 0; i < NUM_ALARMAS; i++) {
    if (alarmas[i] == 0) {
      alarmas[i] = alarma;
      tiempo[i] = g_alarma_retardo(alarma);
      return;
    }
  }
}

void g_alarma_comprobar_alarmas() {
  for (int i = 0; i < NUM_ALARMAS; i++) {
    if (alarmas[i] == 0 || --tiempo[i] > 0) continue;
    cola_encolar_msg(g_alarma_id_msg(alarmas[i]), 0);
    if (!g_alarma_es_periodica(alarmas[i])) {
      alarmas[i] = 0;  // cancelar
    } else {
      tiempo[i] = g_alarma_retardo(alarmas[i]);  // reset
    }
  }
}

void g_alarma_tratar_evento(evento_t evento) {
  switch (evento.ID_evento) {
    case TEMPORIZADOR:
      g_alarma_comprobar_alarmas();
      break;
  }
}

void g_alarma_tratar_mensaje(msg_t mensaje) {
  switch (mensaje.ID_msg) {
    case RESET:
      temporizador_empezar();
      break;
    case SET_ALARM:
      g_alarma_programar(mensaje.auxData);
      break;
    case FIN:
      temporizador_parar();
      break;
  }
}
