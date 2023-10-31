#include "frame_proto.h"


//--------------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------------

frame_proto::frame_proto()
	: frameNo(-1), keytime(-1.0f)
{ }

frame_proto::~frame_proto()
{ }

frame_proto::frame_proto(const frame_proto& f)
	: frameNo(f.frameNo), keytime(f.keytime)
{ }

frame_proto& frame_proto::operator=(const frame_proto& f)
{
	if (this != &f)
	{
		this->frameNo = f.frameNo;
		this->keytime = f.keytime;
	}

	return *this;
}


//--------------------------------------------------------------------------------
//	SERIALIZATION
//--------------------------------------------------------------------------------

void frame_proto::serialize(frame_proto_mssg& out) const
{
	out.set_frameno((unsigned int)this->frameNo);
	out.set_keytime(this->keytime);

	//bone list
	for (unsigned int i = 0; i < bones.size(); ++i)
	{
		//add new element
		bone_proto_mssg* mssg = out.add_bones();

		//serialize info to mssg
		this->bones[i].serialize(*mssg);
	}
}

void frame_proto::deserialize(const frame_proto_mssg& in)
{
	this->frameNo = (int)in.frameno();
	this->keytime = in.keytime();

	//bone list
	assert(in.bones_size() > 0);
	this->bones.clear();

	bone_proto tempb;
	for (int i = 0; i < in.bones_size(); ++i)
	{
		this->bones.push_back(tempb);
	}

	for (int k = 0; k < in.bones_size(); ++k)
	{
		//grab element at given index
		bone_proto_mssg mssg = in.bones(k);

		//fill vector
		this->bones[(unsigned int)k].deserialize(mssg);
	}
}
