#pragma once
#ifndef CAMERA_MESH_H
#define CAMERA_MESH_H

#include "Mesh.h"

class CameraMesh : public Mesh
{
public:
	// deleted functions
	CameraMesh(const CameraMesh&) = delete;
	CameraMesh& operator=(const CameraMesh&) = delete;

	CameraMesh();
	virtual ~CameraMesh();

	void Update();


private:
	void prCreateMesh();


};
#endif // !CAMERA_MESH_H
