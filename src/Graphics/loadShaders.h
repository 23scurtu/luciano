#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>

using namespace std;

GLuint loadShaders(const char* vertShaderPath, const char* fragShaderPath);
