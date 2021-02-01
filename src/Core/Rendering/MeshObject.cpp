//
// Created by andgel on 09/12/2020
//

#include <vector>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "MeshObject.hpp"
#include "../Utils/GlmUtils.hpp"
#include "../Exceptions.hpp"
#include "../Resources/Game.hpp"

namespace TouhouFanGame::Rendering
{
	glm::vec2 toGlmVec2(aiVector3D vec)
	{
		return {vec.x, vec.y};
	}

	glm::vec3 toGlmVec3(aiVector3D vec)
	{
		return {vec.x, vec.y, vec.z};
	}

	void MeshObject::draw(ShaderProgram &shaderProgram) const
	{
		for (auto &mesh : this->_meshes) {
			auto mat = mesh.getMaterialInfo();

			glUniform3fv(shaderProgram.uniform("Kd"), 1, glm::value_ptr(mat.Kd));
			glUniform3fv(shaderProgram.uniform("Ks"), 1, glm::value_ptr(mat.Ks));
			glUniform3fv(shaderProgram.uniform("Ka"), 1, glm::value_ptr(mat.Ka));
			glUniform1f(shaderProgram.uniform("shininess"), mat.shininess);
			mesh.draw(shaderProgram);
		}
	}

	MaterialInfo MeshObject::getMaterialInfo() const
	{
		return MaterialInfo{
			{0.3, 0.3, 0.3, 1},
			{0.3, 0.3, 0.3, 1},
			{0.1, 0.1, 0.1, 1},
			2
		};
	}

	MeshObject::MeshObject(const std::map<std::string, sf::Image> &textures, const std::string &path)
	{
		logger.debug("Loading mesh file " + path);
		Assimp::Importer importer;
		std::string dir = path.substr(0, path.find_last_of('/'));
		const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			throw AssimpImportErrorException(importer.GetErrorString());
		if (!scene->HasMeshes())
			throw InvalidMeshFileException("This file contains no meshes");

		this->_consumeNode(textures, scene->mRootNode, scene, dir);
	}

	void MeshObject::_consumeNodes(const std::map<std::string, sf::Image> &textures, size_t nbNodes, aiNode ** const nodes, const aiScene *scene, const std::string &dir)
	{
		for (size_t i = 0; i < nbNodes; i++) {
			logger.debug("Loading child meshes " + std::to_string(i));
			this->_consumeNode(textures, nodes[i], scene, dir);
		}
	}

	void MeshObject::_consumeNode(const std::map<std::string, sf::Image> &textures, const aiNode *node, const aiScene *scene, const std::string &dir)
	{
		auto transform = node->mTransformation;

		logger.debug("Loading more meshes...");
		for (size_t i = 0; i < node->mNumMeshes; i++) {
			Mesh::MeshInfo info;
			const auto *mesh = scene->mMeshes[node->mMeshes[i]];

			logger.debug("Loading mesh " + std::to_string(i));
			info.elements = nullptr;
			info.elemsSize = 0;
			if (!mesh->HasNormals())
				throw InvalidMeshFileException("Mesh doesn't have normals");

			info.vertices.reserve(mesh->mNumVertices);
			info.normals.reserve(mesh->mNumVertices);
			info.textureCoords.reserve(mesh->mNumVertices);
			logger.debug("Loading vertices...");
			for (size_t j = 0; j < mesh->mNumVertices; j++) {
				info.vertices.push_back(toGlmVec3(transform * mesh->mVertices[j]));
				info.normals.push_back(toGlmVec3(transform * mesh->mNormals[j]));
				if (*mesh->mTextureCoords)
					info.textureCoords.push_back(toGlmVec2((*mesh->mTextureCoords)[j]));
				else
					info.textureCoords.emplace_back(0, 0);
			}

			logger.debug("Loading indexes...");
			for (size_t j = 0; j < mesh->mNumFaces; j++)
				info.elemsSize += mesh->mFaces[j].mNumIndices * sizeof(*mesh->mFaces[j].mIndices);

			info.elements = static_cast<unsigned int *>(malloc(info.elemsSize));
			auto ptr = info.elements;
			for (size_t j = 0; j < mesh->mNumFaces; j++) {
				auto dataSize = mesh->mFaces[j].mNumIndices * sizeof(*mesh->mFaces[j].mIndices);

				std::memcpy(ptr, mesh->mFaces[j].mIndices, dataSize);
				ptr += mesh->mFaces[j].mNumIndices;
			}

			logger.debug("Loading material...");
			auto *mat = scene->mMaterials[mesh->mMaterialIndex];
			aiString str;

			mat->GetTexture(aiTextureType_DIFFUSE, i, &str);
			for (int j = 0; str.data[j]; j++)
				if (str.data[j] == '\\')
					str.data[j] = '/';
			if (mat->Get(AI_MATKEY_COLOR_AMBIENT, &info.mat.Ka, nullptr))
				info.mat.Ka = {1, 1, 1, 1};
			if (mat->Get(AI_MATKEY_COLOR_DIFFUSE, &info.mat.Kd, nullptr))
				info.mat.Kd = {1, 1, 1, 1};
			if (mat->Get(AI_MATKEY_COLOR_SPECULAR, &info.mat.Ks, nullptr))
				info.mat.Ks = {0, 0, 0, 0};
			if (mat->Get(AI_MATKEY_SHININESS, &info.mat.shininess, nullptr))
				info.mat.shininess = 50;
			info.texturePath = dir + "/" + str.C_Str();
			logger.debug("Making mesh object...");
			this->_meshes.emplace_back(textures, info);
			free(info.elements);
		}

		this->_consumeNodes(textures, node->mNumChildren, node->mChildren, scene, dir);
	}

	std::vector<Mesh> MeshObject::getMeshes() const
	{
		return this->_meshes;
	}

	void Mesh::draw(ShaderProgram &) const
	{
		glBindTexture(GL_TEXTURE_2D, this->_texHandle);
		glBindVertexArray(this->_vaoHandle);
		int size;
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

		glDrawElements(GL_TRIANGLES, size / sizeof(GLuint), GL_UNSIGNED_INT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	MaterialInfo Mesh::getMaterialInfo() const
	{
		return this->_mat;
	}

	Mesh::Mesh(const std::map<std::string, sf::Image> &textures, const Mesh::MeshInfo &infos)
	{
		auto it = textures.find(infos.texturePath);

		this->_mat = infos.mat;
		if (it != textures.end())
			this->setTexture(it->second);
		else
			this->setTexture(sf::Color::Red);

		//Create VAOs
		glGenVertexArrays(1, &this->_vaoHandle);
		glBindVertexArray(this->_vaoHandle); // Select particular VAO

		//VBO for vertices
		glGenBuffers(1, &this->_vboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, this->_vboVertices);
		//Alloc memory on GPU and copy data from CPU to GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(infos.vertices.front()) * infos.vertices.size(), infos.vertices.data(), GL_STATIC_DRAW);
		//How the GPU should interpret the data
		glVertexAttribPointer(
			0,        //ID
			3,        //nb of data for each vertex
			GL_FLOAT, //data type
			GL_FALSE, //normalised ?
			0,        //stride
			nullptr   //
		);
		//Enable attribute 0
		glEnableVertexAttribArray(0);

		//VBO for colors
		glGenBuffers(1, &this->_vboColors);
		glBindBuffer(GL_ARRAY_BUFFER, this->_vboColors);
		//Alloc memory on GPU and copy data from CPU to GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(infos.normals.front()) * infos.normals.size(), infos.normals.data(), GL_STATIC_DRAW);
		//How the GPU should interpret the data
		glVertexAttribPointer(
			1,        //ID
			3,        //nb of data for each vertex
			GL_FLOAT, //data type
			GL_FALSE, //normalised ?
			0,        //stride
			nullptr   //
		);
		//Enable attribute 1
		glEnableVertexAttribArray(1);

		//VBO for colors
		glGenBuffers(1, &this->_vboTextureMap);
		glBindBuffer(GL_ARRAY_BUFFER, this->_vboTextureMap);
		//Alloc memory on GPU and copy data from CPU to GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(infos.textureCoords.front()) * infos.textureCoords.size(), infos.textureCoords.data(), GL_STATIC_DRAW);
		//How the GPU should interpret the data
		glVertexAttribPointer(
			2,        //ID
			2,        //nb of data for each vertex
			GL_FLOAT, //data type
			GL_FALSE, //normalised ?
			0,        //stride
			nullptr   //
		);
		//Enable attribute 2
		glEnableVertexAttribArray(2);

		glGenBuffers(2, &this->_iboElements);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_iboElements);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, infos.elemsSize, infos.elements, GL_STATIC_DRAW);

		//VAO close
		glBindVertexArray(0);
	}

	void Mesh::setTexture(const sf::Image &image)
	{
		this->setTexture(image.getPixelsPtr(), image.getSize().x, image.getSize().y, false);
	}

	void Mesh::setTexture(const sf::Color &color)
	{
		this->setTexture(reinterpret_cast<const unsigned char *>(&color), 1, 1, true, false);
	}

	void Mesh::setTexture(const unsigned char *pixels, unsigned width, unsigned height, bool isColor, bool hasAlpha)
	{
		this->isTextureColor = isColor;
		glGenTextures(1, &this->_texHandle);
		glBindTexture(GL_TEXTURE_2D, this->_texHandle);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}
