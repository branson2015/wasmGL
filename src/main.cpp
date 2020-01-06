#define DEBUG

#include "render.hpp"

/*TODO:
- seperate loading of meshes and loading of materials into something more generic - make mesh and material classes/files?
- finish shader class interface
*/

class MyEngine : public Render::Engine<MyEngine>{
    public:
    MyEngine();
    ~MyEngine() = default;

    void renderFrame();

    // camera
    Render::Camera camera;
    float lastX = window->getWidth() / 2.0f;
    float lastY = window->getHeight() / 2.0f;
    bool mousePressed = false;

    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Our IMGUI state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    static void framebuffer_size_callback(void* engine, int width, int height);
    static void mouse_callback(void* engine, double xpos, double ypos);
    static void mouse_button_callback(void* engine, int button, int action, int mods);
    static void scroll_callback(void* engine, double xoffset, double yoffset);
    void process_input();
};

MyEngine::MyEngine(): camera(glm::vec3(0.0f, 0.0f, 3.0f)){

    window->setFrameBufferSizeCallback(framebuffer_size_callback);
    window->setMouseCallback(mouse_callback);
    window->setMouseButtonCallback(mouse_button_callback);
    window->setScrollCallback(scroll_callback);
    
    
    shader = Render::Shader::createFromFile("resources/shaders/1.model_loading.vs", "resources/shaders/1.model_loading.fs");
    shader->Bind();

    const Render::Model *model = Render::Model::create("model1", "resources/objects/nanosuit/nanosuit.obj", shader);

    Render::Object *model1 = scene.add("model1", model);
    model1->scale(0.2f);
    model1->translate(glm::vec3(1,-2, 0));

    Render::Object *model2 = scene.add("model2", model);
    model2->scale(0.2f);
    model2->translate(glm::vec3(-1,-2, 0));

    scene.update();
}

void MyEngine::renderFrame(){

    process_input();
    
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->setMat4("projection", glm::perspective(glm::radians(camera.Zoom), (float)window->getWidth() / (float)window->getHeight(), 0.1f, 100.0f));
    shader->setMat4("view", camera.GetViewMatrix());
    
    scene.update();
    scene.draw();

    //TODO: contain imgui in it's own abstract class
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Controls");                          // Create a window called "Controls" and append into it.
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

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


}    

int main(){

    MyEngine engine;
    engine.start();
    
    system("pause");
    return 0;
}











void MyEngine::process_input(){
    if (window->getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)  window->close();
    if (window->getKey(GLFW_KEY_W) == GLFW_PRESS)       camera.ProcessKeyboard(Render::FORWARD, deltaTime);
    if (window->getKey(GLFW_KEY_S) == GLFW_PRESS)       camera.ProcessKeyboard(Render::BACKWARD, deltaTime);
    if (window->getKey(GLFW_KEY_A) == GLFW_PRESS)       camera.ProcessKeyboard(Render::LEFT, deltaTime);
    if (window->getKey(GLFW_KEY_D) == GLFW_PRESS)       camera.ProcessKeyboard(Render::RIGHT, deltaTime);
}

void MyEngine::framebuffer_size_callback(void* engine, int width, int height){}

void MyEngine::mouse_callback(void* engine, double xpos, double ypos){
    MyEngine *myEngine = static_cast<MyEngine*>(engine);

    float xoffset = xpos - myEngine->lastX;
    float yoffset = myEngine->lastY - ypos; // reversed since y-coordinates go from bottom to top

    myEngine->lastX = xpos;
    myEngine->lastY = ypos;

    if(myEngine->mousePressed)    myEngine->camera.ProcessMouseMovement(xoffset, yoffset);
}

void MyEngine::mouse_button_callback(void* engine, int button, int action, int mods){ 
     MyEngine *myEngine = static_cast<MyEngine*>(engine);

    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)    myEngine->mousePressed = true;
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)  myEngine->mousePressed = false;
}

void MyEngine::scroll_callback(void *engine, double xoffset, double yoffset){
     MyEngine *myEngine = static_cast<MyEngine*>(engine);

    myEngine->camera.ProcessMouseScroll(yoffset);
}