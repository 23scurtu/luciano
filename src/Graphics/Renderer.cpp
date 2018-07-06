#include "Renderer.h"
#include <iostream>
#include <chrono>
using namespace std::chrono;

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

Window* Renderer::createWindow(int width, int height, string name)
{
  GLFWwindow* glwindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
  if (glwindow == NULL)
  {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return 0;
  }

  Window* window = new Window(glwindow);

  return window;
}

int Renderer::setWindow(Window* window, int flags)
{
  // Perhaps add ability to set such options
  // // draw in wireframe
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  this->window = window;

  glfwMakeContextCurrent(window->window);

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

  // Enable or disable v-sync
  glfwSwapInterval(flags & VERTICAL_SYNC);

  return 0;
}

void Renderer::clear()
{
  glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw()
{
  if(!window->window) throw;
  // Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
  glfwSwapBuffers(window->window);
  glfwPollEvents(); // Find way to decouple...
}

Window* Renderer::getWindow()
{
  return window;
}
