/*+===================================================================
  File:      CHIP8KEYBOARD.C

  Summary:   Contains the implementation of the keyboard used by the
             emulator.

  Functions: MapKey, KeyDown, KeyUp, IsKeyDown.

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#include <SDL3\SDL_assert.h>
#include <stdint.h>
#include <globals.h>
#include <chip8keyboard.h>

_Success_( return != -1 )
Sint64 MapKey( const SDL_Keycode Keycode )
{
    for ( Sint64 i = 0; i < CHIP8_KEYCNT; i++ )
    {
        if ( g_aKeyboardMap[ i ] == Keycode )
        {
            return i;
        }
    }

    return -1;
}

SDL_INLINE void KeyDown( _In_ PCHIP8KEYBOARD pKeyboard, _In_range_( <, CHIP8_KEYCNT ) size_t dwKey )
{
    SDL_assert( pKeyboard != NULL );
    SDL_assert( dwKey < CHIP8_KEYCNT );

    pKeyboard->abKeyboard[ dwKey ] = true;
}

SDL_INLINE void KeyUp( _In_ PCHIP8KEYBOARD pKeyboard, _In_range_( <, CHIP8_KEYCNT ) size_t dwKey )
{
    SDL_assert( pKeyboard != NULL );
    SDL_assert( dwKey < CHIP8_KEYCNT );

    pKeyboard->abKeyboard[ dwKey ] = false;
}

_Check_return_
SDL_INLINE bool IsKeyDown( _In_ PCHIP8KEYBOARD pKeyboard, _In_range_( <, CHIP8_KEYCNT ) size_t dwKey )
{
    SDL_assert( pKeyboard != NULL );
    SDL_assert( dwKey < CHIP8_KEYCNT );

    return pKeyboard->abKeyboard[ dwKey ];
}
