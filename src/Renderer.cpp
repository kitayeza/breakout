#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utils.h"
#include "GameObject.h"

Renderer::Renderer(float width, float height)
{
    this->proj = glm::ortho(0.0f, width, 0.0f, height, -1.f, 1.f);
    this->view = glm::mat4(1.0f);
}

Renderable Renderer::CreateRect(float w, float h, const Shader &shader)
{
    const float vertices[] = {
            0.f, 0.f,
            w, 0.f,
            w, h,
            0.f, h
    };

    const unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    unsigned int vao;
    unsigned int vbo;
    unsigned int ibo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (const void*)vertices, GL_STATIC_DRAW);

    // glEnableVertexArrayAttrib(vao, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), (const void*)indices, GL_STATIC_DRAW);

    return { vao, w, h, &shader };
}

void Renderer::SetClearColor(float v0, float v1, float v2, float v3)
{
    clearColor.r = v0;
    clearColor.g = v1;
    clearColor.b = v2;
    clearColor.a = v3;
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

void Renderer::UseShader(const Shader& shader)
{
    if (currentShader == shader.getProgramID())
        return;

    currentShader = shader.getProgramID();

    shader.Bind();
}

void Renderer::UseShader(const Shader* shader)
{
    UseShader(*shader);
}

void Renderer::Draw(const GameObject& object, const Shader& shader)
{
    UseShader(shader);
    auto model = glm::translate(glm::mat4(1.0f), object.transform.pos);
    auto mvp = proj * view * model;
    shader.setUniformMat4f("u_MVP", mvp);

    shader.setUniform4f("u_Color", object.color.r, object.color.g, object.color.b, object.color.a);

    ASSERT(object.getRenderable().vao != 0);
    GL_CALL(glBindVertexArray(object.getRenderable().vao));
    GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

}

void Renderer::Draw(const GameObject* object, const Shader* shader)
{
    Draw(*object, *shader);
}

