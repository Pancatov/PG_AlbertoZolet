#include "SceneManager.h"

//static controllers for mouse and keyboard
static bool keys[1024];
static bool resized;
static GLuint width, height;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::initialize(GLuint w, GLuint h)
{
	width = w;
	height = h;
	
	// GLFW - GLEW - OPENGL general setup -- TODO: config file
	initializeGraphics();

}

void SceneManager::initializeGraphics()
{
	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(width, height, "Hello Sprites", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	//Setando a callback de redimensionamento da janela
	glfwSetWindowSizeCallback(window, resize);
	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Build and compile our shader program
	addShader("../shaders/transformations.vs", "../shaders/transformations.frag");
	addShader("../shaders/GrayScale.vs", "../shaders/GrayScale.frag");
	addShader("../shaders/Colorizar.vs", "../shaders/Colorizar.frag");
	addShader("../shaders/Inversao.vs", "../shaders/Inversao.frag");
	addShader("../shaders/Binarizar.vs", "../shaders/Binarizar.frag");
	addShader("../shaders/SemFiltro.vs", "../shaders/SemFiltro.frag");
	addShader("../shaders/MeuFiltro.vs", "../shaders/MeuFiltro.frag");
	//setup the scene -- LEMBRANDO QUE A DESCRIÇÃO DE UMA CENA PODE VIR DE ARQUIVO(S) DE 
	// CONFIGURAÇÃO
	setupScene();

	resized = true; //para entrar no setup da câmera na 1a vez

}

void SceneManager::addShader(string vFilename, string fFilename)
{
	Shader* shader = new Shader (vFilename.c_str(), fFilename.c_str());
	shaders.push_back(shader);
}


void SceneManager::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void SceneManager::resize(GLFWwindow * window, int w, int h)
{
	width = w;
	height = h;
	resized = true;

	// Define the viewport dimensions
	glViewport(0, 0, width, height);
}


void SceneManager::update()
{
	if (keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);


	//AQUI aplicaremos as transformações nos sprites
	
	//altera o angulo do segundo objeto
	//objects[1]->setAngle((float)glfwGetTime());
}

void SceneManager::render()
{
	// Clear the colorbuffer
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (resized) //se houve redimensionamento na janela, redefine a projection matrix
	{
		setupCamera2D();
		resized = false;
	}

	//atualiza e desenha os Sprites

	for (int i = 0; i < objects.size(); i++)
	{
		//Precisa ser descomentado para o exercicio 1.A
		shaders[0]->setInt("IDExercicio", i + 1);
		shaders[4]->setInt("limiar",84);
		shaders[6]->setInt("limiarMeuFiltro",84);

		objects[i]->update();
		objects[i]->draw();
	}
	

}

void SceneManager::run()
{
	//GAME LOOP
	while (!glfwWindowShouldClose(window))
	{
		
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		//Update method(s)
		update();

		//Render scene
		render();
		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
}

void SceneManager::finish()
{
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}


void SceneManager::setupScene()
{
	//Criação dos Sprites iniciais -- pode-se fazer métodos de criação posteriormente
	
	//Mínimo: posicao e escala e ponteiro para o shader

//=========================================================================================================================================
	//MEU FILTRO
	
	Sprite* obj = new Sprite;
	obj->setPosition(glm::vec3(350.5f, 496.0f, 0.0));
	obj->setDimension(glm::vec3(701.0f, 992.0f, 1.0f));
	obj->setShader(shaders[5]);
	objects.push_back(obj); //adiciona o primeiro obj
	

	//Adicionando mais um
	obj = new Sprite;
	obj->setPosition(glm::vec3(350.9f, 572.7f, 0.0));
	obj->setDimension(glm::vec3(575.0f, 416.0f, 1.0f)); //note que depois podemos reescalar conforme tamanho da sprite
	obj->setShader(shaders[6]);
	objects.push_back(obj); //adiciona o primeiro obj
	shaders[6]->setInt("limiarMeuFiltro", 64);
	shaders[6]->setVec3("novaCorMeuFiltro", 0.29, 0.21, 0.12);

	unsigned int texID = loadTexture("../textures/TemplateBannerOP.png");
	objects[0]->setTexture(texID);


	//use essa textura para uma feliz surpresa
	//texID = loadTexture("../textures/Snow.png");

	texID = loadTexture("../textures/lena.png");
	objects[1]->setTexture(texID);


//=========================================================================================================================================
	//EXERCICIO 1.A
	//Sprite* obj = new Sprite;
	//obj->setPosition(glm::vec3(200.0f, 300.0f, 0.0));
	//obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));//note que depois podemos reescalar conforme tamanho da sprite
	//obj->setShader(shaders[0]);
	//objects.push_back(obj); //adiciona o primeiro obj
	//shaders[0]->setInt("IDExercicio", 1);

	//obj = new Sprite;
	//obj->setPosition(glm::vec3(400.0f, 300.0f, 0.0));
	//obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));//note que depois podemos reescalar conforme tamanho da sprite
	//obj->setShader(shaders[0]);
	//objects.push_back(obj);

	//obj = new Sprite;
	//obj->setPosition(glm::vec3(600.0f, 300.0f, 0.0));
	//obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));//note que depois podemos reescalar conforme tamanho da sprite
	//obj->setShader(shaders[0]);
	//objects.push_back(obj);

	//unsigned int texID = loadTexture("../textures/lena.png");
	//objects[0]->setTexture(texID);
	//objects[1]->setTexture(texID);
	//objects[2]->setTexture(texID);

	//Dar comment nos 2 ultimos Shaders do render;

//=========================================================================================================================================
	//EXERCICIO 1.B


	/*Sprite* obj = new Sprite;
	obj->setPosition(glm::vec3(350.0f, 300.0f, 0.0));
	obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));
	obj->setShader(shaders[1]);
	objects.push_back(obj); 

	unsigned int texID = loadTexture("../textures/lena.png");
	objects[0]->setTexture(texID);*/

//=========================================================================================================================================
	//EXERCICIO 1.C

	/*Sprite* obj = new Sprite;
	obj->setPosition(glm::vec3(350.0f, 300.0f, 0.0));
	obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));
	obj->setShader(shaders[2]);
	objects.push_back(obj); 
	shaders[2]->setVec3("novaCor", 0.0, 0.0, 1.0);

	unsigned int texID = loadTexture("../textures/lena.png");
	objects[0]->setTexture(texID);*/
//=========================================================================================================================================
		//EXERCICIO 1.D

	/*Sprite* obj = new Sprite;
	obj->setPosition(glm::vec3(350.0f, 300.0f, 0.0));
	obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));
	obj->setShader(shaders[3]);
	objects.push_back(obj); 
	

	unsigned int texID = loadTexture("../textures/lena.png");
	objects[0]->setTexture(texID);*/
//=========================================================================================================================================
		//EXERCICIO 1.E

	/*Sprite* obj = new Sprite;
	obj->setPosition(glm::vec3(350.0f, 300.0f, 0.0));
	obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));
	obj->setShader(shaders[4]);
	objects.push_back(obj); 
	shaders[4]->setInt("limiar", 84);

	unsigned int texID = loadTexture("../textures/lena.png");
	objects[0]->setTexture(texID);*/
//=========================================================================================================================================

	//EXERCICIO 2

	//Sprite* obj = new Sprite;
	//obj->setPosition(glm::vec3(100.0f, 100.0f, 0.0));
	//obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));//note que depois podemos reescalar conforme tamanho da sprite
	//obj->setShader(shaders[0]);
	//objects.push_back(obj); //adiciona o primeiro obj
	//shaders[0]->setInt("IDExercicio", 1);

	//obj = new Sprite;
	//obj->setPosition(glm::vec3(300.0f, 100.0f, 0.0));
	//obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));//note que depois podemos reescalar conforme tamanho da sprite
	//obj->setShader(shaders[0]);
	//objects.push_back(obj);

	//obj = new Sprite;
	//obj->setPosition(glm::vec3(500.0f, 100.0f, 0.0));
	//obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));//note que depois podemos reescalar conforme tamanho da sprite
	//obj->setShader(shaders[0]);
	//objects.push_back(obj);

    //obj = new Sprite;
    //obj->setPosition(glm::vec3(100.0f, 300.0f, 0.0));
	//obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));
	//obj->setShader(shaders[1]);
	//objects.push_back(obj); 

    //obj = new Sprite;
    //obj->setPosition(glm::vec3(300.0f, 300.0f, 0.0));
	//obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));
	//obj->setShader(shaders[2]);
	//objects.push_back(obj); 
	//shaders[2]->setVec3("novaCor", 0.0, 0.0, 1.0);

	//obj = new Sprite;
    //obj->setPosition(glm::vec3(500.0f, 300.0f, 0.0));
	//obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));
	//obj->setShader(shaders[3]);
	//objects.push_back(obj); 

	//obj = new Sprite;
	//obj->setPosition(glm::vec3(100.0f, 500.0f, 0.0));
	//obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));
	//obj->setShader(shaders[4]);
	//objects.push_back(obj); 
	//shaders[4]->setInt("limiar", 84);

	//obj = new Sprite;
	//obj->setPosition(glm::vec3(300.0f, 500.0f, 0.0));
	//obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));
	//obj->setShader(shaders[5]);
	//objects.push_back(obj); 

    //obj = new Sprite;
	//obj->setPosition(glm::vec3(500.0f, 500.0f, 0.0));
	//obj->setDimension(glm::vec3(200.0f, 266.0f, 1.0f));
	//obj->setShader(shaders[6]);
	//objects.push_back(obj); 
    //shaders[6]->setInt("limiarMeuFiltro", 84);
    //shaders[6]->setVec3("novaCorMeuFiltro", 0.29, 0.21, 0.12);


	//unsigned int texID = loadTexture("../textures/lena.png");
	//objects[0]->setTexture(texID);
	//objects[1]->setTexture(texID);
	//objects[2]->setTexture(texID);
    //objects[3]->setTexture(texID);
	//objects[4]->setTexture(texID);
	//objects[5]->setTexture(texID);
    //objects[6]->setTexture(texID);
	//objects[7]->setTexture(texID);
	//objects[8]->setTexture(texID);

//=========================================================================================================================================
	//Carregamento das texturas (pode ser feito intercalado na criação)
	//Futuramente, utilizar classe de materiais e armazenar dimensoes, etc
	//unsigned int texID = loadTexture("../textures/TemplateBannerOP.png");
	//objects[0]->setTexture(texID);

	//texID = loadTexture("../textures/lena.png");
	//objects[1]->setTexture(texID);

	//objects[2]->setTexture(texID);
	//texID = loadTexture("../textures/wall.jpg");
	//objects[1]->setTexture(texID);
	//objects[2]->setTexture(texID);

	//Definindo a janela do mundo (ortho2D)
	ortho2D[0] = 0.0f; //xMin
	ortho2D[1] = 701.0f; //xMax
	ortho2D[2] = 0.0f; //yMin
	ortho2D[3] = 992.0f; //yMax

	//Habilita transparência
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void SceneManager::setupCamera2D() //TO DO: parametrizar aqui
{
	float zNear = -1.0, zFar = 1.0; //estão fixos porque não precisamos mudar

	projection = glm::ortho(ortho2D[0], ortho2D[1], ortho2D[2], ortho2D[3], zNear, zFar);


	//Obtendo o identificador da matriz de projeção para enviar para o shader

	for (int i = 0; i < shaders.size(); i++)
	{
		shaders[i]->Use();
		GLint projLoc = glGetUniformLocation(shaders[i]->ID, "projection");
		//Enviando a matriz de projeção para o shader
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	}
}

unsigned int SceneManager::loadTexture(string filename)
{
	unsigned int texture;

	// load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	
	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	glActiveTexture(GL_TEXTURE0);

	return texture;
}
