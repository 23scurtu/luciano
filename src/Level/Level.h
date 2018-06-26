#pragma once

#include "entityx/entityx.h"
#include <string>
#include "Graphics/ResourceManager.h"
#include "Graphics/Renderer.h"

class Level
{
public:
  virtual void update(entityx::TimeDelta dt) = 0;
};

class MainLevel: public Level, public entityx::EntityX
{
  ResourceManager resources;
  Renderer renderer;

public:
  MainLevel(std::string filename);
  void update(entityx::TimeDelta dt) override;
};
