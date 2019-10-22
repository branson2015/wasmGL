#include <cinttypes> //uint32_t
#include <set>
#include <unordered_map>

#include "model.hpp"
#include "glm/matrix.hpp"

namespace Render{
    
    class Node{
    public:
        Node(Node *_p): parent(_p){}
        virtual Node *addChild(Node *);

        glm::mat4 transform;
    private:
        Node *parent;
    };

    class RenderNode : public Node{
    public:
        RenderNode(ModelBase *_m, Node *_p): Node(_p), model(_m){}
        Node *addChild(Node *) final;
    private:
        ModelBase *model;
    };
    

    class Scene{
    public:
        Scene();
        ~Scene() = default;

        Node* add(ModelBase*, Node*);
        void remove(ModelBase*);

        void render() const;

    private:
        uint32_t m_numElements;
        //Camera camera;
        std::unordered_multimap<Shader *, Node*> m_shaderGroups;
        Node *root;
    };

}