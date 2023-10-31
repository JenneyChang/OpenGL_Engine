#pragma once
#ifndef FRAME_PROTO_H
#define FRAME_PROTO_H

#include "bone_proto.h"
#include "frame_proto.pb.h"

class frame_proto
{
public:
	int frameNo;
	float keytime;

	//series of bone(joint) manipulations asso w/ a frame
	std::vector<bone_proto> bones;

	frame_proto();
	~frame_proto();
	frame_proto(const frame_proto& f);
	frame_proto& operator=(const frame_proto& f);

	void serialize(frame_proto_mssg& out) const;
	void deserialize(const frame_proto_mssg& in);


};
#endif // !FRAME_PROTO_H
