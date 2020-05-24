#include "sampleMultiModel.h"

class RandomMaterialProvider : public wolf::Model::MaterialProvider
{
public:
    RandomMaterialProvider() : m_matNames() { }
    void addMaterial(const std::string& name) { m_matNames.push_back(name); }

    wolf::Material* getMaterial(const std::string& nodeName, int subMeshIndex, const std::string& name) const override
    {
        // Regardless of what mesh index or mat name the model wants, we just
        // use a random mat from the list we were seeded with. 
        // Note that we create a new one each time so the DestroyMaterial 
        // calls line up. This could be improved, but they do share shaders.
        int choice = rand() % m_matNames.size();
        return nullptr;//wolf::MaterialManager::CreateMaterial(m_matNames[choice]);
    }

private:
    std::vector<std::string> m_matNames;
};

SampleMultiModel::~SampleMultiModel()
{
	printf("Destroying Model with Multiple Nodes Sample\n");
    wolf::MaterialManager::DestroyMaterial(m_pMat);
    delete m_pModel;
    delete m_pGrid;
    delete m_pOrbitCam;
}

void SampleMultiModel::init()
{
    srand(time(nullptr));

	// Only init if not already done
    if(!m_pModel)
    {
        RandomMaterialProvider matProvider;

        for(int i = 0; i < 5; i++)
        {
            std::string name = std::string("mesh") + std::to_string(i);
            wolf::Material *pMat = wolf::MaterialManager::CreateMaterial(name);
            pMat->SetProgram("data/mesh.vsh", "data/mesh.fsh");
            pMat->SetDepthTest(true);
            pMat->SetDepthWrite(true);
            pMat->SetUniform("albedo", glm::vec4(wolf::randFloat(), wolf::randFloat(), wolf::randFloat(), 1.0f));

            matProvider.addMaterial(name);
        }

        m_pModel = new wolf::Model("data/scene.fbx", matProvider);

        glm::vec3 min = m_pModel->getAABBMin();
        glm::vec3 max = m_pModel->getAABBMax();
        glm::vec3 center = m_pModel->getAABBCenter();

        m_pOrbitCam = new OrbitCamera(m_pApp);
        m_pOrbitCam->focusOn(min,max);

        float gridSize = 2.5f * wolf::max(max.x,max.z);
        m_pGrid = new Grid3D(10, gridSize / 10.0f);
        m_pGrid->hideAxes();
    }

    printf("Successfully initialized Model with Multiple Nodes Sample\n");
}

void SampleMultiModel::update(float dt) 
{
    m_pOrbitCam->update(dt);
    m_pGrid->update(dt);
}

void SampleMultiModel::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 mProj = m_pOrbitCam->getProjMatrix(width, height);
	glm::mat4 mView = m_pOrbitCam->getViewMatrix();
	glm::mat4 mWorld = glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(0.0f, 1.0f, 0.0f));

    m_pGrid->render(mView, mProj);
    m_pModel->Render(mWorld, mView, mProj);
}


