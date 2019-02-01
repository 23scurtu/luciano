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
  entityx::ComponentHandle<PerspectiveCamera> camera;

  renderer.clear();

  entityx::Entity main_camera;

  for(entityx::Entity entity : es.entities_with_components(camera, transform))
  {
    if(camera->projection_dirty)
      camera->projection = glm::perspective(camera->getFovy(), camera->getAspectRatio(), camera->getNear(), camera->getFar());

    // For now only render the main game window
    // TODO Find better way to handle which camera renders to game window
    if(camera->target_display == 0)
      main_camera = entity;
  }

  for (entityx::Entity entity : es.entities_with_components(draw, transform)) {
    Model* model = resources.getModel(draw->filename);
    Shader* shader = resources.getShader(draw->vertshader, draw->fragshader);

    // Enable shader before setting uniforms
    shader->enable();
        
    //Camera camera(glm::vec3(0.0f, -10.0f, -2.0f));
    
    // view/projection transformations
    glm::mat4 projection, view;
    projection = main_camera.component<PerspectiveCamera>()->projection;
    // TODO Add more indepth transformation to make camera vertical, horizontal
    // and depth directions consistent with normal game objects.
    view = glm::toMat4(main_camera.component<Transform>()->getLocalRotation()) 
         * glm::translate(glm::mat4(1.0f),(-1.0f)*main_camera.component<Transform>()->getLocalTranslation());
    
    shader->setUniformMat4("projection", projection);
    shader->setUniformMat4("view", view);

    shader->setUniformMat4("model", transform->getWorldMatrix());
    shader->setUniformVec3("in_light", glm::vec3(0.0f,-4.5f,-1.0f));
    model->Draw(*shader);
  }

  renderer.draw();
}
