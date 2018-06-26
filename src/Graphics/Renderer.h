#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "Model.h"



//make abstract that returns this?
using Window = GLFWwindow;

class Renderer
{
  GLFWwindow* window;

  public:

  Renderer();
  ~Renderer();

  int init();

  GLFWwindow* createWindow(int width, int height, std::string name);
  int setWindow(GLFWwindow* window);
  GLFWwindow* getWindow();
  void clear();
  void draw();
};
