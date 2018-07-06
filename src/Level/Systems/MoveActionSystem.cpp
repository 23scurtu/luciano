#include "MoveActionSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Graphics/Camera.h"
#include <iostream>

MoveActionSystem::MoveActionSystem()
{
}

void MoveActionSystem::update
(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
  entityx::ComponentHandle<MoveAction> move;
  entityx::ComponentHandle<Transform> transform;

  for (entityx::Entity entity : es.entities_with_components(move,transform)) {
    // TEMP Code for testing inputs. Directly handles movement since
    // there's no movement system yet.
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), 0.01f * move->velocity);
    transform->translate *= translate;
    move.remove();
  }
}
