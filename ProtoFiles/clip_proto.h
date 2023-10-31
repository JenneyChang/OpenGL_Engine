#pragma once
#ifndef CLIP_PROTO_H
#define CLIP_PROTO_H

#include "frame_proto.h"
#include "clip_proto.pb.h"

class clip_proto
{
public:
	int numFrames;
	float duration;

	std::vector<frame_proto> frames;

	clip_proto();
	~clip_proto();
	clip_proto(const clip_proto&) = default;
	clip_proto& operator=(const clip_proto&) = default;

	void serialize(clip_proto_mssg& out) const;
	void deserialize(const clip_proto_mssg& in);


};
#endif // !CLIP_PROTO_H
