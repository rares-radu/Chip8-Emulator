/*+===================================================================
  File:      CHIP8MEMORY.H

  Summary:   Contains the implementation of the memory used by the
             emulator.

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#ifndef CHIP8MEMORY_H
#define CHIP8MEMORY_H

#include <sal.h>
#include <SDL3\SDL_stdinc.h>
#include <config.h>

typedef struct CHIP8MEMORY
{
    Uint8 aMemory[ CHIP8_MEMSIZ ];
} CHIP8MEMORY, *PCHIP8MEMORY;

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: SetMemory

  Summary:  Sets a specific memory fragment to an 8-bit value.

  Args:     PCHIP8MEMORY pMemory
              Pointer to a virtual memory instance.
            size_t i
              Index of the memory fragment to modify.
            Uint8 bValue
              Value to change the memory fragment to.

  Returns:  void
              N/A.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern SDL_INLINE void SetMemory( _In_ PCHIP8MEMORY pMemory, _In_range_( <, CHIP8_MEMSIZ ) size_t i, Uint8 bValue );

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: GetByteFromMem

  Summary:  Gets the value located at the memory fragment indicated
            by i.

  Args:     PCHIP8MEMORY pMemory
              Pointer to a virtual memory instance.
            size_t i
              Index of the memory fragment.

  Returns:  Uint8
              Value located at the memory fragment indicated by i.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern SDL_INLINE Uint8 GetByteFromMem( _In_ PCHIP8MEMORY pMemory, _In_range_( <, CHIP8_MEMSIZ ) size_t i );

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: GetWordFromMem

  Summary:  Gets the Chip8 instruction located at the memory fragment
            indicated by `i`.

  Args:     PCHIP8MEMORY pMemory
              Pointer to a virtual memory instance.
            size_t i
              Index of the memory fragment.

  Returns:  Uint16
              Chip8 instruction located at the memory fragment
              indicated by `i`.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern SDL_INLINE Uint16 GetWordFromMem( _In_ PCHIP8MEMORY pMemory, _In_range_( <, CHIP8_MEMSIZ ) size_t i );

#endif //CHIP8MEMORY_H
