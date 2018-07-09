#pragma once

#include "entityx/entityx.h"
#include <string>
#include "Graphics/ResourceManager.h"
#include "Graphics/Renderer.h"
#include "Timer.h"

class Level
{
public:
  virtual void update() = 0;
};

class MainLevel: public Level, public entityx::EntityX
{
  ResourceManager resources;
  Renderer renderer;

  Timer timer;
  uint64_t next_game_tick;

  void updateGameLogic();
  void updateGraphics(entityx::TimeDelta dt);
public:
  MainLevel(std::string filename);
  void update() override;
};
