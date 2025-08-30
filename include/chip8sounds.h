/*+===================================================================
  File:      CHIP8SOUNDS.H

  Summary:   Contains functions that synthesize sounds made by the
             emulator.

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#ifndef CHIP8_CHIP8SOUNDS_H
#define CHIP8_CHIP8SOUNDS_H

#include <SDL3\SDL_stdinc.h>

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: SDL_Beep

  Summary:  Plays a beeping sound.

  Args:     int iFreq
              Sample rate.
            Uint32 uDuration
              Duration in ms the sound will play for.

  Returns:  void
              N/A.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
void SDL_Beep( int iFreq, Uint32 uDuration );

#endif //CHIP8_CHIP8SOUNDS_H
