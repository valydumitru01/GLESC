/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
/**
 * @brief Prints the name of each entity with its ID and the signature.
 * Also prints the queue of available entities and the living entity count.
 * It also prints the message with the context of the call.
 * @param availableEntities std::queue<EntityID>
 * @param signatures std::array<Signature, maxEntities>
 * @param entityIDs boost::bimap<EntityName, EntityID>
 * @param livingEntityCount EntityID
 */
#define PRINT_ENTITIES_STATUS(availableEntities, signatures, entityIDs, livingEntityCount, contextMessage) \
    do{ /* Scope for allowing calling the function in the same scope without redefinition error */\
    Logger::get().info(std::string("Entity print status - ") + contextMessage); \
    for (auto &entityID : entityIDs) { \
        EntityName entityNamePrint = entityID.left; \
        EntityID entityIDPrint = entityID.right; \
        Signature entitySignaturePrint = signatures[entityIDPrint]; \
        \
        std::string entityListMessage = \
        "Entity: " + std::string(entityNamePrint) + \
        " ID: " + std::to_string(entityIDPrint) + \
        " Signature: " + entitySignaturePrint.to_string(); \
        Logger::get().info(entityListMessage); \
    }\
    std::string availableEntitiesMessage = /* This can cause the redefinition error */\
    "Available entities: " + std::to_string(availableEntities.size()); \
    Logger::get().info(availableEntitiesMessage); \
    std::string livingEntityCountMessage = /* This can cause the redefinition error */\
    "Living entity count: " + std::to_string(livingEntityCount); \
    Logger::get().info(livingEntityCountMessage); \
    } while(false)

