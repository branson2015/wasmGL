#include "engine.hpp"

#include <cstring>
#include <iostream>
#include <string>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
#include "misc/cpp/imgui_stdlib.h"


#include "camera.hpp"
#include "helper.hpp"
#include "scenegraph.hpp"
#include "shader.hpp"
#include "../src/engine.cpp"    //kinda bad hack to seperate Engine.hpp and Engine.cpp because templates are used

/*TODO:
- seperate loading of meshes and loading of materials into something more generic - make mesh and material classes/files?
- replace all pointers with smart pointers
- finish shader class interface
- wrap std::cout in asserts so we can build debug and release versions that do/don't have a debugging console
*/

class MyEngine : public Render::Engine<MyEngine>{
    public:
    MyEngine();
    ~MyEngine() = default;

    void renderFrame();
    
    // settings
    unsigned int SCR_WIDTH = 800;
    unsigned int SCR_HEIGHT = 600;

    // camera
    Render::Camera camera;
    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;
    bool firstMouse = true;

    bool mousePressed = false;

    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;


    //needed between init and renderFrame but haven't implimented enough of Resources to make this happen all in init yet
    Render::Shader *shader;
    Render::SceneGraph::Object *model1;
    float f = 0.0f;

    // Our IMGUI state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void processInput(GLFWwindow *window);
};

MyEngine::MyEngine(): camera(glm::vec3(0.0f, 0.0f, 3.0f)){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    auto scrollCallback = [](GLFWwindow* w, double xoffset, double yoffset){
        static_cast<MyEngine*>(glfwGetWindowUserPointer(w))->scroll_callback(w, xoffset, yoffset);
    };glfwSetScrollCallback(window, scrollCallback);

    auto mouseButtonCallback = [](GLFWwindow* w, int button, int action, int mods){
        static_cast<MyEngine*>(glfwGetWindowUserPointer(w))->mouse_button_callback(w, button, action, mods);
    };glfwSetMouseButtonCallback(window, mouseButtonCallback);

    IMGUI_CHECKVERSION();
    ImGuiContext* context = ImGui::CreateContext();
    ImGui::SetCurrentContext(context);
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 300 es");
    
    
    
    shader = Render::Shader::createFromFile("resources/shaders/1.model_loading.vs", "resources/shaders/1.model_loading.fs");
    shader->Bind();

    const Render::Model *model = Render::Model::create("resources/objects/nanosuit/nanosuit.obj", shader);

    model1 = scene.add(model);
    model1->scale(0.2f);
    scene.update();
}

void MyEngine::renderFrame(){
    
    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // per-frame time logic
    // --------------------
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input
    // -----
    processInput(window);        
    
    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();

    //wasmgl error occours here
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    
    shader->setMat4("model", model1->getWorldMatrix());
    
    model1->draw();
    
    

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //ImGui::ShowDemoWindow();

    ImGui::Begin("Controls");                          // Create a window called "Controls" and append into it.
    ImGui::SliderFloat("float", &f, 0.0f, 100.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    /*struct Func{
        Func(const char *label, std::string *s, const ImVec2 &vec, ImGuiInputTextFlags flags = 0){
            ImGui::InputTextMultiline(label, s, vec, flags | ImGuiInputTextFlags_CallbackResize, MyResizeCallback, (void*)s);
        }

        static int MyResizeCallback(ImGuiInputTextCallbackData* data){
            if (data->EventFlag == ImGuiInputTextFlags_CallbackResize){
                std::string *str = (std::string*)data->UserData;
                if(data->BufTextLen > data->BufSize - 1)
                    str->resize((data->BufSize + 1)*2);
                data->Buf = const_cast<char*>(str->c_str());
            }
            return 0;
        }
    };

    
    ImGui::Separator();
    //ImGui::InputTextMultiline("Fragment Source", &fragmentSource, ImVec2(500, 300), ImGuiInputTextFlags_CallbackResize, Func::MyResizeCallback, (void*)&fragmentSource);
    //ImGui::Text("Data: %p\nSize: %d\nCapacity: %d", (void*)&my_str, my_str.size(), my_str.capacity());
    */
   
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    scene.update();

    //poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------

    glfwSwapBuffers(window);
    glfwPollEvents();
}    

int main(){
    MyEngine engine;
    engine.start();
    
    system("pause");
    return 0;
}











void MyEngine::processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Render::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Render::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Render::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Render::RIGHT, deltaTime);
}

void MyEngine::framebuffer_size_callback(GLFWwindow* window, int width, int height){
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, width, height);
}

void MyEngine::mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    if(mousePressed)
        camera.ProcessMouseMovement(xoffset, yoffset);
}

void MyEngine::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)    mousePressed = true;
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)  mousePressed = false;
}

void MyEngine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.ProcessMouseScroll(yoffset);
}