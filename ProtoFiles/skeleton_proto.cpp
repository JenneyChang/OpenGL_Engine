#include "skeleton_proto.h"


//--------------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------------

skeleton_proto::skeleton_proto()
	: nodeIndex(-1), nodeName("na"), parentIndex(-1), parentName("na")
{ }

skeleton_proto::~skeleton_proto()
{ }


//--------------------------------------------------------------------------------
//	SERIALIZATION
//--------------------------------------------------------------------------------

void skeleton_proto::serialize(skeleton_proto_mssg& out) const
{
	out.set_nodeindex(this->nodeIndex);
	out.set_parentindex(this->parentIndex);
	out.set_previndex(this->prevIndex);
	out.set_nextindex(this->nextIndex);
	
	out.set_nodename(this->nodeName);
	out.set_parentname(this->parentName);
}

void skeleton_proto::deserialize(const skeleton_proto_mssg& in)
{
	this->nodeIndex = (int)in.nodeindex();
	this->parentIndex = (int)in.parentindex();
	this->prevIndex = (int)in.previndex();
	this->nextIndex = (int)in.nextindex();

	this->nodeName = in.nodename();
	this->parentName = in.parentname();
}