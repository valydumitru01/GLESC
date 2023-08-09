/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "GDIException.h"

class GDIInitException : public GDIException{
public:
    explicit GDIInitException(const std::string &message) : GDIException("GDI setShaderProgram error:"+message) {}
};
