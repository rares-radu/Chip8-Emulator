/*+===================================================================
  File:      HELPERS.H

  Summary:   Contains various miscellaneous functions.

  Origin:    Written by Rareș Radu.

  I dedicate any and all copyright interest in this software to the
  public domain. I make this dedication for the benefit of the public at
  large and to the detriment of my heirs and successors. I intend this
  dedication to be an overt act of relinquishment in perpetuity of all
  present and future rights to this software under copyright law.

  For more information, please refer to <https://unlicense.org/>
===================================================================+*/

#ifndef CHIP8_HELPERS_H
#define CHIP8_HELPERS_H

#include <sal.h>
#include <SDL3\SDL.h>

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: OpenFileDialog

  Summary:  Opens the file dialog and lets the user choose a ROM.

  Args:     SDL_Window* pWindow
              The window that the dialog should be modal for.

  Returns:  char*
              Path of the file the user chose.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
_Ret_maybenull_z_
const char* OpenFileDialog( _In_opt_ SDL_Window* pWindow );

#endif //CHIP8_HELPERS_H
