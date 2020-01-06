#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

#include "render.hpp"
#include "shader.hpp"
#include "platform/OpenGL/include/OpenGLShader.hpp"

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