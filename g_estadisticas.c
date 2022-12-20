#include "g_estadisticas.h"

void g_estadisticas_tiempo_jugado(int opcion) {
  uint32_t mins;
  uint32_t secs;
  RTC_leer(&mins, &secs);
  if (opcion == 0) {
    cola_encolar_msg(MINUTOS_JUGADOS, mins);
  } else {
    cola_encolar_msg(SEGUNDOS_JUGADOS, secs);
  }
}

void g_estadisticas_calidad_servicio(int tiempo) {
  cola_encolar_msg(CALIDAD_SERVICIO, tiempo);
}

void g_estadisticas_tratar_mensaje(msg_t mensaje) {
  static uint32_t tiempo_total = 0, num_mensajes = 0;
  num_mensajes++;
  tiempo_total = tiempo_total + (clock_get_us() - mensaje.timestamp);
  switch (mensaje.ID_msg) {
    case PEDIR_SEGUNDOS_JUGADOS:
      g_estadisticas_tiempo_jugado(1);
      break;
    case PEDIR_MINUTOS_JUGADOS:
      g_estadisticas_tiempo_jugado(0);
      break;
    case PEDIR_CALIDAD_SERVICIO:
      g_estadisticas_calidad_servicio(tiempo_total / num_mensajes);
      tiempo_total = 0;
      num_mensajes = 0;
      RTC_init();
      break;
  }
}
