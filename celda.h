/**
 * @file celda.h
 * @authors: Profesores de la asignatura &
 *           Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Tipo Abstracto de Datos. Encapsula el formato de celda
 */

#ifndef CELDA_H
#define CELDA_H

#include <inttypes.h>

/**
 * @brief Cada celda se codifica en 8 bits. Sólo se usan los 3 menos
 *        significativos
 *        bit 0 -> 1: ficha blanca, 0 : no hay ficha blanca
 *        bit 1 -> 1: ficha negra,  0 : no hay ficha negra
 *        bit 2 -> 1: ocupada,      0 : posición vacía
 */
typedef uint8_t CELDA;

/**
 * @brief Modifica el valor almacenado en la celda indicada.
 *        Valores válidos:
 *          1: ficha blanca
 *          2: ficha negra
 */
enum { FICHA_BLANCA = 1, FICHA_NEGRA = 2, FICHA_FIJADA = 3 };

__inline static void celda_poner_valor(CELDA *celdaptr, uint8_t val) {
  if ((val == FICHA_BLANCA) || (val == FICHA_NEGRA) || (val == FICHA_FIJADA)) {
    *celdaptr = 0x04 /*ocupado*/ + val;
  }
}

__inline static void celda_vaciar(CELDA *celdaptr) { *celdaptr = 0; }

/**
 * @brief Devuelve 1 si la celda está vacía
 */
__inline static uint8_t celda_vacia(CELDA celda) { return (celda & 0x4) == 0; }

/**
 * @brief Devuelve color celda y si vacia 0
 */
__inline static uint8_t celda_color(CELDA celda) { return (celda & 0x03); }

/**
 * @brief Devuelve 1 si la celda es blanca y valida
 */
__inline static uint8_t celda_blanca(CELDA celda) { return celda == 0x05; }

/**
 * @brief Devuelve 1 si la celda es negra y valida
 */
__inline static uint8_t celda_negra(CELDA celda) { return celda == 0x06; }

/**
 * @brief Devuelve 1 si la celda es fijada y valida
 */
__inline static uint8_t celda_fijada(CELDA celda) { return celda == 0x07; }
#endif  // CELDA_H
