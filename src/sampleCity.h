#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"
#include "../samplefw/FreeRoamCamera.h"
#include "../samplefw/Skybox.h"
#include "../samplefw/Sphere.h"
#include "plane.h"
#include "classicBuilding.h"
#include "blockyBuilding.h"
#include "cubeBuilding.h"

#define R 82

class SampleCity: public Sample
{
public:
    SampleCity(wolf::App* pApp) : Sample(pApp,"Generating City Sample") {}
    ~SampleCity();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    bool _isColliding(Camera* m_cam, Building* m_building);

    const std::string m_skyboxPath      = "data/textures/skybox/skybox.png";
    const std::string m_groundTexPath   = "data/textures/ground/ground.png";
    wolf::Program* m_pCityProgram       = 0;

    bool reset                          = false;
    const int m_gridSize                = 20;

    float m_sunSpeed                    = 0.01f;
    GLfloat m_sunAngle                  = -100;
    glm::vec3 m_sunDirection            = glm::vec3(375.0f, 375.0f, 125.0f);

    Skybox* m_pSkybox                   = 0;
    FreeRoamCamera* m_pFreeRoamCamera   = 0;
    Plane* m_pPlane                     = 0;
    Building* m_pBuildings[20][20];
    Sphere* m_pSun                      = 0;
};