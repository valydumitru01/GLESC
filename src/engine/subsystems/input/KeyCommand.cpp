#include "engine/subsystems/input/KeyCommand.h"
using namespace GLESC::Input;

KeyCommand::KeyCommand(Action action) : action(std::move(action)) {}

void KeyCommand::execute() {
    if (action) {
        action();
    }
}