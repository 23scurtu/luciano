#include "Window.h"

Window::Window(GLFWwindow* window): window{window}
{
  glfwSetWindowUserPointer(window, this);
}

void Window::keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  Keyboard* keyboard = static_cast<Window*>(glfwGetWindowUserPointer(window))->keyboard;
  keyboard->keyInputCallback(key, scancode, action, mods);
}

void Window::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
  Mouse* mouse = static_cast<Window*>(glfwGetWindowUserPointer(window))->mouse;
  mouse->cursorPosCallback(xpos, ypos);
}

void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
  Mouse* mouse = static_cast<Window*>(glfwGetWindowUserPointer(window))->mouse;
  mouse->scrollCallback(xoffset, yoffset);
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
  Mouse* mouse = static_cast<Window*>(glfwGetWindowUserPointer(window))->mouse;
  mouse->mouseButtonCallback(button, action,  mods);
}

void Window::setKeyboard(Keyboard* keyboard)
{
  this->keyboard = keyboard;
  glfwSetKeyCallback(window, keyInputCallback);
}

void Window::setMouse(Mouse* mouse)
{
  this->mouse = mouse;
  glfwSetCursorPosCallback(window, cursorPosCallback);
  glfwSetScrollCallback(window, scrollCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

bool Window::setMouseMode(Mode mode)
{
  if(mouse == nullptr) return false;

  glfwSetInputMode(window, GLFW_CURSOR, mode);

  mouse->mode = mode;
  return true;
}

size_t Window::getWidth()
{
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  return width;
}

size_t Window::getHeight()
{
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  return height;
}
