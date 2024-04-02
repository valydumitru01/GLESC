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

#include "engine/core/hash/Hasher.h"
#include "engine/subsystems/renderer/BoundingVolume.h"
#include "engine/subsystems/renderer/mesh/Vertex.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render
{
    /**
     * @brief A class that represents a mesh.
     * @details This is the mesh class for the engine. Is a template class that needs to be instantiated with the
     * types (@see GAPI::Types) of the vertex attributes that the mesh will have.
     * This mesh class contains only the abstraction of the mesh data.
     * @warning mesh does NOT need to be instantiated with the position attribute, as it is always present, Doing so
     * might lead to unexpected behavior. Position is inside the topology and is always present.
     */
    template <GAPI::Enums::Types... Data>
    class Mesh
    {
    public:
        using Index = unsigned int;
        using Vertex = Vertex<
            VectorT<GAPI::Enums::PrimitiveType_t<Data>, static_cast<unsigned int>(GAPI::Enums::getTypeCount(Data))>...
        >;


        Mesh():
            dirtyFlag(false),
            vertexLayout({Data...}),
            renderType(RenderType::Dynamic)
        {
        }

        ~Mesh() = default;

        [[nodiscard]] const std::vector<Vertex> getVertices() const { return vertices; }
        [[nodiscard]] const std::vector<Index> getIndices() const { return indices; }
        [[nodiscard]] const std::vector<GAPI::Enums::Types> getVertexLayout() const { return vertexLayout; }
        [[nodiscard]] const BoundingVolume& getBoudingVolume() const { return boudingVolume; }
        [[nodiscard]] BoundingVolume& getBoundingVolumeMutable() { return boudingVolume; }
        [[nodiscard]] bool isDirty() const { return dirtyFlag; }
        [[nodiscard]] RenderType getRenderType() const { return renderType; }

        void setRenderType(RenderType renderTypeParam) { renderType = renderTypeParam; }
        void setClean() const { dirtyFlag = false; }


        void addTris(const Vertex& a, const Vertex& b, const Vertex& c)
        {
            this->addVertex(a);
            this->addVertex(b);
            this->addVertex(c);
            this->dirtyFlag = true;
        }

        void addVertex(const Vertex& vertexParam)
        {
            // Attempt to insert the vertex with its index into the map.
            // The insert operation does not overwrite existing entries and returns a pair.
            // The first element of the pair is an iterator to the existing or inserted element,
            // and the second element is a boolean that is true if the insertion was successful.
            auto result = vertexToIndexMap.insert({vertexParam, static_cast<Index>(vertices.size())});


            // If the vertex was not already in the map (i.e., insertion was successful),
            // then add the vertex to the vertices vector.
            if (result.second)
            {
                vertices.push_back(vertexParam);
            }

            // Regardless of whether the vertex was just inserted or already existed,
            // add its index to the indices vector.
            // result.first is an iterator to the pair in the map, and .second accesses the index.
            indices.push_back(result.first->second);

            boudingVolume.updateTopology(vertices);
        }

        [[nodiscard]] bool operator==(const Mesh& other) const
        {
            for (size_t i = 0; i < vertices.size(); ++i)
            {
                if (vertices[i] != other.vertices[i])
                {
                    return false;
                }
            }

            for (size_t i = 0; i < indices.size(); ++i)
            {
                if (indices[i] != other.indices[i])
                {
                    return false;
                }
            }

            return true;
        }

        [[nodiscard]] std::string toString() const
        {
            std::string result = "Mesh\n";
            result += "Vertices (first 10):\n";
            for (size_t i = 0; i < 10 && i < vertices.size(); ++i)
            {
                result += vertices[i].toString() + "\n";
            }
            result += "Indices (first 10):\n";
            for (size_t i = 0; i < 10 && i < indices.size(); ++i)
            {
                result += std::to_string(indices[i]) + "\n";
            }
            return result;
        }

        size_t hash() const
        {
            if (hashDirty)
            {
                cachedHash = this->calculateHash();
                hashDirty = false;
            }
            return cachedHash;
        }

        void operator=(const Mesh& other)
        {
            vertices = other.vertices;
            indices = other.indices;
            vertexToIndexMap = other.vertexToIndexMap;
            boudingVolume = other.boudingVolume;
            vertexLayout = other.vertexLayout;
            dirtyFlag = other.dirtyFlag;
            renderType = other.renderType;
            hashDirty = true;
        }

    private:
        size_t calculateHash() const
        {
            size_t hashValue = 0;

            // Hash vertex data
            for (const auto& vertex : vertices)
            {
                Hasher::hashCombine(hashValue, std::hash<Vertex>{}(vertex));
            }
            // Hash index data
            for (const auto& index : indices)
            {
                Hasher::hashCombine(hashValue, std::hash<Index>{}(index));
            }

            return hashValue;
        }

        RenderType renderType;
        // This is redundant, but it is used to avoid searching the vertices vector for the index of a vertex.
        std::unordered_map<Vertex, Index> vertexToIndexMap{};
        std::vector<Vertex> vertices{};
        std::vector<Index> indices{};
        /**
         * @brief The bounding volume of the mesh.
         * @details The bounding volume is a polyhedron cuboid that encloses the mesh. It is used for culling.
         */
        BoundingVolume boudingVolume;
        /**
         * @brief The vertex layout of the mesh.
         * @details The vertex layout is a vector of GAPI::Types that describes the layout of the
         * vertex data in the vertices vector. The layout is used to create the vertex buffer layout
         * for the vertex array object.
         */
        std::vector<GAPI::Enums::Types> vertexLayout;
        /**
         * @brief A flag that indicates whether the mesh is dirty.
         * @details The flag is set to true when the mesh is modified. It is used to avoid unnecessary
         * updates to the vertex array object. It is mutable because it is modified by const methods, specifically
         * after rendering the mesh, we want to set the flag to false and nothing else.
         */
        mutable bool dirtyFlag;

        mutable size_t cachedHash = 0;
        mutable bool hashDirty = true;
    }; // class Mesh

    using ColorMesh = Mesh<
        GAPI::Enums::Types::Vec3F, // Position is always present
        GAPI::Enums::Types::Vec4F, // RGBA color
        GAPI::Enums::Types::Vec3F // Normal
    >;

    using TextureMesh = Mesh<
        GAPI::Enums::Types::Vec3F, // Position is always present
        GAPI::Enums::Types::Vec2F, // UV
        GAPI::Enums::Types::Vec3F // Normal
    >;

    constexpr std::size_t LayoutPosition = 0;
    constexpr std::size_t LayoutColor = 1;
    constexpr std::size_t LayoutUV = 1;
    constexpr std::size_t LayoutNormal = 2;

    template <typename... Attributes>
    Position getVertexPositionAttr(Vertex<Attributes...> v)
    {
        return v.template getAttribute<LayoutPosition>();
    }

    inline Color getVertexColorAttr(ColorMesh::Vertex v)
    {
        return v.getAttribute<LayoutColor>();
    }

    inline UV getVertexUVAttr(TextureMesh::Vertex v)
    {
        return v.getAttribute<LayoutUV>();
    }

    inline Normal getVertexNormalAttr(ColorMesh::Vertex v)
    {
        return v.getAttribute<LayoutNormal>();
    }
} // namespace GLESC

// Assuming the existence of a getAttributes() method that returns a tuple of all attributes.


template <GLESC::GAPI::Enums::Types... Data>
struct std::hash<GLESC::Render::Mesh<Data...>>
{
    size_t operator()(const GLESC::Render::Mesh<Data...>& mesh) const
    {
        return mesh.hash();
    }
};
