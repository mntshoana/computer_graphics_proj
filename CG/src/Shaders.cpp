#include "OpenglDebugger.h"
#include "Shaders.h"


ShaderSource Shader::ParseShader()
{
	std::ifstream input(filepath);
	if (!input.is_open())
	{
		// Error opening file
		std::cerr << "Error! unable to open shader file \"" << filepath << std::endl;
		ASSERT(false);
	}
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream stream[2];
	ShaderType type = ShaderType::NONE;
	while (getline(input, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			// if current line read contains a new shader type syntax
			// switch into the correct shader moder
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			// continue reading in current mode
			stream[(unsigned int)type] << line << std::endl;
		}
	}
	return { stream[0].str(), stream[1].str() };
}

Shader::Shader(const std::string& filepath) :filepath(filepath)
{
	shaderID = 0;
	ShaderSource source = ParseShader();
	shaderID = CreateShader(source.vertexSource, source.fragmentSource);

}

Shader::~Shader()
{
	glDeleteProgram(shaderID); ASSESS_LINE;
}

void Shader::Bind()
{
	glUseProgram(shaderID); ASSESS_LINE;
}

void Shader::Unbind()
{
	glUseProgram(0); ASSESS_LINE;
	uniformCache.clear();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int shader = glCreateShader(type);
	const char* ptrSource = static_cast<const char*>(source.c_str());
	glShaderSource(shader, 1, &ptrSource, nullptr); ASSESS_LINE;
	glCompileShader(shader); ASSESS_LINE;

	// Verify if successfully compiled
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &(success));
	if (success == GL_FALSE)
	{
		int errorLength;
		char* message = nullptr;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLength);
		message = static_cast<char*>(alloca(sizeof(char) * errorLength));
		glGetShaderInfoLog(shader, errorLength, &errorLength, message);

		// Output mesage
		std::cout << "Error! Failed to compile ";
		if (type == GL_VERTEX_SHADER) std::cout << "the Vertex Shader ";
		else if (type == GL_FRAGMENT_SHADER) std::cout << "the Fragment Shader ";
		std::cout << std::endl
			<< message;

		// Clean up
		glDeleteShader(shader);
		return 0;
	}
	// assert if not

	return shader;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vs); ASSESS_LINE;
	glAttachShader(program, fs); ASSESS_LINE;
	glLinkProgram(program); ASSESS_LINE;
	glValidateProgram(program); ASSESS_LINE;

	// Clean Up
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int Shader::GetUniformAddress(const std::string& name) const  
{
	if (uniformCache.find(name) != uniformCache.end())
		return uniformCache[name];
	else
	{
		int address = glGetUniformLocation(shaderID, name.c_str()); ASSESS_LINE;
		ASSERT(address != -1); // validate address
		uniformCache[name] = address;
		return address;
	}
}

void Shader::SetUniform(const std::string& name, float f1, float f2, float f3, float f4)
{
	int address = GetUniformAddress(name);
	glUniform4f(address, f1, f2, f3, f4); ASSESS_LINE;
}
void Shader::SetUniform(const std::string& name, glm::vec4 vector)
{
	int address = GetUniformAddress(name);
	glUniform4f(address, vector.x, vector.y, vector.z, vector.w); ASSESS_LINE;
}
void Shader::SetUniform(const std::string& name, int i1)
{
	int address = GetUniformAddress(name);
	glUniform1i(address, i1); ASSESS_LINE;
}

void Shader::SetUniform(const std::string& name, const glm::mat4 matrix)
{
	int address = GetUniformAddress(name);
	glUniformMatrix4fv(address, 1, GL_FALSE, &matrix[0][0]); ASSESS_LINE;
}
