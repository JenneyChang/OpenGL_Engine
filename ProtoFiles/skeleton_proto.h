#pragma once
#ifndef SKELETON_PROTO_H
#define SKELETON_PROTO_H

#include "skeleton_proto.pb.h"

class skeleton_proto
{
public:
	int nodeIndex;
	std::string nodeName;

	int parentIndex;
	std::string parentName;

	int prevIndex = -1;
	int nextIndex = -1;

	skeleton_proto();
	~skeleton_proto();
	skeleton_proto(const skeleton_proto&) = default;
	skeleton_proto& operator= (const skeleton_proto&) = default;

	void serialize(skeleton_proto_mssg& out) const;
	void deserialize(const skeleton_proto_mssg& in);


};
#endif // !SKELETON_PROTO_H
