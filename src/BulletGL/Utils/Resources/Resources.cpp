#include "UI.h"
#include "Utils/Resources/Resources.h"
#include "Utils/Resources/ModelLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


namespace BulletGL
{
	std::vector<Shader*>	Resources::shaders = {};
	std::vector<Model*>		Resources::models = {};
	std::vector<Texture*>	Resources::textures = {};

	Shader* Resources::LoadShader(const char* vertexPath, const char* fragmentPath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			//open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			std::cout << e.what() << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex, fragment;
		int success;
		char infoLog[512];


		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		// print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		unsigned int programID = glCreateProgram();
		glAttachShader(programID, vertex);
		glAttachShader(programID, fragment);
		glLinkProgram(programID);

		glGetProgramiv(programID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(programID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			std::cout << vertexPath << std::endl;
			std::cout << fragmentPath << std::endl << std::endl;
		}

		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		shaders.push_back(new Shader(programID));

		return shaders.back();
	}

	Model* Resources::LoadModel(const char* modelPath, bool processMaterial)
	{
		models.push_back(ModelLoader::loadModel(modelPath, processMaterial));
		return models.back();
	}

	Texture* Resources::LoadTexture(const char* imagePath, bool srgb, unsigned int  filterMode)
	{
		Texture* texture = new Texture();
		int nrChannels = 0;
		texture->data = stbi_load(imagePath, &texture->width, &texture->height, &nrChannels, 0);
		if (!texture->data)
		{
			std::cout << "Failed to load texture" << std::endl;
		}

		cout << "Loaded texture from "s + imagePath << endl;
		cout << "texture size: " << texture->width << "x" << texture->height << endl;

		glCreateTextures(GL_TEXTURE_2D, 1, &texture->id);

		glTextureParameteri(texture->id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(texture->id, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(texture->id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(texture->id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (nrChannels == 1)
		{
			texture->format = GL_RED;
			texture->internalFormat = GL_R8;
		}
		else if (nrChannels == 2)
		{
			texture->format = GL_RG;
			texture->internalFormat = GL_RG8;
		}
		else if (nrChannels == 3)
		{
			texture->format = GL_RGB;
			texture->internalFormat = srgb ? GL_SRGB8 : GL_RGB8;
		}
		else if (nrChannels == 4)
		{
			texture->format = GL_RGBA;
			texture->internalFormat = srgb ? GL_SRGB8_ALPHA8 : GL_RGBA8;
		}

		glTextureStorage2D(texture->id, 6, texture->internalFormat, texture->width, texture->height);
		glTextureSubImage2D(texture->id, 0, 0, 0, texture->width, texture->height, texture->format, GL_UNSIGNED_BYTE, texture->data);

		glGenerateTextureMipmap(texture->id);

		textures.push_back(texture);
		return texture;
	}


	void Resources::DeallocateMemory()
	{
		for (auto shader : shaders)	delete shader;
		for (auto model : models)	delete model;
		for (auto texture : textures)	delete texture;
	}

}