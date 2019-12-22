#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

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
            typedef std::unordered_set<T*,  std::hash<T*>> typeSet;
            virtual ~ResourceList() final = default;

            T *const add(T *const t){ resources.insert(t); return t; }
            typename typeSet::iterator query(T *const t){ return resources.find(t); }
            void remove( T*const t){ resources.erase(query(t)); }
            
            typeSet resources;

            friend class Resources;
        };

    public:

        template <typename T, typename... Args>
        static T *Allocate(Args... args){
            getInstance()->getResourceList<T>()->add(new T(args...));
        }
        
        template <typename T>
        static T* add(T *const t){
            return getInstance()->getResourceList<T>()->add(t);
        }
        
        template<typename T>
        static void remove(T *const t){
            getInstance()->getResourceList<T>()->remove(t);
        }

        template <typename T>
        static bool query(const T *const t){
            return getInstance()->getResourceList<T>()->query(t);
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