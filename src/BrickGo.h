#ifndef BREAKOUT_BRICKGO_H
#define BREAKOUT_BRICKGO_H

#include "GameObject.h"
#include "MyApp.h"
#include <iostream>

class MyApp;

class BrickGo: public GameObject {

private:

    float mRadius;
    float mRadiusShrink = 3.5f;

    float colorRate = 0.005f;
    float blinkingColor = 0.8f;

public:

    BrickGo(MyApp *app, Renderable r);

    float getDestroyEffRadius();
    void OnUpdate() override;
    void OnDraw() override;
};


#endif //BREAKOUT_BRICKGO_H
