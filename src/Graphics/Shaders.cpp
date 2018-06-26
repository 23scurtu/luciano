#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include "loadShaders.h"

Shader::Shader(const char* vertex, const char* fragment)
{
	ID = loadShaders(vertex, fragment);
}

void Shader::enable()
{
	glUseProgram(ID);
}

void Shader::disable()
{
	glUseProgram(0);
}

void Shader::setUniformVec3(GLchar* name, glm::vec3 vector)
{
	glUniform3f(glGetUniformLocation(ID, name), vector.x, vector.y, vector.z);
}

void Shader::setUniformMat4(GLchar* name, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setFloat(const GLchar* name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name), value);
}
