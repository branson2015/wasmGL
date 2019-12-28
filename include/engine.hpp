#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "resources.hpp"
#include "scenegraph.hpp"

namespace Render{
    
    template<typename T>
    class Engine{
    public:
        Engine();
        ~Engine() = default;

        void start();

        void cleanup();
        static void loop(void*);

    //protected:

        SceneGraph scene;
        Resources * const m_resources;
        GLFWwindow * window;
    };
}
#endif