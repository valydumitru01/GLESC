

#include "engine/subsystems/renderer/camera/CameraPerspective.h"
#ifndef NDEBUG_GLESC
std::vector<EntityStatsManager::Value> GLESC::Render::CameraPerspective::getDebuggingValues() {
    std::vector<EntityStatsManager::Value> values;
    EntityStatsManager::Value fovValue;
    fovValue.name = "Fov";
    fovValue.data = reinterpret_cast<void*>(&fovDegrees);
    fovValue.type = EntityStatsManager::ValueType::FLOAT;
    fovValue.isModifiable = true;
    fovValue.usesSlider = true;
    fovValue.valueDirty = &dirty;
    fovValue.min = 0.1f; // Lower value crashes
    fovValue.max = 180.0f;
    values.push_back(fovValue);

    EntityStatsManager::Value viewWidthValue;
    viewWidthValue.name = "View Width";
    viewWidthValue.data = reinterpret_cast<void*>(&viewWidth);
    viewWidthValue.type = EntityStatsManager::ValueType::FLOAT;
    viewWidthValue.isModifiable = true;
    viewWidthValue.usesSlider = true;
    viewWidthValue.valueDirty = &dirty;
    viewWidthValue.min = 0.1f;
    viewWidthValue.max = 1000.0f;
    values.push_back(viewWidthValue);

    EntityStatsManager::Value viewHeightValue;
    viewHeightValue.name = "View Height";
    viewHeightValue.data = reinterpret_cast<void*>(&viewHeight);
    viewHeightValue.type = EntityStatsManager::ValueType::FLOAT;
    viewHeightValue.isModifiable = true;
    viewHeightValue.usesSlider = true;
    viewHeightValue.valueDirty = &dirty;
    viewHeightValue.min = 0.1f;
    viewHeightValue.max = 1000.0f;
    values.push_back(viewHeightValue);

    EntityStatsManager::Value nearPlaneValue;
    nearPlaneValue.name = "Near Plane";
    nearPlaneValue.data = reinterpret_cast<void*>(&nearPlane);
    nearPlaneValue.type = EntityStatsManager::ValueType::FLOAT;
    nearPlaneValue.isModifiable = true;
    nearPlaneValue.usesSlider = true;
    nearPlaneValue.valueDirty = &dirty;
    nearPlaneValue.min = 0.1f; // Lower value crashes
    nearPlaneValue.max = 1000.0f;
    values.push_back(nearPlaneValue);

    EntityStatsManager::Value farPlaneValue;
    farPlaneValue.name = "Far Plane";
    farPlaneValue.data = reinterpret_cast<void*>(&farPlane);
    farPlaneValue.type = EntityStatsManager::ValueType::FLOAT;
    farPlaneValue.isModifiable = true;
    farPlaneValue.usesSlider = true;
    farPlaneValue.valueDirty = &dirty;
    farPlaneValue.min = 0.2f;
    farPlaneValue.max = 1000.0f;
    values.push_back(farPlaneValue);

    return values;
}
#endif

std::string GLESC::Render::CameraPerspective::toString() const {
    return std::string("\n\tfov: ")
        + std::to_string(fovDegrees)
        + std::string("\n\tviewWidth: ")
        + std::to_string(viewWidth)
        + std::string("\n\tviewHeight: ")
        + std::to_string(viewHeight)
        + std::string("\n\tnearPlane: ")
        + std::to_string(nearPlane)
        + std::string("\n\tfarPlane: ")
        + std::to_string(farPlane);
}
