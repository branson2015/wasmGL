#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include <string>

namespace Render{
    
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string &vertexsrc, const std::string &fragmentsrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void UnBind() const override;
        
        virtual void setInt(std::string &str, int val) const override;

        void UploadUiniformFloat4(/*TODO: GLM*/);
        void UploadUniformMat4(/*TODO: GLM*/);
    };
}

#endif