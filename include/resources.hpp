#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "typemap.hpp"

namespace Render{

    //singleton global resource holder
    class Resources{

        class AbstractResourceList{
        protected:
            virtual ~AbstractResourceList() = default;

            int m_id;
            friend class Resources;
        };

        template<typename T>
        class ResourceList : public AbstractResourceList{
        protected:
            typedef std::unordered_map<std::string, T*> typeSet;
            virtual ~ResourceList() final = default;

            T *const add(const std::string &str, T *const t){ resources.insert(std::make_pair(str, t)); return t; }
            T* get(const std::string &str){ return resources.find(str)->second; }

            void remove( T*const t){ resources.erase(get(t)); }
            void remove(const std::string& str){ resources.erase(get(str)); }
            
            typeSet resources;

            friend class Resources;
        };

    public:

        template <typename T, typename... Args>
        static T *Allocate(const std::string &str, Args... args){
            getInstance()->getResourceList<T>()->add(str, new T(args...));
        }
        
        template <typename T>
        static T* add(const std::string &str, T *const t){
            return getInstance()->getResourceList<T>()->add(str, t);
        }

        template <typename T>
        static T* get(const std::string &str){
            return getInstance()->getResourceList<T>()->get(str);
        }

        template<typename T>
        static void remove(T *const t){
            getInstance()->getResourceList<T>()->remove(t);
        }

        template<typename T>
        static void remove(const std::string &str){
            getInstance()->getResourceList<T>()->remove(str);
        }

        static Resources *getInstance(){
            static Resources resources;
            return &resources;
        }
        
    private:

        template <typename T>
        ResourceList<T>* getResourceList(){
            TypeMap<AbstractResourceList*>::iterator it = resources.find<T>();
            if(it == resources.end()){
                it = resources.put<T>(new ResourceList<T>()).first;
                it->second->m_id = it->first;
            }
                
            return dynamic_cast<ResourceList<T>*>(it->second);
        }

        Resources() = default;
        ~Resources() = default;
        
        Resources(const Resources&) = delete;
        Resources& operator=(const Resources&) = delete;

        TypeMap<AbstractResourceList*> resources;
    };
}

#endif