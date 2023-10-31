#pragma once
#ifndef VBO_PROTO_H
#define VBO_PROTO_H

#include "vbo_proto.pb.h"

class vbo_proto
{
public:
	enum class TARGET
	{
		ARRAY_BUFFER = 0,
		ELEMENT_ARRAY_BUFFER = 1,
		DEFAULT = ARRAY_BUFFER
	};

	enum class COMPONENT
	{
		BYTE = 0,
		UNSIGNED_BYTE = 1,
		SHORT = 2,
		UNSIGNED_SHORT = 3,
		INT = 4,
		UNSIGNED_INT = 5,
		FLOAT = 6,
		DOUBLE = 7,
		DEFAULT = FLOAT
	};

	enum class TYPE
	{
		VEC2 = 0,
		VEC3 = 1,
		VEC4 = 2,
		MAT2 = 3,
		MAT3 = 4,
		MAT4 = 5,
		SCALAR = 6,
		VECTOR = 7,
		MATRIX = 8,
		DEFAULT = VEC2
	};

	TARGET target;
	COMPONENT component;
	TYPE type;

	bool enabled;
	unsigned int attribIndex;
	unsigned int count;
	unsigned int dataSize;
	unsigned char* pData;



public:
	vbo_proto();
	~vbo_proto();
	vbo_proto(const vbo_proto& vp);
	vbo_proto& operator=(const vbo_proto& vp);

	void serialize(vbo_proto_mssg& out) const;
	void deserialize(const vbo_proto_mssg& in);


};
#endif // !VBO_PROTO_H
