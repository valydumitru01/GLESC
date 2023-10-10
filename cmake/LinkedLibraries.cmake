
# This is the list of all the libraries that are needed to build the game
set(MAIN_LIBS
        mingw32 # This is needed to allow the project to be built on different platforms
        SDL2 # This is the SDL library, Simple DirectMedia Layer, used for window creation and input handling
        SDL2main # This is the main component of the SDL library
        SDL2_net # This is the networking component of the SDL library
        SDL2_mixer # This is the audio component of the SDL library
        SDL2_image # This is the image component of the SDL library
        glew32s # This is the glew library, OpenGL Extension Wrangler, used to load OpenGL functions
)
if (WIN32)
    list(APPEND MAIN_LIBS
            opengl32 # This is the OpenGL library, used for rendering, specific for Windows
            imm32 # library is a component of Microsoft Windows that provides Input Method Editor (IME) capabilities,
            # This is necessary for the SDL library, it allows more characters than the standard keyboard
            DbgHelp # Debug Help Library, It allows stacktraces to be printed in Windows
            version # This is a dependency of the SDL library,
            # is used on Windows to obtain version information about operating system
            # components, files, and other resources
            setupapi # This is a dependency of the SDL library,
            # handles installation, enumeration, and management of hardware devices
            winmm # This is a dependency of the SDL library,
            # Windows-specific library that provides a range of multimedia functionalities,
            # such as playing sound files, providing timers, and accessing joysticks
    )
elseif (LINUX)
    # TODO: Add libraries for Linux
elseif (APPLE)
    # TODO: Add libraries for Mac
endif ()
