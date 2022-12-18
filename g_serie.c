// @ts-nocheck
#include "g_serie.h"

enum ObjetoMostrado { TABLERO, RESET_DEBUG, NADA };

static enum ObjetoMostrado mostrando = NADA;

const char* CMD_JUGAR = "C";
const char* CMD_NEW = "NEW";
const char* CMD_END = "END";

int g_serie_ejecutar_cmd(char buffer[BUFFER_SIZE]) {
  const char* cmd[NUM_COMANDOS] = {CMD_JUGAR, CMD_NEW, CMD_END};
  const uint8_t msg[NUM_COMANDOS] = {JUGAR, RESET, FIN};

  for (uint8_t i = 0; i < NUM_COMANDOS; i++) {
    int iguales = TRUE;
    for (uint8_t j = 0; j < BUFFER_SIZE && iguales; j++) {
      if (cmd[i][j] == '\0' || buffer[j] != cmd[i][j]) {
        iguales = FALSE;
      }
    }
    if (iguales) {
      cola_encolar_msg(msg[i], 0);
      return TRUE;
    }
  }

  return FALSE;
}

void clean_buffer(char buffer[BUFFER_SIZE]) {
  for (uint8_t i = 0; i < BUFFER_SIZE; i++) {
    buffer[i] = '\0';
  }
}

void g_serie_caracter_recibido(char c) {
  static char buffer[BUFFER_SIZE];
  static uint8_t i = 0, leer = FALSE;

  if (c == '#') {  // Comienzo de comando
    leer = TRUE;
    i = 0;
    clean_buffer(buffer);
  } else if (leer && c == '!') {  // Fin de comando
    leer = FALSE;
    g_serie_ejecutar_cmd(buffer);
  } else if (leer) {  // Caracter del comando
    if (i >= 3)
      leer = FALSE;
    else
      buffer[i++] = c;
  }
}

static char arrayTablero[8][18] = {
    {'6', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ',
     '|', '\n', '\0'},
    {'5', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ',
     '|', '\n', '\0'},
    {'4', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ',
     '|', '\n', '\0'},
    {'3', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ',
     '|', '\n', '\0'},
    {'2', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ',
     '|', '\n', '\0'},
    {'1', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ', '|', ' ',
     '|', '\n', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-',
     '-', '\n', '\0'},
    {'-', '|', '1', '|', '2', '|', '3', '|', '4', '|', '5', '|', '6', '|', '7',
     '|', '\n', '\0'}};

char g_serie_codificar_jugador(CELDA celda) {
  if (celda_vacia(celda)) {
    return ' ';
  } else if (celda_blanca(celda)) {
    return 'B';
  } else if (celda_negra(celda)) {
    return 'N';
  }
  return 'X';
}

void g_serie_modificar_celda_tablero(int fila, int columna, char valor) {
  int i = NUM_FILAS - fila;
  int j = (columna << 1);
  arrayTablero[i][j] = valor;
}

void g_serie_modificar_fila_tablero(uint32_t datosFila) {
  int fila = datosFila & 0xF;
  datosFila = datosFila >> 4;
  for (int col = 1; col <= NUM_COLUMNAS; col++) {
    char valor = g_serie_codificar_jugador(datosFila & 0xF);
    g_serie_modificar_celda_tablero(fila, col, valor);
    datosFila = datosFila >> 4;
  }
}

void g_serie_mostrar_tablero() {
  static int i = -1;
  mostrando = TABLERO;
  if (i == -1) {
    uart0_enviar_array("\n");
    i++;
  } else {
    uart0_enviar_array(arrayTablero[i++]);
  }
  if (i == 8) {
    i = -1;
    mostrando = NADA;
  }
}

void g_serie_pedir_filas() {
  // Pide las filas al conecta 4
  for (uint8_t i = 1; i <= NUM_FILAS; i++) {
    cola_encolar_msg(PEDIR_FILA, i);
  }
}

void g_serie_continuar_envio() {
  if (!uart0_continuar_envio()) {
    switch (mostrando) {
      case TABLERO:
        g_serie_mostrar_tablero();
        break;
        // case LIMPIAR:
        //   g_serie_limpiar_pantalla();
        //   break;
    }
  }
}

void g_serie_tratar_evento(evento_t evento) {
  switch (evento.ID_evento) {
    case CARACTER_RECIBIDO:
      g_serie_caracter_recibido(evento.auxData);
      break;
    case CARACTER_ENVIADO:
      g_serie_continuar_envio();
      break;
  }
}

void g_serie_tratar_mensaje(msg_t mensaje) {
  static int filasRecibidas = 0;
  switch (mensaje.ID_msg) {
    case DEVOLVER_FILA:
      g_serie_modificar_fila_tablero(mensaje.auxData);
      filasRecibidas++;
      if (filasRecibidas == NUM_FILAS) {
        g_serie_mostrar_tablero();
        filasRecibidas = 0;
      }
      break;
    case JUGADA_REALIZADA:
      g_serie_pedir_filas();  // Para imprimir el tablero
      break;
    case RESET:
      mostrando = RESET_DEBUG;
      uart0_enviar_array("RESET\n");
  }
}

void g_serie_iniciar(void) {
  uart0_iniciar();
  uart0_enviar_array("HOLA\n");
  //g_serie_pedir_filas();  // Para imprimir el tablero
}

// G_SERIE (PEDIR_FILAS, 1) -> C4
// C4 (DEVOLVER_FILAS, F1 1 2 3 4 5 6 7) -> G_SERIE
