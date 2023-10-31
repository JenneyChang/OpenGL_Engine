#pragma once
#ifndef RECT_H
#define RECT_H

namespace Azul
{
	struct Rect
	{
		float x;
		float y;
		float w;
		float h;

		Rect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f) { }
		~Rect() = default;
		
		Rect(float _x, float _y, float _w, float _h)
			: x(_x), y(_y), w(_w), h(_h)
		{ }

		Rect(const Rect&) = default;
		Rect& operator=(const Rect&) = default;
		
		void Set(float _x, float _y, float _w, float _h)
		{
			this->x  = _x;
			this->y  = _y;
			this->w  = _w;
			this->h  = _h;
		}

		void Clear()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->w = 0.0f;
			this->h = 0.0f;
		}
	};
}
#endif // !RECT_H
