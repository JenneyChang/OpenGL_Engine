#pragma once
#ifndef VEC4_PROTO_H
#define VEC4_PROTO_H

#include "vec4_proto.pb.h"

class vec4_proto
{
public:
	float x;
	float y;
	float z;
	float w;


public:
	vec4_proto();
	~vec4_proto();
	vec4_proto(const vec4_proto&);
	vec4_proto& operator=(const vec4_proto&);

	vec4_proto(float x, float y, float z, float w = 1.0f);

	void serialize(vec4_proto_mssg& out) const;
	void deserialize(const vec4_proto_mssg& in);


};
#endif // !VEC4_PROTO_H
