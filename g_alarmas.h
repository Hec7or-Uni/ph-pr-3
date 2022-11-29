#ifndef GESTOR_ALARMAS_H
#define GESTOR_ALARMAS_H
#include <inttypes.h>

#include "cola_msg.h"
#include "temporizador.h"
#include "utils.h"

enum { NUM_ALARMAS = 8 };

typedef uint32_t alarma_t;

/**
 * @brief Crea el campo auxiliar que hay que encolar junto a SET_ALARM
 *  para crear la alarma
 * @param ID_msg ID del mensaje a encolar cuando salte la alarma
 * @param esPeriodica Si TRUE la alarma se resetea cada vez que salta
 * @param retardo Tiempo en ms hasta que salte la alarma
 * @return Devuelve la información de los parámetros con el formato
 *  del campo auxiliar: 8 bits de ID : 1 bit de esPeriodica : 23 bits de retardo
 */
alarma_t g_alarma_crear(uint8_t ID_msg, int esPeriodica, uint32_t retardo);

/**
 * @brief Crea el campo auxiliar que hay que encolar junto a SET_ALARM
 *  para borrar la alarma
 * @param ID_msg ID del mensaje de la alarma a desprogramar
 * @return Devuelve el campo auxiliar de la alarma programado a 0ms
 */
alarma_t g_alarma_borrar(uint8_t ID_msg);

/**
 * @brief Obtiene el retardo de la alarma
 * @param alarma Alarma con formato de campo auxiliar
 * @return Devuelve el retardo de la alarma
 */
uint32_t g_alarma_retardo(alarma_t alarma);

/**
 * @brief Comprueba que la alarma es reiniciada cada vez que salta
 * @param alarma Alarma con formato de campo auxiliar
 * @return TRUE si la alarma es periódica
 */
int g_alarma_es_periodica(alarma_t alarma);

/**
 * @brief Obtiene el mensaje a encolar cuando salte la alarma
 * @param alarma Alarma con formato de campo auxiliar
 * @return Devuelve el identificador del mensaje a encolar cuando
 *  salte la alarma
 */
uint8_t g_alarma_id_msg(alarma_t alarma);

/**
 * @brief Iinicia el gestor de alarmas y los temporizadores
 */
void g_alarma_iniciar(void);

/**
 * @brief Si hay espacio, añade la alarma al conjunto de alarmas.
 *  Si la alarma ya estaba programada la reprograma con la nueva información.
 *  Si el retardo de la alarma es de 0ms la borra del conjunto.
 * @param alarma Alarma con formato de campo auxiliar
 */
void g_alarma_programar(alarma_t alarma);

/**
 * @brief Cuenta 1ms para cada alarma y comprueba las que puede disparar.
 *  Encola los mensajes de las alarmas disparadas.
 */
void g_alarma_comprobar_alarmas(void);

/**
 * @brief Tratamiento de eventos del módulo del gestor de alarmas
 * @param evento Evento a tratar
 */
void g_alarma_tratar_evento(evento_t evento);

/**
 * @brief Tratamiento de mensajes del módulo del gestor de alarmas
 * @param mensaje Mensaje a tratar
 */
void g_alarma_tratar_mensaje(msg_t mensaje);

#endif
