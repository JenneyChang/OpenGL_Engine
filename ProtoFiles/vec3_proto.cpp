#include "vec3_proto.h"


//--------------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------------

vec3_proto::vec3_proto()
	:x(0.0f), y(0.0f), z(0.0f)
{ }

vec3_proto::~vec3_proto()
{ }

vec3_proto::vec3_proto(const vec3_proto& vec)
	: x(vec.x), y(vec.y), z(vec.z)
{ }

vec3_proto& vec3_proto::operator=(const vec3_proto& vec)
{
	if (this != &vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
	}

	return *this;
}

vec3_proto::vec3_proto(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{ }


//--------------------------------------------------------------------------------
//	SERIALIZATION
//--------------------------------------------------------------------------------

void vec3_proto::serialize(vec3_proto_mssg& out) const
{
	out.set_x(this->x);
	out.set_y(this->y);
	out.set_z(this->z);
}

void vec3_proto::deserialize(const vec3_proto_mssg& in)
{
	this->x = in.x();
	this->y = in.y();
	this->z = in.z();
}