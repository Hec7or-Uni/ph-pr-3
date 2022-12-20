#include "g_estadisticas.h"

void g_estadisticas_tratar_mensaje(msg_t mensaje) {
  static uint32_t tiempo_total = 0, num_mensajes = 0;
  static uint32_t minutos_total = 0, segundos_total = 0;
  static int8_t minutos_dif = 0, segundos_dif = 0;
  static uint8_t estado = G_ESTADISTICAS_INACTIVO;
  int8_t minutos_aux, segundos_aux;

  int tiempo_msg = temporizador_leer() - mensaje.timestamp;
  if (tiempo_msg > 0) {
    num_mensajes++;
    tiempo_total = tiempo_total + tiempo_msg;
  }

  switch (mensaje.ID_msg) {
    case FIN:
      estado = G_ESTADISTICAS_INACTIVO;
      minutos_aux = minutos_total;
      segundos_aux = segundos_total;
      RTC_leer(&minutos_total, &segundos_total);
      minutos_dif = minutos_total - minutos_aux;
      segundos_dif = segundos_total - segundos_aux;
      if (segundos_dif < 0) {
        segundos_dif = segundos_total + (60 - segundos_aux);
        minutos_dif--;
      }
      break;
    case CANCELAR:  // los botones y NEW comienzan el juego
    case RESET:
      if (estado == G_ESTADISTICAS_INACTIVO) {
        RTC_leer(&minutos_total, &segundos_total);
        tiempo_total = 0;
        num_mensajes = 0;
        RTC_init();
        estado = G_ESTADISTICAS_ACTIVO;
      }
      break;
    case PEDIR_SEGUNDOS_JUGADOS:
      cola_encolar_msg(SEGUNDOS_JUGADOS, segundos_dif);
      break;
    case PEDIR_MINUTOS_JUGADOS:
      cola_encolar_msg(MINUTOS_JUGADOS, minutos_dif);
      break;
    case PEDIR_CALIDAD_SERVICIO:
      cola_encolar_msg(CALIDAD_SERVICIO, tiempo_total / num_mensajes);
      break;
  }
}
