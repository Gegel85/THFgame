//
// Created by andgel on 09/12/2020
//

#ifndef CHECKBOARD_MESHOBJECT_HPP
#define CHECKBOARD_MESHOBJECT_HPP


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <string>
#include <map>
#include <SFML/Graphics/Image.hpp>
#include <glm/glm.hpp>
#include "Loader.hpp"

namespace TouhouFanGame::Rendering
{
	struct MaterialInfo {
		glm::vec4 Kd;
		glm::vec4 Ks;
		glm::vec4 Ka;
		float shininess;
	};

	class Mesh {
	private:
		bool isTextureColor;
		GLuint _texHandle;
		GLuint _vaoHandle;
		GLuint _vboColors;
		GLuint _vboVertices;
		GLuint _vboTextureMap;
		GLuint _iboElements;
		GLuint _;
		MaterialInfo _mat;

	public:
		struct MeshInfo {
			std::string texturePath;
			std::vector<glm::vec2> textureCoords;
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec3> normals;
			unsigned *elements;
			size_t elemsSize;
			MaterialInfo mat;
		};

		Mesh(const std::map<std::string, sf::Image> &textures, const MeshInfo &infos);
		void draw(ShaderProgram &) const;
		void setTexture(const sf::Image &image);
		void setTexture(const unsigned char *pixels, unsigned width, unsigned height, bool isColor, bool hasAlpha = true);
		void setTexture(const sf::Color &color);
		MaterialInfo getMaterialInfo() const;
	};

	class MeshObject {
	private:
		std::vector<Mesh> _meshes;

		void _consumeNode(const std::map<std::string, sf::Image> &textures, const aiNode *nodes, const aiScene *scene, const std::string &dir);
		void _consumeNodes(const std::map<std::string, sf::Image> &textures, size_t nbNodes, aiNode ** const nodes, const aiScene *scene, const std::string &dir);

	public:
		MeshObject(const std::map<std::string, sf::Image> &textures, const std::string &path);
		void draw(ShaderProgram &) const;
		std::vector<Mesh> getMeshes() const;
		MaterialInfo getMaterialInfo() const;

		template<typename ...type>
		void setTexture(const type &...vals)
		{
			for (auto &mesh : this->_meshes)
				mesh.setTexture(vals...);
		}
	};
}

#endif //CHECKBOARD_MESHOBJECT_HPP
