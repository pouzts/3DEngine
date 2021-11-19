#pragma once
#include "../Resource/Resource.h"
#include "Shader.h"
#include <map>
#include <vector>
#include <memory>

namespace PhoenixEngine
{
	class Program : public Resource
	{
	public:
		Program();
		~Program();

		bool Load(const std::string& name, void* data) override;
		void AddShader(const std::shared_ptr<Shader>& shader);

		void Link();
		void Use();

		GLuint GetID() { return program; }
		bool IsLinked() { return linked; }

		void SetUniform(const std::string& name, float x, float y, float z);
		void SetUniform(const std::string& name, const glm::vec2& v2);
		void SetUniform(const std::string& name, const glm::vec3& v3);
		void SetUniform(const std::string& name, const glm::vec4& v4);
		void SetUniform(const std::string& name, const glm::mat4& mx4);
		void SetUniform(const std::string& name, const glm::mat3& mx3);
		void SetUniform(const std::string& name, float value);
		void SetUniform(const std::string& name, int value);
		void SetUniform(const std::string& name, bool value);
		void SetUniform(const std::string& name, GLuint value);

	private:
		GLint GetUniform(const std::string& name);

	private:
		GLuint program = 0;
		std::vector<std::shared_ptr<Shader>> shaders;
		std::map<std::string, GLuint> uniforms;
		bool linked = false;
	};
}
