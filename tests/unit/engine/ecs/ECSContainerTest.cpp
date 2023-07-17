#include <gtest/gtest.h>
#include "engine/ecs/ECSContainer.h"
#include "engine/ecs/components/Component.h"

class ECSContainersTest : public ::testing::Test {
protected:
    std::shared_ptr <ECSContainers> ecs;
    
    void SetUp() override {
        ecs = ECS::getECS();
    }
};

TEST_F(ECSContainersTest, RegisterSystemTest
) {
ecs->registerSystem("TestSystem");
EXPECT_TRUE(ecs
->systemIsRegistered("TestSystem"));
}}
TEST_F(ECSContainersTest, AssociatedEntitiesTest
) {
ecs->registerSystem("TestSystem");
auto &entities = ecs->getAssociatedEntities("TestSystem");
// Add checks for entities.
// You would add entities to the system in your program.
}

TEST_F(ECSContainersTest, SignatureTest
) {
ecs->registerSystem("TestSystem");
auto &signature = ecs->getSignature("TestSystem");
// Add checks for signature.
// The signature will depend on the components you have added to the system.
}

TEST_F(ECSContainersTest, EntityLifecycleTest
) {
EntityID entity = ecs->getNextEntityID();
EXPECT_TRUE(ecs
->
isEntityAlive(entity)
);

ecs->
entityDestroyed(entity);
EXPECT_FALSE(ecs
->
isEntityAlive(entity)
);
}
