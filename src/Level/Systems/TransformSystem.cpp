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

void TransformSystem::recalculateInverseFinal(entityx::ComponentHandle<Transform> transform)
{
  if(transform->finalInverseDirty)
  {
    entityx::ComponentHandle<Transform> parent_transform;
    if(transform->parent.valid())
    {
      recalculateFinal(transform->parent.component<Transform>());
      parent_transform = transform->parent.component<Transform>();
    }

    // Create the inverse model matrix by applying the transforms in reverse order
    transform->localMatrix = glm::scale(glm::mat4(1.0f), -transform->localScale)
      * glm::toMat4(glm::conjugate(transform->localRotation))
      * glm::translate(glm::mat4(1.0f), -transform->localTranslation);

    if(parent_transform) transform->localMatrix = parent_transform->localMatrix * transform->localMatrix;
    transform->finalInverseDirty = false;
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

void TransformSystem::dirtyInverseChildren(entityx::ComponentHandle<Transform> transform)
{
  for(auto child: transform->children)
  {
    // Do not recurse on transforms that have been or will be visited.
    if(!child.component<Transform>()->finalInverseDirty) dirtyInverseChildren(child.component<Transform>());

    child.component<Transform>()->finalInverseDirty = true;
  }
}

void TransformSystem::update
(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
  entityx::ComponentHandle<Transform> transform;

  for (entityx::Entity entity : es.entities_with_components(transform))
  {
    if(transform->localDirty)
    {
      transform->finalDirty = true;
      transform->finalInverseDirty = true;
    }

    if(transform->finalDirty)
    {
      dirtyChildren(transform);
    }

    if(transform->finalInverseDirty)
    {
      dirtyInverseChildren(transform);
    }
  }

  for (entityx::Entity entity : es.entities_with_components(transform))
  {
    recalculateFinal(transform);
    recalculateInverseFinal(transform);

    // glm::vec3 test_point(0.0,0.0,0.0);
    // std::cout << "before " << test_point.x << ", " << test_point.y << ", " << test_point.z << std::endl;
    // glm::mat4 inverse = transform->getLocalMatrix();
    // glm::mat4 world = transform->getWorldMatrix();

    // test_point = glm::vec3(world*glm::vec4(test_point, 1));
    // std::cout << "between " << test_point.x << ", " << test_point.y << ", " << test_point.z << std::endl;
    // test_point = glm::vec3(inverse*glm::vec4(test_point, 1));
    // std::cout << "after " << test_point.x << ", " << test_point.y << ", " << test_point.z << std::endl;
  }
}
