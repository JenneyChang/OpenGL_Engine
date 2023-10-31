#include "key_proto.h"


//--------------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------------

key_proto::key_proto()
	: key(-1), x(-1), y(-1), w(-1), h(-1)
{ }

key_proto::~key_proto()
{ }

key_proto::key_proto(const key_proto& k)
	:key(k.key), x(k.x), y(k.y), w(k.w), h(k.h)
{ }

key_proto& key_proto::operator=(const key_proto& k)
{
	if (this != &k)
	{
		this->key = k.key;
		this->x = k.x;
		this->y = k.y;
		this->w = k.w;
		this->h = k.h;
	}

	return *this;
}


//--------------------------------------------------------------------------------
//	SERIALIZATION
//--------------------------------------------------------------------------------

void key_proto::serialize(key_proto_mssg& out) const
{
	out.set_key((unsigned int)this->key);
	out.set_x((unsigned int)this->x);
	out.set_y((unsigned int)this->y);
	out.set_w((unsigned int)this->w);
	out.set_h((unsigned int)this->h);
}

void key_proto::deserialize(const key_proto_mssg& in)
{
	this->key = (int)in.key();
	this->x = (int)in.x();
	this->y = (int)in.y();
	this->w = (int)in.w();
	this->h = (int)in.h();
}