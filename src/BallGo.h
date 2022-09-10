#ifndef BREAKOUT_BALLGO_H
#define BREAKOUT_BALLGO_H


#include "GameObject.h"
#include "MyApp.h"

class BallGo : public GameObject {

public:

    BallGo(MyApp *app, Renderable r) : GameObject(app, r) {};

    void OnUpdate() override;
    void OnDraw() override;
};


#endif //BREAKOUT_BALLGO_H
