#include "../samplefw/Grid2D.h"
#include "plane.h"

const Vertex Plane::gs_planeVertices[6] = {
    { -0.5f, 0.0f, 0.5f, 0, 3,  0.0f, 1.0f, 0.0f},
    {  0.5f, 0.0f, 0.5f, 3, 3,  0.0f, 1.0f, 0.0f},
    {  0.5f, 0.0f, -0.5f, 3, 0, 0.0f, 1.0f, 0.0f},
    {  0.5f, 0.0f, -0.5f, 3, 0, 0.0f, 1.0f, 0.0f},
    { -0.5f, 0.0f, -0.5f, 0, 0, 0.0f, 1.0f, 0.0f},
    { -0.5f, 0.0f, 0.5f, 0, 3,  0.0f, 1.0f, 0.0f},
};

Plane::~Plane()
{
	delete m_pDecl;
	wolf::BufferManager::DestroyBuffer(m_pVB);
    wolf::TextureManager::DestroyTexture(m_pTexture);
}

Plane::Plane(wolf::Program* m_pProgram, const std::string& texturePath)
      :Shape(m_pProgram, texturePath)
{
    this->m_pProgram = m_pProgram;

    m_pVB = wolf::BufferManager::CreateVertexBuffer(gs_planeVertices, sizeof(Vertex) * 6);
    m_pTexture = wolf::TextureManager::CreateTexture(texturePath);

    m_pDecl = new wolf::VertexDeclaration();
    m_pDecl->Begin();
    m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
    m_pDecl->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);
    m_pDecl->SetVertexBuffer(m_pVB);
    m_pDecl->End();
}

void Plane::update(float dt) 
{
}

void Plane::setPosition(const glm::vec3& position){
    this->m_position = position;
    this->x = m_position.x;
    this->y = m_position.y;
    this->z = m_position.z;
}

void Plane::setScale(float scale){
    this->m_height *= scale;
    this->m_width *= scale;
    this->m_depth *= scale;
}

glm::vec3 Plane::getPosition() const{
    return m_position;
}

void Plane::setHeight(float height){
    this->m_height = height;
}

void Plane::setWidth(float width){
    this->m_width = width;
}

void Plane::setDepth(float depth){
    this->m_depth = depth;
}

void Plane::setX(float x){
    this->x = x;
};
void Plane::setY(float y){
    this->y = y;
};
void Plane::setZ(float z){
    this->z = z;
};

float Plane::getHeight() const{
    return m_height;
}

float Plane::getWidth() const{
    return m_width;
}

float Plane::getDepth() const{
    return m_depth;
}

float Plane::getX() const{
    return x;
}
float Plane::getY() const{
    return y;
}
float Plane::getZ() const{
    return z;
}

void Plane::render(const glm::mat4& mProj, const glm::mat4& mView, int width, int height){
    m_position = glm::vec3(x,y,z);
    glm::mat4 mWorld = glm::translate(glm::mat4(1.0f), m_position);
    mWorld*= glm::scale(glm::mat4(1.0f), glm::vec3(m_width, m_height, m_depth));    
    
    // Use Texture
    m_pTexture->SetFilterMode(wolf::Texture::FM_TrilinearMipmap, wolf::Texture::FM_TrilinearMipmap);
    m_pTexture->SetWrapMode(wolf::Texture::WM_Repeat);
    m_pTexture->Bind();

	// Bind Uniforms
    m_pProgram->SetUniform("projection", mProj);
    m_pProgram->SetUniform("view", mView);
    m_pProgram->SetUniform("world", mWorld);
    m_pProgram->SetUniform("worldIT", glm::transpose(glm::inverse(mWorld)));
    m_pProgram->SetUniform("u_tex", 0);
    m_pProgram->SetUniform("u_lightColor", glm::vec3(0.4f, 0.4f, 0.4f));
    m_pProgram->SetUniform("u_ambientLight", glm::vec3(0.3f, 0.3f, 0.3f));
    
    // Use Shader Program
    m_pProgram->Bind();

	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
