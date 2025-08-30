/*+===================================================================
  File:      CHIP8SCREEN.C

  Summary:   Contains the implementation of the screen used by the
             emulator.

  Functions: DrawPixel, IsPixelOn, DrawSprite, ClearScreen

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#include <chip8screen.h>
#include <SDL3\SDL_assert.h>

SDL_INLINE void DrawPixel(
        _In_ PCHIP8SCREEN                    pScreen,
        _In_range_( <, CHIP8_WIDTH ) size_t  x,
        _In_range_( <, CHIP8_HEIGHT ) size_t y
        )
{
    SDL_assert( pScreen != NULL );

    pScreen->abPixels[ x ][ y ] = true;
}

_Check_return_
SDL_INLINE bool IsPixelOn(
        _In_ PCHIP8SCREEN                    pScreen,
        _In_range_( <, CHIP8_WIDTH ) size_t  x,
        _In_range_( <, CHIP8_HEIGHT ) size_t y
        )
{
    SDL_assert( pScreen != NULL );

    return pScreen->abPixels[ x ][ y ];
}

_Check_return_opt_
bool DrawSprite(
        _In_ PCHIP8SCREEN                    pScreen,
        _In_range_( <, CHIP8_WIDTH ) size_t  x,
        _In_range_( <, CHIP8_HEIGHT ) size_t y,
        _In_ void*                           pvSprite,
        size_t                               cb
        )
{
    SDL_assert( pScreen != NULL );
    SDL_assert( pvSprite != NULL );

    bool bOverlapped = false;

    // Loop over the sprite's x and y coordinates
    for ( size_t sy = 0; sy < cb; sy++ )
    {
        const Uint8 u8 = SDL_static_cast( const Uint8*, pvSprite )[ sy ];
        for ( size_t sx = 0; sx < 8; sx++ )
        {
            if ( u8 & ( 0x80u >> sx ) )
            {
                bool* pPixel = &pScreen->abPixels[ ( sx + x ) % CHIP8_WIDTH ][ ( sy + y ) % CHIP8_HEIGHT ];
                if ( *pPixel )
                {
                    bOverlapped = true;
                }
                *pPixel ^= true;
            }
        }
    }

    return bOverlapped;
}

SDL_INLINE void ClearScreen( _In_ PCHIP8SCREEN pScreen )
{
    SDL_assert( pScreen != NULL );

    SDL_zeroa( pScreen->abPixels );
}
