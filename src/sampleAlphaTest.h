#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleAlphaTest: public Sample
{
public:
    SampleAlphaTest(wolf::App* pApp) : Sample(pApp,"Alpha Test") {}
    ~SampleAlphaTest();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;
    wolf::Texture* m_pTexture;
    float m_rot = 0.0f;
};
