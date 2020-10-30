#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleDepthTest: public Sample
{
public:
    SampleDepthTest(wolf::App* pApp) : Sample(pApp,"Depth Test") {}
    ~SampleDepthTest();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;
    bool m_bDepthOn = true;
    bool m_bDepthKeyDown = false;
    float m_rot = 0.0f;
};
