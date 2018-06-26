#pragma once

// Heavily using https://learnopengl.com/Model-Loading/Model

#include "Shaders.h"
#include "Mesh.h"
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
  vector<Texture> textures_loaded;
  vector<Mesh> meshes;
  string directory;

  void loadModel(string path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

public:
  Model(const char *path){ loadModel(path); }
  void Draw(Shader shader);
};
