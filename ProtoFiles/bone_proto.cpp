#include "bone_proto.h"


//--------------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------------

bone_proto::bone_proto()
	: trans(0.0f, 0.0f, 0.0f), rot(0.0f, 0.0f, 0.0f, 1.0f), scale(1.0f, 1.0f, 1.0f)
{ }

bone_proto::~bone_proto()
{ }

bone_proto::bone_proto(const bone_proto& b)
	: trans(b.trans), rot(b.rot), scale(b.scale)
{ }

bone_proto& bone_proto::operator=(const bone_proto& b)
{
	if (this != &b)
	{
		this->trans = b.trans;
		this->rot = b.rot;
		this->scale = b.scale;
	}

	return *this;
}


//--------------------------------------------------------------------------------
//	SERIALIZATION
//--------------------------------------------------------------------------------

void bone_proto::serialize(bone_proto_mssg& out) const
{
	vec3_proto_mssg* vec3Mssg = new vec3_proto_mssg();
	this->trans.serialize(*vec3Mssg);
	out.set_allocated_trans(vec3Mssg);

	vec3Mssg = new vec3_proto_mssg();
	this->scale.serialize(*vec3Mssg);
	out.set_allocated_scale(vec3Mssg);

	vec4_proto_mssg* vec4Mssg = new vec4_proto_mssg();
	this->rot.serialize(*vec4Mssg);
	out.set_allocated_rot(vec4Mssg);
}

void bone_proto::deserialize(const bone_proto_mssg& in)
{
	this->scale.deserialize(in.scale());
	this->trans.deserialize(in.trans());
	this->rot.deserialize(in.rot());
}