#include "sampleModel.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class SingleMaterialProvider : public wolf::Model::MaterialProvider
{
public:
    SingleMaterialProvider(const std::string& matName) : m_matName(matName) { }

    wolf::Material* getMaterial(int meshIndex, const std::string& matName) const override
    {
        // Regardless of what mesh index or mat name the model wants, we just
        // use the mat we were seeded with. Note that we create a new one each
        // time so the DestroyMaterial calls line up. This could be improved.
        return wolf::MaterialManager::CreateMaterial(m_matName);
    }

private:
    std::string m_matName;
};

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
        wolf::Material* pMat = wolf::MaterialManager::CreateMaterial("mesh");
        pMat->SetProgram("data/cube.vsh", "data/cube.fsh");
        pMat->SetDepthTest(true);
        pMat->SetDepthWrite(true);
        pMat->SetUniform("albedo", glm::vec4(0.4f,0.8f,0.3f,1.0f));

        SingleMaterialProvider matProvider("mesh");
        m_pModel = new wolf::Model("data/unreal.fbx", matProvider);

        glm::vec3 min = m_pModel->getAABBMin();
        glm::vec3 max = m_pModel->getAABBMax();
        glm::vec3 center = m_pModel->getAABBCenter();

        m_pOrbitCam = new OrbitCamera(m_pApp);
        m_pOrbitCam->focusOn(min,max);

        float gridSize = 2.5f * wolf::max(max.x,max.z);
        m_pGrid = new Grid3D(10, gridSize / 10.0f);
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

