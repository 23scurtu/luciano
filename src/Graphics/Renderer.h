#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "Model.h"
#include "Window.h"

class Renderer;

//make abstract that returns this?
// using Window = GLFWwindow;
//make window a seperate class with pointer to renderer for more oop?


enum WindowRenderOptions
{
  VERTICAL_SYNC = 0x01
};

class Renderer
{
  Window* window;

  public:

  Renderer();
  ~Renderer();

  int init();

  Window* createWindow(int width, int height, std::string name);
  int setWindow(Window* window, int flags = 0);
  //TODO Functions for changing window flags
  Window* getWindow();
  void clear();
  void draw();
};
