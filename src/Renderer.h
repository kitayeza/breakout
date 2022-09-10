#ifndef BREAKOUT_RENDER_H
#define BREAKOUT_RENDER_H

#endif //BREAKOUT_RENDER_H

#pragma once
#include "Shader.h"

class GameObject;

struct Transform {

    glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 velocity = glm::vec3(0.f, 0.f, 0.f);
    glm::vec2 size;

    Transform() = default;
    ~Transform() = default;

};

struct Renderable {

    unsigned int vao;
    float width;
    float height;
    const Shader *shader;
};

class Renderer {

private:

    glm::mat4 proj{};
    glm::mat4 view{};
    glm::vec4 clearColor{};

    unsigned int currentShader = 0;


public:
    Renderer() = default;
    Renderer(float width, float height);
    ~Renderer() = default;
    Renderable CreateRect(float, float , const Shader &);

    void SetClearColor(float, float, float, float);
    void Clear();

    void UseShader(const Shader&);
    void UseShader(const Shader*);
    void Draw(const GameObject&, const Shader&);
    void Draw(const GameObject*,const Shader*);
};
