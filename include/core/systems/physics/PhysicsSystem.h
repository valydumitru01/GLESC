#include "core/systems/System.h"
#include "core/ECSContainer.h"
#include "core/components/TransformComponent.h"
#include "core/components/RigidBodyComponent.h"

class PhysicsSystem : public System {
private:
	double gravity{9.81F};
public:
	void update();

	PhysicsSystem();
};

PhysicsSystem::PhysicsSystem() {
	addComponentRequirement<RigidBodyComponent>();
	addComponentRequirement<TransformComponent>();
}

void PhysicsSystem::update() {
	for (auto const &entity: getAssociatedEntities()) {
		auto &rigidBody = getComponent<RigidBodyComponent>(entity);
		auto &transform = getComponent<TransformComponent>(entity);

		transform.position += rigidBody.velocity;

		rigidBody.velocity += gravity;
	}
}


