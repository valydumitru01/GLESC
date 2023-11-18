/***************************************************************************************************
 * @file   Shader.h
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <string>
#include "engine/core/low-level-renderer/graphic-api/IGraphicInterface.h"
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"
#include "engine/core/math/Matrix.h"
#include "engine/core/math/Vec.h"

namespace GLESC {
    class Shader {
    public:
        Shader(const std::string &fileName);
        
        ~Shader();
        
        void bind() const;
        
        void unbind() const;
        
        UniformSetter setUniform(const std::string &name) const;
    
    private:
        /**
         * @brief The shader program
         */
        GAPIuint shaderProgram;
    }; // class Shader
}