#include "InputSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Graphics/Camera.h"
#include <iostream>

InputSystem::InputSystem(Renderer& renderer)
:renderer(renderer), input_handler{keyboard, mouse, renderer.getWindow()}
{
  renderer.getWindow()->setKeyboard(&keyboard);
  renderer.getWindow()->setMouse(&mouse);

  // TODO Better place to put?
  // renderer.getWindow()->setMouseMode(DISABLED_CURSOR);
}

void InputSystem::update
(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
  keyboard.update();
  mouse.update();

  auto commands = input_handler.handleInput();

  // Make input component that dictates type of input
  entityx::ComponentHandle<Input> input;
  for (entityx::Entity entity : es.entities_with_components(input)) {

    //TODO Make KEYBOARD/MOUSE or PLAYER
    if(input->type == KEYBOARD)
    {
      for(auto command: commands)
      command->execute(entity);
    }
  }
}
