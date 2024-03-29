/**
 * @file g_energia.c
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Implementación de funciones para el manejo de la energía
 */

#include "g_energia.h"

static int estado = NORMAL;

void setup_PLL(void);

void g_energia_iniciar() {
  power_iniciar();
  cola_encolar_msg(SET_ALARM, g_alarma_crear(POWER_DOWN, FALSE, 10000));
}

void g_energia_power_down() {
  estado = POWERDOWN;
  power_down();
  setup_PLL();
  cola_encolar_msg(SET_ALARM, g_alarma_crear(POWER_DOWN, FALSE, 10000));
}

void g_energia_reset() {
  if (estado == IDLE) {
    // Cancelar LATIDO
    cola_encolar_msg(SET_ALARM, g_alarma_crear(LATIDO, TRUE, 0));
    cola_encolar_msg(APAGAR_LATIDO, 0);
    estado = NORMAL;
  }
  // Resetear alarma de POWER_DOWN
  cola_encolar_msg(SET_ALARM, g_alarma_crear(POWER_DOWN, FALSE, 10000));
}

void g_energia_idle() {
  if (estado == NORMAL) {
    // Activar LATIDO
    cola_encolar_msg(SET_ALARM, g_alarma_crear(LATIDO, TRUE, 250));
    estado = IDLE;
  }
  idle();
}

void g_energia_tratar_mensaje(msg_t mensaje) {
  switch (mensaje.ID_msg) {
    case POWER_DOWN:
      g_energia_power_down();
      break;
    case EJECUTAR:
      // No hace falta reiniciar la alarma
      // porque reinicia al salir de powerdown
      if (estado == POWERDOWN) {
        estado = NORMAL;
      } else {
        cola_encolar_msg(mensaje.auxData, 0);
      }
    case RESET_POWERDOWN:
      g_energia_reset();
      break;
  }
}
