#include "transform.hpp"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Render{

    Transform::Transform(const glm::vec3 &position, const glm::quat &rotation, const glm::vec3 &scale){
        m_position = position;
        m_rotation = rotation;
        m_scale = scale;
    }

    Transform &Transform::rotate(const glm::vec3 &axis, float angle){
        m_rotation = glm::rotate(m_rotation, angle, axis);
        return *this;
    }

    Transform &Transform::scale(float scale){
        m_scale *= scale;
        return *this;
    }

    Transform &Transform::scale(const glm::vec3 &scale){
        m_scale *= scale;
        return *this;
    }

    Transform &Transform::translate(const glm::vec3 &translation){
        m_position += translation;
        return *this;
    }

    Transform &Transform::translateTo(const glm::vec3 &translation){
        m_position =  translation;
        return *this;
    }

    glm::mat4 Transform::getTransform() const {
        return glm::translate(m_position) * glm::toMat4(m_rotation) * glm::scale(m_scale);
    }

    glm::vec4 Transform::getDirection() const {
        return m_rotation * glm::vec4(0,0,-1,0);
    }

};