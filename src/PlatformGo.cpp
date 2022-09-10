#include "PlatformGo.h"
#include "utils.h"

void PlatformGo::OnUpdate()
{
    auto pltSpeed = transform.velocity.x;

    if (Application::IsKeyPressed(GLFW_KEY_LEFT) || Application::IsKeyPressed(GLFW_KEY_RIGHT))
    {
        curAccelerationSpeed += accelerationSpeed * (std::max(fabsf(curAccelerationSpeed), topAccelerationSpeed * 0.15f));
    }
    else
    {
        curAccelerationSpeed -= std::min(friction / 2, fabsf(curAccelerationSpeed)) * sign(curAccelerationSpeed);

        if (fabsf(pltSpeed) > 0)
            pltSpeed += std::min(friction * (std::max(fabsf(pltSpeed), 0.25f) / topSpeed), fabsf(pltSpeed)) * -sign(pltSpeed);
    }
    pltSpeed += curAccelerationSpeed * (Application::IsKeyPressed(GLFW_KEY_LEFT) ? -1 : 1);
    curAccelerationSpeed =std::min(fabsf(curAccelerationSpeed), topAccelerationSpeed) * sign(curAccelerationSpeed);
    pltSpeed = std::min(fabsf(pltSpeed), topSpeed) * sign(pltSpeed);

    move(pltSpeed, 0.f);
    transform.velocity.x = pltSpeed;

    if (transform.pos.x < 0)
    {
        transform.pos.x = 0;
        transform.velocity.x = 0;
        curAccelerationSpeed = 0;
    }
    else if (transform.pos.x > windowWidth - transform.size.x)
    {
        transform.pos.x = windowWidth - transform.size.x;
        transform.velocity.x = 0;
        curAccelerationSpeed = 0;
    }
}

void PlatformGo::OnDraw()
{
    renderer->Draw(this, getRenderable().shader);
}

PlatformGo::PlatformGo(MyApp *app, Renderable r) : GameObject(app, r)
{
    Application::getApp().GetWindowSize(windowWidth, windowHeight);
}
