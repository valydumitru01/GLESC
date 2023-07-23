#pragma once

#include "GDIException.h"

class GDIInitException : public GDIException{
public:
    explicit GDIInitException(const std::string &message) : GDIException("GDI setShaderProgram error:"+message) {}
};
