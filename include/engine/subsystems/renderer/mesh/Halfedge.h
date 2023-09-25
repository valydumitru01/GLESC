
/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include <memory>
#include "Vertex.h"
#include "Edge.h"
#include "Face.h"

namespace GLESC {
    class HalfEdge;
    
    class HalfEdgeVertex {
        friend class HalfEdge;
        
        friend class Mesh;
    
    private:
        
        explicit HalfEdgeVertex(const Vertex &vertex);
        
        explicit HalfEdgeVertex(const Vertex &&vertex);
        
        bool operator==(const HalfEdgeVertex &other) const;
        
        /**
         * @brief Pointer to one of the outgoing half-edges from this vertex
         */
        std::shared_ptr<HalfEdge> halfEdge{};
        /**
         * @brief The data of the vertex
         */
        Vertex vertex;
    };
    
    class HalfEdgeEdge {
        friend class HalfEdge;
        
        friend class Mesh;
    private:
        explicit HalfEdgeEdge(const Edge &edge);
        explicit HalfEdgeEdge(const Edge &&edge);
        
        bool operator==(const HalfEdgeEdge &other) const;
        
        /**
         * @brief Pointer to one of the half-edges that belong to this edge
         */
        std::shared_ptr<HalfEdge> halfEdge{};
        /**
         * @brief The data of the edge
         */
        Edge edge;
    };
    
    class HalfEdgeFace {
        friend class HalfEdge;
        
        friend class Mesh;
    private:
        explicit HalfEdgeFace(const Face &face);
        explicit HalfEdgeFace(const Face &&face);
        
        bool operator==(const HalfEdgeFace &other) const;
        
        /**
         * @brief Pointer to one of the half-edges that bound this face
         */
        std::shared_ptr<HalfEdge> halfEdge{};
        
        /**
         * @brief The data of the face
         */
        Face face;
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
    
}
