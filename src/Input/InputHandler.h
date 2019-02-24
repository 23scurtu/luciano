#pragma once

#include "entityx/entityx.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Command.h"
#include <glm/glm.hpp>
#include <vector>
#include "Graphics/Window.h"

class Command;
class MoveCommand;

// Assigns inputs from the input manager to commands.
class InputHandler
{
  Command* W_PRESS;
  Command* A_PRESS;
  Command* S_PRESS;
  Command* D_PRESS;
  Command* LEFT_BUTTON_PRESS;
  AnalogCommand* MOUSE_MOVE_X;
  AnalogCommand* MOUSE_MOVE_Y;

  // Variables for handling mouse rotation
  bool initial_click = false;
  glm::vec2 last_mouse_pos = glm::vec2(0.0,0.0);

  Keyboard& keyboard;
  Mouse& mouse;

  Window* window;

public:
  // TODO Should InputHandler always take these in or make them seperate setters
  InputHandler(Keyboard & keyboard, Mouse & mouse, Window* window);
  void setWindow(Window* window);
  // Previous commands returned may be invalid after calling
  std::vector<Command*> handleInput();
};
