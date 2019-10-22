#include <vector>

#include "shader.hpp"


namespace Render{

    class ModelBase{
    public:
        virtual ~ModelBase() = default;
        ModelBase(Shader *shader):m_shader(shader){}

        virtual void render() const = 0;
    protected:
        Shader * m_shader;

    private:
        friend class Scene;
    };


    class Model : public ModelBase{
    public:
        Model(Shader*);

        virtual void render() const override;
    private:
    };

}