#include "engine/scene/engine-scenes/Default.h"

#include "engine/ecs/frontend/component/LightComponent.h"
#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"

using namespace GLESC;
static std::vector<ECS::Entity> entities;

void Default::init() {
    int itemsPerRow;
    int numOfRows;
    itemsPerRow = 50;
    numOfRows = 30;
#ifndef NDEBUG
    itemsPerRow = 10; // Number of items per row
    numOfRows = 4; // Total number of different material properties to test: diffuse, specular, emission
#endif
    std::vector<std::function<void(Render::Material&, float)>> propertySetters = {
        // Set both color and intensity for diffuse property
        [](Render::Material& mat, float value) {
            mat.setDiffuseColor(Render::ColorRgb(value * 255, 255 - value * 255, 0));
            mat.setDiffuseIntensity(value);
        },
        // Set both color and intensity for specular property
        [](Render::Material& mat, float value) {
            mat.setSpecularColor(Render::ColorRgb(0, value * 255, 255 - value * 255));
            mat.setSpecularIntensity(value);
        },
        // Set both color and intensity for emission property
        [](Render::Material& mat, float value) {
            mat.setEmissionColor(Render::ColorRgb(255 - value * 255, 0, value * 255));
            mat.setEmmissionIntensity(value);
        },
        // Set shininess property
        [](Render::Material& mat, float value) {
            mat.setShininess(value);
        }

    };

    for (int rowIndex = 0; rowIndex < numOfRows; ++rowIndex) {
        for (int i = 0; i < itemsPerRow; ++i) {
            ECS::Entity entity = createEntity("entity", {EntityType::Instance})
                                 .addComponent<ECS::TransformComponent>()
                                 .addComponent<ECS::RenderComponent>();


            // Calculate increment to vary color and intensity
            float increment = Math::clamp(static_cast<float>(i) / static_cast<float>(itemsPerRow - 1), 0.0f, 1.0f);
            // Choosing a color
            Render::ColorRgba color = Render::ColorRgba(255, 255, 255, 255);

            float sizeIncrement = increment * 0.5f;
            if (i % 3 == 1)
                entity.getComponent<ECS::RenderComponent>().moveMesh(
                    Render::MeshFactory::sphere(4 + i, 4 + i, 1, color));
            else if (i % 3 == 2)
                entity.getComponent<ECS::RenderComponent>().moveMesh(
                    Render::MeshFactory::pyramid(1 + sizeIncrement, 1 + sizeIncrement, 1 - sizeIncrement, color));
            else
                entity.getComponent<ECS::RenderComponent>().moveMesh(
                    Render::MeshFactory::cuboid(1, 1 + sizeIncrement, 1 - sizeIncrement, color));
            // Position entities in a row
            Transform::Position position = Transform::Position(i * 3, rowIndex * 3, 0);
            entity.getComponent<ECS::TransformComponent>().transform.setPosition(position);

            // Apply both color and intensity settings using the property setter
            propertySetters[rowIndex % propertySetters.size()](entity.getComponent<ECS::RenderComponent>().getMaterial(), increment);

            // Put a light in front of all entities
            ECS::Entity lighteEntity = createEntity("light", {EntityType::Instance})
                                       .addComponent<ECS::TransformComponent>()
                                       .addComponent<ECS::LightComponent>();

            Transform::Position lightPosition = Transform::Position(i * 3, rowIndex * 3, 5);
            lighteEntity.getComponent<ECS::TransformComponent>().transform.setPosition(lightPosition);


            // Add to entities list
            entities.push_back(entity);
        }
    }

    // Create a bunch of spheres with increasingly more slices and stacks
    int numberOfSpheres = 10;
    int stepOfPosition = 2;
    for (int i = 0; i < numberOfSpheres; ++i) {
        ECS::Entity entity = createEntity("sphere", {EntityType::Instance})
                             .addComponent<ECS::TransformComponent>()
                             .addComponent<ECS::RenderComponent>();

        // Calculate increment to vary color and intensity
        float increment = Math::clamp(static_cast<float>(i) / static_cast<float>(numberOfSpheres - 1), 0.0f, 1.0f);
        // Choosing a color
        Render::ColorRgba color = Render::ColorRgba(255, 255, 255, 255);

        entity.getComponent<ECS::RenderComponent>().moveMesh(
            Render::MeshFactory::sphere(2 + i, 2 + i, 1, color));

        // Position entities in a row
        Transform::Position position = Transform::Position(i * stepOfPosition, 0, 20);
        entity.getComponent<ECS::TransformComponent>().transform.setPosition(position);

        // Apply both color and intensity settings using the property setter
        propertySetters[0](entity.getComponent<ECS::RenderComponent>().getMaterial(), increment);
    }
    // A light for the spheres
    ECS::Entity lighteEntity = createEntity("lightForSpheres")
                               .addComponent<ECS::TransformComponent>()
                               .addComponent<ECS::LightComponent>();
    lighteEntity.getComponent<ECS::TransformComponent>().transform.setPosition(
        {numberOfSpheres * stepOfPosition, 0, 18});
}

void Default::update() {
    for (auto& entity : entities) {
        auto& transform = entity.getComponent<ECS::TransformComponent>().transform;
        transform.addRotation(Transform::Rotation(0.01, 0.01, 0.1));
    }
}
