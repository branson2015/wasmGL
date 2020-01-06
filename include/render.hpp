#ifndef RENDER_H
#define RENDER_H

#define NONE 0
#define OPENGL 1
#define API OPENGL

#include "engine.hpp"
#include "../src/engine.cpp"

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

#include "resources.hpp"
#include "camera.hpp"
#include "helper.hpp"
#include "scenegraph.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "logger.hpp"

#endif