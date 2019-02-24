#include "Graphics/Renderer.h"
#include "entityx/entityx.h"
#include <vector>
#include <string>
#include <utility>
#include "Graphics/ResourceManager.h"
#include "Level/Components.h"
#include "Graphics/Renderer.h"
#include "Input/InputHandler.h"

class InputSystem: public entityx::System<InputSystem>
{
  // TODO Abstract devices and have input system hold a list of them?
  Keyboard keyboard;
  Mouse mouse;

  InputHandler input_handler;
  Renderer& renderer;

public:
  InputSystem(Renderer& renderer);
  void update(entityx::EntityManager &es,
              entityx::EventManager &events,
              entityx::TimeDelta dt) override;
};
