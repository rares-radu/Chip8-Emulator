/*+===================================================================
  File:      GLOBALS.C

  Summary:   Contains global variables used by the emulator.

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#include <SDL3\SDL_keycode.h>
#include <globals.h>

const SDL_Keycode g_aKeyboardMap[ CHIP8_KEYCNT ] =
{
  SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5,
  SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_A, SDLK_B,
  SDLK_C, SDLK_D, SDLK_E, SDLK_F
};
