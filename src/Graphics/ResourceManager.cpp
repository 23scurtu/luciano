#include "ResourceManager.h"

using namespace std;

Model* ResourceManager::getModel(string filepath)
{
  auto modelIt = models.find(filepath);
  if(modelIt != models.end()) return modelIt->second;

  // File hasn't yet been loaded
  modelIt = models.insert( pair<string,Model*>(filepath, new Model(filepath.c_str())) ).first;
  return modelIt->second;
}

Shader* ResourceManager::getShader(string vertshader,string fragshader)
{
  auto shaderIt = shaders.find(make_pair(vertshader,fragshader));
  if(shaderIt != shaders.end()) return shaderIt->second;

  shaderIt = shaders.insert( pair<pair<string,string>,Shader*>(make_pair(vertshader,fragshader),
                                                              new Shader(vertshader.c_str(),fragshader.c_str()) )).first;
  return shaderIt->second;
}
