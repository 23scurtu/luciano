#include "Graphics/Renderer.h"
#include "entityx/entityx.h"
#include <vector>
#include <string>
#include <utility>
#include "Graphics/ResourceManager.h"
#include "Level/Components.h"
#include "Graphics/Renderer.h"

class RenderingSystem: public entityx::System<RenderingSystem>
{
  ResourceManager& resources;
  Renderer& renderer;

  GLFWwindow* window;

public:
  RenderingSystem(ResourceManager& resources, Renderer& renderer);
  void update(entityx::EntityManager &es,
              entityx::EventManager &events,
              entityx::TimeDelta dt) override;
};
