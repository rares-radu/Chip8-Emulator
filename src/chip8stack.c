/*+===================================================================
  File:      CHIP8STACK.C

  Summary:   Contains the implementation of the stack used by the
             emulator.

  Functions: StackPush, StackPop

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#include <sal.h>
#include <SDL3\SDL_assert.h>
#include <chip8stack.h>
#include <chip8.h>

SDL_INLINE void StackPush( _In_ PCHIP8 pChip8, Uint16 wVal )
{
    SDL_assert( pChip8 != NULL );
    SDL_assert( pChip8->pRegisters->SP < CHIP8_STACKSIZ );

    pChip8->pStack->aStack[ pChip8->pRegisters->SP++ ] = wVal;
}

SDL_INLINE Uint16 StackPop( _In_ PCHIP8 pChip8 )
{
    SDL_assert( pChip8 != NULL );
    SDL_assert( pChip8->pRegisters->SP != 0 );

    return pChip8->pStack->aStack[ --pChip8->pRegisters->SP ];
}
