#include <iostream>
#include <utility>
#include "scene.hpp"

namespace Render{

    Scene::Scene(){
        //camera
        //m_renderables
    }

    void Scene::add(Renderable *renderable){
        Shader *shader = renderable->m_shader;

        bool success = m_renderables.insert(renderable).second;
        if(success){
            std::map<Shader *, std::set<Renderable *>>::iterator SGit = m_shaderGroups.find(shader);
            if(SGit == m_shaderGroups.end())
                SGit = m_shaderGroups.insert({shader, std::set<Renderable*>()}).first;

            SGit->second.insert(renderable);
        }else{
            std::cout << "Error, renderable already inserted" << std::endl;
            return;
        }
    }
    
    void Scene::remove(Renderable *renderable){
        m_renderables.erase(m_renderables.find(renderable));
        m_shaderGroups.find(renderable->m_shader)->second.find(renderable);
    }

    void Scene::render() const{

        for(std::map<Shader *, std::set<Renderable*>>::const_iterator itm = m_shaderGroups.begin(); itm != m_shaderGroups.end(); itm++){
            itm->first->Bind();
            for(std::set<Renderable*>::iterator its = itm->second.begin(); its != itm->second.end(); its++){
                (*its)->render();
            }
        }

    }

}