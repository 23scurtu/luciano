#pragma once

#include "entityx/entityx.h"
#include "Keyboard.h"
#include "Command.h"
#include <glm/glm.hpp>
#include <vector>

class Command;
class MoveCommand;

// Assigns inputs from the input manager to commands.
class InputHandler
{
  Command* W_PRESS;
  Command* A_PRESS;
  Command* S_PRESS;
  Command* D_PRESS;

  Keyboard& keyboard;
public:
  InputHandler(Keyboard & keyboard);
  std::vector<Command*> handleKeyboardInput();
};
