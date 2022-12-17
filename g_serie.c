#include "g_serie.h"

extern char letra;

void g_serie_tratar_evento(evento_t evento) {
  switch (evento.ID_evento) {
    case CARACTER_RECIBIDO:
      letra = evento.auxData;
      break;
    case CARACTER_ENVIADO:
      uart0_continuar_envio();
  }
}

void g_serie_tratar_mensaje(msg_t mensaje) {
  /*switch (mensaje.ID_msg) {
    
  }*/
}

void g_serie_iniciar(void) { 
  uart0_iniciar(); 
  uart0_enviar_array("Hola");
}
