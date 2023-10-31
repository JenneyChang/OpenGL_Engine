#include "texture_proto.h"


//--------------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------------

texture_proto::texture_proto()
	: type(TYPE::DEFAULT), magFilter(MAG_FILTER::DEFAULT), minFilter(MIN_FILTER::DEFAULT),
	wrapS(WRAP::DEFAULT), wrapT(WRAP::DEFAULT), pixelType(COMPONENT::DEFAULT), eformat(EFORMAT::DEFAULT),
	ncomponent(NCOMPONENT::DEFAULT), enabled(false), as_is(false), width(0), height(0),
	component(0), bits(0), hash(0), dataSize(0), filename{ 0 }, pData(nullptr)
{ }

texture_proto::~texture_proto()
{
	delete[] this->pData;
}

texture_proto::texture_proto(const texture_proto& tp)
	: type(tp.type), magFilter(tp.magFilter), minFilter(tp.minFilter), wrapS(tp.wrapS), wrapT(tp.wrapT),
	pixelType(tp.pixelType), eformat(tp.eformat), ncomponent(tp.ncomponent), enabled(tp.enabled),
	as_is(tp.as_is), width(tp.width), height(tp.height), component(tp.component), bits(tp.bits),
	hash(tp.hash), dataSize(tp.dataSize)
{
	//file name
	memcpy_s((void*)this->filename, FILENAME_SIZE, tp.filename, FILENAME_SIZE);

	//raw buffer bits
	this->pData = new unsigned char[this->dataSize]();
	assert(this->pData);

	memcpy_s(this->pData, this->dataSize, tp.pData, tp.dataSize);
}

texture_proto& texture_proto::operator=(const texture_proto& tp)
{
	if (this != &tp)
	{
		//clear buffer
		delete[] this->pData;
		this->pData = nullptr;

		this->type = tp.type;
		this->magFilter = tp.magFilter;
		this->minFilter = tp.minFilter;
		this->wrapS = tp.wrapS;
		this->wrapT = tp.wrapT;
		this->pixelType = tp.pixelType;
		this->eformat = tp.eformat;
		this->ncomponent = tp.ncomponent;

		this->enabled = tp.enabled;
		this->as_is = tp.as_is;
		this->width = tp.width;
		this->height = tp.height;
		this->component = tp.component;
		this->bits = tp.bits;
		this->hash = tp.hash;
		this->dataSize = tp.dataSize;

		//file name
		memcpy_s((void*)this->filename, FILENAME_SIZE, tp.filename, FILENAME_SIZE);

		//raw data buffer
		this->pData = new unsigned char[this->dataSize]();
		assert(this->pData);

		memcpy_s(this->pData, this->dataSize, tp.pData, tp.dataSize);
	}

	return *this;
}


//--------------------------------------------------------------------------------
//	SERIALIZATION
//--------------------------------------------------------------------------------

void texture_proto::serialize(texture_proto_mssg& out) const
{
	out.set_type((texture_proto_mssg_TYPE)this->type);
	out.set_magfilter((texture_proto_mssg_MAG_FILTER)this->magFilter);
	out.set_minfilter((texture_proto_mssg_MIN_FILTER)this->minFilter);
	out.set_wraps((texture_proto_mssg_WRAP)this->wrapS);
	out.set_wrapt((texture_proto_mssg_WRAP)this->wrapT);
	out.set_pixeltype((texture_proto_mssg_COMPONENT)this->pixelType);
	out.set_eformat((texture_proto_mssg_EFORMAT)this->eformat);
	out.set_ncomponent((texture_proto_mssg_NCOMPONENT)this->ncomponent);

	out.set_enabled(this->enabled);
	out.set_as_is(this->as_is);
	out.set_width(this->width);
	out.set_height(this->height);
	out.set_component(this->component);
	out.set_bits(this->bits);
	out.set_hash(this->hash);
	out.set_datasize(this->dataSize);

	//file name
	std::string name((const char*)this->filename, FILENAME_SIZE);
	out.set_filename(name);

	//raw data
	std::string data((const char*)this->pData, this->dataSize);
	out.set_pdata(data);
}

void texture_proto::deserialize(const texture_proto_mssg& in)
{
	this->type = (TYPE)in.type();
	this->magFilter = (MAG_FILTER)in.magfilter();
	this->minFilter = (MIN_FILTER)in.minfilter();
	this->wrapS = (WRAP)in.wraps();
	this->wrapT = (WRAP)in.wrapt();
	this->pixelType = (COMPONENT)in.pixeltype();
	this->eformat = (EFORMAT)in.eformat();
	this->ncomponent = (NCOMPONENT)in.ncomponent();

	this->enabled = in.enabled();
	this->as_is = in.as_is();
	this->width = in.width();
	this->height = in.height();
	this->component = in.component();
	this->bits = in.bits();
	this->hash = in.hash();
	this->dataSize = in.datasize();

	//file name
	memcpy_s((void*)this->filename, this->FILENAME_SIZE, in.filename().data(), this->FILENAME_SIZE);

	//raw data
	if (this->dataSize > 0)
	{
		this->pData = new unsigned char[this->dataSize]();
		assert(this->pData);

		memcpy_s(this->pData, this->dataSize, in.pdata().data(), in.datasize());
	}
}