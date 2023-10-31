#pragma once
#ifndef MESH_NODE_MAN_H
#define MESH_NODE_MAN_H

#include "Manager.h"
#include "MeshNode.h"
#include "Mesh.h"

class MeshNodeMan : public Manager
{
public:
	MeshNodeMan() = delete;
	MeshNodeMan(const MeshNodeMan&) = delete;
	MeshNodeMan& operator=(const MeshNodeMan&) = delete;

	static void Create(int toReserve = 4, int toGrow = 2);
	static void Destroy();

	static MeshNode* Add(Mesh::Name name, Mesh* pMesh);
	static Mesh* Find(Mesh::Name name);
	static void Remove(MeshNode* pNode);
	static void Remove(Mesh::Name name);
	static void Print();


protected:
	Node* derivedCreateNode() override;


private:
	MeshNode* poComparison;
	
	static MeshNodeMan* poInstance;
	static MeshNodeMan* prInstance();

	MeshNodeMan(int toReserve = 4, int toGrow = 2);
	virtual ~MeshNodeMan();


};
#endif // !MESH_NODE_MAN_H
