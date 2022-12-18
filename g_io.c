#include "g_io.h"

void g_io_iniciar() {
  gpio_iniciar();
  gpio_marcar_salida(0, 32);
  // todos los pines a 0
  gpio_escribir(0, 32, 0);
  // menos los de los botones (evitar interrupción al comienzo)
  gpio_escribir(14, 2, 3);
  gpio_marcar_entrada(3, 7);
  gpio_marcar_entrada(14, 2);
  cola_encolar_msg(SET_ALARM, g_alarma_crear(LEER_ENTRADA, TRUE, 100));
}

void g_io_mostrar_jugador(int jugador) { gpio_escribir(1, 2, jugador); }

int g_io_leer_entrada() {
  int input = gpio_leer(3, 7);
  int msb = MSB(input) + 1;

  // Comprueba que no hay más de una columna seleccionada a la vez
  if ((input & ((1 << (msb - 1)) - 1)) != 0) return 0;

  // Para que corresponda a la visión del jugador hay que invertir la columna
  return 8 - msb;
}

void g_io_encender_realizada() {
  gpio_escribir(16, 1, 1);
  // Al cabo de 2s apagar
  cola_encolar_msg(SET_ALARM, g_alarma_crear(APAGAR_REALIZADA, FALSE, 2000));
}

void g_io_apagar_realizada() { gpio_escribir(16, 1, 0); }

void g_io_mostrar_invalido() { gpio_escribir(17, 1, 1); }

void g_io_apagar_invalido() { gpio_escribir(17, 1, 0); }

void g_io_fin() {
  gpio_escribir(18, 1, 1);
  cola_encolar_msg(SET_ALARM, g_alarma_borrar(LEER_ENTRADA));
}

void g_io_overflow() { gpio_escribir(30, 1, 1); }

void g_io_latido() {
  static uint8_t ON = 0;
  gpio_escribir(31, 1, ON);
  ON = 1 - ON;  // alternar estado
}

void g_io_apagar_latido() { gpio_escribir(31, 1, 0); }

void g_io_tratar_evento(evento_t evento) {
  switch (evento.ID_evento) {
    case OVERFLOW_E:
      g_io_overflow();
      while (1)
        ;
  }
}

void g_io_tratar_mensaje(msg_t mensaje) {
  static uint32_t entrada_anterior, entrada;
  switch (mensaje.ID_msg) {
    case RESET:
      g_io_iniciar();
      break;
    case LATIDO:
      g_io_latido();
      break;
    case APAGAR_LATIDO:
      g_io_apagar_latido();
      break;
    case LEER_ENTRADA:
      entrada = g_io_leer_entrada();
      if (entrada != entrada_anterior) {
        cola_encolar_msg(ENTRADA_ACTUALIZADA, 0);
      }
      entrada_anterior = entrada;
      cola_encolar_msg(VALIDAR_ENTRADA, entrada);
      break;
    case ENTRADA_VALIDADA:
      if (mensaje.auxData)
        g_io_apagar_invalido();
      else
        g_io_mostrar_invalido();
      break;
    case JUGADA_REALIZADA:
      g_io_encender_realizada();
      break;
    case APAGAR_REALIZADA:
      g_io_apagar_realizada();
      break;
    /*case JUGADOR:
      g_io_mostrar_jugador(mensaje.auxData);
      break;*/
    case FIN:
      g_io_fin();
      break;
    case OVERFLOW_M:
      g_io_overflow();
      while (1)
        ;
  }
}
