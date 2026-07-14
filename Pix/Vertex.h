#pragma once

#include "MathHelper.h"
#include <XColors.h>

struct Vertex
{
	Vector3 _pos;		// position of the vertex
	X::Color _color;	// color of the vertex

};

inline Vector3 LerpPosition(const Vector3& a, const Vector3& b, float t)
{
	return
	{
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t
	};
}

inline X::Color LerpColor(const X::Color& a, const X::Color& b, float t)
{
	return
	{
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t,
		a.a + (b.a - a.a) * t
	};
}

inline Vertex LerpVertex(const Vertex& a, const Vertex& b, float t)
{
	Vertex v;
	v._pos = LerpPosition(a._pos, b._pos, t);
	v._color = LerpColor(a._color, b._color, t);

	// because this is typically done in screen space, x and y should be "pixel positions".
	// to convert float to int/index it std::floor(pos.y + 0.5f) , adding 0.5f to round up
	// this is to get pixel position when all is calculated
	// otherise in some functions, the floats miss checks and program infinite loops
	v._pos.x = floorf(v._pos.x + 0.5f);
	v._pos.y = floorf(v._pos.y + 0.5f);

	return v;
}
