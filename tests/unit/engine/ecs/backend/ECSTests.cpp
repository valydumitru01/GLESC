/**************************************************************************************************
 * @file   ECSTests.cpp
 * @author Valentin Dumitru
 * @date   27/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "TestsConfig.cpp"
#if ECS_BACKEND_UNIT_TESTING
#include <gtest/gtest.h>
#include "engine/ecs/backend/ECS.h"
#include "unit/CustomTestingFramework.cpp"

class ECSTests : public testing::Test {
protected:
    ECSTests() = default;

    void SetUp() override {}

    void TearDown() override {}

    GLESC::ECS::ECSCoordinator ecs;

    struct TestComponent1 : GLESC::ECS::IComponent {
        TestComponent1() = default;
        explicit TestComponent1(int x) : x(x) {}
        int x{};
        [[nodiscard]] std::string toString() const override { return "x: " + std::to_string(x); }
        [[nodiscard]] std::string getName() const override { return "TestComponent1"; }
        void setDebuggingValues() override {}
    };

    struct TestComponent2 : GLESC::ECS::IComponent {
        TestComponent2() = default;
        explicit TestComponent2(int y) : y(y) {}
        int y{};
        [[nodiscard]] std::string toString() const override { return "y: " + std::to_string(y); }
        [[nodiscard]] std::string getName() const override { return "TestComponent2"; }
        void setDebuggingValues() override {}
    };

    struct TestComponent3 : GLESC::ECS::IComponent {
        TestComponent3() = default;
        explicit TestComponent3(int z) : z(z) {}
        int z{};
        [[nodiscard]] std::string toString() const override { return "z: " + std::to_string(z); }
        [[nodiscard]] std::string getName() const override { return "TestComponent3"; }
        void setDebuggingValues() override {}
    };

    TestComponent1 testComponent1{3};
    TestComponent2 testComponent2{4};
    TestComponent3 testComponent3{5};
    GLESC::ECS::EntityManager& getEntityManager() { return ecs.entityManager; }
    GLESC::ECS::ComponentManager& getComponentManager() { return ecs.componentManager; }
    GLESC::ECS::SystemManager& getSystemManager() { return ecs.systemManager; }
};

TEST_F(ECSTests, EmptyState) {
    TEST_SECTION("Checking Entity Manager state");
    ASSERT_TRUE(getEntityManager().getEntityNameToID().empty());
    ASSERT_TRUE(getEntityManager().getEntityIDToName().empty());
    ASSERT_EQ(getEntityManager().getSignatures().size(), GLESC::ECS::maxEntities);
    ASSERT_EQ(getEntityManager().getAvailableEntities().size(), GLESC::ECS::maxEntities);
    ASSERT_EQ(getEntityManager().getLivingEntityCount(), 0);

    TEST_SECTION("Checking Component Manager state");
    ASSERT_TRUE(getComponentManager().getComponentIDs().empty());
    ASSERT_TRUE(getComponentManager().getComponentArrays().empty());
    ASSERT_EQ(getComponentManager().getNextComponentID(), GLESC::ECS::ComponentManager::firstComponentID);

    TEST_SECTION("Checking System Manager state");
    ASSERT_TRUE(getSystemManager().getAllAssociatedEntities().empty());
    ASSERT_TRUE(getSystemManager().getSystemSignatures().empty());
}

TEST_F(ECSTests, CreateEntity) {
    GLESC::ECS::EntityID entityID = ecs.createEntity("TestEntity");
    ASSERT_EQ(getEntityManager().getLivingEntityCount(), 1);
    ASSERT_EQ(getEntityManager().getEntityNameToID().size(), 1);
    ASSERT_EQ(getEntityManager().getEntityIDToName().size(), 1);
    ASSERT_EQ(getEntityManager().getAvailableEntities().size(), GLESC::ECS::maxEntities -1);
    ASSERT_EQ(getEntityManager().getSignatures().size(), GLESC::ECS::maxEntities);
    ASSERT_EQ(getEntityManager().getSignatures().at(entityID).to_ullong(), 0);
}

TEST_F(ECSTests, DestroyEntity) {
    GLESC::ECS::EntityID entityID = ecs.createEntity("TestEntity");
    ecs.destroyEntity(entityID);
    ASSERT_EQ(getEntityManager().getLivingEntityCount(), 0);
    ASSERT_TRUE(getEntityManager().getEntityNameToID().empty());
    ASSERT_TRUE(getEntityManager().getEntityIDToName().empty());
    ASSERT_EQ(getEntityManager().getAvailableEntities().size(), GLESC::ECS::maxEntities);
    ASSERT_EQ(getEntityManager().getSignatures().size(), GLESC::ECS::maxEntities);
    ASSERT_EQ(getEntityManager().getSignatures().at(entityID).to_ullong(), 0);
}

TEST_F(ECSTests, GetEntityID) {
    GLESC::ECS::EntityID entityID = ecs.createEntity("TestEntity");
    ASSERT_EQ(getEntityManager().getEntityNameToID().at("TestEntity"), entityID);
    ASSERT_EQ(getEntityManager().getEntityIDToName().at(entityID), "TestEntity");
}

TEST_F(ECSTests, TryGetEntityID) {
    GLESC::ECS::EntityID entityID = ecs.createEntity("TestEntity");
    ASSERT_EQ(ecs.tryGetEntityID("TestEntity"), entityID);
    // Now checking for non-existent entity
    ASSERT_EQ(ecs.tryGetEntityID("NonExistentEntity"), GLESC::ECS::EntityManager::nullEntity);
}

TEST_F(ECSTests, GetEntityName) {
    GLESC::ECS::EntityID entityID = ecs.createEntity("TestEntity");
    ASSERT_TRUE(getEntityManager().getEntityName(entityID) == "TestEntity");
}


TEST_F(ECSTests, AddComponent) {
    GLESC::ECS::EntityID entityID = ecs.createEntity("TestEntity");
    ecs.registerSystem("TestSystem");
    ecs.addComponent<TestComponent1>(entityID, testComponent1);
    ASSERT_EQ(getComponentManager().getComponentIDs().size(), 1);
    ASSERT_EQ(getComponentManager().getComponentArrays().size(), 1);
    ASSERT_EQ(getComponentManager().getComponentID<TestComponent1>(), GLESC::ECS::ComponentManager::firstComponentID);
    ASSERT_EQ(getEntityManager().getSignature(entityID).to_ullong(), 1);
}

TEST_F(ECSTests, RemoveComponent) {
    GLESC::ECS::EntityID entityID = ecs.createEntity("TestEntity");
    ecs.registerSystem("TestSystem");
    ecs.addComponent<TestComponent1>(entityID, testComponent1);
    ecs.removeComponent<TestComponent1>(entityID);
    // Even if the component is removed, it still is registered, and therefore has ID assigned to its type
    ASSERT_EQ(getComponentManager().getComponentIDs().size(), 1);
    ASSERT_EQ(getComponentManager().getComponentArrays().size(), 1);
    // The signature should be 0, as the component was removed
    ASSERT_EQ(getEntityManager().getSignature(entityID).to_ullong(), 0);
}

TEST_F(ECSTests, DoesEntityHaveComponent) {
    GLESC::ECS::EntityID entityID = ecs.createEntity("TestEntity");
    GLESC::ECS::EntityID entityID2 = ecs.createEntity("TestEntity2");
    ecs.registerSystem("TestSystem");
    ecs.addComponent<TestComponent1>(entityID, testComponent1);
    ecs.addComponent<TestComponent2>(entityID2, testComponent2);
    ASSERT_TRUE(ecs.hasComponent<TestComponent1>(entityID));
    ASSERT_FALSE(ecs.hasComponent<TestComponent2>(entityID));
}


TEST_F(ECSTests, GetComponentID) {
    GLESC::ECS::EntityID entityID = ecs.createEntity("TestEntity");
    ecs.registerSystem("TestSystem");
    ecs.addComponent<TestComponent1>(entityID, testComponent1);
    ASSERT_EQ(ecs.getComponentID<TestComponent1>(), GLESC::ECS::ComponentManager::firstComponentID);
}

TEST_F(ECSTests, GetComponent) {
    GLESC::ECS::EntityID entityID = ecs.createEntity("TestEntity");
    ecs.registerSystem("TestSystem");
    ecs.addComponent<TestComponent1>(entityID, testComponent1);
    ASSERT_EQ(ecs.getComponent<TestComponent1>(entityID).x, testComponent1.x);
}

TEST_F(ECSTests, GetComponents) {
    GLESC::ECS::EntityID entityID = ecs.createEntity("TestEntity");
    ecs.registerSystem("TestSystem");
    ecs.addComponent<TestComponent1>(entityID, TestComponent1(1));
    ecs.addComponent<TestComponent2>(entityID, TestComponent2(2));
    ecs.addComponent<TestComponent3>(entityID, TestComponent3(3));
    std::vector<GLESC::ECS::IComponent*> components = ecs.getComponents(entityID);
    ASSERT_EQ(components.size(), 3);
    for (auto component : components) {
        if (component->getName() == "TestComponent1") {
            ASSERT_EQ(dynamic_cast<TestComponent1*>(component)->x, TestComponent1(1).x);
        } else if (component->getName() == "TestComponent2") {
            ASSERT_EQ(dynamic_cast<TestComponent2*>(component)->y, TestComponent2(2).y);
        } else if (component->getName() == "TestComponent3") {
            ASSERT_EQ(dynamic_cast<TestComponent3*>(component)->z, TestComponent3(3).z);
        }
    }

    GLESC::ECS::EntityID entityID2 = ecs.createEntity("TestEntity2");
    ecs.addComponent<TestComponent1>(entityID2, TestComponent1(4));
    ecs.addComponent<TestComponent2>(entityID2, TestComponent2(5));
    std::vector<GLESC::ECS::IComponent*> components2 = ecs.getComponents(entityID2);
    ASSERT_EQ(components2.size(), 2);
    for (auto component : components2) {
        if (component->getName() == "TestComponent1") {
            ASSERT_EQ(dynamic_cast<TestComponent1*>(component)->x, TestComponent1(4).x);
        } else if (component->getName() == "TestComponent2") {
            ASSERT_EQ(dynamic_cast<TestComponent2*>(component)->y, TestComponent2(5).y);
        }
    }

    GLESC::ECS::EntityID entityID3 = ecs.createEntity("TestEntity3");
    ecs.addComponent<TestComponent1>(entityID3, TestComponent1(6));
    ecs.addComponent<TestComponent2>(entityID3, TestComponent2(7));
    ecs.addComponent<TestComponent3>(entityID3, TestComponent3(8));
    std::vector<GLESC::ECS::IComponent*> components3 = ecs.getComponents(entityID3);
    ASSERT_EQ(components3.size(), 3);
    for (auto component : components3) {
        if (component->getName() == "TestComponent1") {
            ASSERT_EQ(dynamic_cast<TestComponent1*>(component)->x, TestComponent1(6).x);
        } else if (component->getName() == "TestComponent2") {
            ASSERT_EQ(dynamic_cast<TestComponent2*>(component)->y, TestComponent2(7).y);
        } else if (component->getName() == "TestComponent3") {
            ASSERT_EQ(dynamic_cast<TestComponent3*>(component)->z, TestComponent3(8).z);
        }
    }


}


TEST_F(ECSTests, RegisterSystem) {
    GLESC::ECS::SystemName systemName{"TestSystem"};
    ecs.registerSystem(systemName);
    ASSERT_TRUE(getSystemManager().isSystemRegistered(systemName));
    ASSERT_TRUE(getSystemManager().getAssociatedEntitiesOfSystem(systemName).empty());
    ASSERT_EQ(getSystemManager().getSystemSignatures().at(systemName).to_ullong(), 0);
}

TEST_F(ECSTests, AddComponentRequirementToSystem) {
    GLESC::ECS::SystemName systemName{"TestSystem"};
    ecs.registerSystem(systemName);
    ecs.addComponentRequirementToSystem<TestComponent1>(systemName);
    ASSERT_TRUE(getSystemManager().isSystemRegistered(systemName));
    ASSERT_TRUE(getSystemManager().getAssociatedEntitiesOfSystem(systemName).empty());
    ASSERT_EQ(getSystemManager().getSystemSignatures().at(systemName).to_ullong(), 1);
}

TEST_F(ECSTests, GetAssociatedEntities) {
    GLESC::ECS::SystemName systemName{"TestSystem"};
    ecs.registerSystem(systemName);
    ecs.addComponentRequirementToSystem<TestComponent1>(systemName);
    GLESC::ECS::EntityID entityID = ecs.createEntity("TestEntity");
    ecs.addComponent<TestComponent1>(entityID, testComponent1);
    ASSERT_EQ(ecs.getAssociatedEntities(systemName).size(), 1);

    // More than one entity
    GLESC::ECS::EntityID entityID2 = ecs.createEntity("TestEntity2");
    ecs.addComponent<TestComponent1>(entityID2, testComponent1);
    ASSERT_EQ(ecs.getAssociatedEntities(systemName).size(), 2);
}


#endif
