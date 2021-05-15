//
// Created by Gegel85 on 15/01/2019.
//

#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <hwloc.h>
#include <glm/gtc/type_ptr.hpp>
#include "../Resources/Game.hpp"
#include "Screen.hpp"
#include "../Utils/GlmUtils.hpp"

static const glm::vec3 DEFAULT_VIEW_POINT = { 5, 5, 5 };
static const glm::vec3 DEFAULT_VIEW_CENTER = { 0, 0, 0 };
static const glm::vec3 DEFAULT_UP_VECTOR = { 0, 1, 0 };

namespace TouhouFanGame::Rendering
{
	static glm::mat4 perspective(float fovy, float aspect, float near, float far)
	{
		fovy *= M_PI / 180;
		return {
			{1 / (aspect * std::tan(fovy / 2)), 0,                         0,                               0},
			{0,                                    1 / std::tan(fovy / 2), 0,                               0},
			{0,                                    0,                         (far + near) / (near - far),     -1},
			{0,                                    0,                         (2 * far * near) / (near - far), 0},
		};
	}

	static glm::mat4 lookAt(glm::vec3 camPos, glm::vec3 target, glm::vec3 upvec)
	{
		glm::vec3 zaxis = glm::normalize(target - camPos);
		glm::vec3 xaxis = glm::normalize(glm::cross(zaxis, upvec));
		glm::vec3 yaxis = glm::normalize(glm::cross(xaxis, zaxis));

		return glm::mat4{
			{xaxis.x, yaxis.x, -zaxis.x, 0},
			{xaxis.y, yaxis.y, -zaxis.y, 0},
			{xaxis.z, yaxis.z, -zaxis.z, 0},
			{-glm::dot(xaxis, camPos), -glm::dot(yaxis, camPos), glm::dot(zaxis, camPos), 1},
		};
	}

	Screen::Screen(Resources &resources, const std::string &title, unsigned int width, unsigned int height) :
		sf::RenderWindow(sf::VideoMode(width, height), title),
		Viewer(DEFAULT_VIEW_POINT, DEFAULT_VIEW_CENTER, DEFAULT_UP_VECTOR, 45, width / (float) height),
		_resources(resources),
		_title(title),
		_fps(60)
	{
		TouhouFanGame::logger.info("Opening window \"" + title + "\"");
		this->setFramerateLimit(60);
		this->_text.setOutlineThickness(0);
		this->_rect.setOutlineThickness(0);
		this->_circle.setOutlineThickness(0);
	}

	Screen::~Screen()
	{
		TouhouFanGame::logger.info("Destroying window \"" + this->_title + "\"");
	}

	const std::string &Screen::getTitle() const
	{
		return this->_title;
	}

	void Screen::setTitle(const std::string &title)
	{
		this->_title = title;
		sf::RenderWindow::setTitle(title);
	}

	void    Screen::fillColor(const sf::Color &color)
	{
		this->_rect.setFillColor(color);
		this->_text.setFillColor(color);
		this->_sprite.setColor(color);
		this->_circle.setFillColor(color);
	}

	void	Screen::setFont(const sf::Font &font)
	{
		this->_text.setFont(font);
	}

	void	Screen::textSize(size_t size)
	{
		this->_text.setCharacterSize(size);
	}

	void	Screen::draw(sf::IntRect rect)
	{return;
		this->_rect.setPosition(Vector2f(rect.left, rect.top));
		this->_rect.setSize(Vector2f(rect.width, rect.height));
		sf::RenderWindow::draw(this->_rect);
	}

	void Screen::draw(float radius, Vector2f pos)
	{return;
		this->_circle.setPosition(Vector2f(pos.x, pos.y));
		this->_circle.setRadius(radius);
		sf::RenderWindow::draw(this->_circle);
	}

	void	Screen::draw(const std::string &str, Vector2f pos, unsigned style)
	{return;
		this->_text.setPosition(pos);
		this->_text.setString(str);
		this->_text.setStyle(style);
		sf::RenderWindow::draw(this->_text);
	}

	void	Screen::draw(sf::Sprite &sprite, Vector2f pos)
	{return;
		sprite.setPosition(pos);
		sf::RenderWindow::draw(sprite);
	}

	void	Screen::draw(sf::Texture &texture, Vector2f pos, Vector2u size, sf::IntRect rect)
	{return;
		auto textureSize = texture.getSize();

		if (!rect.width)
			rect.width = textureSize.x - rect.left;

		if (!rect.height)
			rect.height = textureSize.y - rect.top;

		if (!size.x)
			size.x = rect.width;

		if (!size.y)
			size.y = rect.height;

		this->_sprite.setTexture(texture, true);
		this->_sprite.setTextureRect(rect);
		this->_sprite.setScale({
		       static_cast<float>(size.x) / rect.width,
		       static_cast<float>(size.y) / rect.height
		});
		this->draw(this->_sprite, pos);
	}

	Entity &Screen::addEntity(const std::string &configFile)
	{
		logger.debug("Making new rendering entity " + configFile);
		return *this->_entities.emplace_back(new Entity(this->_resources, configFile));
	}

	Vector2f Screen::getCameraCenter() const
	{
		return this->_cameraCenter;
	}

	static glm::vec3 computeNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
	{
		return glm::normalize(glm::cross(glm::normalize(p1 - p2), glm::normalize(p3 - p2)));
	}

	static void tmp(Resources &resources, Screen &screen, ShaderProgram &prog)
	{
		float elems3[4] = {0.25, 0.25, 0.25, 1};
		float elems2[4] = {1, 1, 1, 1};
		float elems[4] = {0, 10, 0, 1};
		static struct {
			GLuint _vaoHandle;
			GLuint _vbo_cube_vertices;
			GLuint _vbo_cube_colors;
			GLuint _ibo_cube_elements;
			GLuint _;
			GLuint tex_2d;
		} y;
		static int value = -1;

		if (value == -1) {
			glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &y.tex_2d);  //tex_2d is a member variable
			glBindTexture(GL_TEXTURE_2D, y.tex_2d);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA,  GL_UNSIGNED_BYTE, &sf::Color::Yellow);
			glGenerateMipmap(GL_TEXTURE_2D);

			std::vector<glm::vec3> normals;
			std::vector<glm::vec3> vertices = {
				// back
				{-1.0, -1.0, -1.0},
				{ 1.0, -1.0, -1.0},
				{ 1.0,  1.0, -1.0},
				{-1.0,  1.0, -1.0},
				{-1.0, -1.0, -1.0},
				{ 1.0,  1.0, -1.0},
				// front
				{ 1.0, -1.0,  1.0},
				{-1.0, -1.0,  1.0},
				{ 1.0,  1.0,  1.0},
				{-1.0, -1.0,  1.0},
				{-1.0,  1.0,  1.0},
				{ 1.0,  1.0,  1.0},
				// top
				{-1.0,  1.0, -1.0},
				{ 1.0,  1.0, -1.0},
				{ 1.0,  1.0,  1.0},
				{-1.0,  1.0,  1.0},
				{-1.0,  1.0, -1.0},
				{ 1.0,  1.0,  1.0},
				// bottom
				{ 1.0, -1.0, -1.0},
				{-1.0, -1.0, -1.0},
				{ 1.0, -1.0,  1.0},
				{-1.0, -1.0, -1.0},
				{-1.0, -1.0,  1.0},
				{ 1.0, -1.0,  1.0},
				//left
				{-1.0, -1.0, -1.0},
				{-1.0,  1.0, -1.0},
				{-1.0,  1.0,  1.0},
				{-1.0, -1.0,  1.0},
				{-1.0, -1.0, -1.0},
				{-1.0,  1.0,  1.0},
				//right
				{ 1.0,  1.0, -1.0},
				{ 1.0, -1.0, -1.0},
				{ 1.0,  1.0,  1.0},
				{ 1.0, -1.0, -1.0},
				{ 1.0, -1.0,  1.0},
				{ 1.0,  1.0,  1.0},
			};
			std::vector<glm::vec2> texture = {
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
			};

			for (unsigned i = 0; i < vertices.size(); i += 3) {
				glm::vec3 computed = computeNormal(vertices[i], vertices[i + 1], vertices[i + 2]);

				normals.push_back(computed);
				normals.push_back(computed);
				normals.push_back(computed);
			}

			//Create VAOs
			glGenVertexArrays(1, &y._vaoHandle);
			glBindVertexArray(y._vaoHandle); // Select particular VAO

			//VBO for vertices
			glGenBuffers(1, &y._vbo_cube_vertices);
			glBindBuffer(GL_ARRAY_BUFFER, y._vbo_cube_vertices);
			//Alloc memory on GPU and copy data from CPU to GPU
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices.front()) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
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
			glGenBuffers(1, &y._vbo_cube_colors);
			glBindBuffer(GL_ARRAY_BUFFER, y._vbo_cube_colors);
			//Alloc memory on GPU and copy data from CPU to GPU
			glBufferData(GL_ARRAY_BUFFER, sizeof(normals.front()) * normals.size(), normals.data(), GL_STATIC_DRAW);
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

			GLuint i;
			//VBO for colors
			glGenBuffers(1, &i);
			glBindBuffer(GL_ARRAY_BUFFER, i);
			//Alloc memory on GPU and copy data from CPU to GPU
			glBufferData(GL_ARRAY_BUFFER, sizeof(texture.front()) * texture.size(), texture.data(), GL_STATIC_DRAW);
			//How the GPU should interpret the data
			glVertexAttribPointer(
				2,        //ID
				2,        //nb of data for each vertex
				GL_FLOAT, //data type
				GL_FALSE, //normalised ?
				0,        //stride
				nullptr   //
			);
			//Enable attribute 1
			glEnableVertexAttribArray(2);

			/*glGenBuffers(2, &this->_ibo_cube_elements);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ibo_cube_elements);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements.front()) * cube_elements.size(), cube_elements.data(), GL_STATIC_DRAW);
		*/
			//VAO close
			glBindVertexArray(0);
			value = 0;
		}

		screen.setActive(true);
		static glm::vec3 f{0, 0, 0};
		glm::vec3 eye = screen.getViewPoint();
		glm::vec3 look = screen.getViewCenter();
		glm::vec3 up = screen.getUpVector();

		screen.rotate(0.001, 0.001);
		//screen.zoom(-0.001);
		glm::mat4 view = glm::lookAt(eye, look, up);
		glm::mat4 projection = glm::perspective(45.f, 1.0f * screen.getView().getSize().x / screen.getView().getSize().y, 0.001f, 1000.f);

		prog.use();
		glEnable(GL_DEPTH_TEST);

		glm::mat4 mv = view;// * model.getModelMatrix();
		glm::mat4 mvp = projection * mv;
		glm::mat4 imvp = glm::inverse(mv);
		glm::mat3 nmat = glm::mat3(glm::transpose(imvp));  //normal matrix

		glUniformMatrix4fv(prog.uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
		glUniformMatrix4fv(prog.uniform("mv"), 1, GL_FALSE, glm::value_ptr(mv));
		glUniform1i(prog.uniform("Tex1"), 0);
		for (int i = 0; i < 5; i++) {
			glUniform4fv(prog.uniform("lightPos[" + std::to_string(i) + "]"), 1, elems);//glm::value_ptr(view * this->lightPos[i]));
			glUniform3fv(prog.uniform("Is[" + std::to_string(i) + "]"), 1, elems2);//glm::value_ptr(this->light[i]));
			glUniform3fv(prog.uniform("Id[" + std::to_string(i) + "]"), 1, elems2);//glm::value_ptr(this->light[i]));
		}
		glUniformMatrix3fv(prog.uniform("normalMatrix"), 1, GL_FALSE, glm::value_ptr(nmat));
		glUniform3fv(prog.uniform("Kd"), 1, elems3);
		glUniform3fv(prog.uniform("Ks"), 1, elems3);
		glUniform3fv(prog.uniform("Ka"), 1, elems3);
		glUniform1f(prog.uniform("shininess"), 5);

		// Draw the cube
		glBindTexture(GL_TEXTURE_2D, y.tex_2d);
		glBindVertexArray(y._vaoHandle);
		int size;
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindTexture(GL_TEXTURE_2D, 0);

		for (auto &s : resources.models)
			s.second.draw(prog);

		prog.disable();
		screen.setActive(false);
	}

	void Screen::renderEntities()
	{
		this->popGLStates();
		tmp(this->_resources, *this, *this->_shader);
		this->pushGLStates();
		//for (auto &entity : this->_entities)
		//	entity->render(*this);
	}

	void Screen::deleteEntities()
	{
		this->_entities.clear();
	}

	void Screen::removeEntity(Entity &entity)
	{
		for (auto it = this->_entities.begin(); it < this->_entities.end(); it++)
			if (&**it == &entity)
				this->_entities.erase(it);
	}

	void Screen::display()
	{
		this->_fps = 1 / this->_clock.getElapsedTime().asSeconds();
		this->_clock.restart();
		sf::RenderWindow::display();
	}

	void Screen::setCameraCenter(Vector2f newCamera)
	{
		this->_cameraCenter = newCamera;
		this->_view.setCenter(this->_cameraCenter.x, this->_cameraCenter.y);
		this->_view.setSize(this->getSize().x, this->getSize().y);
		this->setView(this->_view);
	}

	double Screen::getFPS()
	{
		return this->_fps;
	}

	float Screen::getTextWidth(const std::string &text)
	{
		float size = 0;
		auto font = this->_text.getFont();

		if (!font)
			return 0;

		for (char c : text)
			size += font->getGlyph(c, this->_text.getCharacterSize(), false).advance;
		return size;
	}

	void Screen::setShaders(const std::string &vertexShader, const std::string &fragmentShader)
	{
		if (!this->_shader)
			this->_shader = std::make_unique<ShaderProgram>();
		this->_shader->initFromFiles(vertexShader, fragmentShader);
		this->_shader->addUniform("mvp");
		this->_shader->addUniform("mv");
		this->_shader->addUniform("lightPos[0]");
		this->_shader->addUniform("lightPos[1]");
		this->_shader->addUniform("lightPos[2]");
		this->_shader->addUniform("lightPos[3]");
		this->_shader->addUniform("lightPos[4]");
		this->_shader->addUniform("Id[0]");
		this->_shader->addUniform("Id[1]");
		this->_shader->addUniform("Id[2]");
		this->_shader->addUniform("Id[3]");
		this->_shader->addUniform("Id[4]");
		this->_shader->addUniform("Is[0]");
		this->_shader->addUniform("Is[1]");
		this->_shader->addUniform("Is[2]");
		this->_shader->addUniform("Is[3]");
		this->_shader->addUniform("Is[4]");
		this->_shader->addUniform("Kd");
		this->_shader->addUniform("Ks");
		this->_shader->addUniform("Ka");
		this->_shader->addUniform("normalMatrix");
		this->_shader->addUniform("shininess");
		this->_shader->addUniform("Tex1");
	}
}