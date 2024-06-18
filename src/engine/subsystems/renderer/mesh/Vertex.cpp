


#include "engine/subsystems/renderer/mesh/Vertex.h"

std::vector<GLESC::GAPI::Enums::Types> GLESC::Render::BaseVertex::layout = {
    GAPI::Enums::Types::Vec3F,
    GAPI::Enums::Types::Vec3F
};

std::vector<GLESC::GAPI::Enums::Types> GLESC::Render::ColorVertex::layout = {
    GAPI::Enums::Types::Vec3F,
    GAPI::Enums::Types::Vec3F,
    GAPI::Enums::Types::Vec4F
};

std::vector<GLESC::GAPI::Enums::Types> GLESC::Render::TextureVertex::layout = {
    GAPI::Enums::Types::Vec3F,
    GAPI::Enums::Types::Vec3F,
    GAPI::Enums::Types::Vec2F
};
