#include "g_serie.h"

static uint8_t first = 0, last = 0, full = FALSE;
static uint8_t cola_cadenas[COLA_CADENAS_SIZE];

void g_serie_encolar_cadena(uint8_t cadena) {
  if (full) return;

  if (first == last) {  // Si está vacía antes de encolar se muestra
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

  if (first != last) {  // Si está vacía una vez desencolado se muestra
    uint8_t cadena = cola_cadenas[first];
    g_serie_mostrar_cadena(cadena);
  }
}

void g_serie_mostrar_cadena(uint8_t cadena) {
  if (cadena >= CADENA_FILA1 && cadena <= CADENA_FILA6) {  // Caso de una fila
    cola_encolar_msg(PEDIR_FILA, cadena - CADENA_FILA1 + 1);
  } else {
    uart0_enviar_array(cadenas[cadena]);
  }
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
      if (buffer[j] != cmd[i][j]) {
        iguales = FALSE;
      } else if (cmd[i][j] == '\0') {
        break;
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
  char array_fila[BUFFER_ENVIO_SIZE] = "      x| | | | | | | |\n";

  int fila = datosFila & 0xF;
  array_fila[6] = '0' + fila;

  datosFila = datosFila >> 4;

  for (int i = 8; i <= 20; i += 2) {
    array_fila[i] = g_serie_codificar_jugador(datosFila & 0xF);

    datosFila = datosFila >> 4;
  }

  uart0_enviar_array(array_fila);
}

void g_serie_encolar_tablero() {
  for (uint8_t c = CADENA_FILA6; c >= CADENA_FILA1; c--) {
    g_serie_encolar_cadena(c);
  }
  g_serie_encolar_cadena(CADENA_BASE1);
  g_serie_encolar_cadena(CADENA_BASE2);
}

void g_serie_encolar_inicio() {
  for (uint8_t c = CADENA_CABECERA1; c <= CADENA_CABECERA20; c++) {
    g_serie_encolar_cadena(c);
  }
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
      break;
    case FIN:
      // g_serie_encolar_cadena(CADENA_FIN);
      break;
  }
}

void g_serie_iniciar(void) {
  uart0_iniciar();
  g_serie_encolar_inicio();
  g_serie_encolar_tablero();
}
