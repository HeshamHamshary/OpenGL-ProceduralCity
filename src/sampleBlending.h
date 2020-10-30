#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleBlending: public Sample
{
public:
    SampleBlending(wolf::App* pApp) : Sample(pApp,"Blending") {}
    ~SampleBlending();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;
    wolf::Texture* m_pTexture = 0;
    wolf::BlendMode m_eSrcFactor = wolf::BM_SrcAlpha;
    wolf::BlendMode m_eDstFactor = wolf::BM_OneMinusSrcAlpha;
    float m_rot = 0.0f;
	bool m_leftKeyDown = false;
	bool m_rightKeyDown = false;
	bool m_upKeyDown = false;
	bool m_downKeyDown = false;
};


