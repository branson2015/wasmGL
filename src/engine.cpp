#include "engine.hpp"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "logger.hpp"


#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

namespace Render{

    template <typename T>
    Engine<T>::Engine():resources(Resources::getInstance()){
        
        window = Window::create(this, 800, 600);
        
        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        timer.update();
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
        
        #ifndef EMSCRIPTEN
        while(!engine->window->shouldClose()){
        #endif
            engine->timer.update();
            engine->window->pollEvents();
            engine->renderFrame();            
            engine->window->swapBuffers();
            
        #ifndef EMSCRIPTEN
        }
        engine->cleanup();
        #endif
    }

    template <typename T>
    void Engine<T>::cleanup(){
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        window->terminate();
    }

}