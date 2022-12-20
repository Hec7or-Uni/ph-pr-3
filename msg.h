#ifndef MSG_H
#define MSG_H

enum Mensajes {
  SET_ALARM,  // auxData := 8 bits ID:1 bit esPeriodica:23 bits retardo
  BAJAR_PULSACION_1,
  BAJAR_PULSACION_2,
  POWER_DOWN,

  LATIDO,
  APAGAR_LATIDO,

  PEDIR_JUGADOR,
  JUGADOR,           // auxData := turno
  ENTRADA_VALIDADA,  // auxData := celda_valida

  CELDA_MARCADA,
  CONFIRMAR_JUGADA,
  JUGADA_REALIZADA,
  APAGAR_REALIZADA,

  JUGAR,     // auxData := columna
  EJECUTAR,  // auxData := mensaje a encolar
  RESET_POWERDOWN,

  PEDIR_FILA,
  DEVOLVER_FILA,

  PEDIR_CALIDAD_SERVICIO,
  PEDIR_SEGUNDOS_JUGADOS, 
  PEDIR_MINUTOS_JUGADOS,  

  CALIDAD_SERVICIO, // auxData := tiempo
  SEGUNDOS_JUGADOS, // auxData := segundos
  MINUTOS_JUGADOS,  // auxData := minutos


  CANCELAR,
  RESET,
  FIN, //auxData := ganador o 0 (empate)
  OVERFLOW_M
};

#endif
