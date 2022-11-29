#ifndef POWER_H
#define POWER_H

#include <LPC210x.H> /* LPC210x definitions */

/**
 * @brief Permite que el procesador se despierte de PD.
 */
void power_iniciar(void);

/**
 * @brief LLama a función ASM establecida en Startup.s para restablecer
 * la configuración del PLL.
 */
void setup_PLL(void);

/**
 * @brief Pone al procesador a dormir.
 * En el estado power-down los periféricos también entran en bajo consumo y
 * dejan de funcionar pero se sigue manteniendo el estado.
 */
void power_down(void);

/**
 * @brief Pone el procesador en modo bajo consumo.
 * En g_energia_idle el procesador se para, pero los periféricos del chip, como
 * el temporizador, siguen activos y lo pueden despertar al realizar una
 * interrupción.
 */
void idle(void);

#endif
