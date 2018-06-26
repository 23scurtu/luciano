#include "Mesh.h"
#include <iostream>

using namespace std;

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

void Mesh::setupMesh()
{
  //Note: struct layout is sequential
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  // vertex positions
  glEnableVertexAttribArray(VERT);
  glVertexAttribPointer(VERT, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  // vertex normals
  glEnableVertexAttribArray(NORM);
  glVertexAttribPointer(NORM, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
  // vertex texture coords
  glEnableVertexAttribArray(TEXT);
  glVertexAttribPointer(TEXT, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0); //zero to break the existing vertex array object binding
}

void Mesh::Draw(Shader shader)
{
  unsigned int diffuse_cnt = 1;
  unsigned int specular_cnt = 1;
  for(int i = 0; i < textures.size(); i++)
  {
    // activate proper texture unit before building
    glActiveTexture(GL_TEXTURE0 + i);

    // retrieve texture number (N in diffuse_textureN)
    string number;
    string name = textures[i].type;
    if(name == "texture_diffuse"){
            number = std::to_string(diffuse_cnt++);}
    else if(name == "texture_specular")
        number = std::to_string(specular_cnt++);

    shader.setFloat(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
  }
  glActiveTexture(GL_TEXTURE0);

  // draw mesh
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
