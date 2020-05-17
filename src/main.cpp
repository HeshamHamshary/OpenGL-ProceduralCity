#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../wolf/wolf.h"
#include "../samplefw/SampleRunner.h"
#include "sampleClipSpace.h"
#include "sampleClipSpaceColors.h"
#include "sampleOrtho.h"
#include "samplePerspective.h"
#include "sampleWorldTransform.h"

class Week2: public App
{
public:
    Week2() : App("Week 4")
    {
        m_sampleRunner.addSample(new SampleClipSpace(this));
        m_sampleRunner.addSample(new SampleClipSpaceColors(this));
        m_sampleRunner.addSample(new SampleOrtho(this));
        m_sampleRunner.addSample(new SamplePerspective(this));
        m_sampleRunner.addSample(new SampleWorldTransform(this));
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