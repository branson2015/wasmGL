#include <iostream>

#include "helper.hpp"
#include "scenegraph.hpp"
#include "transform.hpp"
#include "resources.hpp"

namespace Render{

    SceneGraph::SceneGraph(): root(new Node(new Node(nullptr))){}   //new Node(new Node()) to give root an unused parent to make matrix propogation simpler

    Object *const SceneGraph::add(const Model *const model){
        return new Object(model, root);
    }

    Object *const SceneGraph::add(const std::string &id, const Model * const model){
        return Resources::getInstance()->add<Object>(id, new Object(model, root));
    }
    
    void SceneGraph::remove(Node * const node){
        node->remove();
    }

    void SceneGraph::update(){
        root->update();
    }






    //NODE
    Node *Node::addChild(const std::string &id){
        return Resources::getInstance()->add<Node>(id, new Node(this));
    }

    Node *Node::addParent(Node *_m_parent){
        m_parent = _m_parent;
        m_parent->m_children.push_back(this);
        return this;
    }

    Node *Node::addChild(Node *child){
        child->addParent(this);
        return this;
    }

    void Node::remove(){
        if(m_parent->m_parent == nullptr){
            std::cout << "Error, cannot remove root node" << std::endl;
            return;
        }
        for(std::vector<Node*>::iterator curr = m_children.begin(); curr != m_children.end(); ++curr)
            (*curr)->m_parent = m_parent;

        //delete this from m_parent->m_children vector (maybe change to use set?...)
        
        delete this;
    }

    void Node::update(){
        m_worldMatrix = m_parent->m_worldMatrix * m_transform();

        for(Node *child : m_children)   child->update();
    }

    Node &Node::rotate(const glm::vec3 &axis, float angle){
        m_transform.rotate(axis, angle);
        return *this;
    }

    Node &Node::scale(float scale){
        m_transform.scale(scale);
        return *this;
    }

    Node &Node::scale(const glm::vec3 &scale){
        m_transform.scale(scale);
        return *this;
    }

    Node &Node::translate(const glm::vec3 &translation){
        m_transform.translate(translation);
        return *this;
    }

    Node &Node::translateTo(const glm::vec3 &translation){
        m_transform.translateTo(translation);
        return *this;
    }

    glm::vec3 Node::getPosition(){
        return glm::vec3(m_parent->m_worldMatrix * glm::vec4(m_transform.m_position, 1));
    }

    glm::vec4 Node::getDirection(){
        return glm::normalize(m_parent->m_worldMatrix * m_transform.getDirection());
    }

    glm::mat4 Node::getWorldMatrix(){
        return m_worldMatrix;
    }
}