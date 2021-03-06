#include "Graphics/Renderer.h"
#include "entityx/entityx.h"
#include <vector>
#include <string>
#include <utility>
#include "Graphics/ResourceManager.h"
#include "Level/Components.h"
#include "Graphics/Renderer.h"
#include "Input/InputHandler.h"

class MovementSystem: public entityx::System<MovementSystem>
{
  void translateEntity(glm::vec3 velocity,
    entityx::TimeDelta dt,
    entityx::ComponentHandle<Transform> transform);

  void rotateEntity(glm::vec3 euler_rotation,
    entityx::ComponentHandle<Transform> transform,
    bool is_global = false);

public:
  MovementSystem();
  void update(entityx::EntityManager &es,
              entityx::EventManager &events,
              entityx::TimeDelta dt) override;
};
