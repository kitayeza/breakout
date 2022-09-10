#ifndef BREAKOUT_PLATFORMGO_H
#define BREAKOUT_PLATFORMGO_H

#include "GameObject.h"
#include "MyApp.h"

class PlatformGo : public GameObject {

private:

    int windowWidth;
    int windowHeight;

    const float topSpeed = 17.f;
    const float friction = 3.4f;
    const float topAccelerationSpeed = 3.5f;
    const float accelerationSpeed = 0.7f;
    float curAccelerationSpeed = .0f;

    void OnUpdate() override;
    void OnDraw() override;

public:

    PlatformGo(MyApp *app, Renderable r);
};


#endif //BREAKOUT_PLATFORMGO_H
