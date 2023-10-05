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
#include "engine/subsystems/renderer/mesh/Vertex.h"
#include "engine/subsystems/renderer/mesh/Face.h"

namespace GLESC {
    class Mesh {
        using VertexPtr = std::shared_ptr<Vertex>;
        using FaceVertices = Vector3<VertexPtr>;
    public:
        Mesh() = default;
        
        VertexPtr addVertex(Vertex vertex);
        
        [[nodiscard]] VertexPtr getVertex(Vertex vertex) const;
        
        [[nodiscard]] VertexPtr getVertex(size_t index) const;
        
        std::vector<VertexPtr>
        addVertices(std::initializer_list<Vertex> verticesParam);
        
        void addFace(const FaceVertices &faceVertices);
        
        void addFaces(const std::initializer_list<FaceVertices> &faceVertices);
        
        std::vector<Vertex>& getVertices();
        
        std::vector<Face>& getFaces();
        
        [[nodiscard]] std::string toString() const;
    
    private:
        std::vector<Vertex> vertices;
        std::vector<Face> faces;
    }; // class Mesh
}// namespace GLESC