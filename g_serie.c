#include "g_serie.h"

enum Cadenas {
  CADENA_FILA1 = 1,
  CADENA_FILA2 = 2,
  CADENA_FILA3 = 3,
  CADENA_FILA4 = 4,
  CADENA_FILA5 = 5,
  CADENA_FILA6 = 6,
  CADENA_GUIONES,
  CADENA_BASE,

  CADENA_INICIAL,
  CADENA_RESET
};

enum { COLA_CADENAS_SIZE = 16 };

static uint8_t first = 0, last = 0, full = FALSE;
static uint8_t cola_cadenas[COLA_CADENAS_SIZE];

void g_serie_encolar_cadena(uint8_t cadena) {
  if (full) return;

  if (first == last) {  // Si está vacía lo muestras
    g_serie_mostrar_cadena(cadena);
  }

  cola_cadenas[last] = cadena;

  last++;
  if (last == COLA_CADENAS_SIZE) {
    last = 0;
  }
  if (last == first) {
    full = TRUE;
  }
}

void g_serie_desencolar_cadena(void) {
  first++;
  if (first == COLA_CADENAS_SIZE) {
    first = 0;
  }
  full = FALSE;

  if (first != last) {
    uint8_t cadena = cola_cadenas[first];
    g_serie_mostrar_cadena(cadena);
  }
}

void g_serie_mostrar_cadena(uint8_t cadena) {
  if (cadena > 0 && cadena <= NUM_FILAS) {  // Caso de una fila
    cola_encolar_msg(PEDIR_FILA, cadena);
    return;
  }

  char array[BUFFER_ENVIO_SIZE];
  int i = 0;
  switch (cadena) {
    case CADENA_GUIONES:
      // imprime "----------------\n"
      for (i = 0; i < 16; i++) {
        array[i] = '-';
      }
      array[16] = '\n';
      array[17] = '\0';
      break;
    case CADENA_BASE:
      // imprime "-|1|2|3|4|5|6|7|\n"
      array[0] = '-';
      for (i = 1; i <= NUM_COLUMNAS; i++) {
        int indice = ((i - 1) << 1);
        array[indice + 1] = '|';
        array[indice + 2] = '0' + i;
      }
      array[15] = '|';
      array[16] = '\n';
      array[17] = '\0';
      break;
    case CADENA_INICIAL:
      for (char* p = "Hola\n"; *p; p++, i++) {
        array[i] = *p;
      }
      array[i] = '\0';
      break;
    case CADENA_RESET:
      for (char* p = "Reset\n"; *p; p++, i++) {
        array[i] = *p;
      }
      array[i] = '\0';
      break;
    default:
      array[0] = '\0';
      break;
  }
  uart0_enviar_array(array);
}

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

void g_serie_mostrar_fila(uint32_t datosFila) {
  char array_fila[18];

  int fila = datosFila & 0xF;
  array_fila[0] = '0' + fila;

  datosFila = datosFila >> 4;

  for (int col = 1; col <= NUM_COLUMNAS; col++) {
    int indice = ((col - 1) << 1);
    char valor = g_serie_codificar_jugador(datosFila & 0xF);
    array_fila[indice + 1] = '|';
    array_fila[indice + 2] = valor;

    datosFila = datosFila >> 4;
  }

  array_fila[15] = '|';
  array_fila[16] = '\n';
  array_fila[17] = '\0';

  uart0_enviar_array(array_fila);
}

void g_serie_encolar_tablero() {
  for (int i = NUM_FILAS; i >= 1; i--) {
    g_serie_encolar_cadena(i);
  }
  g_serie_encolar_cadena(CADENA_GUIONES);
  g_serie_encolar_cadena(CADENA_BASE);
}

void g_serie_tratar_evento(evento_t evento) {
  switch (evento.ID_evento) {
    case CARACTER_RECIBIDO:
      g_serie_caracter_recibido(evento.auxData);
      break;
    case CARACTER_ENVIADO:
      if (!uart0_continuar_envio()) {
        g_serie_desencolar_cadena();
      }
      break;
  }
}

void g_serie_tratar_mensaje(msg_t mensaje) {
  switch (mensaje.ID_msg) {
    case DEVOLVER_FILA:
      g_serie_mostrar_fila(mensaje.auxData);
      break;
    case JUGADA_REALIZADA:
      g_serie_encolar_tablero();
      break;
    case RESET:
      g_serie_encolar_cadena(CADENA_RESET);
  }
}

void g_serie_iniciar(void) {
  uart0_iniciar();
  g_serie_encolar_cadena(CADENA_INICIAL);
  g_serie_encolar_tablero();
}

// G_SERIE (PEDIR_FILAS, 1) -> C4
// C4 (DEVOLVER_FILAS, F1 1 2 3 4 5 6 7) -> G_SERIE
