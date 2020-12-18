#ifndef BUBO_MODEL_H
#define BUBO_MODEL_H

#include <assimp/scene.h>
#include "Mesh.h"
#include "Scene.h"

namespace bubo {

    class ModelLoader {
    public:
        static SceneNode *LoadModel(const std::string& path);
        static std::shared_ptr<Texture> LoadTexture(const std::string& path);

    private:
        static SceneNode* processNode(aiNode *node, const aiScene *scene, const std::string& directory);

        static Mesh* parseMesh(aiMesh *aMesh);

        static Material* parseMaterial(aiMaterial *aMaterial, const std::string& directory);

        static std::string parseFilename(const std::string &dir, aiString *aPath);

    public:
        static std::vector<Mesh*> s_loadedMeshes;
        static std::map<std::string, std::shared_ptr<Texture>> s_loadedTextures;

    };

}

#endif //BUBO_MODEL_H
