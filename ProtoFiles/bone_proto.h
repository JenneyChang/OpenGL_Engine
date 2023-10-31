#pragma once
#ifndef BONE_PROTO_H
#define BONE_PROTO_H

#include "vec3_proto.h"
#include "vec4_proto.h"
#include "bone_proto.pb.h"

class bone_proto
{
public:
	vec3_proto trans;
	vec4_proto rot;
	vec3_proto scale;

	bone_proto();
	~bone_proto();
	bone_proto(const bone_proto& b);
	bone_proto& operator=(const bone_proto& b);

	void serialize(bone_proto_mssg& out) const;
	void deserialize(const bone_proto_mssg& in);


};
#endif // !BONE_PROTO_H
