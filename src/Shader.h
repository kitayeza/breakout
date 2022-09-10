#ifndef BREAKOUT_SHADER_H
#define BREAKOUT_SHADER_H

#endif //BREAKOUT_SHADER_H

#include <glm/glm.hpp>
#include <memory>

class Shader {

private:

 unsigned int programID;

 static unsigned int compileShader(unsigned int, const std::unique_ptr<char[]>&);
 static unsigned int createShaderProgram(const std::unique_ptr<char[]>&, const std::unique_ptr<char[]>&);

public:

 Shader(const char*, const char*);
 ~Shader();

    void setUniform4f(const char* name, float v0, float v1, float v2, float v3) const;
    void setUniformMat4f(const char* name, glm::mat4 matrix) const;
    void setUniformVec2f(const char* name, glm::vec2 vec) const;
    void setUniform1f(const char* name, float v0) const;
    int getUniformLocation(const char* name) const;

    void Bind() const;
    void Unbind() const;
    [[nodiscard]] unsigned int getProgramID() const { return this->programID; };


};

