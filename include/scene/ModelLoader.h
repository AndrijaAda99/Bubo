#ifndef BUBO_MODEL_H
#define BUBO_MODEL_H

#include <assimp/scene.h>
#include "Mesh.h"
#include "Scene.h"

namespace bubo {

    class ModelLoader {
    public:
        static SceneNode *LoadModel(const std::string& path, bool flipUVs);
        static const Texture* LoadTexture(const std::string& path);
        static void destroyMeshData();
        static void destroyMaterialData();
        static void destroyTextures();

    private:
        static SceneNode* processNode(aiNode *node, const aiScene *scene, const std::string& directory);

        static Mesh* parseMesh(aiMesh *aMesh);

        static Material* parseMaterial(aiMaterial *aMaterial, const std::string& directory);

        static std::string parseFilename(const std::string &dir, aiString *aPath);

        static std::vector<Mesh*> s_loadedMeshes;
        static std::vector<Material*> s_loadedMaterials;
        static std::map<std::string, const Texture*> s_loadedTextures;

    };

}

#endif //BUBO_MODEL_H
