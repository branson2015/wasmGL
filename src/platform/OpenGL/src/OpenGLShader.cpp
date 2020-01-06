#include <iostream>

#include <glad/glad.h>

#include "OpenGLShader.hpp"
#include "logger.hpp"

namespace Render{

    OpenGLShader::OpenGLShader(const std::string vertexsrc, const std::string fragmentsrc) : Shader(vertexsrc, fragmentsrc){
        
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const GLchar *source = (const GLchar *)vertexsrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE){
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            GLchar *infoLog = new GLchar[maxLength];
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog);

            glDeleteShader(vertexShader);

            LOG(infoLog);

            delete[] infoLog;

            return;
        }
        
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = (const GLchar *)fragmentsrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE){
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            GLchar *infoLog = new GLchar[maxLength];
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog);

            glDeleteShader(fragmentShader);

            //TODO: better error logging
            LOG(infoLog);

            delete[] infoLog;

            return;
        }

        GLuint program = glCreateProgram();
        m_shaderID = program;

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if(isLinked == GL_FALSE){
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            GLchar *infoLog = new GLchar[maxLength];
            glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);

            glDeleteProgram(program);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            LOG(infoLog);

            delete[] infoLog;

            return;
        }

        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
    }

    OpenGLShader::~OpenGLShader(){
        glDeleteProgram(m_shaderID);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_shaderID);
    }

    void OpenGLShader::UnBind() const {
        glUseProgram(0);
    }

    void OpenGLShader::setInt(const std::string &str, int val) const {
        glUniform1i(glGetUniformLocation(m_shaderID, str.c_str()), val); 
    }

    void OpenGLShader::setMat4(const std::string &str, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(m_shaderID, str.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

}