
#include <iostream>

#include "helper.hpp"
#include "scenegraph.hpp"
#include "transform.hpp"

namespace Render{

    SceneGraph::SceneGraph(): root(new Node(new Node(nullptr))){}   //new Node(new Node()) to give root an unused parent to make matrix propogation simpler

    SceneGraph::Node *const SceneGraph::add(Node * const child){
        return child->addParent(root);
    }
    
    void SceneGraph::remove(Node * const node){
        node->remove();
    }

    void SceneGraph::update(){
        root->update();
    }






    //NODE
    SceneGraph::Node *SceneGraph::Node::addParent(Node *_m_parent){
        m_parent = _m_parent;
        m_parent->m_children.push_back(this);
        return this;
    }

    SceneGraph::Node *SceneGraph::Node::addChild(Node *child){
        child->addParent(this);
        return this;
    }

    void SceneGraph::Node::remove(){
        if(m_parent->m_parent == nullptr){
            std::cout << "Error, cannot remove root node" << std::endl;
            return;
        }
        for(std::vector<Node*>::iterator curr = m_children.begin(); curr != m_children.end(); ++curr)
            (*curr)->m_parent = m_parent;

        //delete this from m_parent->m_children vector (maybe change to use set?...)
        
        delete this;
    }

    void SceneGraph::Node::update(){
        m_worldMatrix = m_parent->m_worldMatrix * m_transform();

        for(Node *child : m_children)   child->update();
    }

    SceneGraph::Node &SceneGraph::Node::rotate(const glm::vec3 &axis, float angle){
        m_transform.rotate(axis, angle);
        return *this;
    }

    SceneGraph::Node &SceneGraph::Node::scale(float scale){
        m_transform.scale(scale);
        return *this;
    }

    SceneGraph::Node &SceneGraph::Node::scale(const glm::vec3 &scale){
        m_transform.scale(scale);
        return *this;
    }

    SceneGraph::Node &SceneGraph::Node::translate(const glm::vec3 &translation){
        m_transform.translate(translation);
        return *this;
    }

    SceneGraph::Node &SceneGraph::Node::translateTo(const glm::vec3 &translation){
        m_transform.translateTo(translation);
        return *this;
    }

    glm::vec3 SceneGraph::Node::getPosition(){
        return glm::vec3(m_parent->m_worldMatrix * glm::vec4(m_transform.m_position, 1));
    }

    glm::vec4 SceneGraph::Node::getDirection(){
        return glm::normalize(m_parent->m_worldMatrix * m_transform.getDirection());
    }

    glm::mat4 SceneGraph::Node::getWorldMatrix(){
        return m_worldMatrix;
    }
}