#include "sampleCity.h"
#include "../samplefw/Grid2D.h"

SampleCity::~SampleCity()
{
	printf("Destroying City Sample\n");
	for(int i = 0; i < m_gridSize; i++){
		for(int j = 0; j < m_gridSize; j++){
			delete m_pBuildings[i][j];
		}
	}
	delete m_pSun;
	delete m_pSkybox;
	delete m_pPlane;
	delete m_pFreeRoamCamera;
	wolf::ProgramManager::DestroyProgram(m_pCityProgram);
}

void SampleCity::init()
{
    // Only init if not already done
    if(!m_pCityProgram)
    {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glEnable(GL_DEPTH_TEST);
		srand((unsigned int)time(NULL));

		m_pCityProgram = wolf::ProgramManager::CreateProgram("data/sampleCity.vsh", "data/sampleCity.fsh");


		if(!m_pFreeRoamCamera){
			m_pFreeRoamCamera = new FreeRoamCamera(m_pApp);
			m_pFreeRoamCamera->setPosition(glm::vec3(0.0f, 187.0f, 187.0f));
		}
		m_pSkybox = new Skybox(m_pCityProgram, m_pFreeRoamCamera, m_skyboxPath);
		
		m_pSun = new Sphere(5.0f);
		m_pSun->SetColor(glm::vec3(252.0f, 212.0f, 64.0f));

		m_pPlane = new Plane(m_pCityProgram, m_groundTexPath);
		m_pPlane->setScale(750.0f);
		
		float x, z;
		x = z = -m_pPlane->getWidth()/2;
		for(int i = 0; i < m_gridSize; i++){
			for(int j = 0; j < m_gridSize; j++){
				int ratio = rand() % 10 + 1;
				if(ratio <= 4) 	
					m_pBuildings[i][j] = new BlockyBuilding(m_pCityProgram);
				else if (ratio <= 7)    
					m_pBuildings[i][j] = new ClassicBuilding(m_pCityProgram);
				else 			   
					m_pBuildings[i][j] = new CubeBuilding(m_pCityProgram);
				
				m_pBuildings[i][j]->setPosition(glm::vec3(x, 0.0f, z));
				x += m_pBuildings[i][j]->getWidth() + rand() % 3 + 15;
			}
			x = -m_pPlane->getWidth()/2;
			z += rand() % 6 + 31;
		}
	}
	
    printf("Successfully initialized City Sample\n");
}

void SampleCity::update(float dt) 
{
	m_pFreeRoamCamera->update(dt);
	m_pSkybox->update(dt);

	// Dynamically move sun around city
	m_sunAngle += dt * m_sunSpeed;
	float sunX = 375.0f * cos(m_sunAngle), sunY = 375.0f * sin(m_sunAngle);
	m_sunDirection = glm::vec3(sunX, sunY, 125.0f);
	m_pSun->SetPosition(m_sunDirection);

	if(m_pApp->isKeyDown(R)){

		// Reset Scene (Takes a while!)

		for(int i = 0; i < m_gridSize; i++){
			for(int j = 0; j < m_gridSize; j++){
				delete m_pBuildings[i][j];
			}
		}
		delete m_pSkybox;
		delete m_pPlane;
		wolf::ProgramManager::DestroyProgram(m_pCityProgram);
		m_pCityProgram = 0;
		init();
		m_pFreeRoamCamera->setPosition(glm::vec3(0.0f, 187.0f, 187.0f)); // Reset camera to original position
		printf("Sucessfully Reset City\n");
	}

	for(int i = 0; i < m_gridSize; i++){
		for(int j = 0; j < m_gridSize; j++){
			if(_isColliding(m_pFreeRoamCamera, m_pBuildings[i][j])){
				// colliding
			}
		}
	}
}

void SampleCity::render(int width, int height)
{	
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 mProj = m_pFreeRoamCamera->getProjMatrix(width, height);
	glm::mat4 mView = m_pFreeRoamCamera->getViewMatrix();
	glm::mat4 mWorld = glm::mat4(1.0f);
	
	m_pCityProgram->SetUniform("u_lightDir", m_sunDirection);

	// Render all objects
	m_pSkybox->render(mProj,mView,width,height);
	m_pSun->Render(mWorld, mView, mProj);
	m_pPlane->render(mProj,mView,width,height);

	for(int i = 0; i < m_gridSize; i++){
		for(int j = 0; j < m_gridSize; j++){
			m_pBuildings[i][j]->render(mProj,mView,width,height);
		}
	}	
}

bool SampleCity::_isColliding(Camera* m_cam, Building* m_building){
	
	bool collisionX = m_cam->getPosition().x >= m_building->getPosition().x - m_building->getWidth()/2
				   && m_building->getPosition().x + m_building->getWidth()/2 >= m_cam->getPosition().x;
	bool collisionY = m_cam->getPosition().y >= m_building->getPosition().y - m_building->getHeight()
				   && m_building->getPosition().y + m_building->getHeight() >= m_cam->getPosition().y;
	bool collisionZ = m_cam->getPosition().z >= m_building->getPosition().z - m_building->getDepth()/2
				   && m_building->getPosition().z + m_building->getDepth()/2 >= m_cam->getPosition().z;
	
	
	return collisionX && collisionY && collisionZ;
}
