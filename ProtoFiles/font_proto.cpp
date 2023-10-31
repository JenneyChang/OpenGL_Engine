#include "font_proto.h"

//--------------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------------

font_proto::font_proto()
	: fontname{ 0 },/* hashID(0),*/ fontTex()
{ }

font_proto::~font_proto()
{
	this->keylist.clear();
}


//--------------------------------------------------------------------------------
//	SERIALIZATION
//--------------------------------------------------------------------------------

void font_proto::serialize(font_proto_mssg& out) const
{
	//font name
	std::string name((const char*)this->fontname, NAMESIZE);
	out.set_fontname(name);

	//hash id
	//out.set_hashid(this->hashID);

	//associated texture hash id
	//out.set_textureid(this->textureID);

	//texture data
	texture_proto_mssg* texMssg = new texture_proto_mssg();
	this->fontTex.serialize(*texMssg);
	out.set_allocated_fonttex(texMssg);

	//font key/charas
	for (unsigned int i = 0; i < keylist.size(); ++i)
	{
		//add new element (returns pointer to it)
		key_proto_mssg* mssg = out.add_keys();

		//serialize key info --> mssg
		this->keylist[i].serialize(*mssg);
	}
}

void font_proto::deserialize(const font_proto_mssg& in)
{
	//font name
	memcpy_s(this->fontname, NAMESIZE, in.fontname().data(), NAMESIZE);

	//hash
	//this->hashID = in.hashid();

	//texture
	this->fontTex.deserialize(in.fonttex());


	//font keys
	assert(in.keys_size() > 0);
	this->keylist.clear();

	//fill w/ default
	key_proto tempk;
	for (int k = 0; k < in.keys_size(); ++k)
	{
		this->keylist.push_back(tempk);
	}

	//push actual info
	for (int i = 0; i < in.keys_size(); ++i)
	{
		//grab element at given index
		key_proto_mssg mssg = in.keys(i);

		//fill vector
		this->keylist[(unsigned int)i].deserialize(mssg);
	}
}