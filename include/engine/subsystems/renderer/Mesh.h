/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <vector>
#include <string>
#include <memory>
#include "engine/core/math/Vector.h"

namespace GLESC {
    struct Vertex {
        inline static const Vector3F defaultVertexColor = Vector3F(0, 0, 0);
        inline static const Vector2F defaultVertexUv = Vector2F(0, 0);
        
        explicit Vertex(const Vector3F &position, const Vector3F &color, const Vector2F &uv);
        
        explicit Vertex(const Vector3F &position);
        
        explicit Vertex(const Vector3F &position, const Vector3F &color);
        
        explicit Vertex(const Vector3F &position, const Vector2F &uv);
        
        Vector3F position;
        Vector3F normal;
        Vector3F color;
        Vector2F uv;
    };
    
    struct Face {
        /**
         * @brief The normal (perpendicular vector that comes out of the face) of the face
         */
        Vector3F normal;
    };
    struct Edge {
        // Data
    };
    
    class HalfEdge;
    
    class HalfEdgeVertex {
        friend class HalfEdge;
        
        friend class Mesh;
    
    protected:
        
        explicit HalfEdgeVertex(const Vertex &vertex);
        
        explicit HalfEdgeVertex(const Vertex &&vertex);
        
        /**
         * @brief Pointer to one of the outgoing half-edges from this vertex
         */
        std::shared_ptr<HalfEdge> halfEdge{};
        Vertex vertex;
    };
    
    class HalfEdgeEdge {
        friend class HalfEdge;
        
        friend class Mesh;
        
        /**
         * @brief Pointer to one of the half-edges that belong to this edge
         */
        std::shared_ptr<HalfEdge> halfEdge{};
    };
    
    class HalfEdgeFace {
        friend class HalfEdge;
        
        friend class Mesh;
        
        /**
         * @brief Pointer to one of the half-edges that bound this face
         */
        std::shared_ptr<HalfEdge> halfEdge{};
    };
    
    /**
     * @brief Half-edges act as glue between mesh elements. It's a type of linked list.
     */
    class HalfEdge {
        friend class Mesh;
        
        /**
         * @brief The twin of this half-edge is the half edge but in the
         * other side of it and going in the previous direction.
         */
        std::shared_ptr<HalfEdge> twin;
        /**
         * @brief The next half-edge that follows this half edge
         */
        std::shared_ptr<HalfEdge> next;
        /**
         * @brief The vertex where the half-edge COMES FROM
         */
        std::shared_ptr<HalfEdgeVertex> vertex;
        /**
         * @brief This is the face that is linked to the half-edge.
         * There is only one face linked to one half edge.
         */
        std::shared_ptr<HalfEdgeFace> face;
        /**
         * @brief This is the edge which the half-edge belongs to.
         */
        std::shared_ptr<HalfEdgeEdge> edge;
    };
    
    using HalfEdgePtr = std::shared_ptr<HalfEdge>;
    using HalfEdgeVertexPtr = std::shared_ptr<HalfEdgeVertex>;
    using HalfEdgeEdgePtr = std::shared_ptr<HalfEdgeEdge>;
    using HalfEdgeFacePtr = std::shared_ptr<HalfEdgeFace>;
    
    using VertexIndex = std::size_t;
    
    using EdgeVertixIndices = std::pair<VertexIndex, VertexIndex>;
    using EdgeVertices = std::pair<HalfEdgeVertexPtr, HalfEdgeVertexPtr>;
    
    using FaceEdgeIndices = std::pair<VertexIndex, VertexIndex>;
    using FaceEdges = std::pair<HalfEdgePtr, HalfEdgePtr>;
    
    
    class Mesh {
        // TODO: Try to change half edges to a vector of indices for
        //  a vector of half edges to take advantage of cache locality
        //  and reduce memory usage. Check if it's worth it.
    public:
        std::vector<HalfEdgePtr> halfEdges;
        std::vector<HalfEdgeVertexPtr> halfEdgeVertices;
        std::vector<HalfEdgeEdgePtr> halfEdgeEdges;
        
        Mesh() = default;
        
        explicit Mesh(const std::vector<Vertex> &vertices,
                      const std::vector<EdgeVertixIndices> &edgeIndicesList = {},
                      const std::vector<FaceEdgeIndices> &faceIndicesList = {});
        
        explicit Mesh(const std::vector<Vertex> &vertices,
                      const std::vector<EdgeVertices> &edgeVerticesList = {},
                      const std::vector<FaceEdges> &faceVerticesList = {});
        
        // Additions
        HalfEdgeVertexPtr addVertex(const Vertex &vertex);
        
        HalfEdgeVertexPtr addVertex(const Vertex &&vertex);
        
        HalfEdgeVertexPtr addVertex(const Vertex &vertex, const std::vector<VertexIndex>& endVerticesForEdge);
        
        void addEdge(const EdgeVertixIndices &edgeIndices);
        
        void addEdge(const EdgeVertices &edgeVertices);
        
        HalfEdgeFacePtr addFace(const FaceEdgeIndices &faceIndices);
        
        HalfEdgeFacePtr addFace(const FaceEdges &faceVertices);
        
        // Factory functions
        static Mesh createCube();
        
        static Mesh createSphere(int resolution);
        
        // Queries
        std::vector<HalfEdgeVertexPtr> getNeighbors(HalfEdgeVertexPtr vertex);
        
        std::vector<HalfEdgeFacePtr> getAdjacentFaces(HalfEdgeVertexPtr vertex);
        
        // Updates & Deletions
        void deleteVertex(HalfEdgeVertexPtr vertex);
        
        void deleteEdge(HalfEdgeEdgePtr edge);
        
        void deleteFace(HalfEdgeFacePtr face);
        
        void updateVertexPosition(HalfEdgeVertexPtr vertex, const Vertex &newPosition);
    };
}// namespace GLESC