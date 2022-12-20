/**
 * @file power.c
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Implementacion de funciones para el manejo del bajo consumo
 */

#include "power.h"

void power_iniciar() { EXTWAKE = 6; }

void power_down() { PCON = PCON | 0x2; }

void idle() { PCON = PCON | 0x1; }
