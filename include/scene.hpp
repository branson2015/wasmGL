#include <cinttypes> //uint32_t
#include <set>
#include <map>

#include "renderable.hpp"

namespace Render{

    class Scene{
    public:
        Scene();
        ~Scene() = default;

        void add(Renderable*);
        void remove(Renderable*);

        void render() const;

    private:
        uint32_t m_numElements;
        //Camera camera;
        std::set<Renderable*> m_renderables;
        std::map<Shader *, std::set<Renderable*>> m_shaderGroups;
    };

}