#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "OpenGLWindow.hpp"
#include "logger.hpp"

namespace Render{

    OpenGLWindow::OpenGLWindow(void *_engine, int width, int height){
        engine = _engine;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(width, height, "Render", NULL, NULL);
        if(window == NULL){
            LOG("Failed to create GLFW window");
            glfwTerminate();
        }

        makeContextCurrent();

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            LOG("Failed to initialize GLAD");
        }

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        setWidth(width);
        setHeight(height);
        glViewport(0, 0, width, height);

        //make defines for debug here (assuming release will not use imgui)
        IMGUI_CHECKVERSION();
        ImGuiContext* context = ImGui::CreateContext();
        ImGui::SetCurrentContext(context);
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 300 es");
    }   

    void OpenGLWindow::makeContextCurrent(){ glfwMakeContextCurrent(window); glfwSetWindowUserPointer(window, this); }
    bool OpenGLWindow::shouldClose(){ return glfwWindowShouldClose(window); }
    void OpenGLWindow::swapBuffers(){ glfwSwapBuffers(window); }
    void OpenGLWindow::pollEvents(){ glfwPollEvents(); }
    void OpenGLWindow::close(){ glfwSetWindowShouldClose(window, true); }

    void OpenGLWindow::setFrameBufferSizeCallback(void(*fn)(void*, int, int)){            
        FrameBufferSizeCallback = fn;
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int width, int height)->void{ 
            OpenGLWindow *oglw = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(w));
            oglw->setWidth(width);
            oglw->setHeight(height);
            glViewport(0, 0, width, height);
            (*oglw->FrameBufferSizeCallback)(oglw->engine, width, height); 
        });
    }
    void OpenGLWindow::setMouseCallback(void(*fn)(void*, double, double)){
        MouseCallback = fn;
        glfwSetCursorPosCallback(window, [](GLFWwindow* w, double xpos, double ypos)->void{ 
            OpenGLWindow *oglw = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(w));
            (*oglw->MouseCallback)(oglw->engine, xpos, ypos); 
        });
    }
    void OpenGLWindow::setMouseButtonCallback(void(*fn)(void*, int, int, int)){
        MouseButtonCallback = fn;
        glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods)->void{ 
            OpenGLWindow *oglw = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(w));
            (*oglw->MouseButtonCallback)(oglw->engine, button, action, mods); 
        });
    }
    void OpenGLWindow::setScrollCallback(void(*fn)(void*, double, double)){
        ScrollCallback = fn;
        glfwSetScrollCallback(window, [](GLFWwindow* w, double xoffset, double yoffset)->void{ 
            OpenGLWindow *oglw = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(w));
            (*oglw->ScrollCallback)(oglw->engine, xoffset, yoffset); 
        });
    }
    void OpenGLWindow::setKeyboardCallback(void (*fn)(void*, int key, int scancode, int action, int mods)){ 
        KeyboardCallback = fn;
        glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods)->void{ 
            OpenGLWindow *oglw = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(w));
            (*oglw->KeyboardCallback)(oglw->engine, key, scancode, action, mods); 
        });
    }

    int OpenGLWindow::getKey(int key){
        return glfwGetKey(window, key);
    }


    void OpenGLWindow::terminate(){
        glfwTerminate();
    }
}