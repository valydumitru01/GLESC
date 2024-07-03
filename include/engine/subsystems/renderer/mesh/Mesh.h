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
#include <mutex>
#include <utility>
#include "engine/core/low-level-renderer/graphic-api/GapiEnums.h"
#include "engine/core/low-level-renderer/buffers/IndexBuffer.h"
#include "engine/core/low-level-renderer/buffers/VertexArray.h"
#include "engine/core/low-level-renderer/buffers/VertexBuffer.h"
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/core/hash/Hasher.h"
#include "engine/core/math/geometry/figures/BoundingVolume.h"
#include "engine/subsystems/EngineComponent.h"
#include "engine/subsystems/renderer/mesh/Vertex.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
    class Renderer;
    /**
     * @brief A class that represents a mesh.
     * @details This is the mesh class for the engine. Is a template class that needs to be instantiated with the
     * types (@see Types) of the vertex attributes that the mesh will have.
     * This mesh class contains only the abstraction of the mesh data.
     * This mesh is thread safe, so its safe to modify it from multiple threads.
     * @warning mesh does NOT need to be instantiated with the position attribute, as it is always present, Doing so
     * might lead to unexpected behavior. Position is inside the topology and is always present.
     */
    template <typename VertexT>
    class Mesh : public EngineComponent {
        friend class GLESC::Render::Renderer;

    public:
        /**
         * @brief Static assert to ensure that the vertex is a ColorVertex or TextureVertex. As we currently only
         * support these two types of vertices.
         */
        S_ASSERT_TRUE((std::is_base_of_v<ColorVertex, VertexT> ||std::is_base_of_v<TextureVertex, VertexT>),
                      "Vertex must be a ColorVertex or TextureVertex");
        /**
         * @brief Alias for the index type of the mesh. Is unsigned because the index can't be negative.
         */
        using Index = unsigned int;
        /**
         * @brief Alias for the vertex, for readability purposes.
         */
        using Vertex = VertexT;


        /**
         * @brief Mesh constructor.
         * @details Starts with some default values:
         * RenderType - SingleDrawDynamic
         */
        Mesh():
            dirtyFlag(false),
            vertexLayout({Vertex::getLayout()}),
            renderType(RenderType::SingleDrawDynamic),
            vertexArray(), indexBuffer(), vertexBuffer() {
        }

        /**
         * @details Default destructor, nothing else to do.
         */
        ~Mesh() override = default;


        Mesh(const Mesh& other) : vertices(other.vertices),
                                  indices(other.indices),
                                  boundingVolume(other.boundingVolume),
                                  vertexLayout(other.vertexLayout),
                                  faces(other.faces),
                                  dirtyFlag(other.dirtyFlag),
                                  renderType(other.renderType),
                                  hashDirty(other.hashDirty),
                                  cachedHash(other.cachedHash) {
        }

        Mesh(Mesh&& other) noexcept : vertices(std::move(other.vertices)),
                                      indices(std::move(other.indices)),
                                      boundingVolume(std::move(other.boundingVolume)),
                                      vertexLayout(std::move(other.vertexLayout)),
                                      faces(std::move(other.faces)),
                                      dirtyFlag(other.dirtyFlag),
                                      renderType(other.renderType),
                                      hashDirty(other.hashDirty),
                                      cachedHash(other.cachedHash){}

        Mesh& operator=(Mesh&& other) noexcept {
            if (this == &other)
                return *this;
            vertices = std::move(other.vertices);
            indices = std::move(other.indices);
            boundingVolume = std::move(other.boundingVolume);
            vertexLayout = std::move(other.vertexLayout);
            faces = std::move(other.faces);
            dirtyFlag = other.dirtyFlag;
            renderType = other.renderType;
            hashDirty = other.hashDirty;
            cachedHash = other.cachedHash;
            return *this;
        }

        Mesh& operator=(const Mesh& other) {
            if (this == &other)
                return *this;
            vertices = other.vertices;
            indices = other.indices;
            boundingVolume = other.boundingVolume;
            vertexLayout = other.vertexLayout;
            dirtyFlag = other.dirtyFlag;
            renderType = other.renderType;
            hashDirty = other.hashDirty;
            cachedHash = other.cachedHash;
            faces = other.faces;
            return *this;
        }

        /**
         * @brief Starts the building of the mesh.
         * @details This method should be called before adding any vertices or indices to the mesh.
         * It will also set the isBuilding flag to true.
         * It is only possible to attach vertices or whole meshes to the mesh while it is being built.
         */
        void startBuilding() {
            dirtyFlag = true;
            isBuilding = true;
        }

        void clear() {
            vertices.clear();
            indices.clear();
            faces.clear();
            dirtyFlag = true;
        }

        void finishBuilding() {
            D_ASSERT_TRUE(isBuilding, "Mesh is not being built");
            D_ASSERT_TRUE(!vertices.empty(), "No vertices in mesh");
            D_ASSERT_TRUE(!indices.empty(), "No indices in mesh");
            boundingVolume.updateBoundingBox(vertices.data(), vertices.size() * sizeof(Vertex), sizeof(Vertex), 0);
            isBuilding = false;
        }

        void reserveVertices(size_t size) {
            D_ASSERT_TRUE(isBuilding, "Mesh is not being built");
            vertices.reserve(size);
        }

        void reserveIndices(size_t size) {
            D_ASSERT_TRUE(isBuilding, "Mesh is not being built");
            indices.reserve(size);
        }

        void reserveFaces(size_t size) {
            D_ASSERT_TRUE(isBuilding, "Mesh is not being built");
            faces.reserve(size);
        }

        [[nodiscard]] const std::vector<Vertex>& getVertices() const { return vertices; }
        [[nodiscard]] std::vector<Vertex>& getModifiableVertices() { return vertices; }
        [[nodiscard]] const std::vector<Index>& getIndices() const { return indices; }
        [[nodiscard]] const std::vector<GLESC::GAPI::Enums::Types>& getVertexLayout() const { return vertexLayout; }
        [[nodiscard]] const std::vector<Math::FaceIndices>& getFaces() const { return faces; }
        [[nodiscard]] const Math::BoundingVolume& getBoundingVolume() const { return boundingVolume; }
        [[nodiscard]] Math::BoundingVolume& getBoundingVolumeMutable() { return boundingVolume; }
        [[nodiscard]] bool isDirty() const { return dirtyFlag; }
        [[nodiscard]] const RenderType& getRenderType() const { return renderType; }
        [[nodiscard]] bool isBeingBuilt() const { return isBuilding; }

        void setRenderType(RenderType renderTypeParam) { renderType = renderTypeParam; }

        /**
         * @brief Struct with only color and position vertex.
         */
        struct VertexColorParam {
            VertexColorParam(Position positionParam, ColorRgba colorParam)
                : position(std::move(positionParam)), color(std::move(colorParam)) {
            }

            Position position;
            ColorRgba color;
        };

        /**
         * @brief Struct with only texture UV and position vertex.
         */
        struct VertexTexParam {
            VertexTexParam(Position positionParam, UV textureCoordinateParam)
                : position(std::move(positionParam)), textureCoordinate(std::move(textureCoordinateParam)) {
            }

            Position position;
            UV textureCoordinate;
        };

        /**
         * @brief Adds a tris to the mesh, tris are defined by 3 vertices.
         * @details The order of the faces is important, the vertices should be defined in a counter-clockwise order.
         * @param a The first vertex of the tris.
         * @param b The second vertex of the tris.
         * @param c The third vertex of the tris.
         */
        void addTris(const VertexColorParam& a, const VertexColorParam& b, const VertexColorParam& c) {
            D_ASSERT_TRUE(isBuilding, "Mesh is not being built");
            Normal normal = calculateNormal(a.position, b.position, c.position);
            unsigned int v1Index;
            unsigned int v2Index;
            unsigned int v3Index;
            if constexpr (std::is_same_v<Vertex, ColorVertex>) {
                v1Index = this->addVertex({a.position, normal, a.color});
                v2Index = this->addVertex({b.position, normal, b.color});
                v3Index = this->addVertex({c.position, normal, c.color});
            }
            else {
                v1Index = this->addVertex({a.position, normal, a.textureCoordinate});
                v2Index = this->addVertex({b.position, normal, b.textureCoordinate});
                v3Index = this->addVertex({c.position, normal, c.textureCoordinate});
            }
            this->addTris(v1Index, v2Index, v3Index);
        }

        /**
         * @brief Adds a tris to the mesh, tris are defined by 3 vertices.
         * @details The order of the faces is important, the vertices should be defined in a counter-clockwise order.
         * @param v1 The first vertex of the tris.
         * @param v2 The second vertex of the tris.
         * @param v3 The third vertex of the tris.
         */
        void addTris(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
            D_ASSERT_TRUE(isBuilding, "Mesh is not being built");
            unsigned int v1Index = this->addVertex(v1);
            unsigned int v2Index = this->addVertex(v2);
            unsigned int v3Index = this->addVertex(v3);
            this->addTris(v1Index, v2Index, v3Index);
        }

        /**
         * @brief Attaches a mesh to the current mesh.
         * @details This method will add the faces and vertices to the current mesh.
         * It is an expesive operation as will iterate over all the faces of other mesh to add
         * to this one.
         * @param mesh The mesh to be attached.
         */
        void attatchMesh(const Mesh& mesh) {
            D_ASSERT_TRUE(isBuilding, "Mesh is not being built");


            for (Math::FaceIndices face : mesh.getFaces()) {
                Index v1Index = face[0];
                Index v2Index = face[1];
                Index v3Index = face[2];
                const Vertex& v1 = mesh.getVertices()[v1Index];
                const Vertex& v2 = mesh.getVertices()[v2Index];
                const Vertex& v3 = mesh.getVertices()[v3Index];
                addTris(v1, v2, v3);
            }
        }

        /**
         * @brief Adds a quad to the mesh, quads are defined by 4 vertices.
         * @details The order of the faces is important, the vertices should be defined in a counter-clockwise order.
         * @param v1 The first vertex of the quad.
         * @param v2 The second vertex of the quad.
         * @param v3 The third vertex of the quad.
         * @param v4 The fourth vertex of the quad.
         */
        void addQuad(const VertexColorParam& v1,
                     const VertexColorParam& v2,
                     const VertexColorParam& v3,
                     const VertexColorParam& v4) {
            D_ASSERT_TRUE(isBuilding, "Mesh is not being built");
            Normal normal = calculateNormal(v1.position, v2.position, v3.position);
            unsigned int v1Index;
            unsigned int v2Index;
            unsigned int v3Index;
            unsigned int v4Index;
            if constexpr (std::is_same_v<Vertex, ColorVertex>) {
                v1Index = this->addVertex({v1.position, normal, v1.color});
                v2Index = this->addVertex({v2.position, normal, v2.color});
                v3Index = this->addVertex({v3.position, normal, v3.color});
                v4Index = this->addVertex({v4.position, normal, v4.color});
            }
            else {
                v1Index = this->addVertex({v1.position, normal, v1.textureCoordinate});
                v2Index = this->addVertex({v2.position, normal, v2.textureCoordinate});
                v3Index = this->addVertex({v3.position, normal, v3.textureCoordinate});
                v4Index = this->addVertex({v4.position, normal, v4.textureCoordinate});
            }
            this->addQuad(v1Index, v2Index, v3Index, v4Index);
        }

        /**
         * @brief Adds a quad to the mesh, quads are defined by 4 vertices.
         * @details Will add two tris to the mesh. The order of the faces is important, the vertices should be defined
         * in a counter-clockwise order.
         * @param index1
         * @param index2
         * @param index3
         * @param index4
         */
        void addQuad(Index index1, Index index2, Index index3, Index index4) {
            D_ASSERT_TRUE(isBuilding, "Mesh is not being built");
            addTris(index1, index2, index3);
            addTris(index1, index3, index4);
        }

        /**
         * @brief Adds a vertex to the mesh
         * @details This method will just add a vertex to the vertex buffer of the mesh.
         * The mesh is a thread safe structure, so it is safe to call this method from multiple threads.
         * @param vertexParam
         * @return
         */
        Index addVertex(const Vertex& vertexParam) {
            D_ASSERT_TRUE(isBuilding, "Mesh is not being built");
            // Insert new vertex
            auto newIndex = static_cast<Index>(vertices.size());
            {
                std::lock_guard<std::mutex> lock(verticesMutex);
                vertices.push_back(vertexParam);
            }
            return newIndex;
        }

        /**
         * @brief Adds a list of vertices to the mesh
         * @details This method will just add a list of vertices to the vertex buffer of the mesh.
         * Will call addVertex for each vertex in the list.
         * @param verticesParam
         */
        void addVertices(const std::vector<Vertex>& verticesParam) {
            D_ASSERT_TRUE(isBuilding, "Mesh is not being built");
            for (const auto& vertex : verticesParam) {
                addVertex(vertex);
            }
        }

        /**
         * @brief Adds a list of indices to the mesh
         * @details This method will add a list of indices to the index buffer of the mesh.
         * The indices must be valid indices of the vertices vector, not out of bounds.
         * @param index1 The first index of the tris.
         * @param index2 The second index of the tris.
         * @param index3 The third index of the tris.
         */
        void addTris(Index index1, Index index2, Index index3) {
            D_ASSERT_TRUE(isBuilding, "Mesh is not being built");
            D_ASSERT_NOT_EQUAL(index1, index2, "Index 1 and 2 are equal");
            D_ASSERT_NOT_EQUAL(index1, index3, "Index 1 and 3 are equal");
            D_ASSERT_NOT_EQUAL(index2, index3, "Index 2 and 3 are equal");
            D_ASSERT_LESS(index1, vertices.size(), "Index 1 out of bounds");
            D_ASSERT_LESS(index2, vertices.size(), "Index 2 out of bounds");
            D_ASSERT_LESS(index3, vertices.size(), "Index 3 out of bounds");
            {
                std::lock_guard<std::mutex> lock(indicesMutex);
                indices.push_back(index1);
                indices.push_back(index2);
                indices.push_back(index3);
                faces.push_back({index1, index2, index3});
            }
            this->dirtyFlag = true;
        }

        /**
         * @brief To check if a mesh is equal to another mesh we iterate over the vertices and indices and compare them.
         * If the vertices and indices are the same, the meshes are equal.
         * @details This is a slow operation and should be avoided.
         * @param other
         * @return
         */
        [[nodiscard]] bool operator==(const Mesh& other) const {
            for (size_t i = 0; i < vertices.size(); ++i) {
                if (vertices[i] != other.vertices[i]) {
                    return false;
                }
            }

            for (size_t i = 0; i < indices.size(); ++i) {
                if (indices[i] != other.indices[i]) {
                    return false;
                }
            }

            return true;
        }

        /**
         * @brief This converts the mesh to a string
         * @details Will only convert the first 10 vertices and indices to a string, just for debugging purposes.
         * @return The string representation of the mesh.
         */
        [[nodiscard]] std::string toString() const override {
            std::string result = "Mesh\n";
            result += "Vertices (first 10):\n";
            for (size_t i = 0; i < 10 && i < vertices.size(); ++i) {
                result += vertices[i].toString() + "\n";
            }
            result += "Indices (first 10):\n";
            for (size_t i = 0; i < 10 && i < indices.size(); ++i) {
                result += std::to_string(indices[i]) + "\n";
            }
            return result;
        }

        /**
         * @brief Calculates lazily the hash of the mesh. Only recalculates if the mesh has been changed.
         * @return The hash of the mesh.
         */
        size_t hash() const {
            if (hashDirty) {
                cachedHash = this->calculateHash();
                hashDirty = false;
            }
            return cachedHash;
        }


#ifndef NDEBUG_GLESC
          std::vector<EntityStatsManager::Value> getUpdatedDebuggingValues() override {
            std::vector<EntityStatsManager::Value> values;
            if (wasDataSentToGpu) {
                EntityStatsManager::Value vertexCountValue;
                vertexCountValue.name = "Vertex Count";
                vertexCountValue.stringData = std::to_string(vertices.size());
                vertexCountValue.isString = true;
                values.push_back(vertexCountValue);

                EntityStatsManager::Value faceCountValue;
                faceCountValue.name = "Face Count";
                faceCountValue.stringData = std::to_string(faces.size());
                faceCountValue.isString = true;
                values.push_back(faceCountValue);

                EntityStatsManager::Value VAOIDValue;
                VAOIDValue.name = "VAO ID";
                VAOIDValue.stringData = std::to_string(getVertexArray().getRendererID());
                VAOIDValue.isString = true;
                values.push_back(VAOIDValue);
            }
            else {
                EntityStatsManager::Value errorValue;
                errorValue.name = "Error";
                errorValue.stringData = "Data was not sent to GPU";
                errorValue.isString = true;
                values.push_back(errorValue);
            }
            return values;
        }
#endif

    private:
        /**
         * @brief This method creates GPU buffers and sends the data to the GPU.
         * @details This method will create the vertex array, vertex buffer and index buffer objects and send the data
         * to the GPU. This method also ensures that it is only called once. Even if the data is modified,
         * as the mesh is not prepared for modifications.
         * @todo Prepare the mesh for modifications.
         */
        void sendToGpuBuffers() const {
            if (wasDataSentToGpu) return;
            vertexArray = std::make_unique<GLESC::GAPI::VertexArray>();

            const void* bufferData = getVertices().data();
            size_t bufferCount = getVertices().size();
            size_t vertexBytes = sizeof(Vertex);
            GLESC::GAPI::Enums::BufferUsages bufferUsage = getBufferUsage(getRenderType());

            vertexArray->bind();

            vertexBuffer = std::make_unique<GLESC::GAPI::VertexBuffer>(
                bufferData,
                bufferCount,
                vertexBytes,
                bufferUsage
            );

            indexBuffer = std::make_unique<GLESC::GAPI::IndexBuffer>(
                getIndices().data(),
                getIndices().size());

            GLESC::GAPI::VertexBufferLayout layout;
            for (GLESC::GAPI::Enums::Types type : getVertexLayout()) {
                layout.push(type);
            }

            vertexArray->addBuffer(*vertexBuffer, layout);
            wasDataSentToGpu = true;
        }

        /**
         * @brief This destroys the buffers in the GPU, removing the data with it.
         * @details This will call gpu functions that will destroy the buffers in the GPU.
         * @details If needed to render again, must be called sendToGpuBuffers again.
         * @details If the data was never sent to the GPU, this method will do nothing.
         */
        void destroyBuffers() const {
            if (!wasDataSentToGpu) return;
            vertexArray->destroy();
            vertexBuffer->destroy();
            indexBuffer->destroy();
            wasDataSentToGpu = false;
        }


        const GLESC::GAPI::VertexArray& getVertexArray() const {
            D_ASSERT_TRUE(wasDataSentToGpu, "Data was not sent to GPU");
            return *vertexArray;
        }

        const GLESC::GAPI::IndexBuffer& getIndexBuffer() const {
            D_ASSERT_TRUE(wasDataSentToGpu, "Data was not sent to GPU");
            return *indexBuffer;
        }

        const GLESC::GAPI::VertexBuffer& getVertexBuffer() const {
            D_ASSERT_TRUE(wasDataSentToGpu, "Data was not sent to GPU");
            return *vertexBuffer;
        }

        /**
         * @brief Helper function to automatically calculate the normal of a face with 3 points.
         * @details The formula to calculate the normal of a face is:
         * normal = ((p2 - p1) x (p3 - p1)).normalize()
         * @param p1 The first point of the face.
         * @param p2 The second point of the face.
         * @param p3 The third point of the face.
         * @return The normal of the face.
         */
        Normal calculateNormal(const Position& p1, const Position& p2, const Position& p3) const {
            return (p2 - p1).cross(p3 - p1).normalize();
        }

        /**
         * @brief Helper function to calculate the hash of the mesh.
         * @details This method will calculate the hash of the mesh by hashing the vertices and indices.
         * @details This a heavy function and should be avoided.
         * @return The hash of the mesh.
         */
        size_t calculateHash() const {
            size_t hashValue = 0;

            // Hash vertex data
            for (const auto& vertex : vertices) {
                Hasher::hashCombine(hashValue, std::hash<Vertex>{}(vertex));
            }
            // Hash index data
            for (const auto& index : indices) {
                Hasher::hashCombine(hashValue, std::hash<Index>{}(index));
            }

            return hashValue;
        }

        RenderType renderType;
        std::vector<Math::FaceIndices> faces{};
        std::vector<Index> indices{};
        std::vector<Vertex> vertices{};

        /**
         * @brief The bounding volume of the mesh.
         * @details The bounding volume is a polyhedron cuboid that encloses the mesh. It is used for culling.
         */
        Math::BoundingVolume boundingVolume;
        /**
         * @brief The vertex layout of the mesh.
         * @details The vertex layout is a vector of Types that describes the layout of the
         * vertex data in the vertices vector. The layout is used to create the vertex buffer layout
         * for the vertex array object.
         */
        std::vector<GLESC::GAPI::Enums::Types> vertexLayout;

        /**
         * @brief A flag that indicates whether the mesh is dirty.
         * @details The flag is set to true when the mesh is modified. It is used to avoid unnecessary
         * updates to the vertex array object. It is mutable because it is modified by const methods, specifically
         * after rendering the mesh, we want to set the flag to false and nothing else.
         */
        mutable bool dirtyFlag = false;
        /**
         * @brief A flag that indicates whether the mesh is being built.
         * @details The mesh can only be modified while it is being built. If trying to modify the mesh while it is not
         * being built, the renderer will assert error.
         */
        mutable bool isBuilding = false;

        mutable size_t cachedHash = 0;
        mutable bool hashDirty = true;

        /**
         * @brief buffer that handles the indices of the mesh in the gpu.
         */
        mutable std::unique_ptr<GLESC::GAPI::IndexBuffer> indexBuffer;
        /**
         * @brief buffer that handles the vertices of the mesh in the gpu.
         */
        mutable std::unique_ptr<GLESC::GAPI::VertexBuffer> vertexBuffer;
        /**
         * @brief
         */
        mutable std::unique_ptr<GLESC::GAPI::VertexArray> vertexArray;
        /**
         * @details Flag to ensure that the data was sent to the gpu only once.
         */
        mutable bool wasDataSentToGpu = false;

        mutable std::mutex verticesMutex{};
        mutable std::mutex indicesMutex{};
        mutable std::mutex facesMutex{};
    }; // class Mesh

    using ColorMesh = Mesh<ColorVertex>;
    using TextureMesh = Mesh<TextureVertex>;
} // namespace GLESC

// Assuming the existence of a getAttributes() method that returns a tuple of all attributes.


template <typename Vertex>
struct std::hash<GLESC::Render::Mesh<Vertex>> {
    std::size_t operator()(const GLESC::Render::Mesh<Vertex>& mesh) const noexcept {
        return mesh.hash();
    }
};
