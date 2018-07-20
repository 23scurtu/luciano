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
  friend class TransformSystem;

private:
  bool localDirty = false;
  bool finalDirty = false;

  glm::vec3 localTranslation;
  glm::quat localRotation;
  glm::vec3 localScale;

  entityx::Entity parent;
  std::vector<entityx::Entity> children;

  glm::mat4 worldMatrix;

public:
  Transform() = default;
  Transform( glm::mat4 translate, glm::mat4 rotation, glm::mat4 scale):
    worldMatrix(translate*rotation*scale){}

  const glm::vec3& getLocalTranslation(){ return localTranslation; }
  const glm::quat& getLocalRotation(){ return localRotation; }
  const glm::vec3& getLocalScale(){ return localScale; }

  const glm::mat4& getWorldMatrix(){ return worldMatrix; }

  void setLocalTranslation(const glm::vec3& translation){ localTranslation = translation; localDirty = true; }
  void setLocalRotation(const glm::quat& rotation){ localRotation = rotation; localDirty = true; }
  void setLocalScale(const glm::vec3& scale){ localScale = scale; localDirty = true; }

  void applyTranslation(glm::vec3 translation){ localTranslation += translation; localDirty = true; }
  void applyRotation(glm::quat rotation){ localRotation *= rotation; localDirty = true; }
  void applyScale(glm::vec3 scale){ localScale *= scale; localDirty = true; }
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
