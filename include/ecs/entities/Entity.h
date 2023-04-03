#pragma once

#include "core/Types.h"
#include "core/ECSContainer.h"
#include "ecs/components/ComponentArray.h"
#include "ecs/components/Component.h"

#include <memory>
#include <cassert>
#include <queue>
#include <array>
#include <unordered_map>


class Entity {
private:
    inline void entitySignatureChanged() const;

public:
    Entity();

    ~Entity();

    /**
     * @brief Adds a component to the entity and returns a reference to it
     * The components is registered to the ECSComponentContainer
     * The entity signature is updated to reflect the new component
     * @tparam T
     */
    template<typename T>
    void addComponent();
    /**
     * @brief Removes a component from the entity
     * The entity signature is updated to reflect the removed component
     *
     * @tparam T
     */
    template<typename T>
    void removeComponent();
    /**
     * @brief Returns a reference to the component
     * @tparam T
     * @return
     */
    template<typename T>
    T &getComponent() const;

    template<typename T>
    [[nodiscard]] bool hasComponent() const;

    [[nodiscard]] EntityID getID() const;

    [[nodiscard]] Signature getSignature() const;

    [[nodiscard]] bool isAlive() const;

    void destroy();

    void revive();




private:
    /**
     * @brief The entity's ID
     * The ID is used to identify the entity in the ECSContainer
     */
    EntityID ID;
};


