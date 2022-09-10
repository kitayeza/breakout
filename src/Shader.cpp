#include "Shader.h"
#include "utils.h"

unsigned int Shader::compileShader(unsigned int type, const std::unique_ptr<char[]>& source)
{
    const auto shader = glCreateShader(type);
    const auto& cStr = source.get();
    glShaderSource(shader, 1, &cStr, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &length);

        auto message = new char[length];
        glGetShaderInfoLog(shader, length, &length, message);

        std::cout << "Failed to compile shader: " << message << '\n';

        delete[] message;
        return 0;

    }

    return shader;

}

unsigned int Shader::createShaderProgram(const std::unique_ptr<char[]>& vertexSource,
                                         const std::unique_ptr<char[]>& fragmentSource)
{
    const auto program = glCreateProgram();

    auto compileVertexSource = Shader::compileShader(GL_VERTEX_SHADER, vertexSource);
    auto compileFragmentSource = Shader::compileShader(GL_FRAGMENT_SHADER,fragmentSource);

    if(compileFragmentSource == 0 ||compileVertexSource == 0) return 0;

    glAttachShader(program, compileVertexSource);
    glAttachShader(program, compileFragmentSource);

    glLinkProgram(program);
    glValidateProgram(program);

    return program;

}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    const auto vertex = readFile(vertexFile);
    const auto fragment = readFile(fragmentFile);
    programID = Shader::createShaderProgram(vertex,fragment);

}

Shader::~Shader()
{
    glDeleteProgram(programID);
}

int Shader::getUniformLocation(const char* name) const
{
    auto location = glGetUniformLocation(programID, name);

    if (location == -1)
        std::cout << "Uniform '" << name << "' doesnt exist" << '\n';

    return location;
}

void Shader::setUniform4f(const char* name, float v0, float v1, float v2, float v3) const
{
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniformMat4f(const char* name, const glm::mat4 matrix) const
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniformVec2f(const char* name, glm::vec2 vec) const
{
    glUniform2fv(getUniformLocation(name), 1, &vec[0]);
}

void Shader::setUniform1f(const char* name, float v0) const
{
    glUniform1f(getUniformLocation(name), v0);
}

void Shader::Bind() const
{
    GL_CALL(glUseProgram(programID));
};

void Shader::Unbind() const
{
    glUseProgram(0);
};


