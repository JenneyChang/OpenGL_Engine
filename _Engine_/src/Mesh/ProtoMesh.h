#pragma once
#ifndef PROTO_MESH_H
#define PROTO_MESH_H

#include "Mesh.h"
#include "Texture.h"
#include "mesh_proto.h"

using namespace Azul;

class ProtoMesh : public Mesh
{
public:
	ProtoMesh() = delete;
	ProtoMesh(const ProtoMesh&) = delete;
	ProtoMesh& operator=(const ProtoMesh&) = delete;

	ProtoMesh(const char* filename);
	ProtoMesh(const char* filename, Texture* texture);
	virtual ~ProtoMesh();

	Texture* GetTexture();


private:
	Texture* pTexture;	//save ref to associated texture?

	void prUnpackProto(const char* filename);
	void prCreateVAO(mesh_proto& mproto);


};
#endif // !PROTO_MESH_H
