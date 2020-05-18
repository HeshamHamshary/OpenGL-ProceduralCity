#include "sampleModel.h"
#include "../samplefw/Grid2D.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void _focusOn(const glm::vec3& min, const glm::vec3& max);

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

        glm::vec3 min = m_pModel->getAABBMin();
        glm::vec3 max = m_pModel->getAABBMax();
        glm::vec3 center = m_pModel->getAABBCenter();
        _focusOn(min, max);

        float gridSize = 2.5f * wolf::max(max.x,max.z);
        m_pGrid = new Grid3D(10, gridSize / 10.0f);
    }

    printf("Successfully initialized Simple Model Sample\n");
}

float m_rotX = 0.0f;
float m_rotY = 0.0f;
float m_distance = 600.0f;
glm::vec3 m_offset(0.0f,0.0f,0.0f);
glm::vec3 m_position(0.0f,0.0f,0.0f);
glm::vec3 m_target(0.0f,0.0f,0.0f);
glm::vec3 m_focusMin(0.0f,0.0f,0.0f);
glm::vec3 m_focusMax(0.0f,0.0f,0.0f);
float m_fov = glm::radians(60.0f);
float m_near = 0.1f;
float m_far = 1000.0f;

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

float _calculateRequiredDistance() 
{
    glm::vec3 min = m_focusMin;
    glm::vec3 max = m_focusMax;
    glm::vec3 center = min + ((max - min) * 0.5f);
    float r = wolf::max(glm::distance(center,min), glm::distance(center,max));

    return (r * 2.0f) / tan(m_fov / 1.5);
}

void _focusOn(const glm::vec3& min, const glm::vec3& max) 
{
    m_focusMin = min;
    m_focusMax = max;
    m_offset = glm::vec3(0.0f,0.0f,0.0f);
    m_rotX = -MATH_PI / 4.0f;
    m_rotY = MATH_PI / 4.0f;

    m_target = min + ((max - min) * 0.5f);

    m_distance = _calculateRequiredDistance();
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

    glm::vec2 mouseScroll = m_pApp->getMouseScroll();

    if(mouseScroll.y > 0) {
        m_distance -= (m_distance / 5.0);
    } else if(mouseScroll.y < 0) {
        m_distance += (m_distance / 5.0);
    }

    m_far = m_distance * 2.0f;
    m_near = m_distance / 10.0f;

    if(m_pApp->isKeyDown('f'))
    {
        _focusOn(m_focusMin,m_focusMax);
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

	glm::mat4 mProj = glm::perspective(glm::radians(60.0f), (float)width / (float)height, m_near, m_far);
	glm::mat4 mView = _getViewMatrix();
	glm::mat4 mWorld = glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(0.0f, 1.0f, 0.0f));

    m_pGrid->render(mView, mProj);
    m_pModel->Render(mWorld, mView, mProj);
}

