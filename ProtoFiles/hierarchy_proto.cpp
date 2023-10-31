#include "hierarchy_proto.h"


//--------------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------------

hierarchy_proto::hierarchy_proto()
	: skelSize(-1), hierarchyDepth(-1), tableSize(0)
{ }

hierarchy_proto::~hierarchy_proto()
{ }


//--------------------------------------------------------------------------------
//	SERIALIZATION
//--------------------------------------------------------------------------------

void hierarchy_proto::serialize(hierarchy_proto_mssg& out) const
{
	out.set_skelsize(this->skelSize);
	out.set_hierarchydepth(this->hierarchyDepth);
	out.set_tablesize(this->tableSize);

	//orig skeleton list
	for (size_t i = 0; i < origList.size(); ++i)
	{
		//add new element
		skeleton_proto_mssg* mssg = out.add_origlist();

		//serialize to mssg
		origList[i].serialize(*mssg);
	}

	//ordered skeleton list
	for (size_t i = 0; i < orderedList.size(); ++i)
	{
		//add new element
		skeleton_proto_mssg* mssg = out.add_orderedlist();

		//serialize to mssg
		orderedList[i].serialize(*mssg);
	}
	//corrected skeleton list
	//for (size_t i = 0; i < correctedList.size(); ++i)
	//{
	//	//add new element
	//	skeleton_proto_mssg* mssg = out.add_correctedlist();
	//	
	//	//serialize to mssg
	//	correctedList[i].serialize(*mssg);
	//}

	//hierarchy table
	for (size_t i = 0; i < tableSize; ++i)
	{
		out.add_hierarchytable(hierarchyTable[i]);
	}
}

void hierarchy_proto::deserialize(const hierarchy_proto_mssg& in)
{
	this->skelSize = (int)in.skelsize();
	this->hierarchyDepth = in.hierarchydepth();
	this->tableSize = in.tablesize();

	//shouldnt be empty...
	assert(in.origlist_size() > 0);
	assert(in.orderedlist_size() > 0);
	//assert(in.correctedlist_size() > 0);
	assert(in.hierarchytable_size() > 0);

	//grab orig skel list
	this->origList.clear();
	for (int i = 0; i < in.origlist_size(); ++i)
	{
		skeleton_proto sproto;
		this->origList.push_back(sproto);
	}
	for (int i = 0; i < in.origlist_size(); ++i)
	{
		skeleton_proto_mssg mssg = in.origlist(i);
		this->origList[(size_t)i].deserialize(mssg);
	}

	//grab ordered skeleton
	this->orderedList.clear();
	for (int i = 0; i < in.orderedlist_size(); ++i)
	{
		skeleton_proto sproto;
		this->orderedList.push_back(sproto);
	}
	for (int i = 0; i < in.orderedlist_size(); ++i)
	{
		skeleton_proto_mssg mssg = in.orderedlist(i);
		this->orderedList[(unsigned int)i].deserialize(mssg);
	}

	//grab corrected skeleton list
	/*this->correctedList.clear();
	for (int i = 0; i < in.correctedlist_size(); ++i)
	{
		skeleton_proto sproto;
		this->correctedList.push_back(sproto);
	}
	for (int i = 0; i < in.correctedlist_size(); ++i)
	{
		skeleton_proto_mssg mssg = in.correctedlist(i);
		this->correctedList[(unsigned int)i].deserialize(mssg);
	}*/
	
	//grab hierarchy table
	this->hierarchyTable.clear();
	for (size_t i = 0; i < tableSize; ++i)
	{
		this->hierarchyTable.push_back(in.hierarchytable(i));
	}
}