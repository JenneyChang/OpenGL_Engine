#pragma once
#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include "MathEngine.h"

using namespace Azul;

class BoundingSphere : public Align16
{
public:
	Vec3 center;
	float radius;

	BoundingSphere();
	~BoundingSphere();
	BoundingSphere(const BoundingSphere&) = default;
	BoundingSphere& operator=(const BoundingSphere&) = default;

	void RitterSphere(Vec3* pt, int numpts);


private:
	void prFurthestPtsAABB(int& min, int& max, Vec3* pt, int numpts);
	void prSphereFromDistPts(Vec3* pt, int numpts);
	void prSphereOfSphereAndPt(Vec3& p);


};
#endif // !BOUNDING_SPHERE_H
