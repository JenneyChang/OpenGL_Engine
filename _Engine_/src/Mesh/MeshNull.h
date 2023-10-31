#pragma once
#ifndef MESH_NULL_H
#define MESH_NULL_H

#include "Mesh.h"

class MeshNull : public Mesh
{
public: 
	MeshNull();
	virtual ~MeshNull();
	MeshNull(const MeshNull&) = delete;
	MeshNull& operator=(const MeshNull&) = delete;



};
#endif // !MESH_NULL_H
