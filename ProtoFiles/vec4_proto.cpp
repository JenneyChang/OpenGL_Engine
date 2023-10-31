#include "vec4_proto.h"


//--------------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------------

vec4_proto::vec4_proto()
	: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{ }

vec4_proto::~vec4_proto()
{ }

vec4_proto::vec4_proto(const vec4_proto& vec)
	: x(vec.x), y(vec.y), z(vec.z), w(vec.w)
{ }

vec4_proto& vec4_proto::operator=(const vec4_proto& vec)
{
	if (this != &vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
		this->w = vec.w;
	}

	return *this;
}

vec4_proto::vec4_proto(float _x, float _y, float _z, float _w)
	: x(_x), y(_y), z(_z), w(_w)
{ }


//--------------------------------------------------------------------------------
//	SERIALIZATION
//--------------------------------------------------------------------------------

void vec4_proto::serialize(vec4_proto_mssg& out) const
{
	out.set_x(this->x);
	out.set_y(this->y);
	out.set_z(this->z);
	out.set_w(this->w);
}

void vec4_proto::deserialize(const vec4_proto_mssg& in)
{
	this->x = in.x();
	this->y = in.y();
	this->z = in.z();
	this->w = in.w();
}