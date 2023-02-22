#pragma once
#include <memory>
#include <assert.h>
#include <unordered_map>
#include "core/systems/system.h"
#include "core/types.h"
class SystemManager
{
    friend class System;
    friend class Entity;
public:




	void entityIDSignatureChanged(EntityID EntityID, Signature EntityIDSignature)
	{
		// Notify each system that an EntityID's signature changed
		for (auto const& pair : systems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = signatures[type];

			// EntityID signature matches system signature - insert into set
			if ((EntityIDSignature & systemSignature) == systemSignature)
			{
				system->entities.insert(EntityID);
			}
			// EntityID signature does not match system signature - erase from set
			else
			{
				system->entities.erase(EntityID);
			}
		}
	}

private:
	// Map from system type string pointer to a signature
	std::unordered_map<const char*, Signature> signatures{};

	// Map from system type string pointer to a system pointer
	std::unordered_map<const char*, std::shared_ptr<System>> systems{};
};
