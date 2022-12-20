#include "cola_asyn.h"
#include "cola_msg.h"
#include "conecta4_2022.h"
#include "contadores.h"
#include "g_alarmas.h"
#include "g_boton.h"
#include "g_energia.h"
#include "g_estadisticas.h"
#include "g_io.h"
#include "g_serie.h"
#include "llamadas_sistema.h"

volatile char letra;

/**
 * @brief Función que prueba la respuesta del sistema ante el overflow
 * @param case 1: Test Overflow para la cola de eventos
 *             2: Test Overflow para la cola de mensajes
 *             default: No se realiza ninguna prueba
 */
void test_overflow(int _case) {
  switch (_case) {
    case 1:
      for (int i = 0; i <= COLA_EVENTOS_SIZE; i++) {
        cola_encolar_eventos(PULSACION, i, 0);
      }
      break;
    case 2:
      for (int i = 0; i <= COLA_MSG_SIZE; i++) {
        cola_encolar_msg(LATIDO, 0);
      }
      break;
  }
}

void init(void) {
  g_io_iniciar();
  g_boton_iniciar();
  g_alarma_iniciar();
  g_energia_iniciar();
  g_serie_iniciar();

  WD_init(1);
  WD_feed();
}

// static volatile uint32_t time;
// static volatile uint32_t I;
// static volatile uint32_t F;

int main(void) {
  // disable_irq();
  // enable_irq();
  // disable_irq_fiq();
  // enable_irq_fiq();

  // time = clock_gettime();
  // I = read_IRQ_bit();
  // F = read_FIQ_bit();

  // volatile uint32_t min = 0, seg = 0;
  // while (1) {
  // 	uint32_t m, s;
  //   RTC_leer(&m, &s);
  // 	min = m;
  // 	//seg = s;
  //   if ((s & 1) != 0) {
  //     seg = s;
  //   }
  // }

  int hay_evento, hay_msg;
  init();
  test_overflow(0);
  while (1) {
    hay_evento = cola_hay_eventos();
    if (hay_evento) {
      evento_t evento = cola_desencolar_eventos();
      g_alarma_tratar_evento(evento);
      g_io_tratar_evento(evento);
      g_serie_tratar_evento(evento);
      g_boton_tratar_evento(evento);
    }
    hay_msg = cola_hay_msg();
    if (hay_msg) {
      msg_t msg = cola_desencolar_msg();
      g_alarma_tratar_mensaje(msg);
      g_energia_tratar_mensaje(msg);
      g_io_tratar_mensaje(msg);
      g_serie_tratar_mensaje(msg);
      g_boton_tratar_mensaje(msg);
      conecta4_tratar_mensaje(msg);
      // El de estadísticas es el último para medir el
      // tiempo que tardan todos
      g_estadisticas_tratar_mensaje(msg);
    }
    if (!hay_evento && !hay_msg) g_energia_idle();

    WD_feed();
  }
}
