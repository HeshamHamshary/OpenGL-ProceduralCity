#include "sampleAlphaTest.h"
#include "../samplefw/Grid2D.h"

SampleAlphaTest::~SampleAlphaTest()
{
	printf("Destroying Texture Format 4444 Sample\n");
}

void SampleAlphaTest::init()
{
	// Only init if not already done
    if(!m_pProgram)
    {
    }

    printf("Successfully initialized Texture Clamp to Edge Sample\n");
}

void SampleAlphaTest::update(float dt) 
{
}

void SampleAlphaTest::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

