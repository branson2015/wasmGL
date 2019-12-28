#include "engine.hpp"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"


#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

namespace Render{

    template <typename T>
    Engine<T>::Engine():m_resources(Resources::getInstance()){
        
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(800, 600, "Render", NULL, NULL);
        if(window == NULL){
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }

        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, this);

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            std::cout << "Failed to initialize GLAD" << std::endl;
        }

    }

    template <typename T>
    void Engine<T>::start(){
        #ifdef EMSCRIPTEN
        emscripten_set_main_loop_arg(&Engine<T>::loop, this, 0, 1);
        #else
        loop(this);
        #endif
    }

    template <typename T>
    void Engine<T>::loop(void *_engine){
        T* engine = static_cast<T*>(_engine);
        
        #ifdef EMSCRIPTEN
        engine->renderFrame();
        #else

        
        while(!glfwWindowShouldClose(engine->window)){
            engine->renderFrame();
        }
        engine->cleanup();

        #endif
    }

    template <typename T>
    void Engine<T>::cleanup(){
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
    }

}