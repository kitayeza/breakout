#include "BrickGo.h"
#include "utils.h"

BrickGo::BrickGo(MyApp *app, Renderable r) : GameObject(app, r)
{
    mRadius = std::max(r.width, r.height);
}

float BrickGo::getDestroyEffRadius()
{
    mRadius = std::max(0.f, (mRadius - mRadiusShrink));
    return mRadius;
}

void BrickGo::OnUpdate()
{
    if (blinkingColor >= 0.9f || blinkingColor <= 0.6f)
        colorRate *= -1;

    blinkingColor += colorRate * (std::rand() % 10);
    blinkingColor = std::min(std::max(blinkingColor, 0.6f), 0.9f);

    if(isDead() && mRadius > 0)
    {
        mRadius = getDestroyEffRadius();
    }
}

void BrickGo::OnDraw()
{
    if(isDead()) {
        renderer->UseShader(getRenderable().shader);
        getRenderable().shader->setUniformVec2f("u_Center", GetCenter());
        getRenderable().shader->setUniform1f("u_Radius", mRadius);
        SetColor(color.r + 0.1f, color.g, color.b, color.a);
    } else {
        renderer->UseShader(getRenderable().shader);
        getRenderable().shader->setUniform1f("u_Radius", -1.f);
        SetColor(color.r, color.g, blinkingColor, color.a);
    }
    renderer->Draw(this, getRenderable().shader);
}

