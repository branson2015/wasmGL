#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include "shader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

//Model should represent an instantiation of a mesh/geometry - multiple models should be able to exist from one geometry, each is unique.

namespace Render{

    class ModelBase{
    protected:
        virtual ~ModelBase() = default;
        ModelBase(Shader *shader):m_shader(shader){}

        inline const Shader *getShader(){return m_shader;}

    protected:
        Shader * m_shader;
    };

    struct Vertex{
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    struct Texture{
        bool operator==(const Texture& rhs){ return id == rhs.id; }
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh{
        public: 

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void draw(Shader*) const;
        
        private:
        unsigned int VAO, VBO, EBO;
        void setupMesh();
    };

    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);


    class Model : public ModelBase{
    public:
       
        void draw() const;
        static const Model *create(const std::string &path, Shader *);
        
        const std::string path;
    private:
        Model(const std::string &path, Shader*);

        std::vector<Mesh> meshes;
        std::vector<Texture> textures_loaded; 

        std::string directory;
        

        void loadModel(const std::string &path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName);
    };

}

#endif