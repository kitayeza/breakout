#ifndef BREAKOUT_GAMEOBJECT_H
#define BREAKOUT_GAMEOBJECT_H

#endif //BREAKOUT_GAMEOBJECT_H

#pragma once

#include "Renderer.h"

class MyApp;

class GameObject {

private:

    Renderable renderable;
    bool dead = false;

protected:

    MyApp* app;
    Renderer* renderer;

public:


    Transform transform;
    glm::vec4 color = glm::vec4(1.f, 0.f, 0.f, 1.f);

    GameObject(MyApp *a, Renderable r);
    virtual void OnUpdate() = 0;
    virtual void OnDraw() = 0;

    GameObject& SetPosition(float x, float y);
    GameObject& SetColor(float v0, float v1, float v2, float v3);
    [[nodiscard]] glm::vec2 GetCenter() const;

    [[nodiscard]] Renderable const &getRenderable() const { return renderable; };

    void move(float x, float y);


    void Destroy();
    [[nodiscard]] bool isDead() const{ return dead; };

};