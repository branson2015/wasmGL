#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/matrix.hpp>

#include "shader.hpp"

namespace Render{
    
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string vertexsrc, const std::string fragmentsrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void UnBind() const override;
        
        virtual void setInt(const std::string &str, const int val) const override;
        virtual void setMat4(const std::string &str, const glm::mat4&) const override;

        void UploadUiniformFloat4(/*TODO: GLM*/);
        void UploadUniformMat4(/*TODO: GLM*/);
    };
}

#endif