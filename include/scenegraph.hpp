#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <vector>

#include <glm/matrix.hpp>

#include "model.hpp"
#include "transform.hpp"

//TODO: change pointers out for smart pointers
//change Node::m_children vector out for set

namespace Render{

    class Node{
    public:

        Node *addChild(const std::string &);

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
        Node(Node * const _p): m_parent(_p), m_worldMatrix(1.0f), m_transform(){ if(m_parent)  addParent(m_parent); }

        virtual void draw(){for(int i = 0; i < m_children.size(); ++i)  m_children[i]->draw(); }

        Node *addParent(Node *);
        virtual Node *addChild(Node *);
        
        void remove();
        
        Node *m_parent;
        std::vector<Node*> m_children;

        Transform m_transform;
        glm::mat4 m_worldMatrix;

        friend class SceneGraph;
    };

    class Object : public Node{
    public:
        Object(const Model *const _m, Node * const _p = nullptr): Node(_p), m_model(_m){}

        virtual void draw() override { m_model->m_shader->setMat4("model", getWorldMatrix()); m_model->draw(); }
    private:
        const Model *const m_model;
    };


    //complete SOC of SceneGraph graph and models
    class SceneGraph{
    public:
    
        SceneGraph();
        ~SceneGraph() = default;

        inline void draw(){ root->draw(); }

        //should be Node*, not Object*
        Object *const add(const Model *const);
        Object *const add(const std::string&, const Model *const);
        void remove(Node * const);
        void update();

    private:
        Node * const root;
    };
}

#endif