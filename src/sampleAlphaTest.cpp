#include "sampleAlphaTest.h"
#include "../samplefw/Grid2D.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class SingleMaterialProvider : public wolf::Model::MaterialProvider
{
public:
    SingleMaterialProvider(wolf::Material* pMat) : m_pMat(pMat) { }

    wolf::Material* getMaterial(int meshIndex, const std::string& matName) const override
    {
        return m_pMat;
    }

private:
    wolf::Material* m_pMat;
};

SampleAlphaTest::~SampleAlphaTest()
{
	printf("Destroying Texture Format 4444 Sample\n");
}

void SampleAlphaTest::init()
{
	// Only init if not already done
    if(!m_pProgram)
    {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

        wolf::Material* pMat = wolf::MaterialManager::CreateMaterial("mesh");
        pMat->SetProgram("data/cube.vsh", "data/cube.fsh");
        pMat->SetDepthTest(true);
        pMat->SetDepthWrite(true);
        pMat->SetUniform("albedo", glm::vec4(0.4f,0.8f,0.3f,1.0f));

        SingleMaterialProvider matProvider(pMat);
        m_pModel = new wolf::Model("data/unreal.fbx", matProvider);
    }

    printf("Successfully initialized Clamp to Edge Sample\n");
}

void SampleAlphaTest::update(float dt) 
{
    m_rot += dt;
}

void SampleAlphaTest::render(int width, int height)
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 mProj = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f,150.0f,400.0f), glm::vec3(0.0f,100.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 mWorld = glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(0.0f, 1.0f, 0.0f));

    m_pModel->Render(mWorld, mView, mProj);
}

