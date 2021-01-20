#include "classicBuilding.h"

/*
    Classic Tiered Buildings
                             */

const std::vector<std::string> ClassicBuilding::texturePaths = {
    "data/textures/buildings/building1.png",
    "data/textures/buildings/building2.png",
    "data/textures/buildings/building3.png",
    "data/textures/buildings/building4.png",
    "data/textures/buildings/building5.png",
    "data/textures/buildings/building6.png"
};

ClassicBuilding::~ClassicBuilding()
{
    for(int i = 0; i < numOfCubes; i++){
        delete m_pCubes[i];
    }
    delete m_pDecl;
	wolf::BufferManager::DestroyBuffer(m_pVB);
}

ClassicBuilding::ClassicBuilding(wolf::Program* m_pProgram)
               :Building(m_pProgram)
{
    this->m_pProgram = m_pProgram;
    this->m_stories = rand() % 6 + 4;
    this->m_blocks = 1;
    int index = rand() % 6;  // building front 
    numOfCubes = m_stories/2;
    float height = (float)m_stories/numOfCubes;
    float width = (float)m_blocks;
    float depth = (float)m_blocks;
    float scale = 16.0f;
    float randY = 0.0f;
    std::string texture = texturePaths[index];
    m_pCubes = new Cube*[numOfCubes];
    for(int i = 0; i < numOfCubes; i++){
        this->m_pCubes[i] = new Cube(m_pProgram, texturePaths[index]);
        this->m_pCubes[i]->setHeight(height);
        this->m_pCubes[i]->setWidth(width);
        this->m_pCubes[i]->setDepth(depth);
        this->m_pCubes[i]->setScale(scale);
        depth -= (float)m_blocks/numOfCubes;
        width -= (float)m_blocks/numOfCubes;
        this->m_pCubes[i]->setY(m_pCubes[i]->getHeight()/2 + randY);
        randY += m_pCubes[i]->getHeight()/5.0f;
   }

}

void ClassicBuilding::update(float dt){

}

void ClassicBuilding::setPosition(const glm::vec3& m_position){
    float curX = m_position.x, curZ = m_position.z;
    for(int i = 0; i < numOfCubes; i++){
        this->m_pCubes[i]->setPosition(glm::vec3(curX, m_pCubes[i]->getY(), curZ));
    }
    this->x = m_position.x;
    this->y = m_pCubes[0]->getY();
    this->z = m_position.z;
    this->m_position = glm::vec3(x,y,z);
}

glm::vec3 ClassicBuilding::getPosition() const{
    return m_position;
}
float ClassicBuilding::getX() const{
    return x;
}
float ClassicBuilding::getY() const{
    return y;
}
float ClassicBuilding::getZ() const{
    return z;
}

int ClassicBuilding::getBlocks() const {
    return m_blocks;
}

int ClassicBuilding::getStories() const {
    return m_stories;
}

float ClassicBuilding::getWidth() const {
    return m_pCubes[0]->getWidth();
}

float ClassicBuilding::getHeight() const {
    float height = m_pCubes[0]->getHeight();
    for(int i = 1; i < numOfCubes; i++){
        height += m_pCubes[i]->getHeight()/5.0f ; // Not very accurate but sufficient for now
    }
    return height;
}

float ClassicBuilding::getDepth() const {
    return m_pCubes[0]->getDepth();
}

void ClassicBuilding::render(const glm::mat4& mProj, const glm::mat4& mView, int width, int height)
{
    for(int i = 0; i < numOfCubes; i++){
        this->m_pCubes[i]->render(mProj,mView,width,height);
    }
}

