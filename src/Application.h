#ifndef BREAKOUT_APPLICATION_H
#define BREAKOUT_APPLICATION_H

#endif //BREAKOUT_APPLICATION_H

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

class Application {

private:

    const static inline double fixedUpdateRate = 0. / 30.;
    const static inline double slowedFixedUpdateRate = 1.;
    static inline Application *instance;
    static inline GLFWwindow *mWindow;

    bool initialized = false;
    double updateRate = fixedUpdateRate;

    static void GlfwErrorCallback(int error, const char* desc);
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);


protected:

    Renderer renderer;
    int mWidth, mHeight;

public:

    Application(const char*, int, int);
    ~Application();
    static Application& getApp() { return *Application::instance; }

    Renderer& GetRenderer() { return renderer; }
    void GetWindowSize(int&, int&);
    [[nodiscard]] bool IsInitialized() const { return initialized; }
    static bool IsKeyPressed(int key);

    void Run();
    void CloseWindow();

    virtual void OnKeyCallback(int key, int action) = 0;
    virtual void OnUpdate() = 0;
    virtual void OnDraw() = 0;
};
