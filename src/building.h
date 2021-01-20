#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"
#include "cube.h"
#include <vector>
#include "string.h"

class Building
{
public:
    Building(wolf::Program* m_pProgram){};
    virtual ~Building(){};
    virtual void update(float dt) = 0;
    virtual void render(const glm::mat4& mProj, const glm::mat4& mView, int width, int height) = 0;
    virtual void setPosition(const glm::vec3& m_position) = 0;

    virtual glm::vec3 getPosition() const = 0;
    virtual float getX() const = 0;
    virtual float getY() const = 0;
    virtual float getZ() const = 0;
    virtual int getBlocks() const = 0;
    virtual int getStories() const = 0;

    virtual float getWidth() const = 0;
    virtual float getHeight() const = 0;
    virtual float getDepth() const = 0;
    
    
protected:
    glm::vec3 m_position             = glm::vec3(0.0f, 0.0f, 0.0f);
    float x                          = 0.0f;
    float y                          = 0.0f;
    float z                          = 0.0f;
    int m_blocks                     = 1;
    int m_stories                    = 1;
    wolf::VertexBuffer* m_pVB        = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram        = 0;
};
