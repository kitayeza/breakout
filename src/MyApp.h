#ifndef BREAKOUT_APP_H
#define BREAKOUT_APP_H


#include "Application.h"
#include "GameObject.h"
#include <vector>
#include <memory>

class PlatformGo;
class BallGo;
class BrickGo;

enum class State {
    START,
    GAME
};

class MyApp : public Application {

private:

    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::shared_ptr<PlatformGo> mPlatform;
    std::shared_ptr<BallGo> mBall;
    Shader simpleShader = Shader("../assets/simple.vert", "../assets/simple.frag");
    Shader roundShader = Shader("../assets/simple.vert", "../assets/simple.frag");

    const int padding_x = 65;
    const int padding_y = 50;
    const int spacing = 5;

    State mState = State::START;

    [[nodiscard]] bool isInside(glm::vec3 point, Transform target) const;
    void OnKeyCallback(int key, int action) override;

public:

    MyApp(const char *title, int width, int height);

    void Start();
    void OnUpdate() override;
    void OnDraw() override;
    [[nodiscard]] glm::vec3 bounceVector(glm::vec3 ballPos, float radius) const;


    [[nodiscard]] State getState() const { return mState; }
    [[nodiscard]] const std::shared_ptr<PlatformGo> getPlatform() const{ return mPlatform; }
};


#endif //BREAKOUT_APP_H