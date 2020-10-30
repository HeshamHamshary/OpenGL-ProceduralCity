#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../wolf/wolf.h"
#include "../samplefw/SampleRunner.h"
#include "sampleDepthTest.h"
#include "sampleAlphaTest.h"
#include "sampleBlending.h"
#include "sampleMaterial.h"
#include "sampleModel.h"
#include "sampleMultiModel.h"
#include "sampleOverrideMat.h"

class Week2: public wolf::App
{
public:
    Week2() : wolf::App("Week 4")
    {
        m_sampleRunner.addSample(new SampleDepthTest(this));
        m_sampleRunner.addSample(new SampleAlphaTest(this));
        m_sampleRunner.addSample(new SampleBlending(this));
        m_sampleRunner.addSample(new SampleMaterial(this));
        m_sampleRunner.addSample(new SampleModel(this));
        m_sampleRunner.addSample(new SampleMultiModel(this));
        m_sampleRunner.addSample(new SampleOverrideMat(this));
    }

    ~Week2()
    {
    }

    void update(float dt) override
    {
        if(isKeyDown(' '))
        {
            m_lastDown = true;
        }
        else if(m_lastDown)
        {
            m_sampleRunner.nextSample();
            m_lastDown = false;
        }

        m_sampleRunner.update(dt);
    }

    void render() override
    {
        m_sampleRunner.render(m_width, m_height);
    }

private:
    SampleRunner m_sampleRunner;
    bool m_lastDown = false;
};

int main(int, char**) {
    Week2 week2;
    week2.run();
}