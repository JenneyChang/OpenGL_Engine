#include "Mixer.h"
#include "MathApp.h"

#include "ShaderMan.h"
#include "ShaderCompute.h"
#include "Joint.h"

using namespace Azul;


void Mixer::Blend(SSBO* pSSBOIn, SSBO* pA, SSBO* pB, const float ts, const int numJoints)
{
	//find shader and set active
	ShaderObj* pComputeMixer = ShaderMan::Find(ShaderObj::Name::COMPUTE_MIXER);
	assert(pComputeMixer);
	pComputeMixer->SetActive();

	//bind to active shader
	pA->Bind(0);
	pB->Bind(1);
	pSSBOIn->Bind(2);

	//set uniforms
	glUniform1f(pComputeMixer->GetLocation("ts"), ts);
	glUniform1i(pComputeMixer->GetLocation("numJoints"), numJoints);

	//dispatch shader & set barrier
	((ShaderCompute*)pComputeMixer)->Dispatch((unsigned int)numJoints/8, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	//Test if we can do pure ssbo in mixer (check)
	//Copy out to Joint Array...for now
	//Joint* pTmp = (Joint*)pSSBOIn->Map(SSBO::Access::READ_ONLY);
	////Trace::out("\n\n--------------------------------------------\n");
	//for (int i = 0; i < numJoints; ++i)
	//{
	//	Joint* pCompute = &pTmp[i];
	//	Trace::out("\nGPU Local[%2d]\n", i);
	//	Trace::out("  T: %+5.6f %+5.6f %+5.6f\n", pCompute->Trans[x], pCompute->Trans[y], pCompute->Trans[z]);
	//	Trace::out("  R: %+5.6f %+5.6f %+5.6f %+5.6f\n", pCompute->Rot[x], pCompute->Rot[y], pCompute->Rot[z], pCompute->Rot[w]);
	//	Trace::out("  S: %+5.6f %+5.6f %+5.6f\n", pCompute->Scale[x], pCompute->Scale[y], pCompute->Scale[z]);

	//	//pResult[i] = pTmp[i];
	//}
	//pSSBOIn->Unmap();
}