#include "shader.hpp"


namespace Render{

    class Renderable{
    public:
        virtual ~Renderable() = default;

        virtual void render() const = 0;
    protected:
        Shader *m_shader;

    private:
        friend class Scene;
    };


    class Model : public Renderable{
        public:
        Model(Shader*);

        virtual void render() const override;
        private:
        //assimp mesh
    };

}