#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scene/Scene.h"

namespace bubo {

    SceneNode* Scene::s_root = new SceneNode();

    SceneNode::SceneNode() {

    }

    SceneNode::~SceneNode() {
        for (int i = 0; i < m_children.size(); ++i) {
            delete m_children[i];
        }
    }

    void SceneNode::setRotation(const glm::vec4 &rotation) {
        m_rotation = rotation;
        m_dirty = true;
    }

    void SceneNode::setPosition(const glm::vec3 &position) {
        m_position = position;
        m_dirty = true;
    }

    void SceneNode::setScale(const glm::vec3 &scale) {
        m_scale = scale;
        m_dirty = true;
    }

    const glm::mat4 & SceneNode::getTransform() {
        updateTransform();
        return m_transform;
    }

    const glm::vec4 &SceneNode::getLocalRotation() const {
        return m_rotation;
    }

    const glm::vec3 &SceneNode::getLocalPosition() const {
        return m_position;
    }

    const glm::vec3 SceneNode::getWorldPosition() {
        glm::mat4 transform = getTransform();
        glm::vec4 worldPosition = transform * glm::vec4(m_position, 1.0f);
        return glm::vec3(worldPosition.x, worldPosition.y, worldPosition.z);
    }

    const glm::vec3 &SceneNode::getLocalScale() const {
        return m_scale;
    }

    void SceneNode::updateTransform() {

        if (m_dirty) {

            m_transform = glm::translate(glm::mat4(1.0f), m_position);
            m_transform = glm::scale(m_transform, m_scale);
            m_transform = glm::rotate(m_transform, m_rotation.a, glm::vec3(m_rotation.x, m_rotation.y, m_rotation.z));

            if (m_parent) {
                m_transform = m_parent->getTransform() * m_transform;
            }

            for (int i = 0; i < m_children.size(); ++i) {
                m_children[i]->m_dirty = true;
            }

            m_dirty = false;

        }

    }

    const bool SceneNode::isDirty() const {
        return m_dirty;
    }

    void SceneNode::addChild(SceneNode *node) {
        node->m_parent = this;
        m_children.push_back(node);
    }

    const std::vector<SceneNode *> &SceneNode::getChildren() const {
        return m_children;
    }

    SceneNode *SceneNode::getParent() const {
        return m_parent;
    }

    void SceneNode::removeChild(SceneNode *node) {
        auto it = std::find(m_children.begin(), m_children.end(), node);
        if (it != m_children.end()) {
           m_children.erase(it);
        }
    }

    void Scene::updateScene() {
        std::vector<SceneNode *> nodesToUpdate;
        nodesToUpdate.push_back(s_root);
        while (!nodesToUpdate.empty()) {

            SceneNode *node = nodesToUpdate.back(); nodesToUpdate.pop_back();
            node->updateTransform();

            for (SceneNode *child : node->getChildren()) {
                nodesToUpdate.push_back(child);
            }
        }
    }

    void Scene::deleteSceneNode(SceneNode *node) {
        node->getParent()->removeChild(node);
        delete node;
    }

    void Scene::clearScene(SceneNode *node = s_root) {
        for (SceneNode *child : node->getChildren()) {
            Scene::clearScene(child);
        }
        if (node != s_root) {
            Scene::deleteSceneNode(node);
        }
    }

}
