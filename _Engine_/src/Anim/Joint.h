#pragma once
#ifndef JOINT_H
#define JOINT_H

#include "MathEngine.h"

using namespace Azul;

struct Joint : public Align16
{
	Vec3 Trans	= Vec3(0.0f, 0.0f, 0.0f);
	Quat Rot	= Quat(0.0f, 0.0f, 0.0f, 1.0f);
	Vec3 Scale	= Vec3(1.0f, 1.0f, 1.0f);
};
#endif // !JOINT_H
