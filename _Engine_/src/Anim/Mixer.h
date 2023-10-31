#pragma once
#ifndef MIXER_H
#define MIXER_H

#include "SSBO.h"
#include "MathEngine.h"

using namespace Azul;

class Mixer
{
public:
	static void Blend(SSBO* pSSBOIn, SSBO* pA, SSBO* pB, const float ts, const int numJoints);


};
#endif
