#ifndef __UTILS_H__
#define __UTILS_H__
#include <LPC210x.H>

/* Definiciones para valores muy utilizados */
enum { FALSE = 0, TRUE = 1, ERROR = 0xFF };

/**
 * @brief Obtiene la posición del bit más significativo -1 en caso de no haber
 */
#define MSB(x) (31 - __clz(x))

/**
 * @brief Multiplica por 60
 */
#define times60(x) ((x << 6) - (x << 2))

/**
 * @brief Multiplica por 3600
 */
#define times3600(x) times60(times60(x))

#endif
