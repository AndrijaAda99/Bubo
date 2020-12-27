#include <scene/ModelLoader.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <scene/Mesh.h>
#include <scene/Scene.h>

namespace bubo {

    std::vector<Mesh*> ModelLoader::s_loadedMeshes;
    std::vector<Material*> ModelLoader::s_loadedMaterials;
    std::map<std::string, const Texture*> ModelLoader::s_loadedTextures;

    SceneNode *ModelLoader::LoadModel(const std::string &path, bool flipUVs) {

        Assimp::Importer importer;

        BUBO_DEBUG_TRACE("Assimp loading model from path: {0}", path);
        const aiScene *scene;
        if (flipUVs) {
            scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                                            aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
        } else {
            scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                                            aiProcess_CalcTangentSpace);
        }

        if (!scene) {
            BUBO_WARN("Assimp failed to load model from path: {0}\nAssimp Error: {1}", path, importer.GetErrorString());
            return nullptr;
        }

        std::string directory = path.substr(0, path.find_last_of("/"));

        BUBO_DEBUG_TRACE("Assimp successfully loaded model from path: {0}", path);
        return ModelLoader::processNode(scene->mRootNode, scene, directory);

    }

    SceneNode *ModelLoader::processNode(aiNode *node, const aiScene *scene, const std::string& directory) {

        SceneNode *sceneNode = new SceneNode();
        for (int i = 0; i < node->mNumMeshes; ++i) {
            aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];
            aiMaterial* assimpMaterial = scene->mMaterials[assimpMesh->mMaterialIndex];

            Mesh* mesh = ModelLoader::parseMesh(assimpMesh);
            Material* material = ModelLoader::parseMaterial(assimpMaterial, directory);

            if (node->mNumMeshes == 1) {
                sceneNode->mesh = mesh;
                sceneNode->material = material;
            } else {
                SceneNode *child = new SceneNode();
                child->mesh = mesh;
                child->material = material;
                sceneNode->addChild(child);
            }
        }

        for (int i = 0; i < node->mNumChildren; ++i) {
            sceneNode->addChild(ModelLoader::processNode(node->mChildren[i], scene, directory));
        }

        return sceneNode;

    }

    Mesh* ModelLoader::parseMesh(aiMesh *aMesh) {

        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> UVs;
        std::vector<glm::vec3> tangents;
        std::vector<glm::vec3> bitangents;
        std::vector<unsigned int> indices;

        positions.resize(aMesh->mNumVertices);
        normals.resize(aMesh->mNumVertices);
        if (aMesh->mNumUVComponents[0] > 0) {
            UVs.resize(aMesh->mNumVertices);
            tangents.resize(aMesh->mNumVertices);
            bitangents.resize(aMesh->mNumVertices);
        }
        indices.resize(aMesh->mNumFaces * 3);

        for (int i = 0; i < aMesh->mNumVertices; ++i) {
            positions[i] = glm::vec3(aMesh->mVertices[i].x, aMesh->mVertices[i].y, aMesh->mVertices[i].z);
            normals[i] = glm::vec3(aMesh->mNormals[i].x, aMesh->mNormals[i].y, aMesh->mNormals[i].z);
            if (aMesh->mTextureCoords[0]) {
                UVs[i] = glm::vec2(aMesh->mTextureCoords[0][i].x, aMesh->mTextureCoords[0][i].y);
                tangents[i] = glm::vec3(aMesh->mTangents[i].x, aMesh->mTangents[i].y, aMesh->mTangents[i].z);
                bitangents[i] = glm::vec3(aMesh->mBitangents[i].x, aMesh->mBitangents[i].y, aMesh->mBitangents[i].z);
            } else {
                UVs[i] = glm::vec2(0.0f, 0.0f);
            }
        }

        for (int i = 0; i < aMesh->mNumFaces; ++i) {
            indices[3 * i + 0] = aMesh->mFaces[i].mIndices[0];
            indices[3 * i + 1] = aMesh->mFaces[i].mIndices[1];
            indices[3 * i + 2] = aMesh->mFaces[i].mIndices[2];
        }

        Mesh* mesh = new Mesh();

        mesh->setPositions(positions);
        mesh->setNormals(normals);
        mesh->setUVs(UVs);
        mesh->setIndices(indices);
        mesh->setTangentSpace(tangents, bitangents);
        mesh->finalize();

        s_loadedMeshes.push_back(mesh);

        return mesh;
    }

    Material *ModelLoader::parseMaterial(aiMaterial *aMaterial, const std::string& directory) {

        Material *material = new Material(ShaderLibrary::get("defaultShader"));

        if (aMaterial->GetTextureCount(aiTextureType_DIFFUSE)) {
            aiString path;
            aMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path);
            std::string filename = ModelLoader::parseFilename(directory, &path);

            const Texture *texture_diffuse = ModelLoader::LoadTexture(filename);
            material->setTexture("u_Material.diffuse", texture_diffuse, 0);
        }

        if (aMaterial->GetTextureCount(aiTextureType_SPECULAR)) {
            aiString path;
            aMaterial->GetTexture(aiTextureType_SPECULAR, 0, &path);
            std::string filename = ModelLoader::parseFilename(directory, &path);

            const Texture *texture_specular = ModelLoader::LoadTexture(filename);
            material->setTexture("u_Material.specular", texture_specular, 1);
        }

        if (aMaterial->GetTextureCount(aiTextureType_HEIGHT)) {
            aiString path;
            aMaterial->GetTexture(aiTextureType_HEIGHT, 0, &path);
            std::string filename = ModelLoader::parseFilename(directory, &path);

            const Texture *texture_specular = ModelLoader::LoadTexture(filename);
            material->setTexture("u_Material.normal", texture_specular, 2);
        }

        if (aMaterial->GetTextureCount(aiTextureType_NORMALS)) {
            aiString path;
            aMaterial->GetTexture(aiTextureType_NORMALS, 0, &path);
            std::string filename = ModelLoader::parseFilename(directory, &path);

            const Texture *texture_specular = ModelLoader::LoadTexture(filename);
            material->setTexture("u_Material.normal", texture_specular, 2);
        }

        s_loadedMaterials.push_back(material);

        return material;
    }

    std::string ModelLoader::parseFilename(const std::string &dir, aiString *aPath) {

        std::string path = std::string(aPath->C_Str());

        if(path.find(":/") == std::string::npos || path.find(":\\") == std::string::npos)
            path = dir + "/" + path;

        return path;
    }

    const Texture* ModelLoader::LoadTexture(const std::string& path) {

        if (s_loadedTextures.find(path) == s_loadedTextures.end())  {
            BUBO_DEBUG_TRACE("Loading texture from path: {0}", path.c_str());
            s_loadedTextures[path] = new Texture(path);
        }

        return s_loadedTextures[path];
    }

    void ModelLoader::destroyMeshData() {
        for (Mesh *mesh : s_loadedMeshes) {
            delete mesh;
        }
    }

    void ModelLoader::destroyMaterialData() {
        for (Material *material : s_loadedMaterials) {
            delete material;
        }
    }

    void ModelLoader::destroyTextures() {
        for (auto it : s_loadedTextures) {
            delete it.second;
        }
    }

}
