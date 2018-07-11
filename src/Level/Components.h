#pragma once

#include <glm/glm.hpp>
#include <string>
#include "entityx/entityx.h"
#include "Input/Command.h"

struct Draw
{
  Draw() = default;
  Draw(std::string filename, std::string vertshader, std::string fragshader):
    filename(filename), vertshader(vertshader), fragshader(fragshader){}

  std::string filename;
  std::string vertshader;
  std::string fragshader;
};

struct Transform
{
  Transform() = default;
  Transform( glm::mat4 translate, glm::mat4 rotation, glm::mat4 scale):
    translate(translate), rotation(rotation), scale(scale) {}

  entityx::Entity parent;
  glm::mat4 translate;
  glm::mat4 rotation;
  glm::mat4 scale;
};

enum InputType
{
  KEYBOARD,
  MOUSE
};

struct Input
{
  InputType type;

  Input() = default;
  Input(InputType type): type{type}{}
};

struct MoveAction
{
  glm::vec3 velocity;

  MoveAction() = default;
  MoveAction(glm::vec3 velocity): velocity{velocity}{}
};

struct Movement
{
  glm::vec3 velocity;
  glm::vec3 acceleration;

  Movement() = default;
};
