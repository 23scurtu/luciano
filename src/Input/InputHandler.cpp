#include "InputHandler.h"
#include <iostream>
#include <glm/glm.hpp>
#include "Command.h"

bool isDown(KeyAction action)
{ return action == PRESS || action == REPEAT; }

bool isUp(KeyAction action)
{ return action == RELEASE; }

InputHandler::InputHandler(Keyboard & keyboard, Mouse & mouse, Window* window): 
  keyboard{keyboard}, mouse{mouse}, window{window}
{
  // Assign bindings
  W_PRESS = new MoveCommand(glm::vec3(0.0,0.0,-1.0));
  A_PRESS = new MoveCommand(glm::vec3(-1.0,0.0,0.0));
  S_PRESS = new MoveCommand(glm::vec3(0.0,0.0,1.0));
  D_PRESS = new MoveCommand(glm::vec3(1.0,0.0,0.0));

  MOUSE_MOVE_X = new RotateCommand(Z_AXIS, true);
  MOUSE_MOVE_Y = new RotateCommand(X_AXIS);
}

vector<Command*> InputHandler::handleInput()
{
  std::vector<Command*> commands;
  // std::cout << keyboard.getKeyInput(W_KEY) << std::endl;
  // std::cout << keyboard.getKeyInput(S_KEY) << std::endl;

  if(isDown(keyboard.getKeyInput(W_KEY))) commands.push_back(W_PRESS);
  if(isDown(keyboard.getKeyInput(A_KEY))) commands.push_back(A_PRESS);
  if(isDown(keyboard.getKeyInput(S_KEY))) commands.push_back(S_PRESS);
  if(isDown(keyboard.getKeyInput(D_KEY))) commands.push_back(D_PRESS);

  // TODO Perhaps make commands return non pointer copies.
  // (Leave internal commands as pointers, but only expose copies)
  if(isDown(mouse.getButtonInput(LEFT_BUTTON)))
  {
    if(!initial_click)
    {
      // TODO Pull out rotation speed (0.002)
      MOUSE_MOVE_X->setAnalog(( mouse.getPosInput().x - window->getWidth()/2 - last_mouse_pos.x) * 0.002);
      MOUSE_MOVE_Y->setAnalog(-( mouse.getPosInput().y - window->getHeight()/2 - last_mouse_pos.y) * 0.002);

      commands.push_back(MOUSE_MOVE_X);
      commands.push_back(MOUSE_MOVE_Y);
    }
    
    last_mouse_pos = mouse.getPosInput() - glm::vec2(window->getWidth()/2, window->getHeight()/2);
    initial_click = false;
  }
  else initial_click = true;

  return commands;
}

void InputHandler::setWindow(Window* window)
{
  this->window = window;
}
