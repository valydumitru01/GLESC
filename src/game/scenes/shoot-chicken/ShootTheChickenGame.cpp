#include "game/scenes/shoot-chicken/ShootTheChickenGame.h"

#include "engine/ecs/frontend/component/CameraComponent.h"
#include "engine/ecs/frontend/component/CollisionComponent.h"
#include "engine/ecs/frontend/component/FogComponent.h"
#include "engine/ecs/frontend/component/InputComponent.h"
#include "engine/ecs/frontend/component/LightComponent.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/SunComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/ingame-debug/Console.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"
#include "engine/subsystems/sound/SoundPlayer.h"
#include "game/scenes/shoot-chicken/ShootTheChickenHUD.h"

using namespace GLESC;

void ShootTheChickenGame::createChickenMesh() {
    Render::ColorMesh chickenBody = Render::MeshFactory::cube(Render::ColorRgb::White);

    Render::ColorMesh chickenHead = Render::MeshFactory::cube(Render::ColorRgb::White, 0.5f);
    Transform::Transformer::translateMesh(chickenHead, {0, 0.5, 0.5});

    Render::ColorMesh chickenPeak = Render::MeshFactory::cube(Render::ColorRgb::Red, 0.1f);
    Transform::Transformer::translateMesh(chickenPeak, {0, 0.5, 0.5 + 0.5 / 2});

    Render::ColorMesh chickenEye1 = Render::MeshFactory::cube(Render::ColorRgb::Black, 0.1f);
    Transform::Transformer::translateMesh(chickenEye1, {0.5 / 2, 0.6, 0.6});

    Render::ColorMesh chickenEye2 = Render::MeshFactory::cube(Render::ColorRgb::Black, 0.1f);
    Transform::Transformer::translateMesh(chickenEye2, {-0.5 / 2, 0.6, 0.6});

    Render::ColorMesh chickenLeg1 = Render::MeshFactory::cuboid(0.1f, 1, 0.1f, Render::ColorRgb::Yellow);
    Transform::Transformer::translateMesh(chickenLeg1, {0.25, -0.5, 0});

    Render::ColorMesh chickenLeg2 = Render::MeshFactory::cuboid(0.1f, 1, 0.1f, Render::ColorRgb::Yellow);
    Transform::Transformer::translateMesh(chickenLeg2, {-0.25, -0.5, 0});

    Render::ColorMesh chickenFoot1 = Render::MeshFactory::cuboid(0.2f, 0.1f, 0.2f, Render::ColorRgb::Yellow);
    Transform::Transformer::translateMesh(chickenFoot1, {0.25, -1, 0.1f});

    Render::ColorMesh chickenFoot2 = Render::MeshFactory::cuboid(0.2f, 0.1f, 0.2f, Render::ColorRgb::Yellow);
    Transform::Transformer::translateMesh(chickenFoot2, {-0.25, -1, 0.1f});

    chickenMesh.startBuilding();
    chickenMesh.attatchMesh(chickenHead);
    chickenMesh.attatchMesh(chickenBody);
    chickenMesh.attatchMesh(chickenLeg1);
    chickenMesh.attatchMesh(chickenLeg2);
    chickenMesh.attatchMesh(chickenFoot1);
    chickenMesh.attatchMesh(chickenFoot2);
    chickenMesh.attatchMesh(chickenPeak);
    chickenMesh.attatchMesh(chickenEye1);
    chickenMesh.attatchMesh(chickenEye2);
    chickenMesh.finishBuilding();
}

void createGrassBlock(Render::ColorMesh& grassBlock, float grassBlockWidth, int bladesPerBlock) {
    grassBlock.startBuilding();
    Render::ColorMesh singleGrassBlade =
        Render::MeshFactory::cuboid(0.3f, 0.5f, 0.3f, Render::ColorRgb::Green);
    for (int j = 0; j < bladesPerBlock; j++) {
        Render::ColorMesh grassBlade = singleGrassBlade;
        Transform::Transformer::translateMesh(grassBlade, {
                                                  Math::generateRandomNumber(
                                                      -grassBlockWidth / 2, grassBlockWidth / 2),
                                                  0,
                                                  Math::generateRandomNumber(
                                                      -grassBlockWidth / 2, grassBlockWidth / 2)
                                              });
        grassBlock.attatchMesh(grassBlade);
    }
    grassBlock.finishBuilding();
}

void ShootTheChickenGame::createGrassMesh() {
    float grassBlockWidth = 2.f;
    int bladesPerBlock = 5;
    int numberOfGrassBlocks = 100;

    allGrassMesh.startBuilding();
    for (int i = 0; i < numberOfGrassBlocks; i++) {
        for (int j = 0; j < numberOfGrassBlocks; j++) {
            if (Math::tossCoinWithChance(0.9) == true) continue;
            Render::ColorMesh grassBlock;
            createGrassBlock(grassBlock, grassBlockWidth, bladesPerBlock);
            Transform::Transformer::translateMesh(grassBlock,
                                                  {
                                                      static_cast<float>(i) * grassBlockWidth - static_cast<float>(
                                                          numberOfGrassBlocks) / 2 * grassBlockWidth,
                                                      0,
                                                      static_cast<float>(j) * grassBlockWidth - static_cast<float>(
                                                          numberOfGrassBlocks) / 2 * grassBlockWidth
                                                  });
            allGrassMesh.attatchMesh(grassBlock);
        }
    }
    allGrassMesh.finishBuilding();
}


void ShootTheChickenGame::createPlayerMesh() {
    Render::ColorMesh playerGun = Render::MeshFactory::cuboid(0.5f, 0.5f, 5, Render::ColorRgb::Brown);
    Render::ColorMesh playerGunHandle = Render::MeshFactory::cuboid(0.5f, 0.5f, 3, Render::ColorRgb::DarkBrown);
    Transform::Transformer::translateMesh(playerGunHandle, {0, -0.5, 1.5});

    Render::ColorMesh playerHand = Render::MeshFactory::cuboid(0.5f, 0.5f, 5, Render::ColorRgb::ClearSkin);
    Transform::Transformer::rotateMesh(playerHand, {-25, -45, 0});
    Transform::Transformer::translateMesh(playerHand, {-0.3, -0.55, 1});

    playerGun.startBuilding();
    playerGun.attatchMesh(playerGunHandle);
    playerGun.attatchMesh(playerHand);
    playerGun.finishBuilding();

    // Rotate the gun to the left
    Transform::Transformer::rotateMesh(playerGun, {25, 25, 0});
    // Lift the gun to the player's hands
    Transform::Transformer::translateMesh(playerGun, {1.3, -1.5, -3});
    playerMesh.startBuilding();
    playerMesh.attatchMesh(playerGun);
    playerMesh.finishBuilding();
}

void ShootTheChickenGame::createTreeMesh() {
    Render::ColorMesh treeTrunk = Render::MeshFactory::cuboid(1.5f, 10, 1.5f, Render::ColorRgb::Brown);
    Render::ColorMesh treeTop = Render::MeshFactory::cuboid(10, 10, 10, Render::ColorRgb::DarkGreen);
    Transform::Transformer::translateMesh(treeTop, {0, 10, 0});
    treeMesh.startBuilding();
    treeMesh.attatchMesh(treeTrunk);
    treeMesh.attatchMesh(treeTop);
    treeMesh.finishBuilding();
}

Vec3 calculateBerryPosition(float bushWidth, float bushRadius, float bushDepth, float berryRadius) {
    // Randomly select one of the six faces
    int face = Math::generateRandomNumber(0, 5);

    // Variables to store berry position
    float x, y, z;

    switch (face) {
    case 0: // Front face
        x = Math::generateRandomNumber(-bushWidth / 2, bushWidth / 2);
        y = Math::generateRandomNumber(0.0f, bushRadius / 2);
        z = bushDepth / 2 - berryRadius;
        break;
    case 1: // Back face
        x = Math::generateRandomNumber(-bushWidth / 2, bushWidth / 2);
        y = Math::generateRandomNumber(0.0f, bushRadius / 2);
        z = -bushDepth / 2 + berryRadius;
        break;
    case 2: // Left face
        x = -bushWidth / 2 + berryRadius;
        y = Math::generateRandomNumber(0.0f, bushRadius / 2);
        z = Math::generateRandomNumber(-bushDepth / 2, bushDepth / 2);
        break;
    case 3: // Right face
        x = bushWidth / 2 - berryRadius;
        y = Math::generateRandomNumber(0.0f, bushRadius / 2);
        z = Math::generateRandomNumber(-bushDepth / 2, bushDepth / 2);
        break;
    default: // Top face
        x = Math::generateRandomNumber(-bushWidth / 2, bushWidth / 2);
        y = bushRadius / 2;
        z = Math::generateRandomNumber(-bushDepth / 2, bushDepth / 2);
        break;
    }
    return {x, y, z};
}

void ShootTheChickenGame::createBushesMeshes() {
    int numOfBushes = 100;
    allBushesMesh.startBuilding();
    for (int i = 0; i < numOfBushes; i++) {
        float bushWidth = Math::generateRandomNumber(4.f, 12.f);
        float bushHeight = Math::generateRandomNumber(1.f, 5.f);
        float bushDepth = Math::generateRandomNumber(4.f, 12.f);
        float bushPositionX = Math::generateRandomNumber(-100.f, 100.f);
        float bushPositionZ = Math::generateRandomNumber(-100.f, 100.f);
        float chanceOfHavingBerries = 0.05;
        float radiusOfBerry = 0.4f;
        float bushVolume = bushWidth * bushHeight * bushDepth;
        int numberOfBerries;
        Render::ColorMesh bush =
            Render::MeshFactory::cuboid(bushWidth, bushHeight, bushDepth, Render::ColorRgb::DarkGreen);
        Render::ColorMesh berryMesh =
            Render::MeshFactory::sphere(6, 6, radiusOfBerry, Render::ColorRgb::Red);
        bush.startBuilding();
        if (Math::tossCoinWithChance(chanceOfHavingBerries) == true
            // Ensure the berries are close to the player to be visible
            && bushPositionX < 100 && bushPositionZ < 100
            && bushPositionX > -100 && bushPositionZ > -100) {
            numberOfBerries = static_cast<int>(Math::generateRandomNumber(bushVolume * 0.05f / radiusOfBerry / 2,
                                                                          bushVolume * 0.05f / radiusOfBerry));
            for (int j = 0; j < numberOfBerries; j++) {
                Render::ColorMesh berry = berryMesh;
                Transform::Transformer::translateMesh(
                    berry, calculateBerryPosition(bushWidth, bushHeight, bushDepth, radiusOfBerry));
                bush.attatchMesh(berry);
            }
        }
        bush.finishBuilding();
        Transform::Transformer::translateMesh(bush, {bushPositionX, 0, bushPositionZ});
        allBushesMesh.attatchMesh(bush);
    }
    allBushesMesh.finishBuilding();
}

void ShootTheChickenGame::createGrassEntity() {
    ECS::Entity grass = createEntity("grass");
    grass.addComponent<ECS::TransformComponent>();
    grass.addComponent<ECS::RenderComponent>();
    grass.addComponent<ECS::PhysicsComponent>();
    grass.getComponent<ECS::TransformComponent>().transform.setPosition({0, 0, 0});
    grass.getComponent<ECS::RenderComponent>().copyMesh(allGrassMesh);
    grass.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(false);
    grass.getComponent<ECS::PhysicsComponent>().physics.setStatic(true);
}


void ShootTheChickenGame::createBulletMesh() {
    Render::ColorMesh bullet1 = Render::MeshFactory::cuboid(0.15f, 0.15f, 0.5, Render::ColorRgb::Purple);
    Transform::Transformer::translateMesh(bullet1, {0.25, 0, 0});
    Render::ColorMesh bullet2 = Render::MeshFactory::cuboid(0.15f, 0.15f, 0.5, Render::ColorRgb::Purple);
    Transform::Transformer::translateMesh(bullet2, {-0.25, 0, 0});
    bulletMesh.startBuilding();
    bulletMesh.attatchMesh(bullet2);
    bulletMesh.finishBuilding();
}


void ShootTheChickenGame::createFloorEntity() {
    // Create a floor
    ECS::Entity floor = createEntity("floor");
    floor.addComponent<ECS::TransformComponent>();
    floor.addComponent<ECS::RenderComponent>();
    floor.addComponent<ECS::PhysicsComponent>();
    floor.addComponent<ECS::CollisionComponent>();
    floor.getComponent<ECS::TransformComponent>().transform.setPosition({0, -1, 0});
    floor.getComponent<ECS::RenderComponent>().copyMesh(
        Render::MeshFactory::cuboid(1000, 2.f, 1000, Render::ColorRgb::Green));
    floor.getComponent<ECS::PhysicsComponent>().physics.setStatic(true);
    floor.getComponent<ECS::CollisionComponent>().collider.setBoundingVolume(
        floor.getComponent<ECS::RenderComponent>().getMesh().getBoundingVolume());
}

void ShootTheChickenGame::createTreeEntities() {
    int numTrees = 10;
    for (int i = 0; i < numTrees; i++) {
        Transform::Position position = Transform::Position(Math::generateRandomNumber(-100, 100),
                                                           -1,
                                                           Math::generateRandomNumber(-100, 100));
        // Add a constant for the position so the tree is not on top of the player
        position += {10, 0, 10};
        ECS::Entity tree = createEntity("tree", {EntityType::Instance});
        tree.addComponent<ECS::TransformComponent>();
        tree.addComponent<ECS::RenderComponent>();
        tree.addComponent<ECS::PhysicsComponent>();
        tree.addComponent<ECS::CollisionComponent>();
        tree.getComponent<ECS::TransformComponent>().transform.setPosition({position});
        tree.getComponent<ECS::RenderComponent>().copyMesh(treeMesh);
        tree.getComponent<ECS::CollisionComponent>().collider.setBoundingVolume(
            tree.getComponent<ECS::RenderComponent>().getMesh().getBoundingVolume());
        tree.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(false);
        tree.getComponent<ECS::PhysicsComponent>().physics.setStatic(true);

        float randomScale = Math::generateRandomNumber(1.f, 3.f);
        tree.getComponent<ECS::TransformComponent>().transform.setScale({
            randomScale,
            randomScale,
            randomScale
        });
    }
}


void ShootTheChickenGame::generateChickenEntities() {
    int numChickens = 10;
    float chickenMass = 5;
    float chickenSpawnHeight = 100;
    chickens.clear();
    for (int i = 0; i < numChickens; i++) {
        Transform::Position position = generateChickenPosition();
        ECS::Entity chicken = createEntity("chicken", {EntityType::Instance});
        chicken.addComponent<ECS::TransformComponent>();
        chicken.addComponent<ECS::RenderComponent>();
        chicken.addComponent<ECS::PhysicsComponent>();
        chicken.addComponent<ECS::CollisionComponent>();
        auto& transform = chicken.getComponent<ECS::TransformComponent>().transform;
        chicken.getComponent<ECS::TransformComponent>().transform.setPosition({position});
        chicken.getComponent<ECS::RenderComponent>().copyMesh(chickenMesh);
        chicken.getComponent<ECS::CollisionComponent>().collider.setBoundingVolume(
            chicken.getComponent<ECS::RenderComponent>().getMesh().getBoundingVolume());
        chicken.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(true);
        transform.setPosition({transform.getPosition().getX(), chickenSpawnHeight, transform.getPosition().getZ()});
        chicken.getComponent<ECS::PhysicsComponent>().physics.setMass(chickenMass);
        chickens.push_back(chicken.getID());
    }
}

void ShootTheChickenGame::createBushesEntity() {
    ECS::Entity bushes = createEntity("bushes");
    bushes.addComponent<ECS::TransformComponent>();
    bushes.addComponent<ECS::RenderComponent>();
    bushes.addComponent<ECS::PhysicsComponent>();
    bushes.getComponent<ECS::TransformComponent>().transform.setPosition({0, 0, 0});
    bushes.getComponent<ECS::RenderComponent>().copyMesh(allBushesMesh);
    bushes.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(false);
    bushes.getComponent<ECS::PhysicsComponent>().physics.setStatic(true);
}


Transform::Position ShootTheChickenGame::generateChickenPosition() {
    // Make the chicken reappear in a circle around the center of the map
    float radius = 100;
    return {
        Math::generateRandomNumber(-radius, radius),
        10,
        Math::generateRandomNumber(-radius, radius)
    };
}

void ShootTheChickenGame::collisionCallback(ECS::EntityID chicken, Physics::Collider& bulletCollider) {
    // Find the chicken that collided with the bullet
    auto it = std::find_if(chickens.begin(), chickens.end(),
                           [this, &bulletCollider](ECS::EntityID chickenID) {
                               return &bulletCollider == &getEntity(chickenID)
                                                          .getComponent<ECS::CollisionComponent>().collider;
                           });

    if (it != chickens.end()) {
        SoundPlayer::play3DSound("chicken_shot",
                                 getCamera().getEntity().getComponent<ECS::TransformComponent>().transform.
                                             getPosition(),
                                 getEntity(*it).getComponent<ECS::TransformComponent>().transform.getPosition());
        ECS::EntityID chickenID = *it;
        getEntity(chickenID).getComponent<ECS::TransformComponent>().transform.setPosition(generateChickenPosition());
        getWindow<ShootTheChickenHUD>(statsWindow).addChickenKill();
        chickens.erase(it);
    }

    // Destroy the bullet entity
    destroyEntity(chicken);
}


void ShootTheChickenGame::shootBulletActionFunc() {
    if (!inputManager.isMouseRelative()) return;
    if (getWindow<ShootTheChickenHUD>(statsWindow).getAmmunition() == 0) return;
    getWindow<ShootTheChickenHUD>(statsWindow).removeAmmunition();
    // Create a bullet
    ECS::Entity bullet = createEntity("bullet", {EntityType::Instance});
    // Copy the camera transform
    auto cameraTransformCopy = getCamera().getEntity().getComponent<ECS::TransformComponent>();
    bullet.addComponent<ECS::TransformComponent>();
    bullet.addComponent<ECS::RenderComponent>();
    bullet.addComponent<ECS::PhysicsComponent>();
    bullet.addComponent<ECS::CollisionComponent>();
    bullet.addComponent<ECS::LightComponent>();
    bullet.getComponent<ECS::LightComponent>().light.setColor(Render::ColorRgb::Purple);
    bullet.getComponent<ECS::TransformComponent>().transform.setPosition(
        cameraTransformCopy.transform.getPosition() - cameraTransformCopy.transform.forward() * 2.f);
    bullet.getComponent<ECS::TransformComponent>().transform.setRotation(
        cameraTransformCopy.transform.getRotation());


    // Capture the bullet ID by value in the lambda
    ECS::EntityID bulletID = bullet.getID();
    bullet.getComponent<ECS::CollisionComponent>().collider.setCollisionCallback(
        [bulletID, this](Physics::Collider& otherCollider) {
            collisionCallback(bulletID, otherCollider);
        });

    SoundPlayer::playSound("shoot");
    auto oldPitch = getCamera().getEntity().getComponent<ECS::TransformComponent>().transform.getRotation().getX();
    getCamera().getEntity().getComponent<ECS::TransformComponent>().transform.setRotation(
        Transform::RotationAxis::Pitch, oldPitch + 2);
    bullet.getComponent<ECS::RenderComponent>().copyMesh(bulletMesh);
    bullet.getComponent<ECS::PhysicsComponent>().physics.setDirectionalForce(
        -bullet.getComponent<ECS::TransformComponent>().transform.forward(), 10.f);
    bullet.getComponent<ECS::PhysicsComponent>().physics.setMass(0.1f);
    bullet.getComponent<ECS::PhysicsComponent>().physics.addVelocity(
        getCamera().getEntity().getComponent<ECS::PhysicsComponent>().physics.getVelocity());
    getCamera().getEntity().getComponent<ECS::PhysicsComponent>().physics.addForce(
        getCamera().getEntity().getComponent<ECS::TransformComponent>().transform.forward() * 300);
    bullet.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(true);
    if (getWindow<ShootTheChickenHUD>(statsWindow).getAmmunition() == 0) {
        inputManager.setMouseRelative(false);
        getWindow<STCGameOverHUD>(gameOverWindow).setVisible(true);
    }
}

void ShootTheChickenGame::jumpActionFunc() {
    if (getCamera().getEntity().getComponent<ECS::CollisionComponent>().collider.
                    getCollisionInformation().isOnGround()) {
        getCamera().getEntity().getComponent<ECS::PhysicsComponent>().physics.addForce({0, 1900, 0});
    }
}


void ShootTheChickenGame::createPlayerEntity() {
    shootBulletAction = Input::KeyCommand([&] { shootBulletActionFunc(); });
    jumpAction = Input::KeyCommand([&] { jumpActionFunc(); });
    getCamera().setForce(100.f);
    getCamera().getEntity().addComponent<ECS::CollisionComponent>().addComponent<ECS::RenderComponent>();


    getCamera().getEntity().getComponent<ECS::RenderComponent>().copyMesh(playerMesh);
    getCamera().getEntity().getComponent<ECS::PhysicsComponent>().physics.setAirFriction(0.01f);
    getCamera().getEntity().getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(true);
    getCamera().getEntity().getComponent<ECS::CollisionComponent>().collider.setSolid(true);
    getCamera().getEntity().getComponent<ECS::PhysicsComponent>().physics.setMass(50);
    getCamera().getEntity().getComponent<ECS::PhysicsComponent>().physics.setFriction(0.1);
    getCamera().getEntity().getComponent<ECS::CollisionComponent>().collider.setBoundingVolume(
        Math::BoundingVolume::createFromVulume(1, 5, 1));

    getCamera().getEntity().getComponent<ECS::TransformComponent>().transform.setPosition({0, 100, 0});
    getCamera().getEntity().getComponent<ECS::CameraComponent>().perspective.setFovDegrees(90);
    getCamera().getEntity().getComponent<ECS::InputComponent>().input.unsubscribeKey(
        {Input::Key::SPACE, Input::KeyAction::ONGOING_PRESSED});
    getCamera().getEntity().getComponent<ECS::InputComponent>().input.unsubscribeKey(
        {Input::Key::LEFT_SHIFT, Input::KeyAction::ONGOING_PRESSED});
    getCamera().getEntity().getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::LEFT_CLICK, Input::KeyAction::ONCE_PRESSED}, shootBulletAction);
    getCamera().getEntity().getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::SPACE, Input::KeyAction::ONCE_PRESSED}, jumpAction);

    getCamera().getEntity().getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::R, Input::KeyAction::ONCE_PRESSED}, {
            [&]()-> void {
                if (getWindow<ShootTheChickenHUD>(statsWindow).getAmmunition() == 0) {
                    switchScene<ShootTheChickenGame>();
                }
            }
        }
    );
}

void ShootTheChickenGame::init() {
    if (!hasAlreadyInitialized) {
        getEntity("fog").getComponent<ECS::FogComponent>().fog.setDensity(0.3);
        getEntity("fog").getComponent<ECS::FogComponent>().fog.setColor({200, 200, 170});
        getEntity("fog").getComponent<ECS::FogComponent>().fog.setEnd(60);
        getEntity("sun").getComponent<ECS::SunComponent>().sun.setIntensity(0.4f);
        getEntity("sun").getComponent<ECS::SunComponent>().sun.setColor({255, 255, 200});
        getEntity("sun").getComponent<ECS::SunComponent>().sun.setDirection({-0.4, -1, -0.4});
        getEntity("sun").getComponent<ECS::SunComponent>().globalAmbientLight.setIntensity(0.5);
        getEntity("sun").getComponent<ECS::SunComponent>().globalAmbientLight.setColor({255, 180, 165});
        statsWindow = addWindow<ShootTheChickenHUD>();
        gameOverWindow = addWindow<STCGameOverHUD>();
        SoundPlayer::loadSong("Chicken_Blasters.mp3", "main_song");
        SoundPlayer::loadSound("chicken_shot.mp3", "chicken_shot");
        SoundPlayer::loadSound("shoot.mp3", "shoot");
        SoundPlayer::loadSound("chicken_idle.mp3", "chicken_idle");
        createChickenMesh();
        createBulletMesh();
        createPlayerMesh();
        createTreeMesh();
        createGrassMesh();
        createBushesMeshes();
        hasAlreadyInitialized = true;
    }

    SoundPlayer::setMusic("main_song");
    SoundPlayer::playMusic();
    SoundPlayer::setMusicVolume(10);
    getWindow<ShootTheChickenHUD>(statsWindow).setVisible(true);
    getWindow<ShootTheChickenHUD>(statsWindow).setAmmunition(10);
    getWindow<ShootTheChickenHUD>(statsWindow).resetChickenKillCount();
    getWindow<STCGameOverHUD>(gameOverWindow).setVisible(false);
    inputManager.setMouseRelative(true);

    createFloorEntity();
    createTreeEntities();
    createBushesEntity();
    createGrassEntity();
    generateChickenEntities();

    createPlayerEntity();
}

void ShootTheChickenGame::update() {
    float chickenMoveForce = 10;
    float distanceWhereChickensMove = 20;
    int rotationSecondsInterval = 4;
    int rotationSecondsDuration = 4;
    float chickenMaxJumpForce = 200;
    float walkingForce = 40;

    // Every 1 seconds, give upword force to all chickens
    for (unsigned short chickenID : chickens) {
        Render::ColorMesh& chickenMesh = getEntity(chickenID).getComponent<ECS::RenderComponent>().getMesh();
        ECS::Entity chicken = getEntity(chickenID);

        // Jump every random seconds between 1 and 10
        if (getSceneTimeSeconds() % Math::generateRandomNumber(1, 10) == 0) {
            auto transform = chicken.getComponent<ECS::TransformComponent>().transform;
            if (chicken.getComponent<ECS::CollisionComponent>().collider.getCollisionInformation().isOnGround())
                chicken.getComponent<ECS::PhysicsComponent>().physics.addForce(
                    transform.up() * Math::generateRandomNumber(chickenMaxJumpForce * 0.5f, chickenMaxJumpForce));
        }
        // If on ground, jump for the walking force, simulating walking
        if (chicken.getComponent<ECS::CollisionComponent>().collider.getCollisionInformation().isOnGround()) {
            chicken.getComponent<ECS::PhysicsComponent>().physics.addDirectionalForce(
                chicken.getComponent<ECS::TransformComponent>().transform.up(),
                Math::generateRandomNumber(walkingForce * 0.8f, walkingForce));
        }

        // Rotate the chickens so they look at the oppsite direction of where the camera is positioned
        // But not in the Y rotation so they dont look up or down
        Transform::Position cameraPosition =
            getCamera().getEntity().getComponent<ECS::TransformComponent>().transform.getPosition();
        Render::Position chickenPosition =
            chicken.getComponent<ECS::TransformComponent>().transform.getPosition();

        Transform::Rotation newChickenRotation = Transform::Transformer::lookAt(
            cameraPosition, chickenPosition, Transform::Transform::worldUp);
        Transform::Rotation currentRotation = chicken.getComponent<ECS::TransformComponent>().transform.
                                                      getRotation();
        bool isCloseToPlayer = (cameraPosition - chickenPosition).length() < distanceWhereChickensMove;
        if (isCloseToPlayer) {
            float rotationSmoothStep = 1.0f;
            // If the rotation is too different, rotate by rotationSmoothStep degree, making the rotation smooth
            if (currentRotation.getY() - newChickenRotation.getY() > rotationSmoothStep) {
                newChickenRotation.setY(currentRotation.getY() - rotationSmoothStep);
            }
            else if (currentRotation.getY() - newChickenRotation.getY() < -rotationSmoothStep) {
                newChickenRotation.setY(currentRotation.getY() + rotationSmoothStep);
            }
            chicken.getComponent<ECS::TransformComponent>().transform.setRotation(newChickenRotation);

            chicken.getComponent<ECS::PhysicsComponent>().physics.addDirectionalForce(
                chicken.getComponent<ECS::TransformComponent>().transform.forward(),
                Math::remap((chickenPosition - cameraPosition).length(), 0, distanceWhereChickensMove,
                            chickenMoveForce, 0)
            );
        }
        else {
            chicken.getComponent<ECS::TransformComponent>().transform.
                    setRotation({0, currentRotation.getY(), 0});
            // Rotate for 4 seconds every 4 seconds
            if (getSceneTimeSeconds() / rotationSecondsDuration % rotationSecondsInterval == 0) {
                chicken.getComponent<ECS::TransformComponent>().transform.addRotation(
                    Transform::RotationAxis::Yaw,
                    4
                );
                chicken.getComponent<ECS::PhysicsComponent>().physics.addDirectionalForce(
                    chicken.getComponent<ECS::TransformComponent>().transform.forward(),
                    chickenMoveForce
                );
            }
        }
    }
}
