/**************************************************************************************************
 * @file   EntityManagerTests.cpp
 * @author Valentin Dumitru
 * @date   29/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "TestsConfig.cpp"
#if ECS_BACKEND_UNIT_TESTING
#include <gtest/gtest.h>
#include "engine/ecs/backend/entity/EntityManager.h"
#include "unit/CustomTestingFramework.cpp"

class EntityManagerTests : public testing::Test {
protected:
    EntityManagerTests() = default;

    void SetUp() override {}

    void TearDown() override {}

    GLESC::ECS::EntityManager& getEntityManager() {
        return entityManager;
    }

    static constexpr GLESC::ECS::EntityID firstEntityID = GLESC::ECS::EntityManager::firstEntity;
    GLESC::ECS::EntityManager entityManager;
};


TEST_F(EntityManagerTests, EmptyState) {
    // Assert that the entity manager is empty
    ASSERT_TRUE(getEntityManager().getEntityNameToID().empty());
    ASSERT_TRUE(getEntityManager().getEntityIDToName().empty());
    ASSERT_TRUE(getEntityManager().getSignatures().size() == GLESC::ECS::maxEntities);
    ASSERT_TRUE(getEntityManager().getAvailableEntities().size() == GLESC::ECS::maxEntities);
    ASSERT_TRUE(getEntityManager().getLivingEntityCount() == 0);
}


TEST_F(EntityManagerTests, CreateEntity) {
    GLESC::ECS::EntityID entity = entityManager.createNextEntity("TestEntity");

    // The entity ID is the first entity ID
    ASSERT_EQ(entity, firstEntityID);
    // The living entity count is one
    ASSERT_TRUE(getEntityManager().getLivingEntityCount() == 1);
    // The available entities queue size is the maximum minus one, as we just created an entity
    ASSERT_EQ(getEntityManager().getAvailableEntities().size(), GLESC::ECS::maxEntities - 1);
    // The entity IDs size is one
    ASSERT_TRUE(getEntityManager().getEntityNameToID().size() == 1);
    ASSERT_TRUE(getEntityManager().getEntityIDToName().size() == 1);
    // The entity IDs map contains the name of the entity we just created with the ID of the entity
    ASSERT_TRUE(getEntityManager().getEntityNameToID().at("TestEntity") == entity);
    ASSERT_TRUE(getEntityManager().getEntityIDToName().at(entity) == "TestEntity");
    // The signature of the entity we just created is empty, as it has no components
    ASSERT_TRUE(getEntityManager().getSignature(entity).to_ulong() == 0);
}

TEST_F(EntityManagerTests, CanEntityBeCreated) {
    // Assert that the entity manager can create an entity
    ASSERT_TRUE(getEntityManager().canEntityBeCreated("TestEntity"));
    // Create an entity
    entityManager.createNextEntity("TestEntity");
    // Now the entity manager cannot create an entity with the same name
    ASSERT_FALSE(getEntityManager().canEntityBeCreated("TestEntity"));
}

TEST_F(EntityManagerTests, TryGetEntity) {
    using namespace GLESC::ECS;
    EntityID entity = entityManager.createNextEntity("TestEntity");

    EntityID foundEntity = getEntityManager().tryGetEntity("TestEntity");

    // The IDs are the same
    ASSERT_EQ(entity, foundEntity);
    // The accessed entity is not null
    ASSERT_TRUE(foundEntity != GLESC::ECS::EntityManager::nullEntity);
    // The entity exists
    ASSERT_TRUE(getEntityManager().doesEntityExist(foundEntity));
    // Checking if an existing entity name exists
    ASSERT_TRUE(getEntityManager().doesEntityExist("TestEntity"));
    // Checking if an existing entity can be created (it should not)
    ASSERT_FALSE(getEntityManager().canEntityBeCreated("TestEntity"));
}

TEST_F(EntityManagerTests, TryGetEntityNullEntity) {
    using namespace GLESC::ECS;
    EntityID nullEntity = getEntityManager().tryGetEntity("TestEntity");

    // The accessed entity is null
    ASSERT_TRUE(nullEntity == GLESC::ECS::EntityManager::nullEntity);
    // The null entity does not exist
    ASSERT_FALSE(getEntityManager().doesEntityExist(nullEntity));
    // The null entity is not alive
    ASSERT_FALSE(getEntityManager().isEntityAlive(nullEntity));
    // Checking if a non-existent entity name exists
    ASSERT_FALSE(getEntityManager().doesEntityExist("TestEntity"));
    // Checking if a non-existent entity can be created (it should)
    ASSERT_TRUE(getEntityManager().canEntityBeCreated("TestEntity"));
}

TEST_F(EntityManagerTests, DestroyEntityWhenThereIsNone) {
    ASSERT_THROW(entityManager.destroyEntity(firstEntityID), AssertFailedException);
}

TEST_F(EntityManagerTests, DestroyNullEntity) {
    ASSERT_THROW(entityManager.destroyEntity(GLESC::ECS::EntityManager::nullEntity), AssertFailedException);
}

TEST_F(EntityManagerTests, DestroyEntityFromOneToZero) {
    using namespace GLESC::ECS;
    EntityID entity = entityManager.createNextEntity("TestEntity");

    entityManager.destroyEntity(entity);
    TEST_SECTION("Checking interface checkers");
    // The entity does not exist
    ASSERT_FALSE(getEntityManager().doesEntityExist(entity));
    // The entity name does not exist
    ASSERT_FALSE(getEntityManager().doesEntityExist("TestEntity"));
    // The entity is not alive
    ASSERT_FALSE(getEntityManager().isEntityAlive(entity));
    // The entity name can be created
    ASSERT_TRUE(getEntityManager().canEntityBeCreated("TestEntity"));

    TEST_SECTION("Checking entity manager internal data structures");
    // The available entities queue size is the maximum, as we just destroyed an entity
    ASSERT_TRUE(getEntityManager().getAvailableEntities().size() == GLESC::ECS::maxEntities);
    // The entity IDs size is zero
    ASSERT_TRUE(getEntityManager().getEntityNameToID().empty());
    ASSERT_TRUE(getEntityManager().getEntityIDToName().empty());
    // The living entity count is zero
    ASSERT_TRUE(getEntityManager().getLivingEntityCount() == 0);
}

TEST_F(EntityManagerTests, DestroyEntityMany) {
    using namespace GLESC::ECS;
    EntityID createdEntities = 100;
    // Destroyed entities must be less than created entities / 2
    EntityID destroyedEntities = 35;
    std::set<EntityID> destroyedEntitiesList;


    for (EntityID entityId = firstEntityID; entityId < createdEntities + firstEntityID; ++entityId) {
        entityManager.createNextEntity("TestEntity" + std::to_string(entityId));
    }

    // Destroy every second entity 1, 3, 5, 7, 9, ... to destroyedEntities * 2 (70)
    for (EntityID entityId = firstEntityID; entityId < destroyedEntities * 2 + firstEntityID; entityId += 2) {
        entityManager.destroyEntity(entityId);
        destroyedEntitiesList.emplace(entityId);
    }

    TEST_SECTION("Checking interface checkers");
    for (EntityID entityId : destroyedEntitiesList) {
        // The destroyed entity does not exist by id
        ASSERT_FALSE(getEntityManager().doesEntityExist(entityId));
        // The destroyed entity does not exist by name
        ASSERT_FALSE(getEntityManager().doesEntityExist("TestEntity" + std::to_string(entityId)));
        // The destroyed entity is not alive
        ASSERT_FALSE(getEntityManager().isEntityAlive(entityId));
        // The destroyed entity can be created again
        ASSERT_TRUE(getEntityManager().canEntityBeCreated("TestEntity" + std::to_string(entityId)));
    }

    TEST_SECTION("Checking entity manager internal data structures");
    ASSERT_EQ(getEntityManager().getAvailableEntities().size(),
              GLESC::ECS::maxEntities - (createdEntities - destroyedEntities));
    // The entity IDs size is createdEntities - destroyedEntities
    ASSERT_EQ(getEntityManager().getEntityNameToID().size(), createdEntities - destroyedEntities);
    ASSERT_EQ(getEntityManager().getEntityIDToName().size(), createdEntities - destroyedEntities);
    // The living entity count is createdEntities - destroyedEntities
    ASSERT_EQ(getEntityManager().getLivingEntityCount(), createdEntities - destroyedEntities);
    // Checking the the entity IDs contain the same entities we created
    for (EntityID entityId = firstEntityID; entityId < createdEntities + firstEntityID; ++entityId) {
        if (destroyedEntitiesList.find(entityId) != destroyedEntitiesList.end()) continue;
        ASSERT_TRUE(getEntityManager().getEntityNameToID().at("TestEntity" + std::to_string(entityId)) == entityId);
        ASSERT_TRUE(getEntityManager().getEntityIDToName().at(entityId) == "TestEntity" + std::to_string(entityId));
        ASSERT_TRUE(getEntityManager().getSignatures().at(entityId).to_ulong() == 0);
    }
}

TEST_F(EntityManagerTests, AddComponentToEntity) {
    using namespace GLESC::ECS;
    EntityID entity = entityManager.createNextEntity("TestEntity");

    entityManager.addComponentToEntity(entity, 0);
    entityManager.addComponentToEntity(entity, 1);
    entityManager.addComponentToEntity(entity, 2);

    TEST_SECTION("Checking interface checkers");
    // checking if entity has the component
    ASSERT_TRUE(getEntityManager().doesEntityHaveComponent(entity, 0));
    ASSERT_TRUE(getEntityManager().doesEntityHaveComponent(entity, 1));
    ASSERT_TRUE(getEntityManager().doesEntityHaveComponent(entity, 2));
    // The signature of the entity we just created is 0b111, as it has three components
    ASSERT_TRUE(getEntityManager().getSignature(entity).to_ulong() == 0b111);

    TEST_SECTION("Checking entity manager internal data structures");
    ASSERT_TRUE(getEntityManager().getSignatures().at(entity).to_ulong() == 0b111);
}

TEST_F(EntityManagerTests, AddAlreadyExistingComponentToEntity) {
    using namespace GLESC::ECS;
    EntityID entity = entityManager.createNextEntity("TestEntity");
    // Adding some components
    entityManager.addComponentToEntity(entity, 0);
    entityManager.addComponentToEntity(entity, 1);
    entityManager.addComponentToEntity(entity, 2);
    // Adding the same component again
    ASSERT_THROW({entityManager.addComponentToEntity(entity, 1);}, AssertFailedException);
}

TEST_F(EntityManagerTests, RemoveComponentFromEntity) {
    using namespace GLESC::ECS;
    EntityID entity = entityManager.createNextEntity("TestEntity");

    entityManager.addComponentToEntity(entity, 0);
    entityManager.addComponentToEntity(entity, 1);
    entityManager.addComponentToEntity(entity, 2);

    entityManager.removeComponentFromEntity(entity, 1);

    TEST_SECTION("Checking interface checkers");
    // checking if entity has the component
    ASSERT_TRUE(getEntityManager().doesEntityHaveComponent(entity, 0));
    ASSERT_FALSE(getEntityManager().doesEntityHaveComponent(entity, 1));
    ASSERT_TRUE(getEntityManager().doesEntityHaveComponent(entity, 2));
    // The signature of the entity we just created is 0b101, as it has three components
    ASSERT_TRUE(getEntityManager().getSignature(entity).to_ulong() == 0b101);

    TEST_SECTION("Checking entity manager internal data structures");
    ASSERT_TRUE(getEntityManager().getSignatures().at(entity).to_ulong() == 0b101);
}

TEST_F(EntityManagerTests, RemoveNonExistentComponentFromEntity) {
    using namespace GLESC::ECS;
    EntityID entity = entityManager.createNextEntity("TestEntity");

    entityManager.addComponentToEntity(entity, 0);
    entityManager.addComponentToEntity(entity, 1);
    entityManager.addComponentToEntity(entity, 2);

    ASSERT_THROW({entityManager.removeComponentFromEntity(entity, 3);}, AssertFailedException);
}

#endif // ECS_BACKEND_UNIT_TESTING