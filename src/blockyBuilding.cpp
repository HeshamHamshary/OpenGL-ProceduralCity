#include "blockyBuilding.h"

/*
    Blocky Skyscrapers
                       */

const std::vector<std::string> BlockyBuilding::texturePaths = {
    "data/textures/buildings/skyscraper1.png",
    "data/textures/buildings/skyscraper2.png",
    "data/textures/buildings/skyscraper3.png",
    "data/textures/buildings/skyscraper4.png",
    "data/textures/buildings/skyscraper5.png",
};

BlockyBuilding::~BlockyBuilding()
{
    for(int i = 0; i < numOfCubes; i++){
        delete m_pCubes[i];
    }
    delete m_pDecl;
	wolf::BufferManager::DestroyBuffer(m_pVB);
}

BlockyBuilding::BlockyBuilding(wolf::Program* m_pProgram)
               :Building(m_pProgram)
{
    this->m_pProgram = m_pProgram;
    this->m_stories = rand() % 6 + 4;
    this->m_blocks = 1;
    int index = rand() % 5;  // skyscraper front 
    numOfCubes = m_stories/2;
    float height = (float)m_stories;
    float width = (float)m_blocks;
    float depth = (float)m_blocks;
    float scale = 16.0f;
    float curX = 0.0f;
    float curZ = 0.0f;
    std::string texture = texturePaths[index];
    m_pCubes = new Cube*[numOfCubes];
    for(int i = 0; i < numOfCubes; i++){
        this->m_pCubes[i] = new Cube(m_pProgram, texturePaths[index]);
        this->m_pCubes[i]->setHeight(height);
        this->m_pCubes[i]->setWidth(width);
        this->m_pCubes[i]->setDepth(depth);
        this->m_pCubes[i]->setScale(scale);
        height -= m_stories/numOfCubes;
        depth -= m_blocks/numOfCubes;
        width -= m_blocks/numOfCubes;
        this->m_pCubes[i]->setX((float)curX);
        this->m_pCubes[i]->setZ((float)curZ);
        this->m_pCubes[i]->setY(m_pCubes[i]->getHeight()/2);
        
        // Generate random float for X and Z positions
        curX = -((width * scale)/2) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(( width * scale )/2 + ((width * scale)/2))));
        curZ = -((depth * scale)/2) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(( depth * scale )/2 + ((depth * scale)/2))));
    }

}

void BlockyBuilding::update(float dt){

}

void BlockyBuilding::setPosition(const glm::vec3& m_position){
    float curX = m_position.x, curZ = m_position.z;
    float prevX = m_pCubes[0]->getX(), prevZ = m_pCubes[0]->getZ();
    this->m_pCubes[0]->setPosition(glm::vec3(curX, m_pCubes[0]->getY(), curZ));
    for(int i = 1; i < numOfCubes; i++){
        // Align building parts based on their previous positions
        curX = (m_pCubes[i]->getX() < prevX) ? m_pCubes[0]->getX() - m_pCubes[i]->getX() 
                                             : m_pCubes[0]->getX() + m_pCubes[i]->getX(); 
        curZ = (m_pCubes[i]->getZ() < prevZ) ? m_pCubes[0]->getZ() - m_pCubes[i]->getZ() 
                                             : m_pCubes[0]->getZ() + m_pCubes[i]->getZ(); 
        m_pCubes[i]->setPosition(glm::vec3(curX, m_pCubes[i]->getY(), curZ));
    }
    this->x = m_position.x;
    this->y = m_pCubes[0]->getY();
    this->z = m_position.z;
    this->m_position = glm::vec3(x,y,z);
}

glm::vec3 BlockyBuilding::getPosition() const{
    return m_position;
}
float BlockyBuilding::getX() const{
    return x;
}
float BlockyBuilding::getY() const{
    return y;
}
float BlockyBuilding::getZ() const{
    return z;
}

int BlockyBuilding::getBlocks() const {
    return m_blocks;
}

int BlockyBuilding::getStories() const {
    return m_stories;
}

float BlockyBuilding::getWidth() const {
    float width = m_pCubes[0]->getWidth();
    for(int i = 1; i < numOfCubes; i++){
        if(m_pCubes[i]->getX() != m_pCubes[0]->getX()){
            width += m_pCubes[0]->getWidth() - m_pCubes[i]->getWidth();
        }
    }
    return width;
}

float BlockyBuilding::getHeight() const {
    return m_pCubes[0]->getHeight();
}

float BlockyBuilding::getDepth() const {
    return m_pCubes[0]->getDepth();
}

void BlockyBuilding::render(const glm::mat4& mProj, const glm::mat4& mView, int width, int height)
{
    for(int i = 0; i < numOfCubes; i++){
        this->m_pCubes[i]->render(mProj,mView,width,height);
    }
}

