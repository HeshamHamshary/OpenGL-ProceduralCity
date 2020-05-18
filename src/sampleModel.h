#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"
#include "../samplefw/Grid3D.h"

class SampleModel: public Sample
{
public:
    SampleModel(App* pApp) : Sample(pApp,"Alpha Test") {}
    ~SampleModel();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::Model* m_pModel = nullptr;
    wolf::Material* m_pMat = nullptr;
    Grid3D* m_pGrid = nullptr;
    float m_rot = 0.0f;
};
