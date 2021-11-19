#include "Shader.h"
#include "Core/FileSystem.h"

namespace PhoenixEngine
{ 
	Shader::~Shader()
	{
		if (program != 0)
		{
			glDeleteShader(shader);
		}
	}

	bool Shader::Load(const std::string& name, void* data)
	{
		std::string source;
		bool success = ReadFileToString(name, source);
		if (success == false)
		{
			SDL_Log("Error: Failed to open file (%s).", name.c_str());
		}

		// create shader
		GLuint shaderType = static_cast<GLuint>(reinterpret_cast<std::uintptr_t>(data));
		shader = glCreateShader(shaderType);

		// compile shader
		const char* source_c = source.c_str();
		glShaderSource(shader, 1, &source_c, NULL);
		glCompileShader(shader);

		// check shader compilation status
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			// display shader error
			GLint length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

			if (length > 0)
			{
				std::string infoLog(length, ' ');
				glGetShaderInfoLog(shader, length, &length, &infoLog[0]);
				SDL_Log("Error: Failed to compile shader.");
				SDL_Log("Shader Info: %s", infoLog.c_str());
			}

			// delete shader
			glDeleteShader(shader);
			shader = 0;
		}

		return true;
	}
}
