/*+===================================================================
  File:      CHIP8MEMORY.C

  Summary:   Contains the implementation of the memory used by the
             emulator.

  Functions: SetMemory, GetByteFromMem

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#include <stdlib.h>
#include <intrin.h>
#include <SDL3\SDL_assert.h>
#include <chip8memory.h>

SDL_INLINE void SetMemory( _In_ PCHIP8MEMORY pMemory, _In_range_( <, CHIP8_MEMSIZ ) size_t i, Uint8 bValue )
{
    SDL_assert( pMemory != NULL );
    SDL_assert( i < CHIP8_MEMSIZ );

    pMemory->aMemory[ i ] = bValue;
}

SDL_INLINE Uint8 GetByteFromMem( _In_ PCHIP8MEMORY pMemory, _In_range_( <, CHIP8_MEMSIZ ) size_t i )
{
    SDL_assert( pMemory != NULL );
    SDL_assert( i < CHIP8_MEMSIZ );

    return pMemory->aMemory[ i ];
}

SDL_INLINE Uint16 GetWordFromMem( _In_ PCHIP8MEMORY pMemory, _In_range_( <, CHIP8_MEMSIZ ) size_t i )
{
    SDL_assert( pMemory != NULL );
    SDL_assert( i < CHIP8_MEMSIZ );

    Uint16 w;
    SDL_memcpy( &w, &pMemory->aMemory[ i ], sizeof( w ) );
    return _byteswap_ushort( w );
}
