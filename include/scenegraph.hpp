#include <vector>
#include <map>

#include "glm/matrix.hpp"

#include "model.hpp"


namespace Render{
    

    //complete SOC of SceneGraph graph and models
    class SceneGraph{

        struct Node{
            Node(Node *_p): m_parent(_p){}

            Node *add(Node *);
            void remove();
            
            virtual Node *addChild(Node *);

            Node *m_parent;
            std::vector<Node*> m_children;
            glm::mat4 m_transform;
        };

        struct RenderNode : public Node{
            RenderNode(ModelBase *_m, Node *_p): Node(_p), m_model(_m){}
            Node *addChild(Node *) final;
            ModelBase *m_model;
        };
    
    public:
        SceneGraph();
        ~SceneGraph() = default;

        void add(ModelBase *, ModelBase*);
        void remove(ModelBase*);

        Node *root;
    
    private:
        Node *getNode(ModelBase *);
        std::map<ModelBase *, Node *> m_nodes;
    };
}