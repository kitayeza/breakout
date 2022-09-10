#include "GameObject.h"

GameObject::GameObject(MyApp *a, Renderable r)
{
    transform.size = glm::vec2(r.width, r.height);
}

GameObject &GameObject::SetPosition(float x, float y)
{
    transform.pos[0] = x;
    transform.pos[1] = y;
    return *this;
}

GameObject &GameObject::SetColor(float v0, float v1, float v2, float v3)
{
    color = glm::vec4(v0, v1, v2, v3);
    return *this;
}

glm::vec2 GameObject::GetCenter() const
{
    return glm::vec2(transform.pos.x + renderable.width / 2., transform.pos.y + renderable.height / 2.);
}


void GameObject::move(float x, float y)
{
    transform.pos[0] += x;
    transform.pos[1] += y;
}

void GameObject::Destroy()
{
    dead = true;
}



