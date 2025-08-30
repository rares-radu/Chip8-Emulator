/*+===================================================================
  File:      CHIP8SCREEN.H

  Summary:   Contains the implementation of the screen used by the
             emulator.

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#ifndef CHIP8_CHIP8SCREEN_H
#define CHIP8_CHIP8SCREEN_H

#include <sal.h>
#include <stdbool.h>
#include <config.h>

typedef struct CHIP8SCREEN
{
    bool abPixels[ CHIP8_WIDTH ][ CHIP8_HEIGHT ];
} CHIP8SCREEN, *PCHIP8SCREEN;

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DrawPixel

  Summary:  Turns on a pixel on the emulator's screen.

  Args:     PCHIP8SCREEN pScreen
              Pointer to a screen instance.
            size_t x
              X coordinate on the screen to draw the pixel.
            size_t y
              Y coordinate on the screen to draw the pixel.

  Returns:  void
              N/A.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern SDL_INLINE void DrawPixel(
    _In_ PCHIP8SCREEN                    pScreen,
    _In_range_( <, CHIP8_WIDTH ) size_t  x,
    _In_range_( <, CHIP8_HEIGHT ) size_t y
    );

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: IsPixelOn

  Summary:  Checks if the pixel at the provided coordinates is on.

  Args:     PCHIP8SCREEN pScreen
              Pointer to a screen instance.
            size_t x
              X coordinate on the screen to check the pixel's state.
            size_t y
              Y coordinate on the screen to check the pixel's state.

  Returns:  bool
              true if it's on, otherwise false.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
_Check_return_
extern SDL_INLINE bool IsPixelOn(
    _In_ PCHIP8SCREEN                    pScreen,
    _In_range_( <, CHIP8_WIDTH ) size_t  x,
    _In_range_( <, CHIP8_HEIGHT ) size_t y
    );

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DrawSprite

  Summary:  Draws a sprite on screen starting from the provided
            coordinates.

  Args:     PCHIP8SCREEN pScreen
              Pointer to a screen instance.
            size_t x
              X coordinate from which to start drawing.
            size_t y
              Y coordinate from which to start drawing.
            void* pvSprite
              Pointer to the sprite to draw.
            size_t cb
              Number of bytes to draw form the sprite.

  Returns:  bool
              Returns false if the drawn pixel did not overlap already
              existing sprites, otherwise true.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
_Check_return_opt_
bool DrawSprite(
        _In_ PCHIP8SCREEN                    pScreen,
        _In_range_( <, CHIP8_WIDTH ) size_t  x,
        _In_range_( <, CHIP8_HEIGHT ) size_t y,
        _In_ void*                           pvSprite,
        size_t                               cb
        );

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: ClearScreen

  Summary:  Clears the screen.

  Args:     PCHIP8SCREEN pScreen
              Pointer to a CHIP8SCREEN instance.

  Returns:  void
              N/A.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern SDL_INLINE void ClearScreen( _In_ PCHIP8SCREEN pScreen );

#endif //CHIP8_CHIP8SCREEN_H
