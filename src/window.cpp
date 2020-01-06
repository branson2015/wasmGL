#include "render.hpp"
#include "window.hpp"
#include "platform/OpenGL/include/OpenGLWindow.hpp"

namespace Render{

    Window* Window::create(void *engine, int width, int height){
        switch(API){
            case NONE:  break;
            case OPENGL: return new OpenGLWindow(engine, width, height);
        }
    }

}