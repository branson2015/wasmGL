#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.hpp"

namespace Render{

    class OpenGLWindow : public Window{
    public:
        OpenGLWindow(void*, int, int);
        ~OpenGLWindow() = default;

        virtual void makeContextCurrent() override;
        virtual bool shouldClose() override;
        virtual void swapBuffers() override;
        virtual void pollEvents() override;
        virtual void close() override;

        virtual void setFrameBufferSizeCallback(void(*)(void*, int, int)) override;
        virtual void setMouseCallback(void(*)(void*, double, double)) override;
        virtual void setMouseButtonCallback(void(*)(void*, int, int, int)) override;
        virtual void setScrollCallback(void(*)(void*, double, double)) override;
        virtual void setKeyboardCallback(void (*)(void*, int, int, int, int)) override;
        virtual int getKey(int) override;

        virtual void terminate() override;
    
    private:
        GLFWwindow * window;
        
        //temporary pointer holders for callback functions
        void (*FrameBufferSizeCallback)(void*, int, int);
        void (*MouseCallback)(void*, double, double);
        void (*MouseButtonCallback)(void*, int, int, int);
        void (*ScrollCallback)(void*, double, double);
        void (*KeyboardCallback)(void*, int, int, int, int);
    };
    
}

#endif