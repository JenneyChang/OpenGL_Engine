#pragma once
#ifndef VEC3_PROTO_H
#define VEC3_PROTO_H

#include "vec3_proto.pb.h"

class vec3_proto
{
public:
	float x;
	float y;
	float z;


public:
	vec3_proto();
	~vec3_proto();
	vec3_proto(const vec3_proto&);
	vec3_proto& operator=(const vec3_proto&);

	vec3_proto(float _x, float _y, float _z);

	void serialize(vec3_proto_mssg& out) const;
	void deserialize(const vec3_proto_mssg& in);


};
#endif // !VEC3_PROTO_H
