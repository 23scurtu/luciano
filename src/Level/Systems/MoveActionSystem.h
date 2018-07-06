#include "Graphics/Renderer.h"
#include "entityx/entityx.h"
#include <vector>
#include <string>
#include <utility>
#include "Graphics/ResourceManager.h"
#include "Level/Components.h"
#include "Graphics/Renderer.h"
#include "Input/InputHandler.h"

class MoveActionSystem: public entityx::System<MoveActionSystem>
{

public:
  MoveActionSystem();
  void update(entityx::EntityManager &es,
              entityx::EventManager &events,
              entityx::TimeDelta dt) override;
};
