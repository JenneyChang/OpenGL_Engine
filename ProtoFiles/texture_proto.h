#pragma once
#ifndef TEXTURE_PROTO_H
#define TEXTURE_PROTO_H

#include "texture_proto.pb.h"

class texture_proto
{
public:
	enum class TYPE
	{
		JPEG = 0,
		PNG = 1,
		BMP = 2,
		GIF = 3,
		TGA = 4,
		DEFAULT = TGA
	};

	enum class MAG_FILTER
	{
		MAG_NEAREST = 0,
		MAG_LINEAR = 1,
		DEFAULT = MAG_LINEAR
	};

	enum class MIN_FILTER
	{
		MIN_NEAREST = 0,
		MIN_LINEAR = 1,
		MIN_NEAREST_MIPMAP_NEAREST = 2,
		MIN_LINEAR_MIPMAP_NEAREST = 3,
		MIN_NEAREST_MIPMAP_LINEAR = 4,
		MIN_LINEAR_MIPMAP_LINEAR = 5,
		DEFAULT = MIN_LINEAR
	};

	enum class WRAP
	{
		CLAMP_TO_EDGE = 0,
		MIRRORED_REPEAT = 1,
		REPEAT = 2,
		DEFAULT = CLAMP_TO_EDGE
	};

	enum class COMPONENT
	{
		BYTE = 0,
		UNSIGNED_BYTE = 1,
		SHORT = 2,
		UNSIGNED_SHORT = 3,
		INT = 4,
		UNSIGNED_INT = 5,
		FLOAT = 6,
		DOUBLE = 7,
		DEFAULT = UNSIGNED_BYTE
	};

	enum class EFORMAT
	{
		EFORMAT_BGR = 0,
		EFORMAT_RGB = 1,
		EFORMAT_RGBA = 2,
		EFORMAT_BGRA = 3,
		DEFAULT = EFORMAT_RGBA
	};

	enum class NCOMPONENT
	{
		NCOMPONENT_BGR = 0,
		NCOMPONENT_RGB = 1,
		NCOMPONENT_RGBA = 2,
		NCOMPONENT_BGRA = 3,
		DEFAULT = NCOMPONENT_RGBA
	};


	static const unsigned int FILENAME_SIZE = 64;

	TYPE			type;
	MAG_FILTER		magFilter;
	MIN_FILTER		minFilter;
	WRAP			wrapS;
	WRAP			wrapT;
	COMPONENT		pixelType;
	EFORMAT			eformat;
	NCOMPONENT		ncomponent;

	bool			enabled;
	bool			as_is;
	unsigned int	width;
	unsigned int	height;

	//     N=#comp     components
	//       1           grey
	//       2           grey, alpha
	//       3           red, green, blue
	//       4           red, green, blue, alpha
	unsigned int	component;	 // bits per channel
	unsigned int	bits;		 // bits per channel 8, 16, 32 per color

	unsigned int	hash;

	unsigned int	dataSize;
	char			filename[FILENAME_SIZE];
	unsigned char* pData;


public:
	texture_proto();
	~texture_proto();
	texture_proto(const texture_proto& tp);
	texture_proto& operator=(const texture_proto& tp);

	void serialize(texture_proto_mssg& out) const;
	void deserialize(const texture_proto_mssg& in);


};
#endif // !TEXTURE_PROTO_H
