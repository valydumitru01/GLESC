#pragma once

#include <SDL2/SDL.h>
#include "GL/gl.h"

#define glCheckError() Debugger::glCheckError_(__FILE__, __LINE__)

class Debugger {
public:
	static GLenum glCheckError_(const char *file, int line);

private:

};