#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <vector>
#include <map>

#include "glm/matrix.hpp"

#include "model.hpp"
#include "transform.hpp"

namespace Render{
    

    //complete SOC of SceneGraph graph and models
    class SceneGraph{

        struct Node;
        struct RenderNode;
    
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




    struct SceneGraph::Node{
        Node(Node *_p): m_parent(_p), m_worldMatrix(), m_transform(){}

        Node *add(Node *);
        void remove();
        
        virtual Node *addChild(Node *);

        glm::vec3 getPosition();
        glm::vec4 getDirection();
        void update();


        Node *m_parent;
        std::vector<Node*> m_children;

        Transform m_transform;
        glm::mat4 m_worldMatrix;
    };

    struct SceneGraph::RenderNode : public SceneGraph::Node{
        RenderNode(ModelBase *_m, Node *_p): Node(_p), m_model(_m){}
        Node *addChild(Node *) final;
        ModelBase *m_model;
    };
}

#endif