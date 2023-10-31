#pragma once
#ifndef HIERARCHY_PROTO_H
#define HIERARCHY_PROTO_H

#include "skeleton_proto.h"
#include "hierarchy_proto.pb.h"

class hierarchy_proto
{
public:
	int skelSize;
	int hierarchyDepth;
	unsigned int tableSize;

	std::vector<skeleton_proto> origList;
	std::vector<skeleton_proto> orderedList;	//act don't need this?
	//std::vector<skeleton_proto> correctedList;	//tech can be arrays...?

	std::vector<int> hierarchyTable;

	hierarchy_proto();
	~hierarchy_proto();
	hierarchy_proto(const hierarchy_proto&) = default;
	hierarchy_proto& operator=(const hierarchy_proto&) = default;

	void serialize(hierarchy_proto_mssg& out) const;
	void deserialize(const hierarchy_proto_mssg& in);


};
#endif // !HIERARCHY_PROTO_H
