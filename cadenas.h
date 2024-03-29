/**
 * @file cadenas.h
 * @authors: Fernando Lahoz & Héctor Toral
 * @date: 22/09/2022
 * @description: Declara las cadenas de texto que se muestran en la pantalla
 */

#ifndef CADENAS_H
#define CADENAS_H

enum Cadenas {
  CADENA_FILA1 = 0xF1,
  CADENA_FILA2 = 0xF2,
  CADENA_FILA3 = 0xF3,
  CADENA_FILA4 = 0xF4,
  CADENA_FILA5 = 0xF5,
  CADENA_FILA6 = 0xF6,

  CADENA_CALIDAD_SERVICIO = 0xFF,
  CADENA_SEGUNDOS_JUGADOS = 0xFE,
  CADENA_MINUTOS_JUGADOS = 0xFD,

  CADENA_CABECERA1 = 0,
  CADENA_CABECERA2 = 1,
  CADENA_CABECERA3 = 2,
  CADENA_CABECERA4 = 3,
  CADENA_CABECERA5 = 4,
  CADENA_CABECERA6 = 5,
  CADENA_CABECERA7 = 6,
  CADENA_CABECERA8 = 7,
  CADENA_CABECERA9 = 8,
  CADENA_CABECERA10 = 9,
  CADENA_CABECERA11 = 10,
  CADENA_CABECERA12 = 11,
  CADENA_CABECERA13 = 12,
  CADENA_CABECERA14 = 13,
  CADENA_CABECERA15 = 14,
  CADENA_CABECERA16 = 15,
  CADENA_CABECERA17 = 16,
  CADENA_CABECERA18 = 17,
  CADENA_CABECERA19 = 18,
  CADENA_CABECERA20 = 19,

  // Alias 16 - 19
  CADENA_COMENZAR1 = 16,
  CADENA_COMENZAR2 = 17,
  CADENA_COMENZAR3 = 18,
  CADENA_COMENZAR4 = 19,

  CADENA_TURNO_BLANCAS = 20,
  CADENA_TURNO_NEGRAS = 21,

  CADENA_COLUMNA_NO_VALIDA = 22,

  CADENA_CANCELAR1 = 23,
  CADENA_CANCELAR2 = 24,
  CADENA_CANCELADO = 25,

  CADENA_BASE1 = 26,
  CADENA_BASE2 = 27,

  CADENA_GANAN_BLANCAS = 28,
  CADENA_GANAN_NEGRAS = 29,
  CADENA_EMPATE = 30,
  CADENA_RESET = 31,
  CADENA_FIN = 32,

  NUM_CADENAS = 33
};

static char *cadenas[NUM_CADENAS] = {
    "--------- Conecta 4 ---------\n\n",   //  0   = CADENA_CABECERA1
    " Jugad por turnos e intentad\n",      //  1   = CADENA_CABECERA2
    " alinear 4 fichas de vuestro\n",      //  2   = CADENA_CABECERA3
    "     color para ganar.\n\n",          //  3   = CADENA_CABECERA4
    "Usad el comando #C(1-7)! para\n",     //  4   = CADENA_CABECERA5
    " introducir una ficha en una\n",      //  5   = CADENA_CABECERA6
    "          columna.\n\n",              //  6   = CADENA_CABECERA7
    " El boton RESET reinicia la\n",       //  7   = CADENA_CABECERA8
    "  partida. El boton CANCEL\n",        //  8   = CADENA_CABECERA9
    " anula el ultimo movimiento\n",       //  9   = CADENA_CABECERA10
    "si se pulsa antes de que pase\n",     //  10  = CADENA_CABECERA11
    "un segundo. Los botones estan\n",     //  11  = CADENA_CABECERA12
    "  disponibles en la pestana\n",       //  12  = CADENA_CABECERA13
    "    \"View/Toolbox Window\".\n\n",    //  13  = CADENA_CABECERA14
    "  El comando #END! termina\n",        //  14  = CADENA_CABECERA15
    "         la partida.\n\n",            //  15  = CADENA_CABECERA16
    "-----------------------------\n",     //  16  = CADENA_CABECERA17
    "  Pulsa un boton o ejecuta\n",        //  17  = CADENA_CABECERA18
    " #NEW! para comenzar jugar.\n",       //  18  = CADENA_CABECERA19
    "-----------------------------\n\n",   //  19  = CADENA_CABECERA20
    "   || Turno de Blancas ||\n\n",       //  20  = CADENA_TURNO_BLANCAS
    "   || Turno de Negras  ||\n\n",       //  21  = CADENA_TURNO_NEGRAS
    "!! -- Columna no valida -- !!\n\n",   //  22  = CADENA_COLUMNA_NO_VALIDA
    "!! -- Pulsa CANCEL para -- !!\n",     //  23  = CADENA_CANCELAR1
    "           cancelar\n\n",             //  24  = CADENA_CANCELAR2
    "# -- Movimiento cancelado -- #\n\n",  //  25  = CADENA_CANCELAR3
    "      ----------------\n",            //  26  = CADENA_BASE1
    "      -|1|2|3|4|5|6|7|\n\n",          //  27  = CADENA_BASE2
    "===== Ganan las Blancas =====\n\n",   //  28  = CADENA_GANAN_BLANCAS
    "===== Ganan las Negras  =====\n\n",   //  29  = CADENA_GANAN_NEGRAS
    "=========== Empate ==========\n\n",   //  30  = CADENA_EMPATE
    "----------- RESET -----------\n\n",   //  31  = CADENA_RESET
    "------ FIN DE PARTIDA -------\n\n"    //  32  = CADENA FIN
};

#endif
