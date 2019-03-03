#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
  bool finalInverseDirty = false;

  glm::vec3 localTranslation;
  glm::quat localRotation;
  glm::vec3 localScale;

  entityx::Entity parent;
  std::vector<entityx::Entity> children;

  glm::mat4 worldMatrix;
  glm::mat4 localMatrix; // Inverse matrix

  // glm::vec3 minRotationClamp;
  // glm::vec3 maxRotationClamp;

public:
  Transform() = default;
  Transform( glm::mat4 translate, glm::mat4 rotation, glm::mat4 scale):
    worldMatrix(translate*rotation*scale){}
  Transform( glm::vec3 translation, glm::quat rotation, glm::vec3 scale):
    localTranslation{translation}, localRotation{rotation}, localScale{scale}{}

  const glm::vec3& getLocalTranslation(){ return localTranslation; }
  const glm::quat& getLocalRotation(){ return localRotation; }
  const glm::vec3& getLocalScale(){ return localScale; }

  glm::vec3 transformDirection(const glm::vec3 & direction)
  {
    glm::vec3 origin(0.0, 0.0, 0.0);
    return  glm::vec3(worldMatrix * glm::vec4(direction,1)) - glm::vec3(worldMatrix * glm::vec4(origin,1));
  }
  glm::vec3 inverseTransformDirection(const glm::vec3 & direction)
  {
    glm::vec3 origin(0.0, 0.0, 0.0);
    return  glm::vec3(localMatrix * glm::vec4(direction,1)) - glm::vec3(localMatrix * glm::vec4(origin,1));
  }

  //TODO Calculate last step here if dirty
  const glm::mat4& getWorldMatrix(){ return worldMatrix; }
  const glm::mat4& getLocalMatrix(){ return localMatrix; }

  // void recalculateInverseFinal()
  // {
  //   // Duplicated code from TransformSystem::recalculateFinal
  //   if(localDirty || finalInverseDirty)
  //   {
  //     entityx::ComponentHandle<Transform> parent_transform;
  //     if(parent.valid())
  //     {
  //       parent.component<Transform>()->recalculateInverseFinal();
  //       parent_transform = parent.component<Transform>();
  //     }

  //     // Create the model matrix by applying the transforms
  //     localMatrix = glm::scale(glm::mat4(1.0f), -localScale)
  //       * glm::toMat4(glm::conjugate(localRotation))
  //       * glm::translate(glm::mat4(1.0f), -localTranslation);

  //     // TODO parent* local?
  //     if(parent_transform) localMatrix = parent_transform->localMatrix * localMatrix;
  //     finalInverseDirty = false;
  //   }
  // }

  // void setRotationClamp(glm::vec3 min, glm::vec3 max);

  void setLocalTranslation(const glm::vec3& translation){ localTranslation = translation; localDirty = true; }
  void setLocalRotation(const glm::quat& rotation){ localRotation = rotation; localDirty = true; }
  void setLocalScale(const glm::vec3& scale){ localScale = scale; localDirty = true; }

  void applyTranslation(glm::vec3 translation){ localTranslation += translation; localDirty = true; }
  void applyRotation(glm::quat rotation){ localRotation =  rotation * localRotation; localDirty = true; }
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
  bool is_global  = false;

  RotateAction() = default;
  RotateAction(glm::vec3 rotation): rotation{rotation} {}
};

struct GlobalRotateAction
{
  glm::vec3 rotation;
  bool is_global  = false;

  GlobalRotateAction() = default;
  GlobalRotateAction(glm::vec3 rotation): rotation{rotation} {}
};
