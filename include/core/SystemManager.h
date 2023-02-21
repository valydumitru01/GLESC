#include <memory>
#include <assert.h>
#include <unordered_map>
#include "core/systems/system.h"
#include "core/types.h"
class SystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> registerSystem()
	{
		const char* typeName = typeid(T).name();

		assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

		// Create a pointer to the system and return it so it can be used externally
		auto system = std::make_shared<T>();
		mSystems.insert({typeName, system});
		return system;
	}

	template<typename T>
	void setSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();

		assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

		// Set the signature for this system
		mSignatures.insert({typeName, signature});
	}

	void entityIDDestroyed(EntityID EntityID)
	{
		// Erase a destroyed EntityID from all system lists
		// mEntities is a set so no check needed
		for (auto const& pair : mSystems)
		{
			auto const& system = pair.second;

			system->entities.erase(EntityID);
		}
	}

	void entityIDSignatureChanged(EntityID EntityID, Signature EntityIDSignature)
	{
		// Notify each system that an EntityID's signature changed
		for (auto const& pair : mSystems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = mSignatures[type];

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
	std::unordered_map<const char*, Signature> mSignatures{};

	// Map from system type string pointer to a system pointer
	std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
};
