#pragma once

//Esta classe vai ir sofrendo alterações durante o curso
//Aqui ela está preparada apenas para sprites texturizados

#include "Shader.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sprite
{
public:
	Sprite();
	~Sprite() {}

	void initialize(); //similar ao setupGeometry

	//Para setar os atributos 
	void setTexture(int texID);
	void setShader(Shader* shader) { this->shader = shader; shader->Use(); }
	void setPosition(glm::vec3 pos) { this->pos = pos; } //dica: fazer setX e setY individualmente
	void setDimension(glm::vec3 scale) { this->scale = scale; }
	void setAngle(float angle) { this->angle = angle; } //para 3D precisa angulo por eixo ou quaternion
	
	glm::vec3 getPosition();
	//Alguns gets e sets para maior controle dos objetos durante a atualização da cena
	void setRotation(float angle, glm::vec3 axis, bool reset = true);
	void setTranslation(glm::vec3 displacements, bool reset = true);
	void setScale(glm::vec3 scaleFactors, bool reset = true);

	float getPosXInicial();
	float getPosYInicial();
	float getPosZInicial();
	
	float getPosX();
	void setPosX(float x);

	void setPosXInicial(float x);
	void setPosYInicial(float y);
	void setPosZInicial(float z);
	//Chamados no ciclo do SceneManager
	void draw();
	void update();

	//Uma versão hardcoded do glfwGetTime(), com ele podemos reiniciar seu valor para que não fique adicionando infinitamente
	float tempo = 0.000f;
protected:
	//Atributos gerais

	GLuint VAO; //ID do buffer de geometria

	glm::mat4 transform; //matriz de transformação

	unsigned int texID; //identificador da textura

	Shader* shader; //ponteiro para o objeto de shader, para fazer a interface

	//Atributos de controle da posição, orientação e dimensões do sprite
	glm::vec3 pos, scale;
	float angle;

	//Atributos para controle da animação
	int nAnims, nFrames;
	int iAnim, iFrame; //indices da animação e frame atual

	float posXInicial=0, posYInicial=0, posZInicial=0;
};

