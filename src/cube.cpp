#include "cube.h"

const Vertex Cube::gs_skyboxCubeVertices[36] = {
    // Front
    { -0.5f, -0.5f, 0.5f, 0.25f, 0.33333333333f, 0.0f, 0.0f, 1.0f},
    { -0.5f,  0.5f, 0.5f, 0.25f, 0.66666666666f, 0.0f, 0.0f, 1.0f},
    {  0.5f,  0.5f, 0.5f, 0.5f, 0.66666666666f,  0.0f, 0.0f, 1.0f},
    {  0.5f,  0.5f, 0.5f, 0.5f, 0.66666666666f,  0.0f, 0.0f, 1.0f},
    {  0.5f, -0.5f, 0.5f, 0.5f, 0.33333333333f,  0.0f, 0.0f, 1.0f},
    { -0.5f, -0.5f, 0.5f, 0.25f, 0.33333333333f, 0.0f, 0.0f, 1.0f},

    // Back
    {  0.5f,  0.5f,-0.5f, 0.75f, 0.66666666666f, 0.0f, 0.0f, -1.0f},
    { -0.5f,  0.5f,-0.5f, 1.0f, 0.66666666666f,  0.0f, 0.0f, -1.0f},
    { -0.5f, -0.5f,-0.5f, 1.0f, 0.33333333333f,  0.0f, 0.0f, -1.0f},
    { -0.5f, -0.5f,-0.5f, 1.0f, 0.33333333333f,  0.0f, 0.0f, -1.0f},
    {  0.5f, -0.5f,-0.5f, 0.75f, 0.33333333333f, 0.0f, 0.0f, -1.0f},
    {  0.5f,  0.5f,-0.5f, 0.75f, 0.66666666666f, 0.0f, 0.0f, -1.0f},

    // Left
    { -0.5f,  0.5f,-0.5f, 0.0f, 0.66666666666f,  -1.0f, 0.0f, 0.0f},
    { -0.5f,  0.5f, 0.5f, 0.25f, 0.66666666666f, -1.0f, 0.0f, 0.0f},
    { -0.5f, -0.5f, 0.5f, 0.25f, 0.33333333333f, -1.0f, 0.0f, 0.0f},
    { -0.5f, -0.5f, 0.5f, 0.25f, 0.33333333333f, -1.0f, 0.0f, 0.0f},
    { -0.5f, -0.5f,-0.5f, 0.0f, 0.33333333333f,  -1.0f, 0.0f, 0.0f},
    { -0.5f,  0.5f,-0.5f, 0.0f, 0.66666666666f,  -1.0f, 0.0f, 0.0f},

    // Right
    {  0.5f,  0.5f, 0.5f, 0.5f, 0.66666666666f,  1.0f, 0.0f, 0.0f},
    {  0.5f,  0.5f,-0.5f, 0.75f, 0.66666666666f, 1.0f, 0.0f, 0.0f},
    {  0.5f, -0.5f,-0.5f, 0.75f, 0.33333333333f, 1.0f, 0.0f, 0.0f},
    {  0.5f, -0.5f,-0.5f, 0.75f, 0.33333333333f, 1.0f, 0.0f, 0.0f},
    {  0.5f, -0.5f, 0.5f, 0.5f, 0.33333333333f,  1.0f, 0.0f, 0.0f},
    {  0.5f,  0.5f, 0.5f, 0.5f, 0.66666666666f,  1.0f, 0.0f, 0.0f},

    // Top
    { -0.5f,  0.5f, 0.5f, 0.25f, 0.66666666666f, 0.0f, 1.0f, 0.0f},
    { -0.5f,  0.5f,-0.5f, 0.25f, 1.0f, 0.0f, 1.0f, 0.0f},
    {  0.5f,  0.5f,-0.5f, 0.5f, 0.66666666666f, 0.0f, 1.0f, 0.0f},
    {  0.5f,  0.5f,-0.5f, 0.5f, 0.66666666666f, 0.0f, 1.0f, 0.0f},
    {  0.5f,  0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f},
    { -0.5f,  0.5f, 0.5f, 0.25f, 0.66666666666f, 0.0f, 1.0f, 0.0f},

    // Bottom
    { -0.5f, -0.5f, 0.5f, 0.25f, 0.33333333333f, 0.0f, -1.0f, 0.0f},
    {  0.5f, -0.5f, 0.5f, 0.5f, 0.33333333333f, 0.0f, -1.0f, 0.0f},
    {  0.5f, -0.5f,-0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f},
    {  0.5f, -0.5f,-0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f},
    { -0.5f, -0.5f,-0.5f, 0.25f, 0.0f, 0.0f, -1.0f, 0.0f},
    { -0.5f, -0.5f, 0.5f, 0.25f, 0.33333333333f, 0.0f, -1.0f, 0.0f},
};
const Vertex Cube::gs_cubeVertices[36]= {
    // Front
    { -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
    {  0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
    {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    { -0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    { -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},

    // Back
    {  0.5f,  0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f},
    {  0.5f, -0.5f,-0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
    { -0.5f, -0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f},
    { -0.5f, -0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f},
    { -0.5f,  0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f},
    {  0.5f,  0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f},

    // Left
    { -0.5f,  0.5f,-0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f},
    { -0.5f, -0.5f,-0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f},
    { -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f},
    { -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f},
    { -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
    { -0.5f,  0.5f,-0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f},

    // Right
    {  0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},
    {  0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
    {  0.5f, -0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f},
    {  0.5f, -0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f},
    {  0.5f,  0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
    {  0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},

    // Top
    { -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
    {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
    {  0.5f,  0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
    {  0.5f,  0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
    { -0.5f,  0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
    { -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},

    // Bottom
    { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f},
    { -0.5f, -0.5f,-0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f},
    {  0.5f, -0.5f,-0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f},
    {  0.5f, -0.5f,-0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f},
    {  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f},
    { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f},
};

Cube::~Cube()
{
    delete m_pDecl;
	wolf::BufferManager::DestroyBuffer(m_pVB);
    if(m_pTexture) wolf::TextureManager::DestroyTexture(m_pTexture);
}

Cube::Cube(wolf::Program* m_pProgram, const std::string& texturePath, bool isSkybox) 
     : Shape(m_pProgram, texturePath)
{
    this->m_pProgram = m_pProgram;
    this->isSkybox = isSkybox;
    m_pVB = isSkybox ? wolf::BufferManager::CreateVertexBuffer(gs_skyboxCubeVertices, sizeof(Vertex) * 6 *3 *2)
                     : wolf::BufferManager::CreateVertexBuffer(gs_cubeVertices, sizeof(Vertex) * 6 *3 *2);
 
    m_pTexture = wolf::TextureManager::CreateTexture(texturePath);

    m_pDecl = new wolf::VertexDeclaration();
    m_pDecl->Begin();
    m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
    m_pDecl->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);
    m_pDecl->SetVertexBuffer(m_pVB);
    m_pDecl->End();
}

void Cube::update(float dt){

}

void Cube::setPosition(const glm::vec3& position){
    this->m_position = position;
    this->x = m_position.x;
    this->y = m_position.y;
    this->z = m_position.z;
}

void Cube::setX(float x){
    this->x = x;
};
void Cube::setY(float y){
    this->y = y;
};
void Cube::setZ(float z){
    this->z = z;
};

void Cube::setScale(float scale){
    this->m_height *= scale;
    this->m_width *= scale;
    this->m_depth *= scale;
}

glm::vec3 Cube::getPosition() const{
    return m_position;
}

void Cube::setHeight(float height){
    this->m_height = height;
}

void Cube::setWidth(float width){
    this->m_width = width;
}

void Cube::setDepth(float depth){
    this->m_depth = depth;
}

float Cube::getHeight() const{
    return m_height;
}

float Cube::getWidth() const{
    return m_width;
}

float Cube::getDepth() const{
    return m_depth;
}

float Cube::getX() const{
    return x;
}
float Cube::getY() const{
    return y;
}
float Cube::getZ() const{
    return z;
}

void Cube::render(const glm::mat4& mProj, const glm::mat4& mView, int width, int height)
{
    m_position = glm::vec3(x,y,z);
    glm::mat4 mWorld = glm::translate(glm::mat4(1.0f), m_position);
    mWorld*= glm::scale(glm::mat4(1.0f), glm::vec3(m_width, m_height, m_depth));
    if(m_pTexture){
    m_pTexture->SetFilterMode(wolf::Texture::FM_TrilinearMipmap, wolf::Texture::FM_TrilinearMipmap);
    m_pTexture->Bind();
    }
    

	// Bind Uniforms
    m_pProgram->SetUniform("projection", mProj);
    m_pProgram->SetUniform("view", mView);
    m_pProgram->SetUniform("world", mWorld);
    m_pProgram->SetUniform("worldIT", glm::transpose(glm::inverse(mWorld)));
    if(m_pTexture)m_pProgram->SetUniform("u_tex", 0);
    if(isSkybox){
        m_pProgram->SetUniform("u_lightColor", glm::vec3(0.02f, 0.02f, 0.02f));
	    m_pProgram->SetUniform("u_ambientLight", glm::vec3(1.0f, 1.0f, 1.0f));
    } else {
        m_pProgram->SetUniform("u_lightColor", glm::vec3(0.05f, 0.05f, 0.05f));
	    m_pProgram->SetUniform("u_ambientLight", glm::vec3(0.2f, 0.2f, 0.2f));
    }
    
    // Use Shader Program
    m_pProgram->Bind();

	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6 * 3 * 2);
}