#include "Translate.h"

GLenum Translate::GetWrap(texture_proto::WRAP w)
{
	GLenum wrap;

	switch (w)
	{
	case texture_proto::WRAP::CLAMP_TO_EDGE:
		wrap = GL_CLAMP_TO_EDGE;
		break;

	case texture_proto::WRAP::REPEAT:
		wrap = GL_REPEAT;
		break;

	case texture_proto::WRAP::MIRRORED_REPEAT:
		wrap = GL_MIRRORED_REPEAT;
		break;

	default:
		wrap = GL_CLAMP_TO_EDGE;
		assert(false);

	}

	return wrap;
}

GLenum Translate::GetFilter(texture_proto::MIN_FILTER _min)
{
	GLenum min;

	switch (_min)
	{
	case texture_proto::MIN_FILTER::MIN_NEAREST:
		min = GL_NEAREST;
		break;

	case texture_proto::MIN_FILTER::MIN_LINEAR:
		min = GL_LINEAR;
		break;

	case texture_proto::MIN_FILTER::MIN_NEAREST_MIPMAP_NEAREST:
		min = GL_NEAREST_MIPMAP_NEAREST;
		break;

	case texture_proto::MIN_FILTER::MIN_LINEAR_MIPMAP_NEAREST:
		min = GL_LINEAR_MIPMAP_NEAREST;
		break;

	case texture_proto::MIN_FILTER::MIN_NEAREST_MIPMAP_LINEAR:
		min = GL_NEAREST_MIPMAP_LINEAR;
		break;

	case texture_proto::MIN_FILTER::MIN_LINEAR_MIPMAP_LINEAR:
		min = GL_LINEAR_MIPMAP_LINEAR;
		break;

	default:
		min = GL_LINEAR;
	}

	return min;
}

GLenum Translate::GetFilter(texture_proto::MAG_FILTER _mag)
{
	GLenum mag;

	switch (_mag)
	{
	case texture_proto::MAG_FILTER::MAG_NEAREST:
		mag = GL_NEAREST;
		break;

	case texture_proto::MAG_FILTER::MAG_LINEAR:
		mag = GL_LINEAR;
		break;

	default:
		mag = GL_LINEAR;
	}

	return mag;
}

GLenum Translate::GetFormat(texture_proto::EFORMAT _eformat)
{
	GLenum eformat;

	switch (_eformat)
	{
	case texture_proto::EFORMAT::EFORMAT_RGB:
		eformat = GL_RGB;
		break;
	case texture_proto::EFORMAT::EFORMAT_RGBA:
		eformat = GL_RGBA;
		break;
	case texture_proto::EFORMAT::EFORMAT_BGR:
		eformat = GL_BGR;
		break;
	case texture_proto::EFORMAT::EFORMAT_BGRA:
		eformat = GL_BGRA;
		break;
	default:
		eformat = GL_RGB;
		break;
	}

	return eformat;
}

GLenum Translate::GetComponent(texture_proto::NCOMPONENT ncomponent)
{
	GLenum component;

	switch (ncomponent)
	{
	case texture_proto::NCOMPONENT::NCOMPONENT_RGB:
		component = GL_RGB;
		break;
	case texture_proto::NCOMPONENT::NCOMPONENT_RGBA:
		component = GL_RGBA;
		break;
	case texture_proto::NCOMPONENT::NCOMPONENT_BGR:
		component = GL_BGR;
		break;
	case texture_proto::NCOMPONENT::NCOMPONENT_BGRA:
		component = GL_BGRA;
		break;
	default:
		component = GL_RGB;
	}

	return component;
}