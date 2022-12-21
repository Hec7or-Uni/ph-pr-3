/**
 * @file g_serie.c
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Implementación de funciones para el manejo de la comunicación
 * por serie
 */

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
  if (first == last && !full) return;  // Si está vacía no hace nada

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
  } else if (cadena == CADENA_CALIDAD_SERVICIO) {
    cola_encolar_msg(PEDIR_CALIDAD_SERVICIO, 0);
  } else if (cadena == CADENA_MINUTOS_JUGADOS) {
    cola_encolar_msg(PEDIR_MINUTOS_JUGADOS, 0);
  } else if (cadena == CADENA_SEGUNDOS_JUGADOS) {
    cola_encolar_msg(PEDIR_SEGUNDOS_JUGADOS, 0);
  } else {
    uart0_enviar_array(cadenas[cadena]);
  }
}

int g_serie_check_c(char buffer[BUFFER_SIZE]) {
  if (buffer[0] == 'C' && buffer[1] >= '0' && buffer[1] <= '9') {
    if (buffer[2] == '\0') {
      uint32_t unidades = buffer[1] - '0';
      cola_encolar_msg(JUGAR, unidades);
      return TRUE;
    } else if (buffer[2] >= '0' && buffer[2] <= '9') {
      uint32_t decenas = buffer[1] - '0';
      uint32_t decenasX10 = (decenas << 3) + (decenas << 1);  // 10x = 8x + 2x
      uint32_t unidades = buffer[2] - '0';
      cola_encolar_msg(JUGAR, decenasX10 + unidades);
      return TRUE;
    }
  }
  return FALSE;
}

void g_serie_ejecutar_cmd(char buffer[BUFFER_SIZE]) {
  const char* cmd[NUM_COMANDOS] = {"NEW", "END"};
  const uint8_t msg[NUM_COMANDOS] = {RESET, FIN};

  if (g_serie_check_c(buffer)) return;

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
      return;
    }
  }
  cola_encolar_msg(IGNORE_CMD, 0);
}

void g_serie_clean_buffer(char buffer[BUFFER_SIZE]) {
  for (uint8_t i = 0; i < BUFFER_SIZE; i++) {
    buffer[i] = '\0';
  }
}

void g_serie_caracter_recibido(char c) {
  static char buffer[BUFFER_SIZE];
  static uint8_t i = 0, k = 0, leer = FALSE;

  if (c == '#') {  // Comienzo de comando
    cola_encolar_msg(APAGAR_IGNORE_CMD, 0);
    leer = TRUE;
    i = 0;
    k = 0;
    g_serie_clean_buffer(buffer);
  } else if (leer && c == '!') {  // Fin de comando
    leer = FALSE;
    k = 0;
    g_serie_ejecutar_cmd(buffer);
  } else if (leer) {  // Caracter del comando
    if (i >= 3)
      leer = FALSE;
    else
      buffer[i++] = c;
  }
  k++;
  if (k > 5) {
    cola_encolar_msg(IGNORE_CMD, 0);
  }
}

char g_serie_codificar_jugador(CELDA celda) {
  if (celda_vacia(celda)) {
    return ' ';
  } else if (celda_blanca(celda)) {
    return 'B';
  } else if (celda_negra(celda)) {
    return 'N';
  }  // celda_fijada(celda)
  return '*';
}

void g_serie_mostrar_fila(uint32_t datosFila) {
  char array_fila[BUFFER_ENVIO_SIZE + 1] = "      x| | | | | | | |\n";

  int fila = datosFila & 0xF;
  array_fila[6] = '0' + fila;

  datosFila = datosFila >> 4;

  for (int i = 8; i <= 20; i += 2) {
    array_fila[i] = g_serie_codificar_jugador(datosFila & 0xF);

    datosFila = datosFila >> 4;
  }

  uart0_enviar_array(array_fila);
}

void g_serie_itoa(char array[], uint32_t i, uint32_t x) {
  if (x == 0) {
    array[i] = '0';
  } else {
    while (x > 0) {
      array[i] = '0' + (x % 10);
      x = x / 10;
      i--;
    }
  }
}

void g_serie_mostrar_qos(uint32_t latencia) {
  char array[BUFFER_ENVIO_SIZE + 1] = "Latencia:                 Xus\n\n";
  g_serie_itoa(array, 26 /*Posicion de la X*/, latencia);
  // g_serie_itoa(array, 26 /*Posicion de la X*/, 365);
  uart0_enviar_array(array);
}

void g_serie_mostrar_minutos(uint32_t minutos) {
  char array[BUFFER_ENVIO_SIZE + 1] = "Tiempo jugado:         Xm";
  g_serie_itoa(array, 23 /*Posicion de la X*/, minutos);
  uart0_enviar_array(array);
}

void g_serie_mostrar_segundos(uint32_t segundos) {
  char array[BUFFER_ENVIO_SIZE + 1] = "  Ys\n";
  g_serie_itoa(array, 2 /*Posicion de la Y*/, segundos);
  uart0_enviar_array(array);
}

void g_serie_encolar_tablero(void) {
  for (uint8_t c = CADENA_FILA6; c >= CADENA_FILA1; c--) {
    g_serie_encolar_cadena(c);
  }
  g_serie_encolar_cadena(CADENA_BASE1);
  g_serie_encolar_cadena(CADENA_BASE2);
}

void g_serie_encolar_inicio(void) {
  for (uint8_t c = CADENA_CABECERA1; c <= CADENA_CABECERA20; c++) {
    g_serie_encolar_cadena(c);
  }
}

void g_serie_encolar_comenzar(void) {
  for (uint8_t c = CADENA_COMENZAR1; c <= CADENA_COMENZAR4; c++) {
    g_serie_encolar_cadena(c);
  }
}

void g_serie_iniciar(void) {
  uart0_iniciar();
  g_serie_encolar_inicio();
}

void g_serie_tratar_evento(evento_t evento) {
  switch (evento.ID_evento) {
    case CARACTER_RECIBIDO:
      g_serie_caracter_recibido(evento.auxData);
      // Avisamos al g_energia de que resetee la alarma de Power-Down
      cola_encolar_msg(RESET_POWERDOWN, 0);
      break;
    case CARACTER_ENVIADO:
      if (!uart0_continuar_envio()) {
        g_serie_desencolar_cadena();
      }
      break;
  }
}

void g_serie_tratar_mensaje(msg_t mensaje) {
  static uint8_t estado = G_SERIE_INACTIVO;
  switch (mensaje.ID_msg) {
    case DEVOLVER_FILA:
      g_serie_mostrar_fila(mensaje.auxData);
      break;
    case CELDA_MARCADA:
      estado = G_SERIE_ESPERANDO;
      cola_encolar_msg(SET_ALARM,
                       g_alarma_crear(CONFIRMAR_JUGADA, FALSE, 1000));
      g_serie_encolar_tablero();
      g_serie_encolar_cadena(CADENA_CANCELAR1);
      g_serie_encolar_cadena(CADENA_CANCELAR2);
      break;
    case JUGADA_REALIZADA:
      g_serie_encolar_tablero();
      cola_encolar_msg(PEDIR_JUGADOR, 0);
      estado = G_SERIE_ACTIVO;
      break;
    case JUGADOR:
      if (estado == G_SERIE_ACTIVO) {
        if (mensaje.auxData == FICHA_BLANCA)
          g_serie_encolar_cadena(CADENA_TURNO_BLANCAS);
        else if (mensaje.auxData == FICHA_NEGRA)
          g_serie_encolar_cadena(CADENA_TURNO_NEGRAS);
      }
      break;
    case CALIDAD_SERVICIO:
      g_serie_mostrar_qos(mensaje.auxData);
      break;
    case MINUTOS_JUGADOS:
      g_serie_mostrar_minutos(mensaje.auxData);
      break;
    case SEGUNDOS_JUGADOS:
      g_serie_mostrar_segundos(mensaje.auxData);
      break;
    case ENTRADA_VALIDADA:
      if (!mensaje.auxData) {  // Si no es valida
        g_serie_encolar_cadena(CADENA_COLUMNA_NO_VALIDA);
      }
      break;
    case CANCELAR:
      if (estado == G_SERIE_INACTIVO) {
        estado = G_SERIE_ACTIVO;
        g_serie_encolar_tablero();
        cola_encolar_msg(PEDIR_JUGADOR, 0);
      } else if (estado == G_SERIE_ESPERANDO) {
        cola_encolar_msg(SET_ALARM, g_alarma_crear(CONFIRMAR_JUGADA, FALSE, 0));
        estado = G_SERIE_ACTIVO;
        g_serie_encolar_cadena(CADENA_CANCELADO);
        g_serie_encolar_tablero();
        cola_encolar_msg(PEDIR_JUGADOR, 0);
      }
      break;
    case RESET:
      if (estado != G_SERIE_ESPERANDO) {
        if (estado == G_SERIE_ACTIVO) {
          g_serie_encolar_cadena(CADENA_RESET);
        }
        estado = G_SERIE_ACTIVO;
        g_serie_encolar_tablero();
        cola_encolar_msg(PEDIR_JUGADOR, 0);
      }
      break;
    case FIN:
      if (estado == G_SERIE_ACTIVO) {
        estado = G_SERIE_INACTIVO;
        g_serie_encolar_cadena(CADENA_FIN);
        if (mensaje.auxData == FICHA_BLANCA) {
          g_serie_encolar_cadena(CADENA_GANAN_BLANCAS);
        } else if (mensaje.auxData == FICHA_NEGRA) {
          g_serie_encolar_cadena(CADENA_GANAN_NEGRAS);
        } else if (mensaje.auxData == FICHA_FIJADA) {
          g_serie_encolar_cadena(CADENA_EMPATE);
        }
        g_serie_encolar_cadena(CADENA_MINUTOS_JUGADOS);
        g_serie_encolar_cadena(CADENA_SEGUNDOS_JUGADOS);
        g_serie_encolar_cadena(CADENA_CALIDAD_SERVICIO);
        g_serie_encolar_comenzar();
      }
      break;
  }
}
