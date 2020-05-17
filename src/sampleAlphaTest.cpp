#include "sampleAlphaTest.h"
#include "../samplefw/Grid2D.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Assimp::Importer importer;
const aiScene* pScene;   

struct InterleavedMesh
{
    int numVertices = 0;
    int posOffset = -1;
    int normalOffset = -1;
    int tangentOffset = -1;
    int bitangentOffset = -1;
    int* pColorOffsets = nullptr;
    int numColorChannels;
    int* pUVOffsets = nullptr;
    int* pUVSizes = nullptr;
    int numUVChannels = 0;

    unsigned char* pInterleavedData = nullptr;
    unsigned short* pIndexData = nullptr;
    int interleavedDataSize = 0;
    int vertexStride = 0;
    int numIndices = 0;

    ~InterleavedMesh() 
    {
        delete[] pInterleavedData;
        delete[] pIndexData;
        pInterleavedData = nullptr;
        if(pUVOffsets)
            delete[] pUVOffsets;
        if(pUVSizes)
            delete[] pUVSizes;
        if(pColorOffsets)
            delete[] pColorOffsets;
    }
};

#define ERROR_IF_PARAM_NOT_PRESENT(msg) if(i + 1 >= argc ) { _errorAndExit(msg); }

bool _fileExists(const char* file)
{
    FILE* fp = fopen(file,"r");
    if(fp)
    {
        fclose(fp);
        return true;
    }
    return false;
}

void _errorAndExit(const char* msg)
{
    printf("Error: %s\n", msg);
    exit(1);
}

void _printMatPropBoolIfPresent(const aiMaterial* pMat, const char* key, int type, int idx, const char* name = nullptr) 
{
    int val;
    if(AI_SUCCESS == pMat->Get(key, type, idx, val))
        printf("\t%s == %s\n", name ? name : "", val ? "true" : "false");
}

void _printMatPropIntIfPresent(const aiMaterial* pMat, const char* key, int type, int idx, const char* name = nullptr) 
{
    int val;
    if(AI_SUCCESS == pMat->Get(key, type, idx, val))
        printf("%s = %d\n", name ? name : "", val);
}

void _printMatPropFloatIfPresent(const aiMaterial* pMat, const char* key, int type, int idx, const char* name = nullptr) 
{
    float val;
    if(AI_SUCCESS == pMat->Get(key, type, idx, val))
        printf("%s = %.2f\n", name ? name : "", val);
}

void _printMatPropColorIfPresent(const aiMaterial* pMat, const char* key, int type, int idx, const char* name = nullptr) 
{
    aiColor3D color;
    if(AI_SUCCESS == pMat->Get(key, type, idx, color))
        printf("%s = %.2f,%.2f,%.2f\n", name ? name : "", color.r,color.g,color.b);
}

void _printMatPropStringIfPresent(const aiMaterial* pMat, const char* key, int type, int idx, const char* name = nullptr) 
{
    aiString val;
    if(AI_SUCCESS == pMat->Get(key, type, idx, val))
        printf("%s = %s\n", name ? name : "", val.C_Str());
}

void _printInfoAboutMaterial(const aiMaterial* pMat) 
{
    for(int i = 0; i < pMat->mNumProperties; i++) 
    {
        aiMaterialProperty* pProp = pMat->mProperties[i];
        printf("  Prop %s (%d,%d) ", pProp->mKey.C_Str(), pProp->mType, pProp->mDataLength);
        switch(pProp->mType) 
        {
            case aiPTI_Float:
            case aiPTI_Double:
                if(pProp->mDataLength == 12)
                    _printMatPropColorIfPresent(pMat, pProp->mKey.C_Str(), pProp->mSemantic, pProp->mIndex);
                else if(pProp->mDataLength == 4)
                    _printMatPropFloatIfPresent(pMat, pProp->mKey.C_Str(), pProp->mSemantic, pProp->mIndex);
                else
                    printf("Unknown float dimension for %s = %d\n", pProp->mKey.C_Str(), pProp->mDataLength);
                break;
            case aiPTI_String:
                _printMatPropStringIfPresent(pMat, pProp->mKey.C_Str(), pProp->mSemantic, pProp->mIndex);
                break;
            case aiPTI_Integer:
                _printMatPropIntIfPresent(pMat, pProp->mKey.C_Str(), pProp->mSemantic, pProp->mIndex);
                break;
        }
    }
}

void _printInfoAboutMesh(const aiMesh* pMesh)
{
    printf("  Num Color Channels = %d\n", pMesh->GetNumColorChannels());
    printf("  Num UV Channels = %d\n", pMesh->GetNumUVChannels());
    if(pMesh->HasBones())
        printf("  Has Bones\n");
    if(pMesh->HasFaces())
        printf("  Has Faces\n");
    if(pMesh->HasNormals())
        printf("  Has Normals\n");
    if(pMesh->HasPositions())
        printf("  Has Positions\n");
    if(pMesh->HasTangentsAndBitangents())
        printf("  Has Tangents and Bitangents\n");
}

void _printInfoAboutScene(const aiScene* pScene)
{
    printf("Scene has %d animations\n", pScene->mNumAnimations);
    printf("Scene has %d cameras\n", pScene->mNumCameras);
    printf("Scene has %d lights\n", pScene->mNumLights);
    printf("Scene has %d materials\n", pScene->mNumMaterials);
    printf("Scene has %d meshes\n", pScene->mNumMeshes);
    printf("Scene has %d textures\n", pScene->mNumTextures);

    for(int i = 0; i < pScene->mNumMaterials; i++) 
    {
        aiMaterial* pMat = pScene->mMaterials[i];
        aiString name;
        pMat->Get(AI_MATKEY_NAME, name);
        printf("==Material %d (%s)==\n", i, name.C_Str());
        _printInfoAboutMaterial(pMat);
    }

    for(int i = 0; i < pScene->mNumMeshes; i++) 
    {
        aiMesh* pMesh = pScene->mMeshes[i];

        printf("==Mesh %d (%s)==\n", i, pMesh->mName.C_Str());
        _printInfoAboutMesh(pMesh);
    }
}

SampleAlphaTest::~SampleAlphaTest()
{
	printf("Destroying Texture Format 4444 Sample\n");
}

int _getInterleavedVertexSize(aiMesh* pMesh)
{
    int total = sizeof(aiVector3D); // assuming presence of positions
    // Only support one color channel right now (to keep wolf simple)
    total += (pMesh->GetNumColorChannels() > 0 ? 1 : 0) * 4;
    total += pMesh->HasNormals() ? sizeof(aiVector3D) : 0;
    total += pMesh->HasTangentsAndBitangents() ? sizeof(aiVector3D) * 2 : 0;

    for(int i = 0; i < pMesh->GetNumUVChannels(); ++i)
    {
        total += pMesh->mNumUVComponents[i] * sizeof(float);
    }

    return total;
}

InterleavedMesh* _interleaveMeshData(aiMesh* pMesh)
{
    InterleavedMesh* pOutMesh = new InterleavedMesh();
    pOutMesh->vertexStride = _getInterleavedVertexSize(pMesh);
    pOutMesh->interleavedDataSize = pOutMesh->vertexStride * pMesh->mNumVertices;
    pOutMesh->pInterleavedData = new unsigned char[pOutMesh->interleavedDataSize];
    pOutMesh->numIndices = pMesh->mNumFaces * 3;
    pOutMesh->pIndexData = new unsigned short[pOutMesh->numIndices];

    unsigned char* pCursor = (unsigned char*)pOutMesh->pInterleavedData;
    int vertOffset = 0;

    for(int i = 0; i < pMesh->mNumVertices; ++i)
    {
        bool firstVert = i == 0;
        aiVector3D* pPos = (aiVector3D*)pCursor;
        *pPos = pMesh->mVertices[i];
        pCursor += sizeof(aiVector3D);

        if(firstVert)
        {
            pOutMesh->posOffset = vertOffset;
            vertOffset += sizeof(aiVector3D);
        }

        if(pMesh->HasNormals())
        {
            aiVector3D* pNormal = (aiVector3D*)pCursor;
            *pNormal = pMesh->mNormals[i];
            pCursor += sizeof(aiVector3D);

            if(firstVert)
            {
                pOutMesh->normalOffset = vertOffset;
                vertOffset += sizeof(aiVector3D);
            }
        }

        if(pMesh->HasTangentsAndBitangents())
        {
            aiVector3D* pTangent = (aiVector3D*)pCursor;
            *pTangent = pMesh->mTangents[i];
            pCursor += sizeof(aiVector3D);

            aiVector3D* pBiTangent = (aiVector3D*)pCursor;
            *pBiTangent = pMesh->mBitangents[i];
            pCursor += sizeof(aiVector3D);

            if(firstVert)
            {
                pOutMesh->tangentOffset = vertOffset;
                vertOffset += sizeof(aiVector3D);
                pOutMesh->bitangentOffset = vertOffset;
                vertOffset += sizeof(aiVector3D);
            }
        }

        // only support one color channel right now (would require changing the "push" attr location mapping)
        // to "pull" which complicates early learning
        const int numColorChannels = pMesh->GetNumColorChannels() > 0 ? 1 : 0;

        for(int c = 0; c < numColorChannels; ++c)
        {
            pCursor[0] = (unsigned char) (pMesh->mColors[i]->r * 255.0f);
            pCursor[1] = (unsigned char) (pMesh->mColors[i]->g * 255.0f);
            pCursor[2] = (unsigned char) (pMesh->mColors[i]->b * 255.0f);
            pCursor[3] = (unsigned char) (pMesh->mColors[i]->a * 255.0f);
            pCursor += 4;

            if(firstVert)
            {
                if( c == 0)
                {
                    pOutMesh->numColorChannels = pMesh->GetNumColorChannels();
                    pOutMesh->pColorOffsets = new int[pOutMesh->numColorChannels];
                }

                pOutMesh->pColorOffsets[c] = vertOffset;
                vertOffset += 4;
            }
        }

        for(int uvSet = 0; uvSet < pMesh->GetNumUVChannels(); ++uvSet)
        {
            if(firstVert)
            {
                if( uvSet == 0)
                {
                    pOutMesh->numUVChannels = pMesh->GetNumUVChannels();
                    pOutMesh->pUVOffsets = new int[pOutMesh->numUVChannels];
                    pOutMesh->pUVSizes = new int[pOutMesh->numUVChannels];
                }
            }

            float* pUV = (float*)pCursor;
            switch(pMesh->mNumUVComponents[uvSet])
            {
                case 1:
                    pUV[0] = pMesh->mTextureCoords[uvSet][i].x;
                    pCursor += sizeof(float);
                    pOutMesh->pUVOffsets[uvSet] = vertOffset;
                    pOutMesh->pUVSizes[uvSet] = 1;
                    vertOffset += sizeof(float);
                    break;
                case 2:
                    pUV[0] = pMesh->mTextureCoords[uvSet][i].x;
                    pUV[1] = pMesh->mTextureCoords[uvSet][i].y;
                    pCursor += sizeof(float) * 2;
                    pOutMesh->pUVOffsets[uvSet] = vertOffset;
                    pOutMesh->pUVSizes[uvSet] = 2;
                    vertOffset += sizeof(float) * 2;
                    break;
                case 3:
                    pUV[0] = pMesh->mTextureCoords[uvSet][i].x;
                    pUV[1] = pMesh->mTextureCoords[uvSet][i].y;
                    pUV[2] = pMesh->mTextureCoords[uvSet][i].z;
                    pCursor += sizeof(float) * 3;
                    pOutMesh->pUVOffsets[uvSet] = vertOffset;
                    pOutMesh->pUVSizes[uvSet] = 3;
                    vertOffset += sizeof(float) * 3;
                    break;
            }
        }
    }

    for(int i = 0; i < pMesh->mNumFaces; ++i)
    {
        aiFace* pFace = &pMesh->mFaces[i];
        assert(pFace->mNumIndices == 3);
        pOutMesh->pIndexData[i*3+0] = pFace->mIndices[0];
        pOutMesh->pIndexData[i*3+1] = pFace->mIndices[1];
        pOutMesh->pIndexData[i*3+2] = pFace->mIndices[2];
    }

    return pOutMesh;
}

void SampleAlphaTest::init()
{
    pScene = importer.ReadFile("data/unreal.fbx", aiProcess_Triangulate | 
                                                  aiProcess_OptimizeMeshes | 
                                                  aiProcess_TransformUVCoords | 
                                                  aiProcess_CalcTangentSpace |
                                                  aiProcess_JoinIdenticalVertices);
    if(!pScene)
        printf("Scene is null\n");
    _printInfoAboutScene(pScene);

	// Only init if not already done
    if(!m_pProgram)
    {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		m_pProgram = wolf::ProgramManager::CreateProgram("data/cube.vsh", "data/cube.fsh");

        InterleavedMesh* pInterleavedMesh = _interleaveMeshData(pScene->mMeshes[0]);
		m_pVB = wolf::BufferManager::CreateVertexBuffer(pInterleavedMesh->pInterleavedData, pInterleavedMesh->interleavedDataSize);
		m_pIB = wolf::BufferManager::CreateIndexBuffer(pInterleavedMesh->pIndexData, pInterleavedMesh->numIndices);

		m_pDecl = new wolf::VertexDeclaration();
		m_pDecl->Begin();
        if(pInterleavedMesh->posOffset != -1)
            m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float, pInterleavedMesh->posOffset);
        if(pInterleavedMesh->normalOffset != -1)
            m_pDecl->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float, pInterleavedMesh->normalOffset);
		m_pDecl->SetVertexBuffer(m_pVB);
		m_pDecl->SetIndexBuffer(m_pIB);
		m_pDecl->End(pInterleavedMesh->vertexStride);
    }

    printf("Successfully initialized Texture Clamp to Edge Sample\n");
}

void SampleAlphaTest::update(float dt) 
{
    m_rot += dt;
}

void SampleAlphaTest::render(int width, int height)
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 mProj = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f,150.0f,400.0f), glm::vec3(0.0f,100.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 mWorld = glm::rotate(glm::mat4(1.0f), m_rot, glm::vec3(0.0f, 1.0f, 0.0f));

    // Use shader program.
	m_pProgram->Bind();
    
	// Bind Uniforms
    m_pProgram->SetUniform("projection", mProj);
    m_pProgram->SetUniform("view", mView);
    m_pProgram->SetUniform("world", mWorld);    
    
	// Set up source data
	m_pDecl->Bind();

    // Draw!
	//glDrawArrays(GL_TRIANGLES, 0, pScene->mMeshes[0]->mNumVertices);
	glDrawElements(GL_TRIANGLES, pScene->mMeshes[0]->mNumFaces * 3, GL_UNSIGNED_SHORT, 0);
}

