#pragma once
#ifndef MESH_PROTO_H
#define MESH_PROTO_H

#include "mesh_proto.pb.h"

#include "vbo_proto.h"
#include "texture_proto.h"
#include "vec3_proto.h"
#include "vec4_proto.h"

//TODO: add target indicators? (enum: target anim/texture?)
//		OR indicators ==> hash ID (anim/texture)
class mesh_proto
{
public:
	enum class RENDER_MODE
	{
		POINTS = 0,
		LINE = 1,
		LINE_LOOP = 2,
		LINE_STRIP = 3,
		TRIANGLES = 4,
		TRIANGLE_STRIP = 5,
		TRIANGLE_FAN = 6,
		DEFAULT = TRIANGLES
	};

	static const unsigned int MESHNAME_SIZE = 64;
	char meshName[MESHNAME_SIZE];

	RENDER_MODE renderMode;
	unsigned int hashid;
	unsigned int numMeshes;
	unsigned int triCount;
	unsigned int vertCount;

	vbo_proto vertices;
	vbo_proto normals;
	vbo_proto texCoords;
	vbo_proto indicies;

	vbo_proto weights;
	vbo_proto joints;
	vbo_proto invMats;

	// bounding sphere
	vec3_proto center;
	float radius;

	vec4_proto baseColor;


public:
	mesh_proto();
	~mesh_proto();
	mesh_proto(const mesh_proto&);
	mesh_proto& operator=(const mesh_proto&);

	void serialize(mesh_proto_mssg& out) const;
	void deserialize(const mesh_proto_mssg& in);


};
#endif // !MESH_PROTO_H
