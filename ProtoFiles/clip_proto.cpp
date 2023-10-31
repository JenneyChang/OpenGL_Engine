#include "clip_proto.h"


//--------------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------------

clip_proto::clip_proto()
	: numFrames(-1), duration(-1.0f)
{ }

clip_proto::~clip_proto()
{ }


//--------------------------------------------------------------------------------
//	SERIALIZATION
//--------------------------------------------------------------------------------

void clip_proto::serialize(clip_proto_mssg& out) const
{
	out.set_numframes((unsigned int)this->numFrames);
	out.set_duration(this->duration);

	//frame list
	for (unsigned int i = 0; i < frames.size(); ++i)
	{
		//add new element
		frame_proto_mssg* mssg = out.add_frames();

		//serialize to mssg
		this->frames[i].serialize(*mssg);
	}
}

void clip_proto::deserialize(const clip_proto_mssg& in)
{
	this->numFrames = (int)in.numframes();
	this->duration = in.duration();

	//frame list
	assert(in.frames_size() > 0);
	this->frames.clear();

	frame_proto tempf;
	for (int i = 0; i < in.frames_size(); ++i)
	{
		//prefill 
		this->frames.push_back(tempf);
	}

	for (int k = 0; k < in.frames_size(); ++k)
	{
		//grab element at given index
		frame_proto_mssg mssg = in.frames(k);

		//fill vector
		this->frames[(unsigned int)k].deserialize(mssg);
	}
}
