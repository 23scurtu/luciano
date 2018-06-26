#include "Level.h"
#include "Components.h"
#include "Systems/RenderingSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

MainLevel::MainLevel( string filename )
{
  systems.add<RenderingSystem>(resources, renderer);
  systems.configure();

  //Create luciano himself
  entityx::Entity luciano_himself = entities.create();
  luciano_himself.assign<Draw>("resources/luciano_himself/doing_it/luciano_renormal.obj",
                      "Shaders/model_load.vertshader",
                      "Shaders/model_load.fragshader");
  luciano_himself.assign<Transform>(
    glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
    glm::rotate(glm::mat4(1.0f),float( 3*M_PI/2), glm::vec3(1.0f,0.0f,0.0f))
        * glm::rotate(glm::mat4(1.0f), float(1*M_PI), glm::vec3(0.0f,1.0f,0.0f)),
    glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 0.05f, 0.05f))

  );
}

void MainLevel::update(entityx::TimeDelta dt)
{
  systems.update<RenderingSystem>(dt);
}
