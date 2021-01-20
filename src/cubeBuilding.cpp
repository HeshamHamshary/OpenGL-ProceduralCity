#include "cubeBuilding.h"

/*
    Classic Tiered Buildings
                             */

const std::vector<std::string> CubeBuilding::texturePaths = {
    "data/textures/buildings/building1.png",
    "data/textures/buildings/building2.png",
    "data/textures/buildings/building3.png",
    "data/textures/buildings/building4.png",
    "data/textures/buildings/building5.png",
    "data/textures/buildings/residential.png",
    "data/textures/buildings/warehouse.png",
    "data/textures/buildings/shop1.png",
    "data/textures/buildings/shop2.png",
    "data/textures/buildings/shop3.png",
    "data/textures/buildings/shop4.png",
    "data/textures/buildings/shop5.png",
};

CubeBuilding::~CubeBuilding()
{
    delete m_pCube;
    delete m_pDecl;
	wolf::BufferManager::DestroyBuffer(m_pVB);
}

CubeBuilding::CubeBuilding(wolf::Program* m_pProgram)
               :Building(m_pProgram)
{
    this->m_pProgram = m_pProgram;
    this->m_stories = rand() % 3 + 1;
    this->m_blocks = 1;
    int index = (m_stories == 1) ? rand() % 5 + 7 // shop front
                                 : rand() % 7;  // building front
    float scale = 16.0f;
    std::string texture = texturePaths[index];
    m_pCube = new Cube(m_pProgram, texturePaths[index]);
    m_pCube->setHeight((float)m_stories);
    m_pCube->setWidth((float)m_blocks);
    m_pCube->setDepth((float)m_blocks);
    m_pCube->setY(m_pCube->getHeight()/2);
    m_pCube->setScale(scale);
}

void CubeBuilding::update(float dt){

}

void CubeBuilding::setPosition(const glm::vec3& m_position){
    this->x = m_position.x;
    this->y = m_pCube->getHeight()/2;
    this->z = m_position.z;
    this->m_position = glm::vec3(x,y,z);
    m_pCube->setPosition(this->m_position);
}

glm::vec3 CubeBuilding::getPosition() const{
    return m_position;
}
float CubeBuilding::getX() const{
    return x;
}
float CubeBuilding::getY() const{
    return y;
}
float CubeBuilding::getZ() const{
    return z;
}

int CubeBuilding::getBlocks() const {
    return m_blocks;
}

int CubeBuilding::getStories() const {
    return m_stories;
}

float CubeBuilding::getWidth() const {
    return m_pCube->getWidth();
}

float CubeBuilding::getHeight() const {
    return m_pCube->getHeight();
}

float CubeBuilding::getDepth() const {
    return m_pCube->getDepth();
}

void CubeBuilding::render(const glm::mat4& mProj, const glm::mat4& mView, int width, int height)
{
    m_pCube->render(mProj,mView,width,height);
}

