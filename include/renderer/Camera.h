#ifndef BUBO_CAMERA_H
#define BUBO_CAMERA_H

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace bubo {

    class Camera {
    public:
        virtual const glm::vec3 &getPosition() const = 0;
        virtual void setPosition(const glm::vec3 &position) = 0;
        virtual const glm::mat4 &getViewProjection() const = 0;

    protected:
        glm::mat4 m_projection      = glm::mat4(1.0f);
        glm::mat4 m_view            = glm::mat4(1.0f);
        glm::mat4 m_viewProjection  = glm::mat4(1.0f);

        glm::vec3 m_position        = glm::vec3(0.0f, 0.0f, 3.0f);

    };

    class PerspectiveCamera : public Camera {

    public:
        PerspectiveCamera(float fov, float aspect, float near, float far);
        ~PerspectiveCamera() = default;

        const glm::vec3 &getPosition() const override { return m_position; }
        void setPosition(const glm::vec3 &position) override { m_position = position; updateViewProjection(); }

        void setYaw(const float yaw) { m_yaw = yaw; updateViewProjection(); }
        void setPitch(const float pitch) { m_pitch = pitch; updateViewProjection(); }

        const glm::mat4 &getViewProjection() const override  { return m_viewProjection; }

    private:
        void updateViewProjection();
    private:
        float m_yaw     = -90.0f;
        float m_pitch   = 0.0f;

        glm::vec3 m_up;
        glm::vec3 m_forward;
        glm::vec3 m_right;

    };

    class OrthographicCamera : public Camera {

    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        ~OrthographicCamera() = default;

        float getRotation() const { return m_rotation; }
        void setRotation(float rotation) { m_rotation = rotation; updateViewProjection(); }

        const glm::vec3 &getPosition() const override { return m_position; }
        void setPosition(const glm::vec3 &position) override { m_position = position; updateViewProjection(); }

        const glm::mat4 &getViewProjection() const override { return m_viewProjection; }

    private:
        void updateViewProjection();

    private:
        float m_rotation = 0;

    };

}


#endif //BUBO_CAMERA_H
