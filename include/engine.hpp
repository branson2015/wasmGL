#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "resources.hpp"
#include "scenegraph.hpp"
#include "shader.hpp"
#include "window.hpp"

namespace Render{
    
    template<typename T>
    class Engine{
    public:
        Engine();
        ~Engine() = default;

        void start();
    protected:
        void cleanup();
        static void loop(void*);

        SceneGraph scene;
        Resources * const resources;
        Shader *shader;
        Window *window;
    };
}
#endif