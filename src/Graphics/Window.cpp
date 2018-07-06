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

void Window::setKeyboard(Keyboard* keyboard)
{
  this->keyboard = keyboard;
  glfwSetKeyCallback(window, keyInputCallback);
}
