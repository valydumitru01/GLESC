#include "engine/subsystems/input/MouseCommand.h"
using namespace GLESC::Input;
MouseCommand::MouseCommand(Action action) : action(std::move(action)) {}

void MouseCommand::execute(const MousePosition& position) {
    if (action) {
        action(position);
    }
}
