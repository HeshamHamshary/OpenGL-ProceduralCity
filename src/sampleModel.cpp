#include "sampleModel.h"
#include "../samplefw/Grid2D.h"
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
	printf("Destroying Texture Format 4444 Sample\n");
    wolf::MaterialManager::DestroyMaterial(m_pMat);
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

        m_pGrid = new Grid3D(200.0f);
    }

    printf("Successfully initialized Simple Model Sample\n");
}

float m_rotX = 0.0f;
float m_rotY = 0.0f;
float m_distance = 600.0f;
glm::vec3 m_offset(0.0f,0.0f,0.0f);
glm::vec3 m_position(0.0f,0.0f,0.0f);
glm::vec3 m_target(0.0f,0.0f,0.0f);

void _rotate(const glm::vec2& mouseMovement)
{
    m_rotX -= mouseMovement.y * 0.003f;
    m_rotY -= mouseMovement.x * 0.003f;
}

glm::vec3 _getCameraSide()
{
    glm::vec3 dir = m_target - m_position;
    glm::vec3 side = glm::cross(dir, glm::vec3(0.0f,1.0f,0.0f));
    return glm::normalize(side);
}

glm::vec3 _getCameraUp()
{
    glm::vec3 dir = m_target - m_position;
    glm::vec3 v = _getCameraSide();
    v = glm::cross(dir, v);
    return glm::normalize(v);
}

void _pan(const glm::vec2& mouseMovement)
{
    glm::vec3 side = _getCameraSide();
    glm::vec3 up = _getCameraUp();

    side = side * -mouseMovement[0] * 0.007f * (m_distance / 5.0f);
    up = up * -mouseMovement[1] * 0.007f * (m_distance / 5.0f);

    m_offset += side;
    m_offset += up;
}

void SampleModel::update(float dt) 
{
    glm::vec2 mousePos = m_pApp->getMousePos();
    static glm::vec2 lastMousePos = mousePos;

    if(m_pApp->isLMBDown())
    {
        glm::vec2 mouseMovement = mousePos - lastMousePos;
        _rotate(mouseMovement);
    }
    else if(m_pApp->isMMBDown())
    {
        glm::vec2 mouseMovement = mousePos - lastMousePos;
        _pan(mouseMovement);
    }

    lastMousePos = mousePos;

    m_pGrid->update(dt);
}

glm::mat4 _getViewMatrix() 
{
    glm::mat4 m(1.0f);
    m = glm::rotate(m_rotY, glm::vec3(0.0f,1.0f,0.0f));
    m = m * glm::rotate(m_rotX, glm::vec3(1.0f,0.0f,0.0f));

    m_position = m * glm::vec4(0.0f,0.0f,m_distance,1.0f);
    glm::vec3 up = m * glm::vec4(0.0f,1.0f,0.0f,1.0f);

    glm::vec3 pos = m_position + m_offset;

    glm::vec3 target = m_target + m_offset;

    return glm::lookAt(pos, target, up);
}

void SampleModel::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 mProj = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 1000.0f);
	glm::mat4 mView = _getViewMatrix();//glm::lookAt(glm::vec3(0.0f,150.0f,400.0f), glm::vec3(0.0f,100.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 mWorld = glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(0.0f, 1.0f, 0.0f));

    m_pGrid->render(mView, mProj);
    m_pModel->Render(mWorld, mView, mProj);
}

