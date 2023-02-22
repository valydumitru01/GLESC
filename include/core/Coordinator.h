#pragma once

#include "core/SystemManager.h"
#include "core/EntityManager.h"
#include "core/ComponentManager.h"
#include "core/Types.h"
#include <memory>
class Coordinator {
public:
	/**
	 * Initialize
	 */
	void Init() {
		// Create pointers to each manager
		componentManager = std::make_unique<ComponentManager>();
		entityManager = std::make_unique<EntityManager>();
		systemManager = std::make_unique<SystemManager>();
	}



	void DestroyEntity(EntityID entity) {
		entityManager->DestroyEntity(entity);

		componentManager->entityDestroyed(entity);

		systemManager->EntityDestroyed(entity);
	}

	// Component methods
	template<typename T>
	void RegisterComponent() {
		componentManager->registerComponent<T>();
	}

	template<typename T>
	void AddComponent(EntityID entity, T component) {
		componentManager->addComponent<T>(entity, component);

		auto signature = entityManager->GetSignature(entity);
		signature.set(componentManager->getComponentID<T>(), true);
		entityManager->SetSignature(entity, signature);

		systemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(EntityID entity) {
		componentManager->removeComponent<T>(entity);

		auto signature = entityManager->GetSignature(entity);
		signature.set(componentManager->getComponentID<T>(), false);
		entityManager->SetSignature(entity, signature);

		systemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(EntityID entity) {
		return componentManager->getComponent<T>(entity);
	}

	template<typename T>
	ComponentID GetComponentType() {
		return componentManager->getComponentID<T>();
	}

	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem() {
		return systemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature) {
		systemManager->SetSignature<T>(signature);
	}

private:
	std::unique_ptr<ComponentManager> componentManager;
	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<SystemManager> systemManager;
};
