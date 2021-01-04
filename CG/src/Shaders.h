#ifndef SHADER_CONSTANT
#define SHADER_CONSTANT

#include "OpenglDebugger.h"

class ShaderSource
{
public:
	std::string vertexSource;
	std::string fragmentSource;
};
class Shader
{
private:
	unsigned int shaderID;
	const std::string filepath;
	ShaderSource ParseShader();
	mutable std::unordered_map<std::string, int> uniformCache;
	
public:
	Shader(const std::string& filepath);
	~Shader();
	
	void Bind();
	void Unbind();
	
private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformAddress(const std::string& name) const;
public:
	void SetUniform(const std::string& name, float, float, float, float);
	void SetUniform(const std::string& name, glm::vec4 vector);
	void SetUniform(const std::string& name, int);
	void SetUniform(const std::string& name, const glm::mat4);
};
#endif