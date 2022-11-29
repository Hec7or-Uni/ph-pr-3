#include "botones.h"

void g_boton_tratar_evento(evento_t evento) {
  switch (evento.ID_evento) {
    case PULSACION:
      if (evento.auxData == 1) {
        cola_encolar_msg(SET_ALARM,
                         g_alarma_crear(BAJAR_PULSACION_1, TRUE, 10));
        cola_encolar_msg(EJECUTAR, JUGAR);
      } else if (evento.auxData == 2) {
        cola_encolar_msg(SET_ALARM,
                         g_alarma_crear(BAJAR_PULSACION_2, TRUE, 10));
        cola_encolar_msg(EJECUTAR, RESET);
      }
      break;
  }
}

void g_boton_tratar_mensaje(msg_t mensaje) {
  switch (mensaje.ID_msg) {
    case BAJAR_PULSACION_1:
      if (!boton1_pulsado()) {
        boton1_reset();
        cola_encolar_msg(SET_ALARM, g_alarma_borrar(BAJAR_PULSACION_1));
      }
      break;
    case BAJAR_PULSACION_2:
      if (!boton2_pulsado()) {
        boton2_reset();
        cola_encolar_msg(SET_ALARM, g_alarma_borrar(BAJAR_PULSACION_2));
      }
      break;
  }
}

void g_boton_iniciar(void) { botones_iniciar(); }
