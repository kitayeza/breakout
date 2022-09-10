#include "MyApp.h"
#include "utils.h"
#include "PlatformGo.h"
#include "BallGo.h"
#include "BrickGo.h"

bool MyApp::isInside(glm::vec3 point, Transform target) const
{
    return (point.x >= target.pos.x && point.x <= target.pos.x + target.size.x) &&
           (point.y >= target.pos.y && point.y <= target.pos.y + target.size.y);
}

void MyApp::OnKeyCallback(int key, int action)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        CloseWindow();

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {

        if (mState == State::START)
        {
            mBall->transform.velocity.x =
                    std::min(10.f, fabsf(mPlatform->transform.velocity.x)) * sign(mPlatform->transform.velocity.x);
            mBall->transform.velocity.y = 6.f;
            mState = State::GAME;
        }
        else Start();
    }
}

MyApp::MyApp(const char *title, int width, int height) : Application(title, width, height)
{
    renderer.SetClearColor(0.1f, 0.1f, 0.1f, 1.f);

    Start();
}

void MyApp::Start()
{
    const int lines = 5;
    const int perLine = 7;
    const float brick_w = ((mWidth - padding_x * 2) - (spacing * perLine)) / perLine;
    const float brick_h = 40.f;
    const int m_BricksNumber = perLine * lines;
    const auto renderable = renderer.CreateRect(brick_w, brick_h, roundShader);

    gameObjects.clear();
    gameObjects.reserve(m_BricksNumber + 2);

    std::shared_ptr<BrickGo> brick;

    for (int k = 0; k < lines; ++k)
    {
        for (int i = 0; i < perLine; ++i)
        {
            brick = std::make_shared<BrickGo>(this, renderable);

            (*brick.get()).SetColor(0.3f, 0.3f, 0.7f, 1.f)
                    .SetPosition(
                            padding_x + (brick_w + spacing) * (i),
                            ((float)mHeight - padding_y) - ((brick_h + spacing) * (k))
                    );
            gameObjects.push_back(std::move(brick));
        }
    }

    srand((unsigned int)glfwGetTime());
    for (int k = 0; k < lines; ++k)
    {
        for (int i = 0; i < perLine / 2; ++i)
        {
            if (std::rand() % 4 == 0)
            {
                if (auto obj = dynamic_cast<BrickGo*>(gameObjects.at((k * perLine) + i).get()))
                    obj->Destroy();

                if (auto obj = dynamic_cast<BrickGo*>(gameObjects.at((k * perLine) + (perLine - i - 1)).get()))
                    obj->Destroy();
            }
        }
    }

    mPlatform = std::make_shared<PlatformGo>(this, renderer.CreateRect(200, 30, simpleShader));
    (*mPlatform.get()).SetColor(0.22f, 0.45f, 0.22f, 1.f)
            .SetPosition(mWidth / 2.f - 120.f / 2.f + 16.f, 20.f + 30.f);
    gameObjects.push_back(mPlatform);

    mBall = std::make_shared<BallGo>(this, renderer.CreateRect(40, 40, roundShader));
    (*mBall.get()).SetColor(0.9f, 0.35f, 0.35f, 1.f)
            .SetPosition(mPlatform->transform.pos.x + 120.f / 2.f - 25.f / 2.f, mPlatform->transform.pos.y + 30.f);
    gameObjects.push_back(mBall);

    mState = State::START;
}


glm::vec3 MyApp::bounceVector(const glm::vec3 ballPos, const float radius) const
{
    glm::vec3 bVec(1.f, 1.f, 1.f); // bounce vector

    if ((ballPos.x + radius) > mWidth || (ballPos.x - radius) < 0)
        bVec.x = -1;

    if ((ballPos.y + radius) > mHeight)
        bVec.y = -1;

    const auto r_diag = radius * 0.75; // distance to pi/4
    const auto ballT = glm::vec3(ballPos.x, ballPos.y + radius, 0.f);
    const auto ballB = glm::vec3(ballPos.x, ballPos.y - radius, 0.f);
    const auto ballL = glm::vec3(ballPos.x + radius, ballPos.y, 0.f);
    const auto ballR = glm::vec3(ballPos.x - radius, ballPos.y, 0.f);
    const auto ballLT = glm::vec3(ballPos.x + r_diag, ballPos.y + r_diag, 0.f);
    const auto ballRT = glm::vec3(ballPos.x - r_diag, ballPos.y + r_diag, 0.f);
    const auto ballLB = glm::vec3(ballPos.x + r_diag, ballPos.y - r_diag, 0.f);
    const auto ballRB = glm::vec3(ballPos.x - r_diag, ballPos.y - r_diag, 0.f);

    for ( auto &object : gameObjects)
    {
        if (dynamic_cast<BrickGo*>(object.get()) == nullptr || object->isDead())
            continue;
        if (isInside(ballT, object->transform) || isInside(ballB, object->transform) ||
            isInside(ballL, object->transform) || isInside(ballR, object->transform) )
        {
            if ( abs(ballPos.x - object->GetCenter().x) / object->transform.size.x >
                 abs(ballPos.y - object->GetCenter().y) / object->transform.size.y)
                bVec.x = -1;
            else
                bVec.y = -1;

            object->Destroy();
            // return bVec;
        }
        else if (isInside(ballLT, object->transform) || isInside(ballRT, object->transform) ||
                 isInside(ballLB, object->transform) || isInside(ballRB, object->transform))
        {
            bVec.x = -1;
            bVec.y = -1;
            object->Destroy();
        }
    }

    if (isInside(ballT, mPlatform->transform) || isInside(ballB, mPlatform->transform) ||
        isInside(ballL, mPlatform->transform) || isInside(ballR, mPlatform->transform) )
    {
        if ( abs(ballPos.x - mPlatform->GetCenter().x) / mPlatform->transform.size.x >
             abs(ballPos.y - mPlatform->GetCenter().y) / mPlatform->transform.size.y)
            bVec.x = -1;
        else
            bVec.y = -1;
        mBall->transform.velocity.x = std::min(10.f, fabsf(mPlatform->transform.velocity.x)) * sign(mPlatform->transform.velocity.x);
    }

    return bVec;
}

void MyApp::OnUpdate()
{
    for (const auto& obj : gameObjects)
    {
        obj->OnUpdate();
    }
}

void MyApp::OnDraw()
{
    for (auto &object : gameObjects)
    {
        object->OnDraw();
    }
}



