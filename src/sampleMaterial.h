#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleMaterial: public Sample
{
public:
    SampleMaterial(wolf::App* pApp) : Sample(pApp,"Wolf Material Class") {}
    ~SampleMaterial();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Material* m_pLeftMat = 0;
    wolf::Material* m_pRightMat = 0;
    float m_rot = 0.0f;
};

