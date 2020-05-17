#include "sampleAlphaTest.h"
#include "../samplefw/Grid2D.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
        //_printInfoAboutMaterial(pMat);
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

void SampleAlphaTest::init()
{
    const aiScene* pScene;   

    Assimp::Importer importer;
    pScene = importer.ReadFile("data/unreal.fbx", aiProcess_Triangulate | aiProcess_LimitBoneWeights);
    if(!pScene)
        printf("Scene is null\n");
    _printInfoAboutScene(pScene);

	// Only init if not already done
    //if(!m_pProgram)
    {
    }

    printf("Successfully initialized Texture Clamp to Edge Sample\n");
}

void SampleAlphaTest::update(float dt) 
{
}

void SampleAlphaTest::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

