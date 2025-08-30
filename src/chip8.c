/*+===================================================================
  File:      CHIP8.C

  Summary:   Contains various structures used by the emulator.

  Functions: InitChip8, UninitChip8, ExecInstruction, LoadProgram

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#include <stdbool.h>
#include <intrin.h>
#include <SDL3\SDL.h>
#include <chip8.h>
#include <globals.h>

static const Uint8 CHIP8_CHARSET[] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

_Success_( return != false )
bool InitChip8(
        _In_ _Pre_satisfies_( SDL_memcmp( pChip8, &( CHIP8 ){ 0 }, sizeof( *pChip8 ) ) == 0 ) PCHIP8 pChip8
        )
{
    SDL_assert( pChip8 != NULL );
    SDL_assert( SDL_memcmp( pChip8, &( CHIP8 ){ 0 }, sizeof( *pChip8 ) ) == 0 );

    pChip8->pMemory = SDL_calloc( 1, sizeof( *pChip8->pMemory ) );
    if ( !pChip8->pMemory )
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Could not allocate memory for CHIP8MEMORY!" );
        goto Failed;
    }

    SDL_memcpy( pChip8->pMemory->aMemory, CHIP8_CHARSET, SDL_arraysize( CHIP8_CHARSET ) );

    pChip8->pRegisters = SDL_calloc( 1, sizeof( *pChip8->pRegisters ) );
    if ( !pChip8->pRegisters )
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Could not allocate memory for CHIP8REGISTERS!" );
        goto Failed;
    }

    pChip8->pStack = SDL_calloc( 1, sizeof( *pChip8->pStack ) );
    if ( !pChip8->pStack )
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Could not allocate memory for CHIP8STACK!" );
        goto Failed;
    }

    pChip8->pKeyboard = SDL_calloc( 1, sizeof( *pChip8->pKeyboard ) );
    if ( !pChip8->pKeyboard )
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Could not allocate memory for CHIP8KEYBOARD!" );
        goto Failed;
    }

    pChip8->pScreen = SDL_calloc( 1, sizeof( *pChip8->pScreen ) );
    if ( !pChip8->pScreen )
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Could not allocate memory for CHIP8SCREEN!" );
        goto Failed;
    }

    return true;

Failed:
    SDL_free( pChip8->pMemory );
    pChip8->pMemory = NULL;

    SDL_free( pChip8->pRegisters );
    pChip8->pRegisters = NULL;

    SDL_free( pChip8->pStack );
    pChip8->pStack = NULL;

    SDL_free( pChip8->pKeyboard );
    pChip8->pKeyboard = NULL;

    SDL_free( pChip8->pScreen );
    pChip8->pScreen = NULL;

    return false;
}

void UninitChip8( _In_ PCHIP8 pChip8 )
{
    SDL_assert( pChip8 != NULL );

    SDL_free( pChip8->pMemory );
    SDL_free( pChip8->pRegisters );
    SDL_free( pChip8->pStack );
    SDL_free( pChip8->pKeyboard );
    SDL_free( pChip8->pScreen );
}

void ExecInstruction( _In_ PCHIP8 pChip8, Uint16 wInstruction )
{
    SDL_assert( pChip8 != NULL );

#ifndef NDEBUG
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Executing 0x%X...", wInstruction );
#endif

    switch ( wInstruction )
    {
    // CLS
    case 0x00E0:
        ClearScreen( pChip8->pScreen );
        break;

    // RET
    case 0x00EE:
        pChip8->pRegisters->PC = StackPop( pChip8 );
        break;

    default:
    {
        switch ( GetMnemonicFromWord( wInstruction ) )
        {
        // JP addr
        case 0x1:
            pChip8->pRegisters->PC = GetAddrFromWord( wInstruction );
            break;

        // CALL addr
        case 0x2:
            StackPush( pChip8, pChip8->pRegisters->PC );
            pChip8->pRegisters->PC = GetAddrFromWord( wInstruction );
            break;

        // SE Vx, byte
        case 0x3:
            if ( pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] == GetByteFromWord( wInstruction ) )
            {
                pChip8->pRegisters->PC += 2;
            }
            break;

        // SNE Vx, byte
        case 0x4:
            if ( pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] != GetByteFromWord( wInstruction ) )
            {
                pChip8->pRegisters->PC += 2;
            }
            break;

        // SE Vx, Vy
        case 0x5:
            if ( GetNibbleFromWord( wInstruction ) == 0 )
            {
                if ( pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] == pChip8->pRegisters->V[ GetYFromWord( wInstruction ) ] )
                {
                    pChip8->pRegisters->PC += 2;
                }
            }
            else
            {
                SDL_LogWarn( SDL_LOG_CATEGORY_APPLICATION, "Unknown instruction 0x%X, skipping...", wInstruction );
            }
            break;

        // LD Vx, byte
        case 0x6:
            pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] = GetByteFromWord( wInstruction );
            break;

        // ADD Vx, byte
        case 0x7:
            pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] += GetByteFromWord( wInstruction );
            break;

        case 0x8:
        {
            switch ( wInstruction & 0x000F )
            {
            // LD Vx, Vy
            case 0x0:
                pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] = pChip8->pRegisters->V[ GetYFromWord( wInstruction ) ];
                break;

            // OR Vx, Vy
            case 0x1:
                pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] |= pChip8->pRegisters->V[ GetYFromWord( wInstruction ) ];
                break;

            // AND Vx, Vy
            case 0x2:
                pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] &= pChip8->pRegisters->V[ GetYFromWord( wInstruction ) ];
                break;

            // XOR Vx, Vy
            case 0x3:
                pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] ^= pChip8->pRegisters->V[ GetYFromWord( wInstruction ) ];
                break;

            // ADD Vx, Vy
            case 0x4:
                pChip8->pRegisters->V[ 0xF ] = _addcarry_u8(
                    0,
                    pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ],
                    pChip8->pRegisters->V[ GetYFromWord( wInstruction ) ],
                    &pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ]
                    );
                break;

            // SUB Vx, Vy
            case 0x5:
                pChip8->pRegisters->V[ 0xF ] = !_subborrow_u8(
                    0,
                    pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ],
                    pChip8->pRegisters->V[ GetYFromWord( wInstruction ) ],
                    &pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ]
                    );
                break;

            // SHR Vx {, Vy}
            case 0x6:
                pChip8->pRegisters->V[ 0xF ] = pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] & 0x1;
                pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] >>= 1;
                break;

            // SUBN Vx, Vy
            case 0x7:
                pChip8->pRegisters->V[ 0xF ] = !_subborrow_u8(
                    0,
                    pChip8->pRegisters->V[ GetYFromWord( wInstruction ) ],
                    pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ],
                    &pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ]
                    );
                break;

            // SHL Vx {, Vy}
            case 0xE:
                pChip8->pRegisters->V[ 0xF ] = ( pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] >> 7 ) & 0x1;
                pChip8->pRegisters->V[GetXFromWord(wInstruction)] <<= 1;
                break;

            default:
                SDL_LogWarn( SDL_LOG_CATEGORY_APPLICATION, "Unknown instruction 0x%X, skipping...", wInstruction );
                break;
            }
            break;
        }

        // SNE Vx, Vy
        case 0x9:
            if ( GetNibbleFromWord( wInstruction ) == 0 )
            {
                if ( pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] != pChip8->pRegisters->V[ GetYFromWord( wInstruction ) ] )
                {
                    pChip8->pRegisters->PC += 2;
                }
            }
            else
            {
                SDL_LogWarn( SDL_LOG_CATEGORY_APPLICATION, "Unknown instruction 0x%X, skipping...", wInstruction );
            }
            break;

        // LD I, addr
        case 0xA:
            pChip8->pRegisters->I = GetAddrFromWord( wInstruction );
            break;

        // JP V0, addr
        case 0xB:
            pChip8->pRegisters->PC = GetAddrFromWord( wInstruction ) + pChip8->pRegisters->V[ 0x0 ];
            break;

        // RND Vx, byte
        case 0xC:
            pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] = SDL_static_cast( Uint8, SDL_rand( 256 ) ) & GetByteFromWord( wInstruction );
            break;

        // DRW Vx, Vy, nibble
        case 0xD:
        {
            void* pvSprite = &pChip8->pMemory->aMemory[ pChip8->pRegisters->I ];
            pChip8->pRegisters->V[ 0xF ] = SDL_static_cast( Uint8, DrawSprite(
                                                                pChip8->pScreen,
                                                                pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ],
                                                                pChip8->pRegisters->V[ GetYFromWord( wInstruction ) ],
                                                                pvSprite,
                                                                GetNibbleFromWord( wInstruction )
                                                            ) );
            break;
        }

        case 0xE:
        {
            switch ( wInstruction & 0x00FF )
            {
            // SKP Vx
            case 0x9E:
                if ( IsKeyDown( pChip8->pKeyboard, pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] ) )
                {
                    pChip8->pRegisters->PC += 2;
                }
                break;

            // SKNP Vx
            case 0xA1:
                if ( !IsKeyDown( pChip8->pKeyboard, pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] ) )
                {
                    pChip8->pRegisters->PC += 2;
                }
                break;

            default:
                SDL_LogWarn( SDL_LOG_CATEGORY_APPLICATION, "Unknown instruction 0x%X, skipping...", wInstruction );
                break;
            }
            break;
        }

        case 0xF:
        {
            switch ( wInstruction & 0x00FF )
            {
            // LD Vx, DT
            case 0x07:
                pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] = pChip8->pRegisters->DT;
                break;

            // LD Vx, K
            case 0x0A:
            {
                SDL_Event Event;
                while ( SDL_WaitEvent( &Event ) )
                {
                    if ( Event.type == SDL_EVENT_KEY_DOWN )
                    {
                        const Sint64 Key = MapKey( Event.key.key );
                        if ( Key != -1 )
                        {
                            pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] = SDL_static_cast( Uint8, Key );
                            break;
                        }
                    }
                }
                break;
            }

            // LD DT, Vx
            case 0x15:
                pChip8->pRegisters->DT = pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ];
                break;

            // LD ST, Vx
            case 0x18:
                pChip8->pRegisters->ST = pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ];
                break;

            // ADD I, Vx
            case 0x1E:
                pChip8->pRegisters->I += pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ];
                break;

            // LD F, Vx
            case 0x29:
                // All sprites are 5 bytes long and are stored in order
                pChip8->pRegisters->I = pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ] * 5;
                break;

            // LD B, Vx
            case 0x33:
            {
                Uint8 u8 = pChip8->pRegisters->V[ GetXFromWord( wInstruction ) ];
                SetMemory( pChip8->pMemory, pChip8->pRegisters->I, u8 / 100 );
                SetMemory( pChip8->pMemory, pChip8->pRegisters->I + 1, ( u8 / 10 ) % 10 );
                SetMemory( pChip8->pMemory, pChip8->pRegisters->I + 2, u8 % 10 );
                break;
            }

            // LD [I], Vx
            case 0x55:
                SDL_memcpy(
                        &pChip8->pMemory->aMemory[ pChip8->pRegisters->I ],
                        pChip8->pRegisters->V,
                        ( GetXFromWord( wInstruction ) + 1 ) * sizeof( pChip8->pRegisters->V[ 0 ] )
                        );
                break;

            // LD Vx, [I]
            case 0x65:
                SDL_memcpy(
                        pChip8->pRegisters->V,
                        &pChip8->pMemory->aMemory[ pChip8->pRegisters->I ],
                        ( GetXFromWord( wInstruction ) + 1 ) * sizeof( pChip8->pMemory->aMemory[ 0 ] )
                        );
                break;

            default:
                SDL_LogWarn( SDL_LOG_CATEGORY_APPLICATION, "Unknown instruction 0x%X, skipping...", wInstruction );
                break;
            }
            break;
        }

        default:
            SDL_LogWarn( SDL_LOG_CATEGORY_APPLICATION, "Unknown instruction 0x%X, skipping...", wInstruction );
            break;
        }
        break;
    }
    }
}

SDL_INLINE void LoadProgram(
        _In_ PCHIP8                   pChip8,
        _In_reads_bytes_( cb ) Uint8* pBuf,
        const size_t                  cb
        )
{
    SDL_assert( pChip8 != NULL );
    SDL_assert( pBuf != NULL );
    SDL_assert( cb + CHIP8_LOAD_ADDR < CHIP8_MEMSIZ );

    SDL_memcpy( &pChip8->pMemory->aMemory[ CHIP8_LOAD_ADDR ], pBuf, cb );
    pChip8->pRegisters->PC = CHIP8_LOAD_ADDR;
}
