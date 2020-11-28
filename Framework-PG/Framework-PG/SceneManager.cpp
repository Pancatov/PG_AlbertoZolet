#include "SceneManager.h"

//static controllers for mouse and keyboard
static bool keys[1024];
static bool resized;
static GLuint width, height;

static Direcoes dir = PARADO;
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

	//setup the scene -- LEMBRANDO QUE A DESCRIÇÃO DE UMA CENA PODE VIR DE ARQUIVO(S) DE 
	// CONFIGURAÇÃO
	setupScene();

	resized = true; //para entrar no setup da câmera na 1a vez

}

void SceneManager::addShader(string vFilename, string fFilename)
{
	shader = new Shader (vFilename.c_str(), fFilename.c_str());
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

	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
		{
			
			dir = NORTE;
			
	    }

		if (key == GLFW_KEY_E)
		{
			dir = NORDESTE;
	
		}

		if (key == GLFW_KEY_D)
		{
			dir = LESTE;
			
		}

		if (key == GLFW_KEY_C)
		{
			dir = SUDESTE;
			
		}

		if (key == GLFW_KEY_X)
		{
			dir = SUL;
			
		}

		if (key == GLFW_KEY_Z)
		{
			dir = SUDOESTE;
			
		}

		if (key == GLFW_KEY_A)
		{
			dir = OESTE;
			
		}

		if (key == GLFW_KEY_Q)
		{
			dir = NOROESTE;
		
		}



	}
}

void SceneManager::do_movement()
{
	if (keys[GLFW_KEY_ESCAPE])
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (dir == NORTE)
	{
		if ((posLinha != 4) && (posColuna != 4))
		{
			if (mapWalking[posLinha + 1][posColuna + 1] == 1)
			{
				mapWalking[posLinha][posColuna] = 0;
				map[posLinha][posColuna] = 0;
				posColuna += 1;
				posLinha += 1;
			}
		}
		dir = PARADO;
	}

	if (dir == NORDESTE)
	{
		personagem->setDireita();
		if (posColuna != 4)
		{
			if (mapWalking[posLinha][posColuna + 1] == 1)
			{
				mapWalking[posLinha][posColuna] = 0;
				map[posLinha][posColuna] = 0;
				posColuna += 1;
				posLinha -= 0;
			}
		}
		dir = PARADO;
	}

	if (dir == LESTE)
	{
		personagem->setDireita();
		if ((posLinha != 0) && (posColuna != 4) )
		{
			if (mapWalking[posLinha - 1][posColuna + 1] == 1)
			{
				mapWalking[posLinha][posColuna] = 0;
				map[posLinha][posColuna] = 0;
				posColuna += 1;
				posLinha -= 1;
			}
		}
		dir = PARADO;
	}

	if (dir == SUDESTE)
	{
		personagem->setDireita();
		if (posLinha != 0)
		{
			if (mapWalking[posLinha - 1][posColuna] == 1)
			{
				mapWalking[posLinha][posColuna] = 0;
				map[posLinha][posColuna] = 0;
				posColuna -= 0;
				posLinha -= 1;
			}
		}
		dir = PARADO;
	}

	if (dir == SUL)
	{
		if ((posColuna != 0) && (posLinha != 0))
		{
			if (mapWalking[posLinha - 1][posColuna - 1] == 1)
			{
				mapWalking[posLinha][posColuna] = 0;
				map[posLinha][posColuna] = 0;
				posColuna -= 1;
				posLinha -= 1;
			}
		}
		dir = PARADO;
	}

	if (dir == SUDOESTE)
	{
		personagem->setEsquerda();
		if (posColuna != 0)
		{
			if (mapWalking[posLinha][posColuna - 1] == 1)
			{
				mapWalking[posLinha][posColuna] = 0;
				map[posLinha][posColuna] = 0;
				posColuna -= 1;
				posLinha += 0;
			}
		}
		dir = PARADO;
	}

	if (dir == OESTE)
	{
		personagem->setEsquerda();
		if ((posColuna != 0)&&(posLinha!=4))
		{
			if (mapWalking[posLinha + 1][posColuna - 1] == 1)
			{
				mapWalking[posLinha][posColuna] = 0;
				map[posLinha][posColuna] = 0;
				posColuna -= 1;
				posLinha += 1;
			}
		}
		dir = PARADO;
	}

	if (dir == NOROESTE)
	{
		personagem->setEsquerda();
		if (posLinha != 4)
		{
			if (mapWalking[posLinha + 1][posColuna] == 1)
			{
				mapWalking[posLinha][posColuna] = 0;
				map[posLinha][posColuna] = 0;
				posColuna += 0;
				posLinha += 1;
			}
		}
		dir = PARADO;
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
	//objects[1]->setAngle((float)glfwGetTime
	if ((mapWalking[posLinha + 1][posColuna] == 0) && (mapWalking[posLinha + 1][posColuna + 1] == 0) && (mapWalking[posLinha][posColuna + 1] == 0))
	{
		if ((mapWalking[posLinha - 1][posColuna] == 0) && (mapWalking[posLinha - 1][posColuna - 1] == 0) && (mapWalking[posLinha][posColuna - 1] == 0))
		{
			if ((mapWalking[posLinha + 1][posColuna - 1] == 0) && (mapWalking[posLinha + 1][posColuna - 1] == 0) && (mapWalking[posLinha - 1][posColuna + 1] == 0) && (mapWalking[posLinha - 1][posColuna + 1] == 0))
			{
				vivo = false;
			}
		}

	}

	/*else if (posLinha = 0 && posColuna!=0 && posColuna!=4)
	{
		if ((mapWalking[posLinha][posColuna-1] == 0) && (mapWalking[posLinha + 1][posColuna ] == 0) && (mapWalking[posLinha+1][posColuna - 1] == 0)&&(mapWalking[posLinha + 1][posColuna + 1] == 0) && (mapWalking[posLinha][posColuna + 1] == 0))
		{
			
					vivo = false;
			

		}
	}*/

	/*else if (posColuna = 0 && posLinha != 0 && posLinha != 4)
	{
		if ((mapWalking[posLinha - 1][posColuna] == 0) && (mapWalking[posLinha][posColuna+1] == 0) && (mapWalking[posLinha - 1][posColuna + 1] == 0) && (mapWalking[posLinha + 1][posColuna + 1] == 0) && (mapWalking[posLinha + 1][posColuna] == 0))
		{

			vivo = false;


		}
	}*/

	if (vivo)
	{
		do_movement();
	}
	else
	{
		//std::cout << "morreu";
		telas[1]->update();
		telas[1]->draw();
		
	}
	
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

	

	float xi = 400.0;
	float yi = 100.0;

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			float x = xi + (j - i) * 160 / 2.0;
			float y = yi + (j + i) * 80 / 2.0;
			/*model = glm::mat4();
			model = glm::translate(model, glm::vec3(x, y, 0.0));*/
			tileset[map[i][j]]->setPosition(glm::vec3(x, y, 0.9f));
			tileset[map[i][j]]->update();
			tileset[map[i][j]]->draw();
			//model
		}
	}

	float xP = xi + (posColuna - posLinha) * 160 / 2.0;
	float yP = yi + (posColuna + posLinha) * 80 / 2.0;
	personagem->setPosition(glm::vec3(xP, yP+40, 1.0f));
	tileset[3]->setPosition(glm::vec3(xP, yP, 1.0f));
	tileset[3]->update();
	tileset[3]->draw();
	
	personagem->update();
	personagem->draw();


	/*
	copia funcao de cima, altera o "tileset" usado pelo player
	
	*/
	

	
	if (posColuna == 4 && posLinha == 4)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				if(mapWalking[i][j] == 1 && map[i][j]!=2)
				{
					
						ind_vitoria = false;
					
					
				}
				
			}
		}


		if (ind_vitoria)
		{
			//vitoria.setPosition(glm::vec3(400.0f,300.0f, 1.0f));
			//vitoria.setDimension(glm::vec3(800.0f, 600.0f, 1.0f));
			telas[0]->update();
			telas[0]->draw();
			
			vivo = false;
		}
		else
		{
			//derrota.setPosition(glm::vec3(400.0f, 300.0f, 1.0f));
			//derrota.setDimension(glm::vec3(800.0f, 600.0f, 1.0f));
			telas[1]->update();
			telas[1]->draw();
			
			vivo = false;
		}

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
	//Tile 0
	TileIso* tile = new TileIso(0, 80.0f, 160.0f);
	
	tile->setDimension(glm::vec3(160.0f, 80.0f, 1.0f)); //note que depois podemos reescalar conforme tamanho da sprite
	tile->setShader(shader);
	tileset.push_back(tile);

	//Tile 1

	tile = new TileIso(1, 80.0f, 160.0f);
	tile->setDimension(glm::vec3(160.0f, 80.0f, 1.0f));
	tile->setShader(shader);
	tileset.push_back(tile);
	

	//Tile 2
	
	tile = new TileIso(2, 80.0f, 160.0f);
	tile->setDimension(glm::vec3(160.0f, 80.0f, 1.0f));
	tile->setShader(shader);
	tileset.push_back(tile);

	tile = new TileIso(3, 80.0f, 160.0f);
	tile->setDimension(glm::vec3(160.0f, 80.0f, 1.0f));
	tile->setShader(shader);
	tileset.push_back(tile);

	unsigned int texID = loadTexture("../textures/TILESET.png");
	tileset[0]->setTexture(texID);
	tileset[1]->setTexture(texID);
	tileset[2]->setTexture(texID);
	tileset[3]->setTexture(texID);
	

	int mapa[5][5] =
	{  1,1,1,1,1,
	   1,1,1,1,1,
	   1,1,0,1,1,
	   1,1,1,1,1,
	   1,1,1,1,2
	};

	int mapaCaminhavel[5][5] =
	{ 1,1,1,1,1,
	  1,1,1,1,1,
	  1,1,0,1,1,
	  1,1,1,1,1,
	  1,1,1,1,1
	};

	

	posLinha = 0;
	posColuna = 0;
	dir = PARADO;
	ind_vitoria = true;
	vivo = true;
	
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			map[i][j] = mapa[i][j];
		}
	}

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			mapWalking[i][j] = mapaCaminhavel[i][j];
		}
	}
	
	//Mínimo: posicao e escala e ponteiro para o shader
	//Sprite* obj = new Sprite;
	//obj->setPosition(glm::vec3(400.0f, 300.0f, 0.0));
	//obj->setDimension(glm::vec3(400.0f, 400.0f, 1.0f)); //note que depois podemos reescalar conforme tamanho da sprite
	//obj->setShader(shader);
	//objects.push_back(obj); //adiciona o primeiro obj
	//objects[0]->setAngle(0.8f);

	////Adicionando mais um
	//obj = new Sprite;
	//obj->setPosition(glm::vec3(700.0f, 300.0f, 0.0));
	//obj->setDimension(glm::vec3(100.0f, 200.0f, 1.0f));
	//obj->setShader(shader);
	//objects.push_back(obj); //adiciona o segundo obj

	////Adicionando mais um
	//obj = new Sprite;
	//obj->setPosition(glm::vec3(0.0f, 0.0f, 0.0));
	//obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
	//obj->setShader(shader);
	//objects.push_back(obj); //adiciona o terceiro obj

	//Carregamento das texturas (pode ser feito intercalado na criação)
	//Futuramente, utilizar classe de materiais e armazenar dimensoes, etc
	//texID = loadTexture("../textures/mario.png");
	

	Sprite* tela= new Sprite;
	texID = loadTexture("../textures/Vitoria.png");
	
	tela->setPosition(glm::vec3(400.0f, 300.0f, 1.0f));
	tela->setDimension(glm::vec3(800.0f, 600.0f, 1.0f));
	tela->setShader(shader);
	
	telas.push_back(tela);

	tela = new Sprite;
	texID = loadTexture("../textures/Derrota.png");
	
	tela->setPosition(glm::vec3(400.0f, 300.0f, 1.0f));
	tela->setDimension(glm::vec3(800.0f, 600.0f, 1.0f));
	tela->setShader(shader);
	
	telas.push_back(tela);

	texID = loadTexture("../textures/Vitoria.png");
	telas[0]->setTexture(texID);

	texID = loadTexture("../textures/Derrota.png");
	telas[1]->setTexture(texID);


	texID = loadTexture("../textures/SpriteSheet_Penguin.png");
	personagem = new Personagem;
	personagem->setPosition(glm::vec3(100.0f, 100.0f, 1.0f));
	personagem->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
	personagem->setShader(shader);
	personagem->setTexture(texID);

	//objects[0]->setTexture(texID);
	
	//objects[1]->setTexture(texID);
//	objects[2]->setTexture(texID);*/

	//Definindo a janela do mundo (ortho2D)
	ortho2D[0] = 0.0f; //xMin
	ortho2D[1] = 800.0f; //xMax
	ortho2D[2] = 0.0f; //yMin
	ortho2D[3] = 600.0f; //yMax

	//Habilita transparência
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void SceneManager::setupCamera2D() //TO DO: parametrizar aqui
{
	float zNear = -1.0, zFar = 1.0; //estão fixos porque não precisamos mudar

	projection = glm::ortho(ortho2D[0], ortho2D[1], ortho2D[2], ortho2D[3], zNear, zFar);


	//Obtendo o identificador da matriz de projeção para enviar para o shader
	GLint projLoc = glGetUniformLocation(shader->ID, "projection");
	//Enviando a matriz de projeção para o shader
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
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


