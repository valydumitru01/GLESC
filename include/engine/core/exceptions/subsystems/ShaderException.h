/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/exceptions/BaseException.h"

class ShaderException : public BaseException {
public:
    explicit ShaderException(const std::string &message) : BaseException("Shader error:" + message) {}
};

class ShaderCompilationException : public ShaderException {
public:
    explicit ShaderCompilationException(const std::string& shaderName, const std::string &message) :
            ShaderException("Shader compilation error:" + shaderName + ":" + message) {}
};

class ShaderLinkingException : public ShaderException {
public:
    explicit ShaderLinkingException(const std::string &message) : ShaderException("Shader linking error:" + message) {}
};

class ShaderUniformNotFoundException : public ShaderException {
public:
    explicit ShaderUniformNotFoundException(const std::string& uniformName, const std::string &message) :
            ShaderException("Shader uniform not found:" + message) {}
};