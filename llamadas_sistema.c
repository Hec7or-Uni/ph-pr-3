/**
 * @file llamadas_sistema.h
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Definición de funciones para el manejo de las llamadas al
 * sistema.
 * @note: El resto de llamadas al sistema se encuentran en el archivo SWI.s
 */

#include "llamadas_sistema.h"

uint32_t __SWI_0() { return CTIME0; }

uint32_t __SWI_1(void) { return T1TC; }
