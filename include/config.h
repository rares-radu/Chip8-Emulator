/*+===================================================================
  File:      CONFIG.H

  Summary:   Contains macros that define various constants used by
             the emulator.

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#ifndef CONFIG_H
#define CONFIG_H

#include <SDL3\SDL_stdinc.h>

#define CHIP8_REGCNT        16
#define CHIP8_STACKSIZ      16
#define CHIP8_KEYCNT        16
#define CHIP8_MEMSIZ        4096
#define CHIP8_WIDTH         64
#define CHIP8_HEIGHT        32
#define CHIP8_CHARSET_ADDR  0x000
#define CHIP8_LOAD_ADDR     0x200

#define EMU_WINDOW_TITLE        "Chip8"
#define EMU_WINDOW_MULTIPLIER   10
#define EMU_WINDOW_WIDTH        ( CHIP8_WIDTH * EMU_WINDOW_MULTIPLIER )
#define EMU_WINDOW_HEIGHT       ( CHIP8_HEIGHT * EMU_WINDOW_MULTIPLIER )

SDL_COMPILE_TIME_ASSERT( IsWindowRatioValid, EMU_WINDOW_WIDTH == EMU_WINDOW_HEIGHT * 2 );

#endif //CONFIG_H
