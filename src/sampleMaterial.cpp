#include "sampleMaterial.h"
#include "../samplefw/Grid2D.h"

struct Vertex
{
	GLfloat x,y,z;
	GLfloat u,v;
};

static const Vertex gs_cubeVertices[] = 
{
	// Front
	{ -0.5f, -0.5f, 0.5f,		0.0f, 0.0f },
	{ -0.5f,  0.5f, 0.5f,		0.0f, 1.0f },
	{  0.5f,  0.5f, 0.5f,		1.0f, 1.0f },
	{  0.5f,  0.5f, 0.5f,		1.0f, 1.0f },
	{  0.5f, -0.5f, 0.5f,		1.0f, 0.0f },
	{ -0.5f, -0.5f, 0.5f,		0.0f, 0.0f },

	// Back
	{  0.5f,  0.5f,-0.5f,		0.0f, 0.0f },
	{ -0.5f,  0.5f,-0.5f,		0.0f, 1.0f },
	{ -0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
	{ -0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
	{  0.5f, -0.5f,-0.5f,		1.0f, 0.0f },
	{  0.5f,  0.5f,-0.5f,		0.0f, 0.0f },

	// Left
	{ -0.5f,  0.5f,-0.5f,		0.0f, 0.0f },
	{ -0.5f,  0.5f, 0.5f,		0.0f, 1.0f },
	{ -0.5f, -0.5f, 0.5f,		1.0f, 1.0f },
	{ -0.5f, -0.5f, 0.5f,		1.0f, 1.0f },
	{ -0.5f, -0.5f,-0.5f,		1.0f, 0.0f },
	{ -0.5f,  0.5f,-0.5f,		0.0f, 0.0f },

	// Right
	{  0.5f,  0.5f, 0.5f,		0.0f, 0.0f },
	{  0.5f,  0.5f,-0.5f,		0.0f, 1.0f },
	{  0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
	{  0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
	{  0.5f, -0.5f, 0.5f,		1.0f, 0.0f },
	{  0.5f,  0.5f, 0.5f,		0.0f, 0.0f },

	// Top
	{ -0.5f,  0.5f, 0.5f,		0.0f, 0.0f },
	{ -0.5f,  0.5f,-0.5f,		0.0f, 1.0f },
	{  0.5f,  0.5f,-0.5f,		1.0f, 1.0f },
	{  0.5f,  0.5f,-0.5f,		1.0f, 1.0f },
	{  0.5f,  0.5f, 0.5f,		1.0f, 0.0f },
	{ -0.5f,  0.5f, 0.5f,		0.0f, 0.0f },

	// Bottom
	{ -0.5f, -0.5f, 0.5f,		0.0f, 0.0f },
	{  0.5f, -0.5f, 0.5f,		0.0f, 1.0f },
	{  0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
	{  0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
	{ -0.5f, -0.5f,-0.5f,		1.0f, 0.0f },
	{ -0.5f, -0.5f, 0.5f,		0.0f, 0.0f },
};

SampleMaterial::~SampleMaterial()
{
	printf("Destroying Wolf Material Sample\n");
	delete m_pDecl;
	wolf::MaterialManager::DestroyMaterial(m_pLeftMat);
	wolf::MaterialManager::DestroyMaterial(m_pRightMat);
	wolf::BufferManager::DestroyBuffer(m_pVB);
}

void SampleMaterial::init()
{
	// Only init if not already done
    if(!m_pDecl)
    {
		glEnable(GL_DEPTH_TEST);

		m_pVB = wolf::BufferManager::CreateVertexBuffer(gs_cubeVertices, sizeof(Vertex) * 6 * 3 * 2);

		m_pDecl = new wolf::VertexDeclaration();
		m_pDecl->Begin();
		m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
		m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
		m_pDecl->SetVertexBuffer(m_pVB);
		m_pDecl->End();

		m_pLeftMat = wolf::MaterialManager::CreateMaterial("Left");
		m_pLeftMat->SetProgram("data/cube_tex.vsh", "data/cube_tex.fsh");
		m_pLeftMat->SetUniform("fade", 0.5f);
		m_pLeftMat->SetBlend(true);
		m_pLeftMat->SetBlendMode(wolf::BM_SrcAlpha, wolf::BM_OneMinusSrcAlpha);
		m_pLeftMat->SetTexture("texture", wolf::TextureManager::CreateTexture("data/brick.dds"));

		m_pRightMat = wolf::MaterialManager::CreateMaterial("Right");
		m_pRightMat->SetProgram("data/cube_tex.vsh", "data/cube_tex.fsh");
		m_pRightMat->SetUniform("fade", 0.7f);
		m_pRightMat->SetBlend(true);
		m_pRightMat->SetBlendMode(wolf::BM_SrcAlpha, wolf::BM_One);
		m_pRightMat->SetTexture("texture", wolf::TextureManager::CreateTexture("data/metal.dds"));
	}

    printf("Successfully initialized Wolf Material Sample\n");
}

void SampleMaterial::update(float dt) 
{
	m_rot += dt;
}

void SampleMaterial::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 mProj = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f,0.0f,4.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));

    // Use shader program.
	glm::mat4 mWorldLeft = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) * 
						   glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(0.0f, 1.0f, 0.0f)) * 
						   glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 mWorldRight = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * 
						    glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(0.0f, 1.0f, 0.0f)) * 
						    glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(1.0f, 0.0f, 0.0f));

	// Set up source data
	m_pDecl->Bind();

	// Bind Uniforms
    m_pLeftMat->SetUniform("projection", mProj);
    m_pLeftMat->SetUniform("view", mView);
    m_pLeftMat->SetUniform("world", mWorldLeft);    
	m_pLeftMat->Apply();
    glDrawArrays(GL_TRIANGLES, 0, 6 * 3 * 2);

    m_pRightMat->SetUniform("projection", mProj);
    m_pRightMat->SetUniform("view", mView);
    m_pRightMat->SetUniform("world", mWorldRight);    
	m_pRightMat->Apply();
	glDrawArrays(GL_TRIANGLES, 0, 6 * 3 * 2);
}


