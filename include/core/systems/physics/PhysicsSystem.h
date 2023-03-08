#include "core/systems/system.h"
#include "core/ECSContainer.h"
class PhysicsSystem : System {
private:
	/* data */
public:
	PhysicsSystem();
	~PhysicsSystem();
    void update();
};

void PhysicsSystem::update()
{
	for (auto const& entity : ecsContainer.getEntities())
	{
		auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
		auto& transform = gCoordinator.GetComponent<Transform>(entity);
		
		// Forces
		auto const& gravity = gCoordinator.GetComponent<Gravity>(entity);
		
		transform.position += rigidBody.velocity;
		
		rigidBody.velocity += gravity.force;
	}
}