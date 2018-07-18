#include "MovementSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Graphics/Camera.h"
#include <iostream>

MovementSystem::MovementSystem()
{
}

void MovementSystem::translateEntity(glm::vec3 velocity,
  entityx::TimeDelta dt,
  entityx::ComponentHandle<Transform> transform)
{
  // Perhaps have a MoveActionSystem and a MovementSystem that inherit from
  // a common system to provide common functionality.
  glm::vec3 translate = float(dt) * velocity;
  transform->localTranslation += translate;
  transform->localDirty = true;
}

void MovementSystem::update
(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
  entityx::ComponentHandle<MoveAction> move_action;
  entityx::ComponentHandle<Movement> movement;
  entityx::ComponentHandle<Transform> transform;

  // Movement system handles any movement in game. Any actions to move
  // are added on top of the current movement for this tick.  They do not
  // accumulate in the movement component of an entity as then it would be
  // too diffucult to cancel.

  for (entityx::Entity entity : es.entities_with_components(move_action,transform))
  {
    translateEntity(move_action->velocity, dt,transform);
    move_action.remove();
  }

  for (entityx::Entity entity : es.entities_with_components(movement,transform))
  {
    translateEntity(movement->velocity, dt,transform);
  }

}
