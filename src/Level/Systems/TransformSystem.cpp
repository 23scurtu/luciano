#include "TransformSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

TransformSystem::TransformSystem()
{
}

void TransformSystem::recalculateFinal(entityx::ComponentHandle<Transform> transform)
{
  if(transform->finalDirty)
  {
    entityx::ComponentHandle<Transform> parent_transform;
    if(transform->parent.valid())
    {
      recalculateFinal(transform->parent.component<Transform>());
      parent_transform = transform->parent.component<Transform>();
    }

    // Create the model matrix by applying the transforms
      transform->worldMatrix = glm::translate(glm::mat4(1.0f), transform->localTranslation)
        * glm::toMat4(transform->localRotation)
        * glm::scale(glm::mat4(1.0f), transform->localScale);

      if(parent_transform) transform->worldMatrix *= parent_transform->worldMatrix;
      transform->finalDirty = false;
  }
}

void TransformSystem::dirtyChildren(entityx::ComponentHandle<Transform> transform)
{
  for(auto child: transform->children)
  {
    // dirtyChildren is called on all transform components with finalDirty in update.
    // Do not recurse on transforms that have been or will be visited.
    if(!child.component<Transform>()->finalDirty) dirtyChildren(child.component<Transform>());

    child.component<Transform>()->finalDirty = true;
  }
}

void TransformSystem::update
(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
  entityx::ComponentHandle<Transform> transform;

  for (entityx::Entity entity : es.entities_with_components(transform))
  {
    if(transform->localDirty) transform->finalDirty = true;

    if(transform->finalDirty)
    {
      dirtyChildren(transform);
    }
  }

  for (entityx::Entity entity : es.entities_with_components(transform))
  {
    recalculateFinal(transform);
  }
}
