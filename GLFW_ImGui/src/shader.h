#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	unsigned int id;

	Shader(const char* vertPath, const char* fragPath) {
		// retrieve the vert/frag source code from filepath
		std::string vertString, fragString;
		std::ifstream vertFile, fragFile;
		// ensure ifstream objects can throw exceptions
		vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			// open files
			vertFile.open(vertPath);
			fragFile.open(fragPath);

			// read the files contents into streams
			std::stringstream vertStream, fragStream;
			vertStream << vertFile.rdbuf();
			fragStream << fragFile.rdbuf();

			// close file handlers
			vertFile.close();
			fragFile.close();

			// convert streams into strings
			vertString = vertStream.str();
			fragString = fragStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER : FILE NOT SUCCESSFULLY READ" << std::endl;
			return;
		}

		const char* vertCode = vertString.c_str();
		const char* fragCode = fragString.c_str();

		// compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertCode, NULL);
		glCompileShader(vertex);

		// print any errors
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX : COMPILATION FAILED\n" << infoLog << std::endl;
		}

		// fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragCode, NULL);
		glCompileShader(fragment);

		// print any errors
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT : COMPILATION FAILED\n" << infoLog << std::endl;
		}

		// create shader program
		id = glCreateProgram();
		glAttachShader(id, vertex);
		glAttachShader(id, fragment);
		glLinkProgram(id);

		// print any linking errors
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM : LINKING FAILED\n" << infoLog << std::endl;
		}

		// delete shaders now that the program is created
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Use() {
		glUseProgram(id);
	}

	void SetBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
	}

	void SetInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}

	void SetFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}

	void SetVec3(const std::string& name, int count, glm::vec3 value) const {
		glUniform3fv(glGetUniformLocation(id, name.c_str()), count, glm::value_ptr(value));
	}

	void SetMat4(const std::string& name, int count, glm::mat4 value) const {
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), count, GL_FALSE, glm::value_ptr(value));
	}
};

#endif