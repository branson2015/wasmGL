#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include "shader.hpp"
#include <string>

namespace Render{
    
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string &vertexsrc, const std::string &fragmentsrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        void UploadUiniformFloat4(/*TODO: GLM*/);
        void UploadUniformMat4(/*TODO: GLM*/);
    private:
        uint32_t m_shaderID;
    };
}

#endif