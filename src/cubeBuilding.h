#pragma once

#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"
#include "building.h"

class CubeBuilding : public Building
{
    public:
        CubeBuilding(wolf::Program* m_pProgram);
        ~CubeBuilding() override;
        void update(float dt) override;
        void render(const glm::mat4& mProj, const glm::mat4& mView, int width, int height) override;
        void setPosition(const glm::vec3& m_position) override;

        glm::vec3 getPosition() const override;
        float getX() const override;
        float getY() const override;
        float getZ() const override;
        int getBlocks() const override;
        int getStories() const  override;

        float getWidth() const override;
        float getHeight() const override;
        float getDepth() const override;

    private:
        static const std::vector<std::string> texturePaths;
        Cube* m_pCube               = nullptr;
};
