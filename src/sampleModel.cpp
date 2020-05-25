#include "sampleModel.h"

SampleModel::~SampleModel()
{
	printf("Destroying Model Import Sample\n");
    wolf::MaterialManager::DestroyMaterial(m_pMat);
    delete m_pModel;
    delete m_pGrid;
    delete m_pOrbitCam;
}

void SampleModel::init()
{
	// Only init if not already done
    if(!m_pModel)
    {
        m_pModel = new wolf::Model("data/unreal.fbx");

        glm::vec3 min = m_pModel->getAABBMin();
        glm::vec3 max = m_pModel->getAABBMax();
        glm::vec3 center = m_pModel->getAABBCenter();

        m_pOrbitCam = new OrbitCamera(m_pApp);
        m_pOrbitCam->focusOn(min,max);

        float gridSize = 2.5f * wolf::max(max.x,max.z);
        m_pGrid = new Grid3D(10, gridSize / 10.0f);
        m_pGrid->hideAxes();
    }

    printf("Successfully initialized Model Import Sample\n");
}

void SampleModel::update(float dt) 
{
    m_pOrbitCam->update(dt);
    m_pGrid->update(dt);
}

void SampleModel::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 mProj = m_pOrbitCam->getProjMatrix(width, height);
	glm::mat4 mView = m_pOrbitCam->getViewMatrix();
	glm::mat4 mWorld = glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(0.0f, 1.0f, 0.0f));

    m_pGrid->render(mView, mProj);
    m_pModel->Render(mWorld, mView, mProj);
}

