#include "Camadas.h"

Camadas::Camadas()
{
	
}

Camadas::~Camadas()
{
}

void Camadas::updateCamada()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->update();
		objects[i]->draw();
	}


}

void Camadas::adcionarObjeto(float posX,float posY,float posZ,float dimX,float dimY,float dimZ ,Shader* shader)
{
	obj = new Sprite;
	obj->setPosition(glm::vec3(posX, posY, posZ));
	obj->setDimension(glm::vec3(dimX, dimY,dimZ)); //note que depois podemos reescalar conforme tamanho da sprite
	obj->setShader(shader);
	objects.push_back(obj);

	obj->setPosXInicial(posX);
	obj->setPosYInicial(posY);
	obj->setPosZInicial(posZ);

	obj->setPosX(posX);
}

void Camadas::setDesloc(float deslocamento)
{
	desloc = deslocamento;

}

float Camadas::getDesloc()
{
	return desloc;
}
