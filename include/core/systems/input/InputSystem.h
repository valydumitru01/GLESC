#include "core/components/InputComponent.h"
#include "System.h"
#include <vector>
#include <glm.hpp>
#include <SDL.h>
#include <functional>
#include <unordered_map>

class InputSystem : System {
public:
  void update();

private:
  std::unordered_map<int, std::function<void(InputComponent&)>> keyActionMap;

};