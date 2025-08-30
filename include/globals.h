/*+===================================================================
  File:      GLOBALS.H

  Summary:   Contains global variables used by the emulator.

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL3\SDL_keycode.h>
#include <config.h>

#define HertzToMs( hz ) ( 1.f / hz * 1000.f )

#define GetMnemonicFromWord( w )  SDL_static_cast( Uint8, ( ( ( w ) & 0xF000 ) >> 12 ) )
#define GetAddrFromWord( w )      ( ( w ) & 0x0FFF )
#define GetByteFromWord( w )      SDL_static_cast( Uint8, ( ( w ) & 0x00FF ) )
#define GetNibbleFromWord( w )    SDL_static_cast( Uint8, ( ( w ) & 0x000F ) )
#define GetXFromWord( w )         SDL_static_cast( Uint8, ( ( ( w ) & 0x0F00 ) >> 8 ) )
#define GetYFromWord( w )         SDL_static_cast( Uint8, ( ( ( w ) & 0x00F0 ) >> 4 ) )

extern const SDL_Keycode g_aKeyboardMap[ CHIP8_KEYCNT ];

#endif //GLOBALS_H
