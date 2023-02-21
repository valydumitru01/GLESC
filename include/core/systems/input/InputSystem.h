#include "core/components/InputComponent.h"
#include <vector>
#include <glm.hpp>
#include <SDL.h>
#include <functional>
#include <unordered_map>

class InputSystem {
public:
  void update(std::vector<InputComponent>& inputComponents);
  void addKeyAction(int key, std::function<void(InputComponent&)> action);

private:
  std::unordered_map<int, std::function<void(InputComponent&)>> keyActionMap;

};