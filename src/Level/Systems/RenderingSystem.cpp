#include "RenderingSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Graphics/Camera.h"

RenderingSystem::RenderingSystem(ResourceManager& resources, Renderer& renderer)
:resources(resources), renderer(renderer)
{
  renderer.init();
  renderer.setWindow(renderer.createWindow(800,600,"luciano"));
}

void RenderingSystem::update
(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
  entityx::ComponentHandle<Draw> draw;
  entityx::ComponentHandle<Transform> transform;

  renderer.clear();

  for (entityx::Entity entity : es.entities_with_components(draw, transform)) {
    Model* model = resources.getModel(draw->filename);
    Shader* shader = resources.getShader(draw->vertshader, draw->fragshader);

    // Enable shader before setting uniforms
    shader->enable();

    // Move to a component or other system
      Camera camera(glm::vec3(0.0f, -10.0f, -2.0f));
      // view/projection transformations
      glm::mat4 projection, view;
      projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
      view = camera.GetViewMatrix();
      shader->setUniformMat4("projection", projection);
      shader->setUniformMat4("view", view);

    // Create the model matrix by applying the transforms
    glm::mat4 modelmat = transform->translate *transform->rotation * transform->scale;

    shader->setUniformMat4("model", modelmat);
    shader->setUniformVec3("in_light", glm::vec3(0.0f,-4.5f,-1.0f));
    model->Draw(*shader);
  }

  renderer.draw();
}
