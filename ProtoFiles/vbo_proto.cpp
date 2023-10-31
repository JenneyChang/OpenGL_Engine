#include "vbo_proto.h"


//--------------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------------

vbo_proto::vbo_proto()
	: target(TARGET::DEFAULT), component(COMPONENT::DEFAULT), type(TYPE::DEFAULT),
	enabled(false), attribIndex(0), count(0), dataSize(0), pData(nullptr)
{ }

vbo_proto::~vbo_proto()
{
	delete[] this->pData;
}

vbo_proto::vbo_proto(const vbo_proto& vp)
	: target(vp.target), component(vp.component), type(vp.type), enabled(vp.enabled),
	attribIndex(vp.attribIndex), count(vp.count), dataSize(vp.dataSize)
{
	//raw data buffer
	this->pData = new unsigned char[this->dataSize]();
	assert(this->pData);

	memcpy_s(this->pData, this->dataSize, vp.pData, vp.dataSize);
}

vbo_proto& vbo_proto::operator=(const vbo_proto& vp)
{
	if (this != &vp)
	{
		//clear raw buffer --> array 
		delete[] this->pData;
		this->pData = nullptr;

		//do the copy
		this->target = vp.target;
		this->component = vp.component;
		this->type = vp.type;

		this->enabled = vp.enabled;
		this->attribIndex = vp.attribIndex;
		this->count = vp.count;
		this->dataSize = vp.dataSize;

		this->pData = new unsigned char[this->dataSize]();
		assert(this->pData);
		memcpy_s(this->pData, this->dataSize, vp.pData, vp.dataSize);
	}

	return *this;
}


//--------------------------------------------------------------------------------
//	SERIALIZATION
//--------------------------------------------------------------------------------

void vbo_proto::serialize(vbo_proto_mssg& out) const
{
	out.set_target((vbo_proto_mssg_TARGET)this->target);
	out.set_component((vbo_proto_mssg_COMPONENT)this->component);
	out.set_type((vbo_proto_mssg_TYPE)this->type);

	out.set_enabled(this->enabled);
	out.set_attribindex(this->attribIndex);
	out.set_count(this->count);
	out.set_datasize(this->dataSize);

	std::string temp((const char*)this->pData, this->dataSize);
	out.set_pdata(temp);
}

void vbo_proto::deserialize(const vbo_proto_mssg& in)
{
	this->target = (vbo_proto::TARGET)in.target();
	this->component = (vbo_proto::COMPONENT)in.component();
	this->type = (vbo_proto::TYPE)in.type();

	this->enabled = in.enabled();
	this->attribIndex = in.attribindex();
	this->count = in.count();
	this->dataSize = in.datasize();

	//clear raw buffer
	delete[] this->pData;
	this->pData = nullptr;

	//deserialize if data exists
	if (this->dataSize > 0)
	{
		this->pData = new unsigned char[this->dataSize]();
		assert(this->pData);

		memcpy_s(this->pData, this->dataSize, in.pdata().data(), in.pdata().size());
	}
}