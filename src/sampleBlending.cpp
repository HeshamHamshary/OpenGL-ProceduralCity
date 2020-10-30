#include "sampleBlending.h"
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

static GLenum gs_blendModeMap[] =
{
	GL_SRC_ALPHA,				//BM_SrcAlpha,		
	GL_ONE,						//BM_One,				
	GL_SRC_COLOR,				//BM_SrcColor,
	GL_ONE_MINUS_SRC_COLOR,		//BM_OneMinusSrcColor,	
	GL_ONE_MINUS_SRC_ALPHA,		//BM_OneMinusSrcAlpha,
	GL_DST_ALPHA,				//BM_DstAlpha,			
	GL_ONE_MINUS_DST_ALPHA,		//BM_OneMinusDstAlpha,
	GL_DST_COLOR,				//BM_DstColor,			
	GL_ONE_MINUS_DST_COLOR,		//BM_OneMinusDstColor,	
	GL_ZERO,					//BM_Zero,				
};

static const char* gs_blendModeStringMap[] =
{
	"GL_SRC_ALPHA",				//BM_SrcAlpha,		
	"GL_ONE",					//BM_One,				
	"GL_SRC_COLOR",				//BM_SrcColor,
	"GL_ONE_MINUS_SRC_COLOR",	//BM_OneMinusSrcColor,	
	"GL_ONE_MINUS_SRC_ALPHA",	//BM_OneMinusSrcAlpha,
	"GL_DST_ALPHA",				//BM_DstAlpha,			
	"GL_ONE_MINUS_DST_ALPHA",	//BM_OneMinusDstAlpha,
	"GL_DST_COLOR",				//BM_DstColor,			
	"GL_ONE_MINUS_DST_COLOR",	//BM_OneMinusDstColor,	
	"GL_ZERO",					//BM_Zero,				
};

wolf::BlendMode ToggleBlendMode(wolf::BlendMode p_eMode, int p_iFactor)
{
	int iNewMode = (int)p_eMode + p_iFactor;

	while( iNewMode < 0 )
		iNewMode += wolf::BM_NUM_BLEND_MODES;

	while( iNewMode >= wolf::BM_NUM_BLEND_MODES )
		iNewMode -= wolf::BM_NUM_BLEND_MODES;

	return (wolf::BlendMode) iNewMode;
}

SampleBlending::~SampleBlending()
{
	printf("Destroying Blending Sample\n");
	delete m_pDecl;
	wolf::ProgramManager::DestroyProgram(m_pProgram);
	wolf::BufferManager::DestroyBuffer(m_pVB);
	wolf::TextureManager::DestroyTexture(m_pTexture);
}

void SampleBlending::init()
{    
	// Only init if not already done
    if(!m_pProgram)
    {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		m_pProgram = wolf::ProgramManager::CreateProgram("data/cube_blend.vsh", "data/cube_blend.fsh");
		m_pVB = wolf::BufferManager::CreateVertexBuffer(gs_cubeVertices, sizeof(Vertex) * 6 * 3 * 2);

		m_pDecl = new wolf::VertexDeclaration();
		m_pDecl->Begin();
		m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
		m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
		m_pDecl->SetVertexBuffer(m_pVB);
		m_pDecl->End();

		m_pTexture = wolf::TextureManager::CreateTexture("data/brick.dds");
	}

    printf("Successfully initialized Blending Sample\n");
}

void SampleBlending::update(float dt) 
{
	m_rot += dt;
}

void SampleBlending::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 mProj = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f,0.0f,4.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 mWorld = glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(0.0f, 1.0f, 0.0f));
	mWorld = mWorld * glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(1.0f, 0.0f, 0.0f));

    if( m_pApp->isKeyDown( GLFW_KEY_LEFT ) == GLFW_PRESS )
		m_leftKeyDown = true;
	else if( m_leftKeyDown )
	{
		m_leftKeyDown = false;
		m_eSrcFactor = ToggleBlendMode(m_eSrcFactor, -1);
	}

    if( m_pApp->isKeyDown( GLFW_KEY_RIGHT ) == GLFW_PRESS )
		m_rightKeyDown = true;
	else if( m_rightKeyDown )
	{
		m_rightKeyDown = false;
		m_eSrcFactor = ToggleBlendMode(m_eSrcFactor, 1);
	}

    if( m_pApp->isKeyDown( GLFW_KEY_UP ) == GLFW_PRESS )
		m_upKeyDown = true;
	else if( m_upKeyDown )
	{
		m_upKeyDown = false;
		m_eDstFactor = ToggleBlendMode(m_eDstFactor, -1);
	}

    if( m_pApp->isKeyDown( GLFW_KEY_DOWN ) == GLFW_PRESS )
		m_downKeyDown = true;
	else if( m_downKeyDown )
	{
		m_downKeyDown = false;
		m_eDstFactor = ToggleBlendMode(m_eDstFactor, 1);
	}

	glBlendFunc(gs_blendModeMap[m_eSrcFactor], gs_blendModeMap[m_eDstFactor]);

	printf("Blend modes are...[%s\t%s]\n", gs_blendModeStringMap[m_eSrcFactor], gs_blendModeStringMap[m_eDstFactor]);

    // Use shader program.
	m_pProgram->Bind();
    
	m_pTexture->Bind();

	// Bind Uniforms
    m_pProgram->SetUniform("projection", mProj);
    m_pProgram->SetUniform("view", mView);
    m_pProgram->SetUniform("world", mWorld);    
    m_pProgram->SetUniform("texture", 0);    
    m_pProgram->SetUniform("fade", 0.5f);    
    
	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6 * 3 * 2);
}



