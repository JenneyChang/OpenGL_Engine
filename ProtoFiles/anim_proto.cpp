#include "anim_proto.h"

//--------------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------------

anim_proto::anim_proto()
	: numClips(-1), skelSize(-1)
{ }

anim_proto::~anim_proto()
{ }


//--------------------------------------------------------------------------------
//	SERIALIZATION
//--------------------------------------------------------------------------------

void anim_proto::serialize(anim_proto_mssg& out) const
{
	out.set_numclips((unsigned int)this->numClips);
	out.set_skelsize((unsigned int)this->skelSize);

	//clip data
	for (unsigned int k = 0; k < clips.size(); ++k)
	{
		//add new element
		clip_proto_mssg* mssg = out.add_clips();

		//serialize to mssg
		clips[k].serialize(*mssg);
	}
}

void anim_proto::deserialize(const anim_proto_mssg& in)
{
	this->numClips = (int)in.numclips();
	this->skelSize = (int)in.skelsize();

	assert(in.clips_size() > 0);

	//grab anim clips
	this->clips.clear();
	for (int k = 0; k < in.clips_size(); ++k)
	{
		clip_proto temp;
		this->clips.push_back(temp);
	}

	for (int n = 0; n < in.clips_size(); ++n)
	{
		clip_proto_mssg mssg = in.clips(n);
		this->clips[(unsigned int)n].deserialize(mssg);
	}
}