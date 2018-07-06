#pragma once

#include <glm/glm.hpp>
#include "Level/Components.h"

class Command
{
public:
  virtual ~Command() = default;
  virtual void execute(entityx::Entity &entity) = 0;
};

class MoveCommand: public Command
{
  glm::vec3 direction;
public:
  MoveCommand(glm::vec3 direction):
    direction{direction} {}
  void execute(entityx::Entity &entity) override;
};
