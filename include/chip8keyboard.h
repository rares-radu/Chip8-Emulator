/*+===================================================================
  File:      CHIP8KEYBOARD.H

  Summary:   Contains the implementation of the keyboard used by the
             emulator.

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#ifndef CHIP8KEYBOARD_H
#define CHIP8KEYBOARD_H

#include <SDL3\SDL_keycode.h>
#include <stdbool.h>
#include <config.h>

typedef struct CHIP8KEYBOARD
{
    bool abKeyboard[ CHIP8_KEYCNT ];
} CHIP8KEYBOARD, *PCHIP8KEYBOARD;

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: MapKey

  Summary:  Maps a keyboard key to a virtual key.

  Args:     SDL_Keycode Keycode
              Keyboard keycode.

  Returns:  Sint64
              The virtual key representation to be used with the
              rest of the functions that manipulate the virtual
              keyboard.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
_Success_( return != -1 )
Sint64 MapKey( SDL_Keycode Keycode );

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: KeyDown

  Summary:  Presses down the specified key.

  Args:     PCHIP8KEYBOARD pKeyboard
              Pointer to the virtual keyboard.
            size_t dwKey
              Key to press down.

  Returns:  void
              N/A.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern SDL_INLINE void KeyDown( _In_ PCHIP8KEYBOARD pKeyboard, _In_range_( <, CHIP8_KEYCNT ) size_t dwKey );

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: KeyUp

  Summary:  Releases the specified key.

  Args:     PCHIP8KEYBOARD pKeyboard
              Pointer to the virtual keyboard.
            size_t dwKey
              Key to release.

  Returns:  MyReturnType
              Description.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern SDL_INLINE void KeyUp( _In_ PCHIP8KEYBOARD pKeyboard, _In_range_( <, CHIP8_KEYCNT ) size_t dwKey );

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: IsKeyDown

  Summary:  Indicates whether a specific virtual key is currently
            pressed.

  Args:     PCHIP8KEYBOARD pKeyboard
              Pointer to the virtual keyboard.
            size_t dwKey
              Code of the key.

  Returns:  bool
              If key is down, result is true, otherwise false.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
_Check_return_
extern SDL_INLINE bool IsKeyDown( _In_ PCHIP8KEYBOARD pKeyboard, _In_range_( <, CHIP8_KEYCNT ) size_t dwKey );

#endif //CHIP8KEYBOARD_H
