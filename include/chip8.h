/*+===================================================================
  File:      CHIP8.H

  Summary:   Contains various structures used by the emulator.

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#ifndef CHIP8_H
#define CHIP8_H

#include <stdbool.h>
#include <chip8memory.h>
#include <chip8registers.h>
#include <chip8stack.h>
#include <chip8keyboard.h>
#include <chip8screen.h>
#include <chip8sounds.h>

typedef struct CHIP8
{
    PCHIP8MEMORY    pMemory;
    PCHIP8REGISTERS pRegisters;
    PCHIP8STACK     pStack;
    PCHIP8KEYBOARD  pKeyboard;
    PCHIP8SCREEN    pScreen;
} CHIP8, *PCHIP8;

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: InitChip8

  Summary:  Allocates and zeroes memory for all members of a CHIP8
            struct.

  Args:     PCHIP8 pChip8
              Pointer to a CHIP8 instance.

  Returns:  bool
              True on success, false on failure.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
_Success_( return != false )
bool InitChip8(
        _In_ _Pre_satisfies_( SDL_memcmp( pChip8, &( CHIP8 ){ 0 }, sizeof( *pChip8 ) ) == 0 ) PCHIP8 pChip8
        );

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: UninitChip8

  Summary:  Frees all memory allocated for the structures used by
            Chip8.

  Args:     PCHIP8 pChip8
              Pointer to a CHIP8 instance.

  Returns:  void
              N/A.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
void UninitChip8( _In_ PCHIP8 pChip8 );

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: ExecInstruction

  Summary:  Executes a Chip-8 instruction.

  Args:     PCHIP8 pChip8
              Pointer to a CHIP8 instance.
            Uint16 wInstruction
              Chip-8 instruction to execute.

  Returns:  void
              N/A.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
void ExecInstruction( _In_ PCHIP8 pChip8, Uint16 wInstruction );

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: LoadProgram

  Summary:  Loads a Chip8 program into memory.

  Args:     PCHIP8 pChip8
              Pointer to a CHIP8 instance.
            Uint8* pBuf
              Buffer from which to load the program.
            size_t cb
              Size of buffer in bytes.

  Returns:  void
              N/A.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern SDL_INLINE void LoadProgram(
        _In_ PCHIP8                   pChip8,
        _In_reads_bytes_( cb ) Uint8* pBuf,
        size_t                        cb
        );

#endif //CHIP8_H
