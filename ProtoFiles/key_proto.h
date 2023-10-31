#pragma once
#ifndef KEY_PROTO_H
#define KEY_PROTO_H

#include "key_proto.pb.h"

class key_proto
{
public:
	int key;	//character key
	int x;		//x,y --> start pos
	int y;
	int w;		//w,h --> size of chara
	int h;

	key_proto();
	~key_proto();
	key_proto(const key_proto& k);
	key_proto& operator=(const key_proto& k);

	void serialize(key_proto_mssg& out) const;
	void deserialize(const key_proto_mssg& in);

};
#endif // !KEY_PROTO_H
