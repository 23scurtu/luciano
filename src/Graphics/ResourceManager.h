#pragma once

#include <map>
#include <string>
#include "Model.h"
#include "Shaders.h"
#include <utility>

using namespace std;

class ResourceManager
{
  map<pair<string,string>, Shader*> shaders;
  map<string, Model*> models;
public:
  Model* getModel(string filepath);
  Shader* getShader(string vertshader,string fragshader);
};
