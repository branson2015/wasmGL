#include "shader.hpp"
#include "platform/OpenGL/include/OpenGLShader.hpp"

#include <fstream>
#include <string>
#include <streambuf>
#include <iostream>

#define NONE 0
#define OPENGL 1
#define API OPENGL

namespace Render{

    Shader *Shader::create(const std::string &vertexsrc, const std::string &fragmentsrc){
        switch (API){
            case NONE: break;
            case OPENGL: return new OpenGLShader(vertexsrc, fragmentsrc);
        }

        //assert
        std::cerr << "Unknown Shader Type!" << std::endl;
        return nullptr;
    }

    Shader *Shader::createFromFile(const std::string &v, const std::string &f){
        return create(FtoStr(v), FtoStr(f));
    }
}