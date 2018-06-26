#pragma once

#include <glm/glm.hpp>
#include <string>
#include "entityx/entityx.h"

struct Draw
{
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
