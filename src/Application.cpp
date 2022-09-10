#include "Application.h"

#include <cstdio>
#include <iostream>

void Application::GlfwErrorCallback(int error, const char *desc)
{
    std::cout << "[GLFW] error #" << error << " " << desc << '\n';
}

void Application::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Application::getApp().OnKeyCallback(key, action);
}

Application::Application(const char* title, int width, int height)
{
    if(Application::instance == nullptr)
        Application::instance = this;

    else
    {
        std::cout << "App is already initialized.\n";
        return;
    }

    glfwSetErrorCallback(Application::GlfwErrorCallback);
    if (!glfwInit()) {
        std::cout << "glfw initialization failed.\n";
        return;
    }

    mWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if(mWindow == nullptr)
    {
        std::cout << "glfw window initialization failed.\n";
        return;
    }

    glfwMakeContextCurrent(mWindow);
    if (glewInit() != 0)
    {
        std::cout << "glew initialization failed.\n";
        return;
    }

    glfwSetKeyCallback(mWindow, KeyCallback);
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';

    glfwGetFramebufferSize(mWindow, &mWidth, &mHeight);
    glViewport(0, 0, mWidth, mHeight);
    glfwSwapInterval(1);

    initialized = true;
    renderer = Renderer((float)mWidth, (float)mHeight);
}

Application::~Application()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void Application::GetWindowSize(int &width, int &height)
{
    width = mWidth;
    height = mHeight;
}

bool Application::IsKeyPressed(int key)
{
    return glfwGetKey(Application::mWindow, key) == GLFW_PRESS;
}

void Application::Run()
{
    auto lastTime = glfwGetTime();
    double curTime;
    double deltaTime = 0.;

    while(!glfwWindowShouldClose(mWindow))
    {
        renderer.Clear();

        curTime = glfwGetTime();
        deltaTime += (curTime - lastTime);
        lastTime = curTime;

        updateRate = IsKeyPressed(GLFW_KEY_LEFT_SHIFT) ? slowedFixedUpdateRate : fixedUpdateRate;

        if(deltaTime >= updateRate)
        {
            OnUpdate();
            deltaTime -= updateRate;
        }

        OnDraw();

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

}

void Application::CloseWindow()
{
    glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
}

