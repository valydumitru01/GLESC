/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <optional>
#include "engine/core/math/Vector.h"
#include "Vertex.h"

namespace GLESC {
    using VertexIndex = std::size_t;
    using VertexPtr = std::shared_ptr<Vertex>;
    
    using EdgevertexIndices = std::pair<VertexIndex, VertexIndex>;
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
        std::vector<HalfEdgeFacePtr> halfEdgeFaces;
        
        Mesh() = default;
        
        /**
         * @brief The mesh is initialized with three vertices
         * @details The mesh starts with three vertices to ensure that the
         * mesh is mainfold. The vertices are connected with edges (and therefore
         * halfedges). The faces are created automatically by default, but can be
         * disabled by setting automaticFace to false.
         * @param vertex1Param
         * @param vertex2Param
         * @param vertex3Param
         * @param edge1 Edge connecting vertex1 and vertex2
         * @param edge2Param Edge connecting vertex2 and vertex3
         * @param edge3Param Edge connecting vertex3 and vertex1
         * @param faceParam If the face is not given, faces wont be created and (they will be set as nullopt)
         * the addition of vertices will must be done without providing faces.
         * But if the face is given. everytime a new vertex is added, a new face
         * must be provided.
         */
        explicit Mesh(const Vertex &vertex1Param,
                      const Edge &edge1,
                      const Vertex &vertex2Param,
                      const Edge &edge2Param,
                      const Vertex &vertex3Param,
                      const Edge &edge3Param,
                      std::optional<Face> faceParam = std::nullopt);
        
        /**
         * @brief This adds a vertex to the mesh and connects it to the given vertices.
         * @details The given vertex is added to the mesh and it's connected to the
         * given vertices by creating half-edges.
         * This method does not require a face, so it must be used if no face was provided
         * in the constructor of this mesh.
         * This wont create a face.
         * @attention The vertices must be connected by edges, otherwise the mesh
         * will be invalid (not manifold).
         * @param vertex The vertex to add
         * @param vertexIndex1 The index of the first vertex to connect to
         * @param edgeData1 The data of the edge connecting the first vertex to the new vertex
         * @param vertexIndex2 The index of the second vertex to connect to
         * @param edgeData2 The data of the edge connecting the second vertex to the new vertex
         * @param face Data of the face that will be created, if no face is given, no face
         * will be created and no face will be created. The faces must be created manually
         *  (or not created at all, this would be a frame mesh).
         * @throws MeshException If the vertices are not connected by edges
         * @return A pointer to the vertex inside the half-edge mesh, so it can be
         * used to add access the half-edge data structure from it.
         */
        HalfEdgeVertexPtr addVertex(const Vertex &vertex,
                                    VertexIndex &vertexIndex1,
                                    Edge &edgeData1,
                                    VertexIndex &vertexIndex2,
                                    Edge &edgeData2);
        
        /**
         * @brief This adds a vertex to the mesh and connects it to the given vertices.
         * @details The given vertex is added to the mesh and it's connected to the
         * given vertices by creating half-edges.
         * This method requires a face, so it must be used if a face was provided
         * in the constructor of this mesh.
         * This will create a face for three vertices.
         * @attention The vertices must be connected by edges, otherwise the mesh
         * will be invalid (not manifold).
         * @param vertex The vertex to add
         * @param vertexIndex1 The index of the first vertex to connect to
         * @param edgeData1 The data of the edge connecting the first vertex to the new vertex
         * @param vertexIndex2 The index of the second vertex to connect to
         * @param edgeData2 The data of the edge connecting the second vertex to the new vertex
         * @throws MeshException If the vertices are not connected by edges
         * @return A pointer to the vertex inside the half-edge mesh, so it can be
         * used to access the half-edge data structure from it.
         */
        HalfEdgeVertexPtr addVertex(const Vertex &vertex,
                                    VertexIndex &vertexIndex1,
                                    Edge edgeData1,
                                    VertexIndex &vertexIndex2,
                                    Edge edgeData2,
                                    Face &face);
        
        
        
        HalfEdgeFacePtr addFace(Vertex& vertex1, VertexIndex vertex2, VertexIndex vertex3);
        
        HalfEdgeFacePtr addFace(Vertex& vertex1, VertexPtr vertex2, VertexPtr vertex3);
        
        HalfEdgeFacePtr addFace(VertexPtr vertex1, VertexPtr vertex2, VertexPtr vertex3);
        
    private:
        bool isManifold() const;
        
        bool areVerticesConnected(VertexIndex vertexIndex1, VertexIndex vertexIndex2) const;
    }; // class Mesh
}// namespace GLESC