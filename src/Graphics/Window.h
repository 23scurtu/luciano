#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Input/Keyboard.h"
#include "Input/Mouse.h"

class Renderer;

#pragma once

class Window
{
  friend class Renderer;
  GLFWwindow * window;
  Window(GLFWwindow* window);
  // TODO Change ownership of keyboard to Window
  Keyboard* keyboard = nullptr;
  Mouse* mouse = nullptr;

  // Window callbacks
  static void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
  static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
  static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

public:
  void setKeyboard(Keyboard* keyboard);
  void setMouse(Mouse* mouse);

  // Returns true if mouse mode has been set
  bool setMouseMode(Mode mode);

  // TODO Perhaps merge to return a vec2?
  // Retrieves the size of the client area of the specified window in screen coordinates. 
  size_t getWidth();
  size_t getHeight();
};
