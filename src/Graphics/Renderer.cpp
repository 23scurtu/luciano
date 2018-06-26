#include "Renderer.h"
#include <iostream>

using namespace std;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
  glfwTerminate();
}

int Renderer::init()
{
  if( !glfwInit() )
  {
      cerr << "Failed to initialize GLFW\n" << endl;
      return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  return 0;
}

GLFWwindow* Renderer::createWindow(int width, int height, string name)
{
  GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
  if (window == NULL)
  {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return 0;
  }

  return window;
}

int Renderer::setWindow(GLFWwindow* window)
{
  // Perhaps add ability to set such options
  // // draw in wireframe
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  this->window = window;

  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental=true;
  if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to initialize GLEW\n");
      return -1;
  }

  // Configure global opengl state
  glEnable(GL_DEPTH_TEST);

  // Tell GLFW to capture our mouse, Remove when adding input system
  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  return 0;
}

void Renderer::clear()
{
  glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw()
{
  if(!window) throw;
  // Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
  glfwSwapBuffers(window);
  glfwPollEvents(); // Find way to decouple...
}

GLFWwindow* Renderer::getWindow()
{
  return window;
}