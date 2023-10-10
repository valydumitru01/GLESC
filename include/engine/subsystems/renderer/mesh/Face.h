/**
 * @file   Face.h
 * @author Valentin Dumitru
 * @date   2023-09-25
 * @brief  Brief description of Face.
 *
 * Copyright (c) 2023 Lenovo. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 */

#include <functional>
#include <memory>
#include "engine/core/math/Vector.h"
#include "Vertex.h"

namespace GLESC {
    class Face {
    public:
        Face() = default;
        
        void calculateData(Vertex &vertex1, Vertex &vertex2, Vertex &vertex3);
        
        bool operator==(const Face &other) const;
        
        bool operator<(const Face &other) const;
        
        [[nodiscard]] Vec3D getNormal() const;
        
        [[nodiscard]] double getArea() const;
        
        [[nodiscard]] Vec3D getCrossProduct() const;
        
        [[nodiscard]] std::string toString() const;
    
    private:
        /**
         * @brief The normal (perpendicular vector that comes out of the face)
         * of the face
         */
        Vec3D crossProduct;
        
        std::shared_ptr<Vertex> vertexA;
        std::shared_ptr<Vertex> vertexB;
        std::shared_ptr<Vertex> vertexC;
    };
    
}

template<>
struct std::hash<GLESC::Face> {
    std::size_t operator()(const GLESC::Face &face) const {
        return std::hash<Vec3D>()(face.getCrossProduct());
    }
};