#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Input/Keyboard.h"

class Renderer;

#pragma once

class Window
{
  friend class Renderer;
  GLFWwindow * window;
  Window(GLFWwindow* window);
  // TODO Change ownership of keyboard to Window
  Keyboard* keyboard;

  // Window callbacks
  static void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
public:

  void setKeyboard(Keyboard* keyboard);
};
