#pragma once
#ifndef FONT_PROTO_H
#define FONT_PROTO_H

#include "key_proto.h"
#include "texture_proto.h"
#include "font_proto.pb.h"

//todo: instead of embedding texture...put hashID identifier?
class font_proto
{
public:
	static const unsigned int NAMESIZE = 64;
	const char* fontname[NAMESIZE];

	std::vector<key_proto> keylist;
	texture_proto fontTex;

	font_proto();
	~font_proto();
	font_proto(const font_proto&) = delete;
	font_proto& operator=(const font_proto&) = delete;

	void serialize(font_proto_mssg& out) const;
	void deserialize(const font_proto_mssg& in);


};
#endif // !FONT_PROTO_H
