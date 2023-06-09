#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

#include "utilities/stb_image.h"

class Texture {
public:
	Texture() {
		diffuse = NULL;
		specular = NULL;
	}

	Texture(std::string diffuseFile, std::string specularFile) {
		stbi_set_flip_vertically_on_load(true);

		int width, height, numChannels;
		unsigned char* data;

		glGenTextures(1, &diffuse);
		glGenTextures(1, &specular);

		glBindTexture(GL_TEXTURE_2D, diffuse);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		data = stbi_load(diffuseFile.c_str(), &width, &height, &numChannels, 0);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		stbi_image_free(data);

		glBindTexture(GL_TEXTURE_2D, specular);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		data = stbi_load(specularFile.c_str(), &width, &height, &numChannels, 0);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		stbi_image_free(data);
	}

	void loadTexture(std::string textureFile, GLuint& outTexture) {
		stbi_set_flip_vertically_on_load(true);

		int width, height, numChannels;
		unsigned char* data;

		glGenTextures(1, &outTexture);
		glBindTexture(GL_TEXTURE_2D, diffuse);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		data = stbi_load(textureFile.c_str(), &width, &height, &numChannels, 0);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		stbi_image_free(data);
	}

	GLuint GetDiffuse() {
		return diffuse;
	}

	GLuint GetSpecular() {
		return specular;
	}

private:
	GLuint diffuse;
	GLuint specular;
};

#endif