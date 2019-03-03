#pragma once

#include <glm/glm.hpp>
#include "Level/Components.h"

class Command
{
public:
  virtual ~Command() = default;
  virtual void execute(entityx::Entity &entity) = 0;
};

class AnalogCommand: public Command
{
  // TODO Find ways to support integers as well? Note that GLFW joysticks use floats.
  // Even though current commands always use this as a float/double, integers might 
  // be needed for gui operations later.
  double analog_input = 0.0;
public:
  virtual ~AnalogCommand() = default;
  void setAnalog(double input) { analog_input = input; }
  double getAnalog() { return analog_input; }
};

class MoveCommand: public Command
{
  glm::vec3 direction;
public:
  MoveCommand(glm::vec3 direction):
    direction{direction} {}
  void execute(entityx::Entity &entity) override;
};

// TODO Centralize enums?
enum Axis
{
  X_AXIS = 1,
  Y_AXIS = 2,
  Z_AXIS = 3
};

class RotateCommand: public AnalogCommand
{
  Axis axis;
  bool is_global;
  public:
  // TODO Make mouse_pos from center?
  RotateCommand(Axis axis, bool is_global = false):
    axis{axis}, is_global{is_global} {}
  void execute(entityx::Entity &entity) override;
};
