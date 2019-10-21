#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <iostream>

namespace Render{

    class Shader{
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
    
        static Shader *create(const std::string &vertexsrc, const std::string &fragmentsrc);
        static Shader *createFromFile(const std::string &v, const std::string &f);

    private:
        static inline std::string FtoStr(const std::string &fn){
            std::ifstream f(fn);

            if(!f.is_open()){
                std::cout << "File " << fn << " could not be opened." << std::endl;
                return nullptr;
            }

            std::string str;

            f.seekg(0, std::ios::end);
            str.reserve(f.tellg());
            f.seekg(0, std::ios::beg);

            str.assign((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

            return str;
        }
    };
}

#endif