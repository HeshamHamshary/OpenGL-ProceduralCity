#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

struct Vertex
{
    GLfloat x,y,z; // Position
    GLfloat u,v; // Texture Coordinates
    GLfloat nX, nY, nZ; // Normals
};

class Shape
{
public:
    Shape(wolf::Program* m_pProgram, const std::string& texturePath){};
    virtual ~Shape(){};

    virtual void update(float dt) = 0;
    virtual void render(const glm::mat4& mProj, const glm::mat4& mView, int width, int height) = 0;
    virtual void setPosition(const glm::vec3& position) = 0;
    virtual void setScale(float scale) = 0;
    virtual glm::vec3 getPosition() const = 0;

    virtual void setHeight(float height) = 0;
    virtual void setWidth(float width) = 0;
    virtual void setDepth(float depth) = 0;
    virtual void setX(float x) = 0;
    virtual void setY(float y) = 0;
    virtual void setZ(float z) = 0;
    
    virtual float getX() const = 0;
    virtual float getY() const = 0;
    virtual float getZ() const = 0;


    virtual float getHeight() const = 0;
    virtual float getWidth() const = 0;
    virtual float getDepth() const = 0;
protected:
    glm::vec3 m_position                  = glm::vec3(0.0f,0.0f,0.0f);
    float x                               = 0.0f;
    float y                               = 0.0f;
    float z                               = 0.0f;
    float m_height                        = 1.0f;
    float m_width                         = 1.0f;
    float m_depth                         = 1.0f;

    wolf::VertexBuffer* m_pVB             = 0;
    wolf::VertexDeclaration* m_pDecl      = 0;
    wolf::Program* m_pProgram             = 0;
    wolf::Texture* m_pTexture             = nullptr;
    wolf::Material* m_pMat                = nullptr;
};