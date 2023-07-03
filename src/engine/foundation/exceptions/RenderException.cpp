#include "exceptions/RenderException.h"

RenderException::RenderException(const string &message)
        : BaseException("Rendering error:"+message) {}

