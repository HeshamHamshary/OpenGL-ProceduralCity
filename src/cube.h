#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"
#include "shape.h"

class Cube : public Shape
{
public:
    Cube(wolf::Program* m_pProgram, const std::string& texturePath, bool isSkybox = false);
    ~Cube() override;

    void update(float dt) override;
    void render(const glm::mat4& mProj, const glm::mat4& mView, int width, int height) override;
    void setPosition(const glm::vec3& position) override;
    void setScale(float scale) override;
    glm::vec3 getPosition() const override;
    void setHeight(float height) override;
    void setWidth(float width) override;
    void setDepth(float depth) override;
    void setX(float x) override;
    void setY(float y) override;
    void setZ(float z) override;

    float getX() const override;
    float getY() const override;
    float getZ() const override;

    float getHeight() const override;
    float getWidth() const override;
    float getDepth() const override;

    static const Vertex gs_skyboxCubeVertices[36];
    static const Vertex gs_cubeVertices[36];
private:
    bool isSkybox       = false;
};
