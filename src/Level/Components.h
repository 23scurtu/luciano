#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>
#include "entityx/entityx.h"
#include "Input/Command.h"
#include <vector>

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
    worldMatrix(translate*rotation*scale){}

  bool localDirty = false;
  bool finalDirty = false;

  glm::vec3 localTranslation;
  glm::quat localRotation;
  glm::vec3 localScale;

  entityx::Entity parent;
  std::vector<entityx::Entity> children;

  glm::mat4 worldMatrix;
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
