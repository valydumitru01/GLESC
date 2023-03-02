#pragma once

#include "core/entities/Entity.h"
#include "core/systems/System.h"
#include "core/Types.h"

#include <memory>
#include <cassert>
#include <unordered_map>

class Entity;
class System;

class SystemContainer {
    friend class Entity;
    friend class System;

private:
    // Map from system type string pointer to a signature
    std::unordered_map<const char *, Signature> signatures{};

    // Map from system type string pointer to a system pointer
    std::unordered_map<const char *, std::shared_ptr<System>> systems{};
};
