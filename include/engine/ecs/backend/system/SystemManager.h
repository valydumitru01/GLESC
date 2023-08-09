/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include <unordered_map>
#include "engine/ecs/ECSTypes.h"

class SystemManager {
public:
    SystemManager() = default;
    
    ~SystemManager() = default;
    
    void registerSystem(SystemName name);
    
    void setSignature(SystemName name, Signature signature);
    
    [[nodiscard]] Signature getSignature(const char *name) const;
    
    void entityDestroyed(EntityID entity);
    
    void entitySignatureChanged(EntityID entity, Signature entitySignature);
    
    [[nodiscard]] std::set<EntityID> getAssociatedEntities(const char *name) const;

private:
    std::unordered_map<SystemName, SystemData> systems;
};


