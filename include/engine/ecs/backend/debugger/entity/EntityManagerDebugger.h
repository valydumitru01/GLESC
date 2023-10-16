/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/debugger/Debugger.h"
/**
 * @brief Prints the name of each entity with its ID and the signature.
 * Also prints the queue of available entities and the living entity count.
 * It also prints the message with the context of the call.
 * @param entityManager The entity manager
 */
#define PRINT_ENTITIES_STATUS(entityManager, contextMessage) \
    LOG( \
    std::string("Entity print status - ") + contextMessage, \
    printStatusEntities(entityManager);\
    )

#ifndef NLOGGING
namespace GLESC {
    [[maybe_unused]] void printStatusEntities(const EntityManager &entityManager) noexcept{
        for (auto &entityID : entityManager.entityIDs) {
            EntityName entityNamePrint = entityID.left;
            EntityID entityIDPrint = entityID.right;
            Signature entitySignaturePrint = entityManager.signatures[entityIDPrint];
            
            std::string entityListMessage =
                    "Entity: " + std::string(entityNamePrint) +
                    " ID: " + std::to_string(entityIDPrint) +
                    " Signature: " + entitySignaturePrint.to_string();
           GLESC::Logger::get().info(entityListMessage);
        }
        std::string availableEntitiesMessage =
                "Available entities: " + std::to_string(entityManager.availableEntities.size());
       GLESC::Logger::get().info(availableEntitiesMessage);
        std::string
                livingEntityCountMessage = "Living entity count: " + std::to_string(entityManager.livingEntityCount);
       GLESC::Logger::get().info(livingEntityCountMessage);
    }
}
#endif

