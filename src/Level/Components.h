#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>
#include "entityx/entityx.h"
#include "Input/Command.h"
#include <vector>
#include <set>

struct Draw
{
  Draw() = default;
  Draw(std::string filename, std::string vertshader, std::string fragshader):
    filename(filename), vertshader(vertshader), fragshader(fragshader){}

  std::string filename;
  std::string vertshader;
  std::string fragshader;
};

struct PerspectiveCamera
{
  friend class RenderingSystem;

private:
  bool projection_dirty = true;

  // target_display of 0 indicates the default game window.
  unsigned int target_display = 0;

  float fovy;
  float aspect_ratio;
  float near, far;

  glm::mat4 projection;

public:

  PerspectiveCamera() = default;
  PerspectiveCamera(float fovy, float aspect_ratio, float near = 0.1f, float far = 100.0f):
    fovy{fovy}, aspect_ratio{aspect_ratio}, near{near}, far{far}{}

  float getFovy(){ return fovy; };
  float getAspectRatio(){ return aspect_ratio; };
  float getNear(){ return near; };
  float getFar(){ return far; };
  const glm::mat4& getProjection(){ return projection; }

  void setFovy(float fovy){ this->fovy = fovy; projection_dirty = true; }
  void setAspectRatio(float aspect_ratio){ this->aspect_ratio = aspect_ratio; projection_dirty = true; }
  void setNear(float near){ this->near = near; projection_dirty = true; }
  void setFar(float far){ this->far = far; projection_dirty = true; }
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
  Transform( glm::vec3 translation, glm::quat rotation, glm::vec3 scale):
    localTranslation{translation}, localRotation{rotation}, localScale{scale}{}

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

struct RotateAction
{
  glm::vec3 rotation;

  RotateAction() = default;
  RotateAction(glm::vec3 rotation): rotation{rotation} {}
};
