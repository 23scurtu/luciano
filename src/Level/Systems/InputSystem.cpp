#include "InputSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Graphics/Camera.h"
#include <iostream>

InputSystem::InputSystem(Renderer& renderer)
:renderer(renderer), input_handler{keyboard}
{
  renderer.getWindow()->setKeyboard(&keyboard);
}

void InputSystem::update
(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
  keyboard.update();
  auto keyboard_commands = input_handler.handleKeyboardInput();

  // Make input component that dictates type of input
  entityx::ComponentHandle<Input> input;
  for (entityx::Entity entity : es.entities_with_components(input)) {

    if(input->type == KEYBOARD)
    {
      for(auto command: keyboard_commands)
      command->execute(entity);
    }
  }
}
