#include "power.h"

void power_iniciar() { EXTWAKE = 6; }

void power_down() { PCON = PCON | 0x2; }


void idle() { PCON = PCON | 0x1; }
