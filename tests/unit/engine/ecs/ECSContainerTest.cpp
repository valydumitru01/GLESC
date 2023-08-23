#include <gtest/gtest.h>
#include "engine/ecs/backend/component/Component.h"

class ECSContainersTest : public ::testing::Test {

};

TEST_F(ECSContainersTest, RegisterSystemTest) {
    ECS::getECS()->registerSystem("TestSystem");
    EXPECT_TRUE(ECS::getECS()->systemIsRegistered("TestSystem"));
}


TEST_F(ECSContainersTest, AssociatedEntitiesTest) {
    ECS::getECS()->registerSystem("TestSystem");
    auto entities = ECS::getECS()->getAssociatedEntities("TestSystem");
// Add checks for entities.
// You would add entities to the system in your program.
}

TEST_F(ECSContainersTest, SignatureTest) {
    ECS::getECS()->registerSystem("TestSystem");
    auto signature = ECS::getECS()->getSignature("TestSystem");
    // Add checks for signature.
    // The signature will depend on the components you have added to the system.
    
}

TEST_F(ECSContainersTest, EntityLifecycleTest) {
    EntityID entity = ECS::getECS()->getNextEntity();
    EXPECT_TRUE(ECS::getECS()->isEntityAlive(entity));
    
    ECS::getECS()->destroyEntity(entity);
    EXPECT_FALSE(ECS::getECS()->isEntityAlive(entity));
}
