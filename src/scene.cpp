#include <iostream>
#include <utility>
#include "scene.hpp"

namespace Render{

    Scene::Scene(){
        root = new Node(nullptr);
        //camera
        //m_renderables
    }

    Node *Scene::add(ModelBase *model, Node *parent){
        Node *child = new RenderNode(model, parent);
        m_shaderGroups.insert(std::make_pair(model->m_shader, child));
        return child;
    }
    
    void Scene::remove(ModelBase *model){

    }

    void Scene::render() const{
    
    }

    Node *Node::addChild(Node *child){

    }

}