#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Shader
{
		int ID;
	public:
		static const int VERTEX_ATTRIB = 0;
		static const int TEXTURE_ATTRIB = 1;

		Shader(const char* vertex, const char* fragment);
		void enable();
		void disable();
		void setUniformVec3(GLchar* name, glm::vec3 vector);
		void setUniformMat4(GLchar* name, glm::mat4 matrix);
		void setFloat(const GLchar* name, float value);
};
