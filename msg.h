#ifndef MSG_H
#define MSG_H

enum Mensajes {
  SET_ALARM,  // auxData := 8 bits ID:1 bit esPeriodica:23 bits retardo
  BAJAR_PULSACION_1,
  BAJAR_PULSACION_2,
  POWER_DOWN,

  LATIDO,
  APAGAR_LATIDO,
  JUGADOR,           // auxData := turno
  LEER_ENTRADA,      // es periódica
  VALIDAR_ENTRADA,   // auxData := columna
  ENTRADA_VALIDADA,  // auxData := celda_valida
  JUGADA_REALIZADA,
  APAGAR_REALIZADA,
  JUGAR,
  COMPROBACION_REALIZADA,
  EJECUTAR,  // auxData := mensaje a encolar
  ENTRADA_ACTUALIZADA,

  RESET,
  FIN,
  OVERFLOW_M
};

#endif
