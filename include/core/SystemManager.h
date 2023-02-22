#pragma once
#include <memory>
#include <cassert>
#include <unordered_map>
#include "core/systems/system.h"
#include "core/types.h"
class SystemManager
{
    friend class System;
    friend class Entity;
private:
	// Map from system type string pointer to a signature
	std::unordered_map<const char*, Signature> signatures{};

	// Map from system type string pointer to a system pointer
	std::unordered_map<const char*, std::shared_ptr<System>> systems{};
};
