#include "Rasterizer.h"

// A function for drawing a line where the slope is <= 1
// Left is the smaller x position, right is the highest x position
// this allows us to always index in a positive direction (sipmle math)
void DrawLineHorizontal(const Vertex& left, const Vertex& right)
{
	float dx = right._pos.x - left._pos.x;
	int startX = static_cast<int>(left._pos.x);
	int endX = static_cast<int>(right._pos.x);
	for (int x = startX; x <= endX; ++x)
	{
		float t = static_cast<float>(x - startX) / dx;
		Vertex v = LerpVertex(left, right, t);
		Rasterizer::Get()->DrawPoint(v);
	}
}

// A function for drawing a line where the slope is > 1 (vertical)
void DrawLineVertical(const Vertex& low, const Vertex& high)
{
	float dy = high._pos.y - low._pos.y;
	int startY = static_cast<int>(low._pos.y);
	int endY = static_cast<int>(high._pos.y);
	for (int y = startY; y <= endY; ++y)
	{
		float t = static_cast<float>(y) / dy;
		Vertex v = LerpVertex(low, high, t);
		Rasterizer::Get()->DrawPoint(v);

	}
}

Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(const Vertex& v)
{
	X::DrawPixel(v._pos.x, v._pos.y, v._color);
}

void Rasterizer::DrawLine(const Vertex& a, const Vertex& b)
{
	float dx = b._pos.x - a._pos.x;
	float dy = b._pos.y - a._pos.y;

	// check if vertical, else horizontal
	if (MathHelper::CheckEqual(dx, 0.0f) || abs(dy / dx) > 1.0f)
	{
		if (a._pos.y < b._pos.y)
		{
			DrawLineVertical(a, b);
		}
		else
		{
			DrawLineVertical(b, a);
		}
	}
	// else draw horizontal
	else
	{
		if (a._pos.x < b._pos.x)
		{
			DrawLineHorizontal(a, b);
		}
		else
		{
			DrawLineHorizontal(b, a);
		}
	}
}

void Rasterizer::DrawTriangle(const Vertex& a, const Vertex& b, const Vertex& c)
{
}
