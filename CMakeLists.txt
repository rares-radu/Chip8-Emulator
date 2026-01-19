cmake_minimum_required( VERSION 3.31 )
project( Chip8 C )

set( CMAKE_C_STANDARD 11 )

find_package( SDL3 CONFIG REQUIRED )

set( SOURCES
     include/config.h
     include/globals.h
     src/globals.c
     include/helpers.h
     src/helpers.c
     src/main.c
     include/chip8screen.h
     src/chip8screen.c
     include/chip8memory.h
     src/chip8memory.c
     include/chip8registers.h
     include/chip8stack.h
     src/chip8stack.c
     include/chip8keyboard.h
     src/chip8keyboard.c
     include/chip8.h
     src/chip8.c
     src/chip8sounds.c
     include/chip8sounds.h )
set( INCLUDES
     ${_sdl3_include_dirs}
     include )

add_executable( ${PROJECT_NAME} WIN32 ${SOURCES} )
target_include_directories( ${PROJECT_NAME} PRIVATE ${INCLUDES} )
target_link_libraries( ${PROJECT_NAME} PRIVATE SDL3::SDL3 )

# Copy the DLL to the output folder
add_custom_command( TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    $<TARGET_FILE:SDL3::SDL3>
                    $<TARGET_FILE_DIR:${PROJECT_NAME}> )
