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
  // Should this be in this system or in MoveCommand
  glm::vec3 final_translation = glm::rotate(transform->getLocalRotation(), 
                                            glm::vec4(translate,1));
  
  transform->applyTranslation(final_translation);
}

void MovementSystem::rotateEntity(glm::vec3 euler_rotation,
  entityx::ComponentHandle<Transform> transform)
{
  glm::quat qPitch = glm::angleAxis(euler_rotation.x, glm::vec3(1, 0, 0));
  glm::quat qYaw =  glm::angleAxis(euler_rotation.y, glm::vec3(0, 1, 0));
  glm::quat qRoll = glm::angleAxis(euler_rotation.z, glm::vec3(0, 0, 1));
  
  glm::quat rotQuat = qYaw *qPitch * qRoll;

  transform->applyRotation(rotQuat);
}

void MovementSystem::update
(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
  entityx::ComponentHandle<MoveAction> move_action;
  entityx::ComponentHandle<RotateAction> rotate_action;
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

  for (entityx::Entity entity : es.entities_with_components(rotate_action,transform))
  {
    rotateEntity(rotate_action->rotation, transform);
    rotate_action.remove();
  }

}
