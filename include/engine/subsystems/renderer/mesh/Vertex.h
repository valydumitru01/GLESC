#pragma once


#include <functional>
#include <string>
#include <utility>
#include "engine/core/low-level-renderer/graphic-api/GapiStructs.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
#pragma pack(push, 1)
    /**
     * @brief Represents the base Vertex in the mesh
     * @details This is tightly packed, and so are all of its members
     */
    class BaseVertex {
    public:
        [[nodisacrd]] static const std::vector<GAPI::Enums::Types>& getLayout() { return layout; }
        BaseVertex(Position  position, Normal  normal)
            : position(std::move(position)), normal(std::move(normal)) {
        }

        [[nodisacrd]] bool operator==(const BaseVertex& other) const {
            return position == other.position && normal == other.normal;
        }

        [[nodiscard]] const Position& getPosition() const { return position; }
        [[nodiscard]] Position& getPosition() { return position; }
        [[nodiscard]] const Normal& getNormal() const { return normal; }
        [[nodiscard]] Normal& getNormal() { return normal; }

        void setPosition(const Position& positionParam) { position = positionParam; }
        void setNormal(const Normal& normalParam) { normal = normalParam; }
        static std::vector<GAPI::Enums::Types> layout;

        [[nodiscard]] std::string toString() const {
            return "Position: " + position.toString() + " Normal: " + normal.toString();
        }

    private:
        Position position;
        Normal normal;
    };

    /**
     * @brief Represents a vertex with color
     * @details This is tightly packed, and so are all of its members
     */
    class ColorVertex : public BaseVertex {
    public:
        [[nodisacrd]] static const std::vector<GAPI::Enums::Types>& getLayout() { return layout; }
        ColorVertex(const Position& position, const Normal& normal, const ColorRgba& color)
            : BaseVertex(position, normal), color(color) {
        }

        bool operator==(const ColorVertex& other) const {
            return BaseVertex::operator==(other) && color == other.color;
        }

        [[nodiscard]] const ColorRgbaNorm& getColor() const { return color; }
        void setColor(const ColorRgba& colorParam) { color = colorParam; }
        [[nodiscard]] std::string toString() const {
            return BaseVertex::toString() + " Color: " + color.toString();
        }
    private:
        ColorRgbaNorm color;
        static std::vector<GAPI::Enums::Types> layout;
    };

    /**
     * @brief Represents a vertex with texture coordinates
     * @details This is tightly packed, and so are all of its members
     */
    class TextureVertex : public BaseVertex {
    public:
        [[nodisacrd]] static const std::vector<GAPI::Enums::Types>& getLayout() { return layout; }
        TextureVertex(const Position& position, const Normal& normal, UV  textureCoordinate)
            : BaseVertex(position, normal), textureCoordinate(std::move(textureCoordinate)) {
        }

        bool operator==(const TextureVertex& other) const {
            return BaseVertex::operator==(other) && textureCoordinate == other.textureCoordinate;
        }

        [[nodiscard]] const UV& getTextureCoordinate() const { return textureCoordinate; }
        void setTextureCoordinate(const UV& textureCoordinateParam) { textureCoordinate = textureCoordinateParam; }
        [[nodiscard]] std::string toString() const {
            return BaseVertex::toString() + " Texture Coordinate: " + textureCoordinate.toString();
        }
    private:
        UV textureCoordinate;
        static std::vector<GAPI::Enums::Types> layout;
    };
#pragma pack(pop)
} // namespace GLESC
namespace std {
    template <>
    struct hash<GLESC::Render::BaseVertex> {
        size_t operator()(const GLESC::Render::BaseVertex& vertex) const noexcept {
            return std::hash<GLESC::Render::Position>()(vertex.getPosition()) ^
                std::hash<GLESC::Render::Normal>()(vertex.getNormal());
        }
    };

    template <>
    struct hash<GLESC::Render::ColorVertex> {
        size_t operator()(const GLESC::Render::ColorVertex& vertex) const noexcept {
            GLESC::Hasher::Hash hash = std::hash<GLESC::Render::BaseVertex>()(vertex);
            GLESC::Hasher::hashCombine(hash, std::hash<GLESC::Render::ColorRgbaNorm>()(vertex.getColor()));
            return hash;
        }
    };

    template <>
    struct hash<GLESC::Render::TextureVertex> {
        size_t operator()(const GLESC::Render::TextureVertex& vertex) const noexcept {
            GLESC::Hasher::Hash hash = std::hash<GLESC::Render::BaseVertex>()(vertex);
            GLESC::Hasher::hashCombine(hash, std::hash<GLESC::Render::UV>()(vertex.getTextureCoordinate()));
            return hash;
        }
    };
} // namespace std
