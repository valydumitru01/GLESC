/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <queue>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap.hpp>

#include "engine/ecs/ECSTypes.h"

namespace GLESC {
    class EntityManager {
    public:
        EntityManager();
        
        /**
         * @brief The default destructor is correct
         */
        ~EntityManager() = default;
        
        [[nodiscard]] EntityID createNextEntity(EntityName name);
        
        void destroyEntity(EntityID entity);
        
        void setSignature(EntityID entity, Signature signature);
        
        [[nodiscard]] Signature getSignature(EntityID entity);
        
        [[nodiscard]] bool doesEntityHaveComponent(EntityID entity, ComponentID componentID) const;
        
        [[nodiscard]] EntityName getEntityName(EntityID entity);
        
        [[nodiscard]] EntityID getEntity(EntityName name);
    
    private:
        std::queue<EntityID> availableEntities;
        std::array<Signature, maxEntities> signatures;
        // TODO: Don't store the name of the entity in the entity manager
        //  It's a waste of memory, hash the name and store the hash instead
        boost::bimap<EntityName, EntityID> entityIDs;
        EntityID livingEntityCount{};
    }; // class EntityManager
    
} // namespace GLESC