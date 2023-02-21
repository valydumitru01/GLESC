#include "core/Types.h"
#include "core/components/Component.h"
#include "core/ComponentManager.h"
#include "core/EntityManager.h"
#include "core/components/ComponentArray.h"
#include <memory>
#include <assert.h>
#include <queue>
#include <array>
#include <unordered_map>

class Entity {
public:
	Entity(std::shared_ptr<EntityManager> entityManager,
			std::shared_ptr<ComponentManager> componentManager);
	void destroy();
	template<typename T>
	void addComponent(T component);
	template<typename T>
	void removeComponent(T component);
	template<typename T>
	T& getComponent(EntityID entityID);

private:
	EntityID ID;
	std::shared_ptr<EntityManager> entityManager;
	std::shared_ptr<ComponentManager> componentManager;
};

Entity::Entity(std::shared_ptr<EntityManager> entityManager,
		std::shared_ptr<ComponentManager> componentManager) :
		entityManager(entityManager), componentManager(componentManager), ID(
				entityManager->CreateEntity()) {

}

template<typename T>
void Entity::addComponent(T component) {
	componentManager->addComponent<T>(ID, component);
}

template<typename T>
void Entity::removeComponent(T component) {
	componentManager->removeComponent<T>(ID);
}

void Entity::destroy() {
	entityManager->destroyEntity(ID);
	componentManager->entityDestroyed(ID);

}

template<typename T>
inline T& Entity::getComponent(EntityID entityID) {
	return componentManager->getComponent<T>(ID);
}
