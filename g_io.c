#include "g_io.h"

void g_io_iniciar() {
  gpio_iniciar();
  gpio_marcar_salida(0, 32);
  // todos los pines a 0
  gpio_escribir(0, 32, 0);
  // menos los de los botones (evitar interrupción al comienzo)
  gpio_escribir(14, 2, 3);
  gpio_marcar_entrada(14, 2);
}

void g_io_encender_realizada() {
  gpio_escribir(16, 1, 1);
  // Al cabo de 2s apagar
  cola_encolar_msg(SET_ALARM, g_alarma_crear(APAGAR_REALIZADA, FALSE, 2000));
}

void g_io_apagar_realizada() { gpio_escribir(16, 1, 0); }

void g_io_mostrar_invalido() { gpio_escribir(17, 1, 1); }

void g_io_apagar_invalido() { gpio_escribir(17, 1, 0); }

void g_io_mostrar_fin() { gpio_escribir(18, 1, 1); }

void g_io_apagar_fin() { gpio_escribir(18, 1, 0); }

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
  static uint8_t estado = G_IO_FIN_LIBRE;
  switch (mensaje.ID_msg) {
    case JUGADA_REALIZADA:
      g_io_encender_realizada();
			estado = G_IO_FIN_LIBRE;
      break;
    case CANCELAR:
      estado = G_IO_FIN_LIBRE;
    case RESET:
      g_io_apagar_fin();
      break;
    case CELDA_MARCADA:
      estado = G_IO_FIN_BLOQUEADO;
      break;
    case LATIDO:
      g_io_latido();
      break;
    case APAGAR_LATIDO:
      g_io_apagar_latido();
      break;
    case ENTRADA_VALIDADA:
      if (mensaje.auxData)
        g_io_apagar_invalido();
      else
        g_io_mostrar_invalido();
      break;
    case APAGAR_REALIZADA:
      g_io_apagar_realizada();
      break;
    case FIN:
      if (estado == G_IO_FIN_LIBRE) {
        g_io_mostrar_fin();
      }
      break;
    case OVERFLOW_M:
      g_io_overflow();
      while (1)
        ;
  }
}
