/*+===================================================================
  File:      HELPERS.C

  Summary:   Contains various miscellaneous functions.

  Functions: OpenFileDialog

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#include <Windows.h>
#include <SDL3\SDL.h>

typedef struct OPENCTX
{
    SDL_Semaphore* pSemaphore;
    const char*    pszPath;
    int            iFilter;
} OPENCTX, *POPENCTX;

/*F+F+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: OnOpen

  Summary:  Callback function that returns the file the user chose
            from the file dialog via `pUserdata`.

  Args:     void* pUserdata
              Pointer to an OPENCTX instance, which will hold the
              path to the file the user chose.
            const char* const* pFilelist
              Pointer to an array of files the user chose from the
              dialog window.
            int iFilter
              Index of the selected filter.

  Returns:  void
              N/A.
-----------------------------------------------------------------F-F*/
static void SDLCALL OnOpen( _In_ void* pUserdata, _In_reads_opt_( 1 ) const char* _In_opt_ const* pFilelist, int iFilter )
{
    POPENCTX pCtx = SDL_static_cast( POPENCTX, pUserdata );

    if ( pFilelist && pFilelist[ 0 ] )
    {
        pCtx->pszPath = SDL_strdup( pFilelist[ 0 ] );
    }
    else
    {
        pCtx->pszPath = NULL;
    }
    pCtx->iFilter = iFilter;

    SDL_SignalSemaphore( pCtx->pSemaphore );
}

_Ret_maybenull_z_
const char* OpenFileDialog( _In_opt_ SDL_Window* pWindow )
{
    static const SDL_DialogFileFilter aFilters[] =
    {
        { "Chip8 ROMs", "ch8" },
        { "All files", "*" }
    };

    OPENCTX ctx    = { 0 };
    ctx.pSemaphore = SDL_CreateSemaphore( 0 );
    if ( !ctx.pSemaphore )
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "CreateSemaphore failed: %s", SDL_GetError() );
        return NULL;
    }

    SDL_ShowOpenFileDialog(
            OnOpen,
            &ctx,
            pWindow,
            aFilters, SDL_arraysize( aFilters ),
            NULL,
            false
            );

    while ( !SDL_WaitSemaphoreTimeout( ctx.pSemaphore, 50 ) )
    {
        SDL_PumpEvents();
    }
    SDL_DestroySemaphore( ctx.pSemaphore );

    return ctx.pszPath;
}
