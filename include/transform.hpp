#ifndef TRANSFORM_H
#define TRANSFORM_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Render{

    class Transform{
        public:
        Transform(const glm::vec3 &position = glm::vec3(), const glm::quat &rotation = glm::quat(), const glm::vec3 &scale = glm::vec3(1.0f));

        inline glm::mat4 operator()(){ return getTransform(); }
        
        Transform &rotate(const glm::vec3 &axis, float angle);
        Transform &scale(float scale);
        Transform &scale(const glm::vec3 &scale);
        Transform &translate(const glm::vec3 &translation);
        Transform &translateTo(const glm::vec3 &translation);

        glm::mat4 getTransform() const;
        glm::vec4 getDirection() const;

        glm::vec3 m_position;
        glm::quat m_rotation;
        glm::vec3 m_scale;
        
    };
    
};

#endif