#include "sampleAlphaTest.h"
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

SampleAlphaTest::~SampleAlphaTest()
{
	printf("Destroying Texture Format 4444 Sample\n");
	delete m_pDecl;
	wolf::ProgramManager::DestroyProgram(m_pProgram);
	wolf::BufferManager::DestroyBuffer(m_pVB);
	wolf::TextureManager::DestroyTexture(m_pTexture);
}

void SampleAlphaTest::init()
{
	// Only init if not already done
    if(!m_pProgram)
    {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_pProgram = wolf::ProgramManager::CreateProgram("data/cube_alphatest.vsh", "data/cube_alphatest.fsh");
		m_pVB = wolf::BufferManager::CreateVertexBuffer(gs_cubeVertices, sizeof(Vertex) * 6 * 3 * 2);

		m_pDecl = new wolf::VertexDeclaration();
		m_pDecl->Begin();
		m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
		m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
		m_pDecl->SetVertexBuffer(m_pVB);
		m_pDecl->End();

		m_pTexture = wolf::TextureManager::CreateTexture("data/alphatest.tga");
	}

    printf("Successfully initialized Texture Clamp to Edge Sample\n");
}

void SampleAlphaTest::update(float dt) 
{
	m_rot += dt;
}

void SampleAlphaTest::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 mProj = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 mWorld = glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(0.0f, 1.0f, 0.0f));
	mWorld = mWorld * glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(1.0f, 0.0f, 0.0f));

    // Use shader program.
	m_pProgram->Bind();
    
	// Bind Uniforms
    m_pProgram->SetUniform("projection", mProj);
    m_pProgram->SetUniform("view", mView);
    m_pProgram->SetUniform("world", mWorld);    
    m_pProgram->SetUniform("texture", 0);    
    
	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6 * 3 * 2);
}

