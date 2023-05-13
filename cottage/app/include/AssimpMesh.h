#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <map>
#include <vector>

#include "graphics/Mesh.h"

class AssimpMesh
{
public:
	bool LoadMesh(const std::string& filename);

	void Draw() const;

private:
	bool InitFromScene(const aiScene* scene, const std::string& filename);
	void InitMesh(unsigned int index, const aiMesh* mesh);
	bool InitMaterials(const aiScene* scene, const std::string& filename);
	void Clear();

	struct MeshEntry
	{
		void Init(const std::vector<gfx::Vertex>& Vertices,
			const std::vector<unsigned int>& Indices);

		std::optional<gfx::Mesh> Mesh;
		std::optional<size_t> TextureIndex;
	};

	std::vector<MeshEntry> m_entries;
	std::vector<std::optional<gfx::Texture>> m_textures;
};
