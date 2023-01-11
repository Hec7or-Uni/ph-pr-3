/**
 * @file celda.h
 * @authors: Profesores de la asignatura &
 *           Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Tipo Abstracto de Datos. Encapsula el formato de celda
 */

#ifndef CONECTA4_H_2022
#define CONECTA4_H_2022

#include <inttypes.h>

#include "celda.h"
#include "cola_msg.h"
#include "g_alarmas.h"
#include "msg.h"
#include "utils.h"

/* Tamaños de la cuadricula */
enum {
  NUM_FILAS = 6,
  PADDING_FIL = 1,
  TAM_FILS = PADDING_FIL + NUM_FILAS,
  NUM_COLUMNAS = 7,
  PADDING_COL = 1,
  TAM_COLS = PADDING_COL + NUM_COLUMNAS
};

enum C4_estado { C4_ACTIVO, C4_ESPERANDO, C4_INACTIVO };

/**
 * @brief Devuelve la longitud de la línea más larga
 */
uint8_t conecta4_buscar_alineamiento_c(CELDA cuadricula[TAM_FILS][TAM_COLS],
                                       uint8_t fila, uint8_t columna,
                                       uint8_t color, int8_t delta_fila,
                                       int8_t delta_columna);

/**
 * @brief Devuelve la longitud de la línea más larga
 */
uint8_t conecta4_buscar_alineamiento_arm(CELDA cuadricula[TAM_FILS][TAM_COLS],
                                         uint8_t fila, uint8_t columna,
                                         uint8_t color, int8_t delta_fila,
                                         int8_t delta_columna);

/**
 * @brief Devuelve true si encuentra una línea de longitud mayor o igual a 4
 */
uint8_t conecta4_hay_linea_c_c(CELDA cuadricula[TAM_FILS][TAM_COLS],
                               uint8_t fila, uint8_t columna, uint8_t color);

/**
 * @brief Devuelve true si encuentra una línea de longitud mayor o igual a 4
 */
uint8_t conecta4_hay_linea_arm_c(CELDA cuadricula[TAM_FILS][TAM_COLS],
                                 uint8_t fila, uint8_t columna, uint8_t color);

/**
 * @brief Devuelve true si encuentra una línea de longitud mayor o igual a 4
 */
uint8_t conecta4_hay_linea_arm_arm(CELDA cuadricula[TAM_FILS][TAM_COLS],
                                   uint8_t fila, uint8_t columna,
                                   uint8_t color);

/**
 * @brief Tratamiento de mensajes del módulo de conecta 4.
 */
void conecta4_tratar_mensaje(msg_t mensaje);

//---------------------------------//

uint8_t C4_calcular_fila(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t columna);

void C4_actualizar_tablero(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila,
                           uint8_t columna, uint8_t val);

void C4_vaciar_celda_tablero(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila,
                             uint8_t columna);

int C4_comprobar_empate(CELDA cuadricula[TAM_FILS][TAM_COLS]);

int C4_verificar_4_en_linea(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila,
                            uint8_t columna, uint8_t color, int *fail);

static inline uint8_t C4_alternar_color(uint8_t colour) {
  return colour == 1 ? 2 : 1;  // jugador 1 o jugador 2
}

static inline uint8_t C4_columna_valida(uint8_t columna) {
  return (columna >= 1) && (columna <= NUM_COLUMNAS);
}

static inline uint8_t C4_fila_valida(uint8_t fila) {
  return (fila >= 1) && (fila <= NUM_FILAS);
}

/**
 * @brief Inicializa el módulo de juego de conecta4
 */
void conecta4_iniciar(CELDA tablero[TAM_FILS][TAM_COLS]);

/**
 * @brief Reacción del juego ante un evento JUGAR
 */
void C4_jugar(CELDA tablero[TAM_FILS][TAM_COLS], uint8_t *estado, uint8_t *fila,
              uint8_t *columna);

/**
 * @brief Reacción del juego ante un evento CONFIRMAR_JUGADA
 */
void C4_confirmar_jugada(CELDA tablero[TAM_FILS][TAM_COLS], uint8_t *estado,
                         uint8_t *fila, uint8_t *columna, uint8_t *color);

/**
 * @brief Reacción del juego ante un evento PEDIR_FILA
 */
void C4_devolver_fila(CELDA tablero[TAM_FILS][TAM_COLS], uint32_t fila);

#endif /* CONECTA4_H_2022 */
