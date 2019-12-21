#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <unordered_set>
#include <vector>

#include "model.hpp"

namespace Render{
    
    
    //singleton subject class - addModel is observer attachment function
    class Resources{

    public:

        void addModel(Model * const);
        void addTexture(const Texture);

        bool queryModels(const Model * const);
        bool queryTextures(const Texture);

        static Resources *getInstance(){
            static Resources resources;
            return &resources;
        }
        
    private:

        Resources() = default;
        ~Resources() = default;
        Resources(const Resources&) = delete;
        Resources& operator=(const Resources&) = delete;


        template<typename T> class ResourceBase;


        //std::vector<ResourceBase *> resources;
        /*std::unordered_set<Model, std::hash<Model>> models;
        std::unordered_set<Texture, std::hash<Texture>> textures;
        *///more to come

        friend class Model;
    };

    template<typename T> class Resources::ResourceBase{
        virtual void add(T * const) = 0;
    };

    template<typename T> class Resource: public Resources::ResourceBase<Resource<T>>{
        T resource;
    };

}

#endif