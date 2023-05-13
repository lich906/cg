#include "AssimpMesh.h"

void AssimpMesh::MeshEntry::Init(const std::vector<gfx::Vertex>& vertices,
	const std::vector<unsigned int>& indices)
{
	Mesh = gfx::Mesh(vertices, indices);
}

bool AssimpMesh::LoadMesh(const std::string& filename)
{
	// Release the previously loaded mesh (if it exists)
	Clear();

	bool ret = false;
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	if (scene)
	{
		ret = InitFromScene(scene, filename);
	}
	else
	{
		printf("Error parsing '%s': '%s'\n", filename.c_str(), importer.GetErrorString());
	}

	return ret;
}

bool AssimpMesh::InitFromScene(const aiScene* scene, const std::string& filename)
{
	m_entries.resize(scene->mNumMeshes);
	m_textures.resize(scene->mNumMaterials);

	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < m_entries.size(); i++)
	{
		const aiMesh* paiMesh = scene->mMeshes[i];
		InitMesh(i, paiMesh);
	}

	return InitMaterials(scene, filename);
}

void AssimpMesh::InitMesh(unsigned int index, const aiMesh* mesh)
{
	m_entries[index].TextureIndex = mesh->mMaterialIndex;

	std::vector<gfx::Vertex> Vertices;
	std::vector<unsigned int> Indices;

	const aiVector3D zeroVect(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		const aiVector3D* pos = &(mesh->mVertices[i]);
		const aiVector3D* normal = &(mesh->mNormals[i]);
		const aiVector3D* texCoords = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &zeroVect;

		gfx::Vertex vert{
			glm::vec3(pos->x, pos->y, pos->z),
			glm::vec3(normal->x, normal->y, normal->z),
			glm::vec2(texCoords->x, texCoords->y)
		};

		Vertices.push_back(vert);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace& Face = mesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}

	m_entries[index].Init(Vertices, Indices);
}

bool AssimpMesh::InitMaterials(const aiScene* scene, const std::string& filename)
{
	// Extract the directory part from the file name
	std::string::size_type slashIndex = filename.find_last_of("/");
	std::string dir;

	if (slashIndex == std::string::npos)
	{
		dir = ".";
	}
	else if (slashIndex == 0)
	{
		dir = "/";
	}
	else
	{
		dir = filename.substr(0, slashIndex);
	}

	// Initialize the materials
	for (unsigned int i = 0; i < scene->mNumMaterials; i++)
	{
		const aiMaterial* pMaterial = scene->mMaterials[i];

		m_textures[i] = std::nullopt;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				std::string fullPath = dir + "/" + path.data;
				m_textures[i] = gfx::Texture(fullPath.c_str(), GL_REPEAT);
#ifdef  _DEBUG
				printf("Loaded texture '%s'\n", fullPath.c_str());
#endif //  _DEBUG
			}
		}

		// Load a white texture in case the model does not include its own texture
		if (!m_textures[i])
		{
			m_textures[i] = gfx::Texture("assets/textures/white.png");
		}
	}

	return true;
}

void AssimpMesh::Clear()
{
	m_entries.clear();
	m_textures.clear();
}

void AssimpMesh::Draw() const
{
	for (unsigned int i = 0; i < m_entries.size(); i++)
	{
		const auto& TextureIndex = m_entries[i].TextureIndex;

		if (TextureIndex && *TextureIndex < m_textures.size() && m_textures[*TextureIndex])
		{
			m_textures[*TextureIndex]->Bind();
		}

		m_entries[i].Mesh->Draw();
	}
}
