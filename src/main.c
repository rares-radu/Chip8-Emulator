/*+===================================================================
  File:      MAIN.C

  Summary:   Contains the entry point to the Chip8 emulator.

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#include <stdlib.h>
#include <SDL3\SDL_main.h>
#include <SDL3\SDL.h>
#include <chip8.h>
#include <helpers.h>
#include <config.h>
#include <globals.h>

int main( int argc, char* argv[] )
{
    SDL_Window*   pWindow   = NULL;
    SDL_Renderer* pRenderer = NULL;
    CHIP8         Chip8     = { 0 };
    int           iCode     = EXIT_SUCCESS;

    // Initialize a bunch of stuff
    if ( !SDL_SetAppMetadata( "Chip8 Emulator", NULL, NULL ) )
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "%s", SDL_GetError() );
        iCode = EXIT_FAILURE;
        goto Done;
    }

    if ( !SDL_Init( SDL_INIT_AUDIO | SDL_INIT_VIDEO ) )
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "%s", SDL_GetError() );
        iCode = EXIT_FAILURE;
        goto Done;
    }

    pWindow = SDL_CreateWindow( EMU_WINDOW_TITLE, EMU_WINDOW_WIDTH, EMU_WINDOW_HEIGHT, 0 );
    if ( !pWindow )
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "%s", SDL_GetError() );
        iCode = EXIT_FAILURE;
        goto Done;
    }

    pRenderer = SDL_CreateRenderer( pWindow, NULL );
    if ( !pRenderer )
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "%s", SDL_GetError() );
        iCode = EXIT_FAILURE;
        goto Done;
    }

    if ( !SDL_SetRenderLogicalPresentation(
                pRenderer,
                CHIP8_WIDTH, CHIP8_HEIGHT,
                SDL_LOGICAL_PRESENTATION_INTEGER_SCALE
                ) )
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "%s", SDL_GetError() );
        iCode = EXIT_FAILURE;
        goto Done;
    }

    if ( !InitChip8( &Chip8 ) )
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Failed to initialize Chip8 struct!" );
        iCode = EXIT_FAILURE;
        goto Done;
    }

    const char* pszROMPath;
    if ( argc == 2 )
    {
        pszROMPath = argv[ 1 ];
        SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Path to ROM provided through command line." );
    }
    else
    {
        pszROMPath = OpenFileDialog( pWindow );
        SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Path to ROM provided through file dialog." );
    }

    SDL_PathInfo FileInfo;
    if ( !SDL_GetPathInfo( pszROMPath, &FileInfo ) )
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error!", "Incorrect file path!", NULL );
        iCode = EXIT_FAILURE;
        goto Done;
    }

    SDL_IOStream* fp     = SDL_IOFromFile( pszROMPath, "rb" );
    Uint8*        pBuf   = SDL_malloc( sizeof( *pBuf ) * FileInfo.size );
    size_t        cbRead = SDL_ReadIO( fp, pBuf, FileInfo.size );
    if ( cbRead == 0 )
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "%s", SDL_GetError() );
        SDL_free( pBuf );
        SDL_CloseIO( fp );
        iCode = EXIT_FAILURE;
        goto Done;
    }

    // Load the ROM into memory
    LoadProgram( &Chip8, pBuf, FileInfo.size );

    // Free the buffer since and close the file, since the ROM is in memory
    SDL_free( pBuf );
    SDL_CloseIO( fp );
    // If the file wasn't passed through the command line, then we must free it too
    if ( argc != 2 )
    {
        SDL_free( SDL_const_cast( char*, pszROMPath ) );
    }

    while ( true )
    {
        SDL_Event Event;
        while ( SDL_PollEvent( &Event ) )
        {
            switch ( Event.type )
            {
            case SDL_EVENT_KEY_DOWN:
            {
                const Sint64 Key = MapKey( Event.key.key );
                if ( Key != -1 )
                {
                    KeyDown( Chip8.pKeyboard, Key );
                }
                break;
            }

            case SDL_EVENT_KEY_UP:
            {
                const Sint64 Key = MapKey( Event.key.key );
                if ( Key != -1 )
                {
                    KeyUp( Chip8.pKeyboard, Key );
                }
                break;
            }

            case SDL_EVENT_QUIT:
                goto Done;

            default:
                break;
            }
        }

        SDL_SetRenderDrawColor( pRenderer, 0, 0, 0, 0 );
        SDL_RenderClear( pRenderer );
        SDL_SetRenderDrawColor( pRenderer, 255, 255, 255, 0 );

        for ( size_t x = 0; x < CHIP8_WIDTH; x++ )
        {
            for ( size_t y = 0; y < CHIP8_HEIGHT; y++ )
            {
                if ( IsPixelOn( Chip8.pScreen, x, y ) )
                {
                    const SDL_FRect frect =
                    {
                        .x = SDL_static_cast( float, x ),
                        .y = SDL_static_cast( float, y ),
                        .w = 1.f,
                        .h = 1.f
                    };
                    SDL_RenderFillRect( pRenderer, &frect );
                }
            }
        }

        SDL_RenderPresent( pRenderer );

         const Uint32 u60Hz = SDL_static_cast( Uint32, HertzToMs( 60 ) ) + 1;    // 60Hz ≈ 17 ms
         if ( Chip8.pRegisters->DT > 0 )
         {
             SDL_Delay( u60Hz );
             Chip8.pRegisters->DT -= 1;
         }

         if ( Chip8.pRegisters->ST > 0 )
         {
             SDL_Beep( 9000, u60Hz * Chip8.pRegisters->ST );
             Chip8.pRegisters->ST = 0;
         }

         const Uint16 wOpcode = GetWordFromMem( Chip8.pMemory, Chip8.pRegisters->PC );
         Chip8.pRegisters->PC += 2;
         ExecInstruction( &Chip8, wOpcode );
    }

Done:
    if ( pRenderer )
    {
        SDL_DestroyRenderer( pRenderer );
    }
    if ( pWindow )
    {
        SDL_DestroyWindow( pWindow );
    }
    UninitChip8( &Chip8 );

#ifndef NDEBUG
    const SDL_AssertData* pAssertData = SDL_GetAssertionReport();
    while ( pAssertData )
    {
        SDL_LogDebug(
                SDL_LOG_CATEGORY_ASSERT,
                "'%s', %s (%s:%d), triggered %u times, always ignore: %s.",
                pAssertData->condition, pAssertData->function, pAssertData->filename,
                pAssertData->linenum, pAssertData->trigger_count,
                pAssertData->always_ignore ? "yes" : "no"
                );
        pAssertData = pAssertData->next;
    }

    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "The program terminated with %d unfreed allocations.", SDL_GetNumAllocations() );
#endif

    return iCode;
}
