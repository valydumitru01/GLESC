#include "TFGL.h"
TFGL::TFGL()
{
}

TFGL::~TFGL()
{
}

void TFGL::loop()
{
    Console::init();
    FPS fps(120);
    // Game is a big object, should be stored on the heap
    Game *game = new Game();
    game->init("Game", 800, 600, false);
    while (game->running())
    {
        fps.timeBeginningOfFrame();
        fps.delay();

        game->handleEvents();
        game->update(fps.getElapsed());
        game->render(fps.getElapsed());

        fps.timeEndOfFrame();
        // fps.printFPS();
    }

    game->clean();
    delete game;
}
void TFGL::update()
{
    for (uint16_t i = 0; i < numPhysicsComponents; i++)
    {
        /* code */
    }
    for (uint16_t i = 0; i < numInputComponents; i++)
    {
        /* code */
    }
    for (uint16_t i = 0; i < numTransformComponents; i++)
    {
        /* code */
    }

    for (uint16_t i = 0; i < numRenderComponents; i++)
    {
        /* code */
    }
}

ID &TFGL::createEntity() const
{
}

std::vector<Component> *TFGL::getEntityComponents(ID &entityID) const
{
}

void TFGL::setComponentToEntity(Component &component, ID &entityID)
{
}
