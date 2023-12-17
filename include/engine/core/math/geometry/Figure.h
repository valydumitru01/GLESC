/**************************************************************************************************
 * @file   Figure.h
 * @author Valentin Dumitru
 * @date   11/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <engine/core/math/geometry/Polyhedron.h>
#include "Plane.h"

namespace GLESC::Math {
    class Figure {
    public:
        virtual ~Figure() = default;
        
        [[nodiscard]] virtual bool intersects(const Plane &plane) const = 0;
        
        [[nodiscard]] virtual bool intersects(const Face & face) const = 0;
        
        [[nodiscard]] virtual bool intersects(const Polyhedron &polyhedron) const = 0;
        
        [[nodiscard]] virtual bool intersects(const Point &point) const = 0;
    }; // class Figure
} // namespace GLESC::Math