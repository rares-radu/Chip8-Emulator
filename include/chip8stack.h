/*+===================================================================
  File:      CHIP8STACK.H

  Summary:   Contains the implementation of the stack used by the
             emulator.

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#ifndef CHIP8STACK_H
#define CHIP8STACK_H

#include <sal.h>
#include <SDL3\SDL_stdinc.h>
#include <config.h>

typedef struct CHIP8 CHIP8, *PCHIP8;

typedef struct CHIP8STACK
{
    Uint16 aStack[ CHIP8_STACKSIZ ];
} CHIP8STACK, *PCHIP8STACK;

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: StackPush

  Summary:  Pushes a 16-bit value onto the stack.

  Args:     PCHIP8 pChip8
              Pointer to a CHIP8 instance.
            Uint16 wVal
              Value to push onto the stack.

  Returns:  void
              N/A.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern SDL_INLINE void StackPush( _In_ PCHIP8 pChip8, Uint16 wVal );

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: StackPop

  Summary:  Pops a value off the stack and returns it.

  Args:     PCHIP8 pChip8
              Pointer to a CHIP8 instance.

  Returns:  Uint16
              Value popped off the stack.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern SDL_INLINE Uint16 StackPop( _In_ PCHIP8 pChip8 );

#endif //CHIP8STACK_H
