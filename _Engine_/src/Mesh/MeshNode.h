#pragma once
#ifndef MESH_NODE_H
#define MESH_NODE_H

#include "DLink.h"
#include "Mesh.h"

class MeshNode : public DLink
{
public:
	MeshNode();
	~MeshNode();
	MeshNode(const MeshNode&) = delete;
	MeshNode& operator=(const MeshNode&) = delete;

	void Set(Mesh::Name name, Mesh* pMesh);
	Mesh* GetMesh();

	bool Compare(Node* pNode) override;


private:
	Mesh* poMesh;


};
#endif // !MESH_NODE_H
