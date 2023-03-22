#pragma once

#include "core/systems/System.h"
#include "core/components/TransformComponent.h"

class TransformSystem : System {
public:
	TransformSystem();

	void update();
};

TransformSystem::TransformSystem() {
	addComponentRequirement<TransformSystem>();
}

void TransformSystem::update() {
	for (EntityID entityId: getAssociatedEntities()) {

	}
}