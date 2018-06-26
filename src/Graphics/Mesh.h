#pragma once

// Heavily using https://learnopengl.com/Model-Loading/Mesh

#include <string>
#include "Shaders.h"
#include <glm/glm.hpp>
#include <vector>

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
    // Store the path of texture to compare with other textures
};

class Mesh
{
  //Render data
  unsigned int VAO, VBO, EBO;

  void setupMesh();
public:
  int VERT = 0;
  int NORM = 1;
  int TEXT = 2;

  vector<Vertex> vertices;
  vector<unsigned int> indices;
  vector<Texture> textures;

  Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
  void Draw(Shader shader);
};
