#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <vector>
#include <map>

#include "glm/matrix.hpp"
#include "transform.hpp"


//TODO: change pointers out for smart pointers
//change Node::m_children vector out for set

namespace Render{
    

    //complete SOC of SceneGraph graph and models
    class SceneGraph{
    public:
        struct Node;
    
        SceneGraph();
        ~SceneGraph() = default;

        Node *const add(Node * const);
        void remove(Node * const);
        void update();

    private:
        Node * const root;
    };




    struct SceneGraph::Node{
    public:
        Node &rotate(const glm::vec3 &axis, float angle);
        Node &scale(float scale);
        Node &scale(const glm::vec3 &scale);
        Node &translate(const glm::vec3 &translation);
        Node &translateTo(const glm::vec3 &translation);

        glm::vec3 getPosition();
        glm::vec4 getDirection();
        glm::mat4 getWorldMatrix();

        void update();
    protected:
        Node(Node * const _p): m_parent(_p), m_worldMatrix(1.0f), m_transform(){ if(m_parent)  m_parent->addChild(this); }

        Node *addParent(Node *);
        virtual Node *addChild(Node *);
        
        void remove();
        
        Node *m_parent;
        std::vector<Node*> m_children;

        Transform m_transform;
        glm::mat4 m_worldMatrix;

        friend class SceneGraph;
    };
}

#endif