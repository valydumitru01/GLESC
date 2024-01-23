/******************************************************************************
 * @file   Mesh.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief  Definition of the Mesh class.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "engine/core/math/geometry/figures/polyhedron/Polyhedron.h"
#include "engine/subsystems/renderer/mesh/Vertex.h"

namespace GLESC {
    class Mesh {
        friend class Renderer;
        using Index = unsigned int;
    public:
        Mesh(): dirtyFlag(false) {}
        
        ~Mesh() = default;
        
        void addTris(const Vertex& a, const Vertex& b, const Vertex& c);
        
        void addQuad(const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d);
        
        bool isDirty() const { return dirtyFlag; }
        
        void setClean() { dirtyFlag = false; }
        
        std::string toString() const;
        
        std::vector<Vertex> getVertices() const { return vertices; }
    private:
        std::vector<Index> getIndices() const { return indices; }
        void addVertex(const Vertex& vertex);
        
        std::unordered_map<Vertex, Index> vertexToIndexMap;
        std::vector<Vertex> vertices;
        std::vector<Index> indices;
        Math::Polyhedron topology;
        bool dirtyFlag;
        
    }; // class Mesh
}// namespace GLESC