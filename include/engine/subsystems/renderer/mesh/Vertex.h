#pragma once


#include <tuple>
#include <string>
#include "engine/core/low-level-renderer/graphic-api/GapiStructs.h"

namespace GLESC {
    template <std::size_t Size, typename Type>
    class VertexAttrib {
    public:
        std::size_t size;
        Type data[Size];
    };

    template <typename... Attributes>
    class Vertex {
    public:
        Vertex(Attributes... args) : attributes(args...) {}

        [[nodiscard]] size_t size() const {
            return sizeof...(Attributes);
        }

        /**
         * @brief Get the attributes of the vertex, compile time
         * @return A tuple with the attributes of the vertex
         */
        template<std::size_t index>
        [[nodiscard]] constexpr decltype(auto) getAttribute() const {
            return std::get<index>(attributes);
        }


        [[nodiscard]] std::tuple<Attributes...> getAttributes() const {
            return attributes;
        }

        [[nodiscard]] std::string toString() const {
            std::string result = "Vertex: ";
            std::apply([&result](auto&&... args) {
                ((result += args.toString() + " "), ...);
            }, attributes);
            return result;
        }

        [[nodiscard]] bool operator==(const Vertex& other) const {
            return attributes == other.attributes;
        }

        [[nodiscard]] bool operator!=(const Vertex& other) const {
            return !(*this == other);
        }

    private:
        std::tuple<Attributes...> attributes;
    };
} // namespace GLESC

template <typename... Attributes>
struct std::hash<GLESC::Vertex<Attributes...>> {
    std::size_t operator()(const GLESC::Vertex<Attributes...>& vertex) const {
        std::size_t hash = 0;
        std::apply([&hash](const auto&... args) {
            // Directly call hashCombine without attempting to assign its result.
            (..., (GLESC::Hasher::hashCombine(hash, std::hash<std::decay_t<decltype(args)>>{}(args)), void()));
        }, vertex.getAttributes());
        return hash;
    }
};