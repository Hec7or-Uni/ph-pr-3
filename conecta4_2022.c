#include "conecta4_2022.h"

// devuelve ERROR en caso de no encontrar fila
uint8_t C4_calcular_fila(CELDA cuadricula[TAM_FILS][TAM_COLS],
                         uint8_t columna) {
  uint8_t fila = 1;  // row 0 is used to enumerate the columns

  if ((columna < 1) || (columna > NUM_COLUMNAS)) {
    return ERROR;
  }  // Out of the board. Columna must go form 1 to 7

  while ((fila <= NUM_FILAS) &&
         (celda_vacia(cuadricula[fila][columna]) == FALSE)) {
    fila++;
  }
  return fila <= NUM_FILAS ? fila : ERROR;
};

// devuelve la longitud de la línea más larga
__attribute__((noinline)) uint8_t conecta4_buscar_alineamiento_c(
    CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila, uint8_t columna,
    uint8_t color, int8_t delta_fila, int8_t delta_columna) {
  // avanzar hasta que cela esté vacía, sea distinto color o lleguemos al borde
  if (!C4_fila_valida(fila) || !C4_columna_valida(columna)) {
    return 0;
  }

  // posicion valida y mismo color
  if (celda_vacia(cuadricula[fila][columna]) ||
      (celda_color(cuadricula[fila][columna]) != color)) {
    return 0;
  }

  // avanzar índices
  uint8_t nueva_fila = fila + delta_fila;
  uint8_t nueva_columna = columna + delta_columna;

  // incrementar longitud y visitar celda vecina
  return 1 + conecta4_buscar_alineamiento_c(cuadricula, nueva_fila,
                                            nueva_columna, color, delta_fila,
                                            delta_columna);
}

// devuelve true si encuentra una línea de longitud mayor o igual a 4
__attribute__((noinline)) uint8_t conecta4_hay_linea_c_c(
    CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila, uint8_t columna,
    uint8_t color) {
  int8_t deltas_fila[4] = {0, -1, -1, 1};
  int8_t deltas_columna[4] = {-1, 0, -1, -1};
  unsigned int i = 0;
  uint8_t linea = FALSE;
  uint8_t long_linea = 0;

  // buscar linea en fila, columna y 2 diagonales
  for (i = 0; (i < 4) && (linea == FALSE); ++i) {
    // buscar sentido
    long_linea = conecta4_buscar_alineamiento_c(
        cuadricula, fila, columna, color, deltas_fila[i], deltas_columna[i]);
    linea = long_linea >= 4;
    if (linea) {
      continue;
    }
    // buscar sentido inverso
    long_linea += conecta4_buscar_alineamiento_c(
        cuadricula, fila - deltas_fila[i], columna - deltas_columna[i], color,
        -deltas_fila[i], -deltas_columna[i]);
    linea = long_linea >= 4;
  }
  return linea;
}

uint8_t conecta4_hay_linea_arm_arm_c(CELDA cuadricula[TAM_FILS][TAM_COLS],
                                     uint8_t fila, uint8_t columna,
                                     uint8_t color) {
  int8_t deltas_fila[4] = {0, -1, -1, 1};
  int8_t deltas_columna[4] = {-1, 0, -1, -1};
  unsigned int i = 0;
  uint8_t long_linea = 0;
  uint8_t fila_aux = fila;
  uint8_t columna_aux = columna;

  if (!C4_fila_valida(fila) || !C4_columna_valida(columna) ||
      celda_vacia(cuadricula[fila][columna]) ||
      (celda_color(cuadricula[fila][columna]) != color)) {
    return FALSE;
  }

  // buscar linea en fila, columna y 2 diagonales
  for (i = 0; i < 4; ++i) {
    long_linea = 1;
    fila += deltas_fila[i];
    columna += deltas_columna[i];
    // buscar sentido
    while (!(!C4_fila_valida(fila) || !C4_columna_valida(columna) ||
             celda_vacia(cuadricula[fila][columna]) ||
             (celda_color(cuadricula[fila][columna]) != color))) {
      fila += deltas_fila[i];
      columna += deltas_columna[i];
      long_linea++;

      if (long_linea == 4) return TRUE;
    }

    fila = fila_aux - deltas_fila[i];
    columna = columna_aux - deltas_columna[i];
    // buscar sentido inverso
    while (!(!C4_fila_valida(fila) || !C4_columna_valida(columna) ||
             celda_vacia(cuadricula[fila][columna]) ||
             (celda_color(cuadricula[fila][columna]) != color))) {
      fila -= deltas_fila[i];
      columna -= deltas_columna[i];
      long_linea++;
      if (long_linea == 4) {
        return TRUE;
      }
    }
    fila = fila_aux;
    columna = columna_aux;
  }
  return FALSE;
}

// devuelve true si encuentra una línea de longitud mayor o igual a 4
__attribute__((noinline)) uint8_t conecta4_hay_linea_c_arm(
    CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila, uint8_t columna,
    uint8_t color) {
  int8_t deltas_fila[4] = {0, -1, -1, 1};
  int8_t deltas_columna[4] = {-1, 0, -1, -1};
  unsigned int i = 0;
  uint8_t linea = FALSE;
  uint8_t long_linea = 0;

  for (i = 0; (i < 4) && (linea == FALSE); ++i) {
    long_linea = conecta4_buscar_alineamiento_arm(
        cuadricula, fila, columna, color, deltas_fila[i], deltas_columna[i]);
    linea = long_linea >= 4;
    if (linea) {
      continue;
    }
    long_linea += conecta4_buscar_alineamiento_arm(
        cuadricula, fila - deltas_fila[i], columna - deltas_columna[i], color,
        -deltas_fila[i], -deltas_columna[i]);
    linea = long_linea >= 4;
  }
  return linea;
}

void C4_actualizar_tablero(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila,
                           uint8_t columna, uint8_t val) {
  celda_poner_valor(&cuadricula[(fila)][(columna)], val);
}

// comprueba si esta jugada llena todo el tablero y hay empate
int C4_comprobar_empate(CELDA cuadricula[TAM_FILS][TAM_COLS]) {
  for (int i = 1; i < TAM_COLS; i++) {
    if (celda_vacia(cuadricula[TAM_FILS - 1][i])) {
      return FALSE;
    }
  }
  return TRUE;
}

int C4_verificar_4_en_linea(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila,
                            uint8_t columna, uint8_t color, int *fail) {
  uint8_t resultado_c_c =
      conecta4_hay_linea_c_c(cuadricula, fila, columna, color);
  uint8_t resultado_c_arm =
      conecta4_hay_linea_c_arm(cuadricula, fila, columna, color);
  uint8_t resultado_arm_c =
      conecta4_hay_linea_arm_c(cuadricula, fila, columna, color);
  uint8_t resultado_arm_arm =
      conecta4_hay_linea_arm_arm(cuadricula, fila, columna, color);
  if (fail != 0)
    *fail = resultado_c_c != resultado_c_arm ||
            resultado_c_c != resultado_arm_c ||
            resultado_c_c != resultado_arm_arm;
  return resultado_c_c && resultado_c_arm && resultado_arm_c &&
         resultado_arm_arm;
}

enum C4_estado { C4_INICIO, C4_ESPERA, C4_JUGANDO, C4_FIN };

static int estado = C4_INICIO;
static uint8_t color = 1;

static CELDA tablero[7][8] = {
    0, 0XC1, 0XC2, 0XC3, 0XC4, 0XC5, 0XC6, 0XC7, 0XF1, 0, 0,    0, 0,    0,
    0, 0,    0XF2, 0,    0,    0,    0,    0,    0,    0, 0XF3, 0, 0,    0,
    0, 0,    0,    0,    0XF4, 0,    0,    0,    0,    0, 0,    0, 0XF5, 0,
    0, 0,    0,    0,    0,    0,    0XF6, 0,    0,    0, 0,    0, 0,    0};

void conecta4_iniciar() {
  color = 1;
  cola_encolar_msg(JUGADOR, color);
  for (int i = 1; i <= NUM_FILAS; i++) {
    for (int j = 1; j <= NUM_COLUMNAS; j++) {
      tablero[i][j] = 0;
    }
  }
  estado = C4_ESPERA;
}

void C4_validar(uint8_t columna) {
  uint8_t fila = 0;
  int ok = C4_columna_valida(columna);
  if (ok) fila = C4_calcular_fila(tablero, columna);
  ok = ok && C4_fila_valida(fila);

  if (estado == C4_ESPERA) {
    cola_encolar_msg(ENTRADA_VALIDADA, ok);
  } else if (estado == C4_JUGANDO) {
    if (ok) {
      C4_actualizar_tablero(tablero, fila, columna, color);
      cola_encolar_msg(JUGADA_REALIZADA, 0);
      int fin = conecta4_hay_linea_arm_arm(tablero, fila, columna, color) ||
                C4_comprobar_empate(tablero);
      cola_encolar_msg(COMPROBACION_REALIZADA, 0);
      if (fin) {
        cola_encolar_msg(FIN, fin);
        estado = C4_FIN;
      } else {
        color = C4_alternar_color(color);
        cola_encolar_msg(JUGADOR, color);
        estado = C4_ESPERA;
      }
    } else {
      estado = C4_ESPERA;
    }
  }  // if (estado == C4_FIN) nothing;
}

void C4_jugar() {
  if (estado != C4_FIN) {
    cola_encolar_msg(LEER_ENTRADA, 0);
    estado = C4_JUGANDO;
  }
}

void C4_devolver_fila(uint32_t fila) {
  uint32_t result = fila;
  for (int col = 1; col <= NUM_COLUMNAS; col++) {
    int desplazamiento = ((col - 1) << 2) + 4;  //(col - 1) * 4 + 4
    result = result | (tablero[fila][col] << desplazamiento);
  }
  cola_encolar_msg(DEVOLVER_FILA, result);
}

void conecta4_tratar_mensaje(msg_t mensaje) {
  static volatile uint32_t tiempo_inicial, tiempo_final, tiempo_total;
  switch (mensaje.ID_msg) {
    case RESET:
      conecta4_iniciar();
      break;
    case VALIDAR_ENTRADA:
      C4_validar(mensaje.auxData);
      break;
    case JUGAR:
      C4_jugar();
      tiempo_inicial = mensaje.timestamp;
      break;
    case COMPROBACION_REALIZADA:
      tiempo_final = mensaje.timestamp;
      tiempo_total = tiempo_final - tiempo_inicial;
      break;
    case PEDIR_FILA:
      C4_devolver_fila(mensaje.auxData);
      break;
  }
}
