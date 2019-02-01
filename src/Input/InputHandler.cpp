#include "InputHandler.h"
#include <iostream>
#include <glm/glm.hpp>
#include "Command.h"

bool isDown(KeyAction action)
{ return action == PRESS || action == REPEAT; }

bool isUp(KeyAction action)
{ return action == RELEASE; }

InputHandler::InputHandler(Keyboard & keyboard): keyboard{keyboard}
{
  // Assign bindings
  W_PRESS = new MoveCommand(glm::vec3(0.0,0.0,-1.0));
  A_PRESS = new MoveCommand(glm::vec3(-1.0,0.0,0.0));
  S_PRESS = new MoveCommand(glm::vec3(0.0,0.0,1.0));
  D_PRESS = new MoveCommand(glm::vec3(1.0,0.0,0.0));
}

vector<Command*> InputHandler::handleKeyboardInput()
{
  std::vector<Command*> commands;
  // std::cout << keyboard.getKeyInput(W_KEY) << std::endl;
  // std::cout << keyboard.getKeyInput(S_KEY) << std::endl;

  if(isDown(keyboard.getKeyInput(W_KEY))) commands.push_back(W_PRESS);
  if(isDown(keyboard.getKeyInput(A_KEY))) commands.push_back(A_PRESS);
  if(isDown(keyboard.getKeyInput(S_KEY))) commands.push_back(S_PRESS);
  if(isDown(keyboard.getKeyInput(D_KEY))) commands.push_back(D_PRESS);

  return commands;
}
