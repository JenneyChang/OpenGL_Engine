#include "GameObj_Skin.h"

#include "ShaderMan.h"
#include "ShaderCompute.h"

#include "AnimMan.h"

using namespace Azul;


//---------------------------------------------------------------------------
//	CONSTRUCTION
//---------------------------------------------------------------------------

GameObj_Skin::GameObj_Skin(GraphicsObj3D* graphicsobj, Skeleton* skel, unsigned int numJoints, SSBO* pSSBO_JointsIn)
	: GameObj_Dynamic(graphicsobj), pSkeleton(skel), numBones(numJoints), pSSBO_JointLocal(pSSBO_JointsIn),
	  poSSBO_WorldResult(new SSBO())
{
	assert(graphicsobj);
	assert(skel);
	assert(numJoints > 0);
	assert(pSSBO_JointsIn);

	assert(this->poSSBO_WorldResult);
	Mat4* poBoneWorld = new Mat4[numBones]();
	assert(poBoneWorld);

	//setup ssbo
	poSSBO_WorldResult->Set(numBones, sizeof(Mat4), poBoneWorld);

	delete[] poBoneWorld;
}

GameObj_Skin::~GameObj_Skin()
{
	delete this->poSSBO_WorldResult;
}


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

SSBO* GameObj_Skin::GetSSBOWorldResult()
{
	assert(this->poSSBO_WorldResult);
	return this->poSSBO_WorldResult;
}

void GameObj_Skin::Update(AnimTime t)
{
	//compute world matrix
	this->prUpdate(t);
}

void GameObj_Skin::prUpdate(AnimTime t)
{
	AZUL_UNUSED_VAR(t);

	//grab needed SSBOS
	SSBO* pSSBO_Table = pSkeleton->GetSSBOTable();
	assert(pSSBO_Table);

	SSBO* pSSBO_InvBind = this->GetGraphicsObj()->GetMesh()->GetSSBOInvbind();
	assert(pSSBO_InvBind);

	//find shader & activate
	ShaderObj* pComputeWorld = ShaderMan::Find(ShaderObj::Name::COMPUTE_WORLD);
	assert(pComputeWorld);
	pComputeWorld->SetActive();

	//bind associated ssbo
	pSSBO_Table->Bind(0);
	pSSBO_JointLocal->Bind(1);
	poSSBO_WorldResult->Bind(2);
	pSSBO_InvBind->Bind(3);

	//set uniforms
	glUniform1i(pComputeWorld->GetLocation("numJoints"), numBones);
	glUniform1i(pComputeWorld->GetLocation("hierarchyDepth"), pSkeleton->GetHierarchyDepth());	

	//dispatch shader & set barrier
	((ShaderCompute*)pComputeWorld)->Dispatch((unsigned int)numBones/8, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);


	//verification 
	//Mat4* pTmp = (Mat4*)poSSBO_WorldResult->Map(SSBO::Access::READ_ONLY);
	//Trace::out("\n\n--------------------------------------------\n");
	//for (int i = 0; i < (int)numBones; ++i)
	//{
	//	Trace::out("GPU World[%2d]\n", i);
	//	Trace::out("  %+5.6f %+5.6f %+5.6f %+5.6f \n", pTmp[i][m0],  pTmp[i][m1],  pTmp[i][m2],  pTmp[i][m3]);
	//	Trace::out("  %+5.6f %+5.6f %+5.6f %+5.6f \n", pTmp[i][m4],  pTmp[i][m5],  pTmp[i][m6],  pTmp[i][m7]);
	//	Trace::out("  %+5.6f %+5.6f %+5.6f %+5.6f \n", pTmp[i][m8],  pTmp[i][m9],  pTmp[i][m10], pTmp[i][m11]);
	//	Trace::out("  %+5.6f %+5.6f %+5.6f %+5.6f \n", pTmp[i][m12], pTmp[i][m13], pTmp[i][m14], pTmp[i][m15]);

	//	//poBoneWorld[i] = pTmp[i];
	//}
	//poSSBO_WorldResult->Unmap();
}