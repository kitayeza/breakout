#include "BallGo.h"
#include "PlatformGo.h"


void BallGo::OnUpdate()
{
    if (app->getState() == State::START) {

        const auto center = app->getPlatform()->GetCenter();
        SetPosition(center.x - (25.f / 2.f), center.y + 30.f);

    }
    else
    {
        const auto ballNextPos = glm::vec3(GetCenter(), .1f) + transform.velocity;
        const auto radius = transform.size.y / 2.;

        transform.velocity *= app->bounceVector(ballNextPos, radius);
        if ((ballNextPos.y - radius) < 0)
        {
            app->Start();
            return;
        }
        move(transform.velocity.x, transform.velocity.y);
    }
}

void BallGo::OnDraw()
{
    renderer->UseShader(getRenderable().shader);
    getRenderable().shader->setUniformVec2f("u_Center", GetCenter());
    getRenderable().shader->setUniform1f("u_Radius", transform.size.y / 2.);
    renderer->Draw(this, getRenderable().shader);
}
