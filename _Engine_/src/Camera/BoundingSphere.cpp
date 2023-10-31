#include "BoundingSphere.h"

using namespace Azul;

//-----------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------

BoundingSphere::BoundingSphere()
	: center(Vec3(0.0f, 0.0f, 0.0f)), radius(0.0f)
{ }

BoundingSphere::~BoundingSphere()
{ }


//-----------------------------------------------------------------------------
//	PUBLIC METHODS
//-----------------------------------------------------------------------------

void BoundingSphere::RitterSphere(Vec3* pt, int numpts)
{
	assert(pt);

	//get sphere encompassing 2 approx furthest pts
	this->prSphereFromDistPts(pt, numpts);

	//grow sphere to include all pts
	for (int i = 0; i < numpts; ++i)
	{
		this->prSphereOfSphereAndPt(pt[i]);
	}
}

//-----------------------------------------------------------------------------
//	PRIVATE METHODS
//-----------------------------------------------------------------------------

void BoundingSphere::prFurthestPtsAABB(int& min, int& max, Vec3* pt, int numpts)
{
	// First find most extreme points along principal axes
	int xmin = 0;
	int xmax = 0;
	int ymin = 0;
	int ymax = 0;
	int zmin = 0;
	int zmax = 0;

	for (int i = 1; i < numpts; ++i)
	{
		if (pt[i][x] < pt[xmin][x])
			xmin = i;
		if (pt[i][x] > pt[xmax][x])
			xmax = i;
		if (pt[i][y] < pt[ymin][y])
			ymin = i;
		if (pt[i][y] > pt[ymax][y])
			ymax = i;
		if (pt[i][z] < pt[zmin][z])
			zmin = i;
		if (pt[i][z] > pt[zmax][z])
			zmax = i;
	}

	// Given 6pts find the greatest distance
	struct tmpNode
	{
		Vec3 v;
		int index;
		int pad[3];  // padding
	};

	tmpNode data[6];

	data[0].v.set(pt[xmin]);
	data[1].v.set(pt[ymin]);
	data[2].v.set(pt[zmin]);
	data[3].v.set(pt[xmax]);
	data[4].v.set(pt[ymax]);
	data[5].v.set(pt[zmax]);

	data[0].index = xmin;
	data[1].index = ymin;
	data[2].index = zmin;
	data[3].index = xmax;
	data[4].index = ymax;
	data[5].index = zmax;


	float maxDist = (data[0].v - data[1].v).len();
	int maxA = data[0].index;
	int maxB = data[1].index;
	float dist = maxDist;

	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			dist = (data[i].v - data[j].v).len();
			//out("dist(%d,%d) = %f\n",i,j,dist);
			if(dist > maxDist)
			{
				//out("--->maxdist(%d,%d) = %f\n",i,j,dist);
				// new max
				maxDist = dist;
				maxA = data[i].index;
				maxB = data[j].index;
			}
		}
	}

	min = maxA;
	max = maxB;
}

void BoundingSphere::prSphereFromDistPts(Vec3* pt, int numpts)
{
	assert(pt);

	// Find the most separated point pair defining the encompassing AABB
	int min, max;
	this->prFurthestPtsAABB(min, max, pt, numpts);

	// Set up sphere to just encompass these two points
	this->center = (pt[min] + pt[max]) * 0.5f;
	this->radius = (pt[max] - this->center).dot(pt[max] - this->center);
	this->radius = sqrtf(this->radius);
}

void BoundingSphere::prSphereOfSphereAndPt(Vec3& p)
{
	// Compute squared distance between point and sphere center
	Vec3 d = p - this->center;

	float dist2 = d.dot(d);
	// Only update s if point p is outside it
	if (dist2 > this->radius * this->radius)
	{
		float dist = sqrtf(dist2);
		float newRadius = (this->radius + dist) * 0.5f;
		float k = (newRadius - this->radius) / dist;
		this->radius = newRadius;
		this->center += d * k;
	}
}