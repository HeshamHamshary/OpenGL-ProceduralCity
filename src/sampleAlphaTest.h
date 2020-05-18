#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleAlphaTest: public Sample
{
public:
    SampleAlphaTest(App* pApp) : Sample(pApp,"Alpha Test") {}
    ~SampleAlphaTest();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = nullptr;
    wolf::IndexBuffer* m_pIB = nullptr;
    wolf::VertexDeclaration* m_pDecl = nullptr;
    wolf::Program* m_pProgram = nullptr;
    wolf::Model* m_pModel = nullptr;
    float m_rot = 0.0f;
};
