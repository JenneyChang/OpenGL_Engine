#pragma once
#ifndef ANIM_PROTO_H
#define ANIM_PROTO_H

#include "clip_proto.h"
#include "anim_proto.pb.h"

class anim_proto
{
public:
	int numClips;
	int skelSize;
	std::vector<clip_proto> clips;

	anim_proto();
	~anim_proto();
	anim_proto(const anim_proto&) = delete;
	anim_proto& operator=(const anim_proto&) = delete;

	void serialize(anim_proto_mssg& out) const;
	void deserialize(const anim_proto_mssg& in);


};
#endif // !ANIM_PROTO_H
