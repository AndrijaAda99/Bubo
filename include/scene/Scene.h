#ifndef BUBO_SCENE_H
#define BUBO_SCENE_H

#include <glm/glm.hpp>
#include <renderer/Material.h>
#include "Mesh.h"

namespace bubo {

    class SceneNode {
    public:
        SceneNode();
        ~SceneNode();

        void setRotation(const glm::vec4& rotation);
        void setPosition(const glm::vec3& position);
        void setScale(const glm::vec3& scale);

        const glm::mat4 &getTransform();
        const glm::vec3 getWorldPosition();

        const glm::vec4& getLocalRotation() const;
        const glm::vec3& getLocalPosition() const;
        const glm::vec3& getLocalScale() const;

        const bool isDirty() const;

        void addChild(SceneNode* node);

        const std::vector<SceneNode *> &getChildren() const;
        SceneNode *getParent() const;

        void removeChild(SceneNode *node);
        void updateTransform();

    public:
        Mesh* mesh;
        Material* material;

    private:
        SceneNode* m_parent;
        std::vector<SceneNode*> m_children;

    private:
        glm::mat4 m_transform = glm::mat4(1.0f);
        glm::vec4 m_rotation = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
        glm::vec3 m_position = glm::vec3(0.0f);
        glm::vec3 m_scale = glm::vec3(1.0f);

        bool m_dirty = false;

    };

    class Scene {
    public:
        static SceneNode* getRoot() { return s_root; }
        static void updateScene();
        static void clearScene(SceneNode* node);
        static void deleteSceneNode(SceneNode* node);

    private:
        static SceneNode* s_root;

    };

}

#endif //BUBO_SCENE_H
