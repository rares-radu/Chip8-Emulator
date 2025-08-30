/*+===================================================================
  File:      CHIP8SOUNDS.C

  Summary:   Contains functions that synthesize sounds made by the
             emulator.

  Functions: SDL_Beep

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#include <chip8screen.h>
#include <SDL3\SDL.h>

static SDL_AudioStream* g_AudioStream = NULL;

/*F+F+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: InitAudioStream

  Summary:  Initializes the audio stream according to the
            specifications passed.

  Args:     const SDL_AudioSpec* pAudioSpec
              Pointer to an SDL_AudioSpec structure.

  Returns:  bool
              true if initialization was successful, otherwise false.
-----------------------------------------------------------------F-F*/
_Check_return_
static bool InitAudioStream( _In_ const SDL_AudioSpec* pAudioSpec )
{
    SDL_assert( pAudioSpec != NULL );

    g_AudioStream = SDL_OpenAudioDeviceStream( SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, pAudioSpec, NULL, NULL );
    if ( !g_AudioStream )
    {
        return false;
    }

    SDL_ResumeAudioStreamDevice( g_AudioStream );
    return true;
}

void SDL_Beep( int iFreq, Uint32 uDuration )
{
    const SDL_AudioSpec AudioSpec = { .freq = iFreq, .format = SDL_AUDIO_F32, .channels = 1 };
    if ( !g_AudioStream && !InitAudioStream( &AudioSpec ) )
    {
        return;
    }

    const size_t nSamples = ( 48000 * uDuration ) / 1000;
    float*       pfBuf    = SDL_static_cast( float*, SDL_malloc( nSamples * sizeof( *pfBuf ) ) );
    float        fPhase   = 0.f;
    const float  fStep    = ( 2.f * SDL_PI_F * SDL_static_cast( float, iFreq ) ) / 48000.f;
    for ( Uint64 i = 0; i < nSamples; i++ )
    {
        pfBuf[ i ] = SDL_sinf( fPhase );
        fPhase += fStep;
    }
    SDL_PutAudioStreamData( g_AudioStream, pfBuf, SDL_static_cast( int, nSamples ) * sizeof( *pfBuf ) );
    SDL_free( pfBuf );
}
