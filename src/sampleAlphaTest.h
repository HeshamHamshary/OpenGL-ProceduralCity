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
};
