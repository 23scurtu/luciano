#include "Level.h"
#include "Components.h"
#include "Systems/RenderingSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/TransformSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

const int GAME_TICKS_PER_SECOND = 60;
const int TIMESTEP_TICKS = 1000000 / GAME_TICKS_PER_SECOND;
const double TIMESTEP_SECS = static_cast<double>(1.0/GAME_TICKS_PER_SECOND);

MainLevel::MainLevel( string filename )
{
  systems.add<RenderingSystem>(resources, renderer);
  // Decouple RenderingSystem needing to be called before Input System
  // (due to Rendering system initing the renderer)
  systems.add<TransformSystem>();
  systems.add<InputSystem>(renderer);
  systems.add<MovementSystem>();

  systems.configure();

  //Create luciano himself
  entityx::Entity luciano_himself = entities.create();
  luciano_himself.assign<Draw>("resources/luciano_himself/doing_it/luciano_renormal.obj",
                      "Shaders/model_load.vertshader",
                      "Shaders/model_load.fragshader");
  luciano_himself.assign<Transform>();

  // float( -2*M_PI/2) glm::vec3(0.0f,1.0f,-1.0f);
  luciano_himself.component<Transform>()->setLocalRotation(glm::quat(glm::vec3(-M_PI/2,0.0f,M_PI)));
  luciano_himself.component<Transform>()->setLocalScale(glm::vec3(0.05f, 0.05f, 0.05f));

  luciano_himself.assign<Input>(KEYBOARD);

  timer.update();
  next_game_tick = timer.curMicros();
}

void MainLevel::update()
{
  // Update timer (request the current time) once per frame
  timer.update();
  double dt = timer.deltaSecs();

  while( timer.curMicros() > next_game_tick)
  {
    cout << dt << endl;
    updateGameLogic();

    next_game_tick += TIMESTEP_TICKS;
  }

  updateGraphics(dt);
}

void MainLevel::updateGameLogic()
{
  systems.update<InputSystem>(TIMESTEP_SECS);
  systems.update<MovementSystem>(TIMESTEP_SECS);
}
void MainLevel::updateGraphics(entityx::TimeDelta dt)
{
  systems.update<TransformSystem>(dt);
  systems.update<RenderingSystem>(dt);
}
