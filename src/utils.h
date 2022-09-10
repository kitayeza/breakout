#ifndef BREAKOUT_UTILS_H
#define BREAKOUT_UTILS_H

#endif //BREAKOUT_UTILS_H

#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <memory>

#ifdef _MSC_VER
#define DEBUG_BREAK __debugbreak()
#else
#include <csignal>
#define DEBUG_BREAK raise(SIGTRAP)
#endif

static void clearGlErrors() { while(glGetError() != GL_NO_ERROR); }
static bool printGLErrors(const char *name);

#define ASSERT(x) if((x)==0) DEBUG_BREAK;

#define GL_CALL(x) clearGlErrors();\
 x;\
    ASSERT(printGLErrors(#x))


static bool printGLErrors(const char* funcName)
{
    while(glGetError() != GL_NO_ERROR)
    {
        const auto error = glGetError();
        std::cout << "[GL_Error] (0x0" << std::hex << error << ") " << "from " << funcName << '\n';
        return false;
    }

    return true;
}

static int sign(float f)
{
    if (f > 0.)
        return 1.f;
    else if (f < 0.)
        return -1.f;
    else return 0.f;
}

static std::unique_ptr<char[]> readFile(const char* fileName)
{
    std::cout << "Reading file " << fileName << '\n';

    std::ifstream file;

    file.open(fileName, std::ios::binary);

    if(!file.is_open())
    {
        std::cout << "Cannot open file " << fileName << '\n';
        exit(1);
    }

    file.seekg(0, std::ios::end);
    long length = file.tellg();
    file.seekg(0, std::ios::beg);

    std::unique_ptr<char[]> buffer{ new char[length + 1]};
    file.read(buffer.get(), length);
    buffer[length] = '\0';

    file.close();

    return buffer;

}



