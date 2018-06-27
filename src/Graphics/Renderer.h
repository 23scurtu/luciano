#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "Model.h"



//make abstract that returns this?
// using Window = GLFWwindow;
//make window a seperate class with pointer to renderer for more oop?

enum WindowRenderOptions
{
  VERTICAL_SYNC = 0x01
};

class Renderer
{
  GLFWwindow* window;

  public:

  Renderer();
  ~Renderer();

  int init();

  GLFWwindow* createWindow(int width, int height, std::string name);
  int setWindow(GLFWwindow* window, int flags = 0);
  //TODO Functions for changing window flags
  GLFWwindow* getWindow();
  void clear();
  void draw();
};
