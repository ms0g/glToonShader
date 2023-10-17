#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Shader.h"


class Model {
public:
    explicit Model(std::string const& path, bool gamma = false);

    void Draw(Shader& shader);

private:
    void LoadModel(std::string const& path);

    void ProcessNode(aiNode* node, const aiScene* scene);

    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

    std::unordered_set<std::string> m_loadedTextures;
    std::vector<Mesh> m_meshes;
    std::string m_directory;
    bool gammaCorrection;
};

