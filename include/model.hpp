#include <vector>

#include "shader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//Model should represent an instantiation of a mesh/geometry - multiple models should be able to exist from one geometry, each is unique.

namespace Render{

    class ModelBase{
    public:
        virtual ~ModelBase() = default;
        ModelBase(Shader *shader):m_shader(shader){}

        inline const Shader *getShader(){return m_shader;}

    protected:
        Shader * m_shader;
    };

    class Mesh{

    };
    
    class Model : public ModelBase{
    public:
        Model(Shader*);

    private:
        std::vector<Mesh> meshes;
    };

    

}