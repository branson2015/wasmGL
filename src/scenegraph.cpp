#include <iostream>

#include "scenegraph.hpp"
#include "transform.hpp"

namespace Render{

    SceneGraph::SceneGraph(): root(new Node(new Node(nullptr))){}   //new Node(new Node()) to give root an unused parent to make matrix propogation simpler

    void SceneGraph::add(ModelBase *model, ModelBase *parent = nullptr){
        
        Node *n_parent = (parent == nullptr ? root : getNode(model));
        if(n_parent == nullptr) return;

        Node *child = new RenderNode(model, n_parent);

        n_parent->addChild(child);
    }
    
    void SceneGraph::remove(ModelBase *model){
        Node *n = getNode(model);
        if(n == nullptr)    return;

        n->remove();
        delete n;
    }

    SceneGraph::Node *SceneGraph::getNode(ModelBase *model){
        std::map<ModelBase *, SceneGraph::Node *>::iterator search = m_nodes.find(model);
        if(search == m_nodes.end()){
            std::cout << "Error, could not find model in node list" << std::endl;
            return nullptr;
        }
        return search->second;
    }






    //NODE
    SceneGraph::Node *SceneGraph::Node::add(Node *_m_parent){
        m_parent = _m_parent;
        m_parent->m_children.push_back(this);
        return this;
    }

    SceneGraph::Node *SceneGraph::Node::addChild(Node *child){
        child->add(this);
        return this;
    }

    void SceneGraph::Node::remove(){
        if(m_parent->m_parent == nullptr){
            std::cout << "Error, cannot remove root node" << std::endl;
            return;
        }
        for(std::vector<Node*>::iterator curr = m_children.begin(); curr != m_children.end(); ++curr)
            (*curr)->m_parent = m_parent;
    }

    void SceneGraph::Node::update(){
        m_worldMatrix = m_parent->m_worldMatrix * m_transform.getTransform();

        for(Node *child : m_children){
            child->update();
        }
    }
    glm::vec3 SceneGraph::Node::getPosition(){
        return glm::vec3(m_parent->m_worldMatrix * glm::vec4(m_transform.m_position, 1));
    }
    glm::vec4 SceneGraph::Node::getDirection(){
        return glm::normalize(m_parent->m_worldMatrix * m_transform.getDirection());
    }





    //RenderNode
    SceneGraph::Node *SceneGraph::RenderNode::addChild(Node *child){

        Node *intermediate = Node::addChild(new Node(m_parent));
        intermediate->m_transform = m_transform;
        m_transform = Transform();

        //should have no other m_children, since RenderNodes are leaf nodes
        m_parent = intermediate;
        reinterpret_cast<Node*>(this)->addChild(child);

        return this;
    }

}