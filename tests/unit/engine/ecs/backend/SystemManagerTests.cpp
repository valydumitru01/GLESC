/**************************************************************************************************
 * @file   SystemManagerTests.cpp
 * @author Valentin Dumitru
 * @date   29/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "TestsConfig.h"
#if ECS_BACKEND_UNIT_TESTING
#include <gtest/gtest.h>
#include "engine/ecs/backend/system/SystemManager.h"
#include "unit/CustomTestingFramework.h"

class SystemManagerTests : public testing::Test {
protected:
    SystemManagerTests() = default;

    void SetUp() override {}

    void TearDown() override {}

    GLESC::ECS::SystemManager& getSystemManager() {
        return systemManager;
    }

    GLESC::ECS::SystemManager systemManager;
};


TEST_F(SystemManagerTests, EmptyState) {
    ASSERT_TRUE(getSystemManager().getAllAssociatedEntities().empty());
    ASSERT_TRUE(getSystemManager().getSystemSignatures().empty());
}

TEST_F(SystemManagerTests, RegisterSystem) {
    GLESC::ECS::SystemName systemName{"TestSystem"};
    getSystemManager().registerSystem(systemName);

    TEST_SECTION("Check ComponentManager interface");
    ASSERT_TRUE(getSystemManager().isSystemRegistered(systemName));
    ASSERT_TRUE(getSystemManager().getAssociatedEntitiesOfSystem(systemName).empty());

    TEST_SECTION("Check manually data structures");
    ASSERT_TRUE(getSystemManager().getSystemSignatures().at(systemName).to_ullong() == 0);
    ASSERT_TRUE(getSystemManager().getAllAssociatedEntities().at(systemName).empty());
}

TEST_F(SystemManagerTests, AddComponentRequirementToSystem) {
    GLESC::ECS::SystemName systemName{"TestSystem"};
    getSystemManager().registerSystem(systemName);

    GLESC::ECS::ComponentID componentID{1};
    getSystemManager().addComponentRequirementToSystem(systemName, componentID);

    GLESC::ECS::Signature expectedSignature = 0;
    expectedSignature.set(componentID);

    TEST_SECTION("Check ComponentManager interface");
    ASSERT_TRUE(getSystemManager().isSystemRegistered(systemName));
    ASSERT_TRUE(getSystemManager().getAssociatedEntitiesOfSystem(systemName).empty());

    TEST_SECTION("Check manually data structures");
    ASSERT_EQ(getSystemManager().getSystemSignatures().at(systemName), expectedSignature);
    ASSERT_TRUE(getSystemManager().getAllAssociatedEntities().at(systemName).empty());

    // Add more components
    GLESC::ECS::ComponentID componentID2{2};
    GLESC::ECS::ComponentID componentID3{3};

    expectedSignature.set(componentID2);
    expectedSignature.set(componentID3);

    getSystemManager().addComponentRequirementToSystem(systemName, componentID2);
    getSystemManager().addComponentRequirementToSystem(systemName, componentID3);

    ASSERT_TRUE(getSystemManager().getSystemSignatures().at(systemName) == expectedSignature);
}

TEST_F(SystemManagerTests, EntitySignatureChanged) {
    GLESC::ECS::SystemName systemName{"TestSystem"};
    getSystemManager().registerSystem(systemName);

    GLESC::ECS::ComponentID componentID{1};
    getSystemManager().addComponentRequirementToSystem(systemName, componentID);

    GLESC::ECS::EntityID entityID{1};
    GLESC::ECS::Signature entitySignature = 0;
    entitySignature.set(componentID);

    getSystemManager().entitySignatureChanged(entityID, entitySignature);

    // Check that the entity is associated with the system
    ASSERT_TRUE(getSystemManager().isEntityAssociatedWithSystem(systemName, entityID));
    ASSERT_TRUE(getSystemManager().getAssociatedEntitiesOfSystem(systemName).size() == 1);
    ASSERT_TRUE(getSystemManager().getAssociatedEntitiesOfSystem(systemName).count(entityID) == 1);

    // Change the entity signature
    entitySignature = 0;
    getSystemManager().entitySignatureChanged(entityID, entitySignature);

    // Check that the entity is no longer associated with the system
    ASSERT_TRUE(getSystemManager().getAssociatedEntitiesOfSystem(systemName).empty());
}

TEST_F(SystemManagerTests, MultipleSystemsWithMultipleEntities) {
    const int numberOfEntities = 100;
    const int numberOfSystems = 5;
    const int componentsPerSystem = 2; // Assuming each system is interested in 2 unique components.

    // Add components to the systems
    // Each system will require 2 components, and there are 5 systems and 10 components
    // Therefore each system will have it's index * 2 and index * 2 + 1 as required components
    // For example:
    // System 0 will require components 0 and 1
    // System 1 will require components 2 and 3
    // System 2 will require components 4 and 5
    // ...
    for (int i = 0; i < numberOfSystems; ++i) {
        GLESC::ECS::SystemName systemName = "TestSystem" + std::to_string(i);
        getSystemManager().registerSystem(systemName);

        // Assigning component requirements to each system.
        for (int j = 0; j < componentsPerSystem; ++j) {
            // ComponentID calculation assumes a unique ID for each component across all systems.
            GLESC::ECS::ComponentID componentID = i * componentsPerSystem + j;
            getSystemManager().addComponentRequirementToSystem(systemName, componentID);
        }
    }

    // Set the entity changes
    // Each entity will have the same number of components as the system so it gets associated with it
    // For example:
    // Entity 0 will have components 0 and 1
    // Entity 1 will also have components 0 and 1
    // ...
    // Entity 9 will also have components 0 and 1
    // Then entity 11 will have components 2 and 3
    // And so on until 99
    for (GLESC::ECS::EntityID entityID = 0; entityID < numberOfEntities; ++entityID) {
        // Assuming a simple round-robin distribution of entities across systems.
        int systemIndex = entityID % numberOfSystems;
        GLESC::ECS::Signature signature = 0;

        // Update signature to include the components required by the target system.
        for (int j = 0; j < componentsPerSystem; ++j) {
            GLESC::ECS::ComponentID componentID = systemIndex * componentsPerSystem + j;
            signature.set(componentID);
        }
        getSystemManager().entitySignatureChanged(entityID, signature);
    }

    // Check the associated entities
    // Each system will have 20 entities associated with it, as there are 100 entities and 5 systems
    // Also, we check that each system has the correct entities associated with it
    // For example:
    // System 0 will have entities 0 to 19 associated with it
    // System 1 will have entities 20 to 39 associated with it
    // ...
    for (int i = 0; i < numberOfSystems; ++i) {
        GLESC::ECS::SystemName systemName = "TestSystem" + std::to_string(i);
        auto associatedEntities = getSystemManager().getAssociatedEntitiesOfSystem(systemName);

        // Expecting an even distribution of entities across systems.
        int expectedEntitiesPerSystem = numberOfEntities / numberOfSystems;
        ASSERT_EQ(associatedEntities.size(), expectedEntitiesPerSystem) << "System " << systemName <<
            " does not have the correct number of associated entities.";
    }
}

#endif // ECS_BACKEND_UNIT_TESTING