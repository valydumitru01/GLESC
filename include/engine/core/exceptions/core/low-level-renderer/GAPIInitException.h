/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "GAPIException.h"

class GAPIInitException : public GAPIException{
public:
    explicit GAPIInitException(const std::string &message) : GAPIException("GDI error:" + message) {}
};
