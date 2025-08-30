/*+===================================================================
  File:      CHIP8REGISTERS.H

  Summary:   Contains the implementation of the registers used by the
             emulator.

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#ifndef CHIP8REGISTERS_H
#define CHIP8REGISTERS_H

#include <SDL3\SDL_stdinc.h>
#include <config.h>

typedef struct CHIP8REGISTERS
{
    Uint8  V[ CHIP8_REGCNT ];
    Uint16 I;
    Uint8  DT;
    Uint8  ST;
    Uint16 PC;
    Uint8  SP;
} CHIP8REGISTERS, *PCHIP8REGISTERS;

#endif //CHIP8REGISTERS_H
