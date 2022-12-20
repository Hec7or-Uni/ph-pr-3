/**
 * @file gpio.h
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Definición de funciones para el manejo del GPIO
 */

#ifndef GPIO_H
#define GPIO_H

#include <LPC210X.H>
#include <inttypes.h>

/**
 * @brief Permite emplear el GPIO y debe ser invocada antes de poder llamar
 * al resto de funciones de la biblioteca.
 */
void gpio_iniciar(void);

/**
 * @brief Leer del GPIO.
 * @param bit_inicial Indica el primer bit a leer.
 * @param num_bits    Indica cuántos bits queremos leer.
 * @return Entero con el valor de los bits indicados.
 */
int gpio_leer(int bit_inicial, int num_bits);

/**
 * @brief Escribir en el GPIO.
 * @param bit_inicial Indica el primer bit a escribir.
 * @param num_bits    Indica cuántos bits queremos escribir.
 */
void gpio_escribir(int bit_inicial, int num_bits, int valor);

/**
 * @brief Los bits indicados se utilizarán como pines de entrada.
 * @param bit_inicial Indica el primer bit de entrada.
 * @param num_bits    Indica cuántos bits queremos introducir.
 */
void gpio_marcar_entrada(int bit_inicial, int num_bits);

/**
 * @brief Los bits indicados se utilizarán como pines de salida.
 * @param bit_inicial Indica el primer bit de salida.
 * @param num_bits    Indica cuántos bits queremos introducir.
 */
void gpio_marcar_salida(int bit_inicial, int num_bits);

#endif
