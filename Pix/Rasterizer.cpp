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
		float t = static_cast<float>(y - startY) / dy;
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
	m_Color = color;
}

void Rasterizer::SetFillMode(FillMode fillMode)
{
	m_FillMode = fillMode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, m_Color);
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
	switch (m_FillMode)
	{
	case FillMode::Wireframe:
	{
		DrawLine(a, b);
		DrawLine(b, c);
		DrawLine(c, a);
	}
	break;
	case FillMode::Solid:
	{
		std::vector<Vertex> sortedVertices = { a, b, c };
		std::sort(sortedVertices.begin(), sortedVertices.end(),
			[](const Vertex& lhs, const Vertex& rhs)
			{
				return lhs._pos.y < rhs._pos.y;
			});
		DrawFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);
	}
	break;
	default:
		break;
	}
}

void Rasterizer::DrawFilledTriangle(const Vertex& a, const Vertex& b, const Vertex& c)
{
	// values passed in are already sorted where a is the lowest value(top of the screen)
	// and c is the highest value (bottom of the screen, remeber positive y goes down)

	float dy = c._pos.y - a._pos.y;
	// if a and b are the same, triangle is a flat top
	if (MathHelper::CheckEqual(a._pos.y, b._pos.y))
	{
		int startY = static_cast<int>(a._pos.y);
		int endY = static_cast<int>(c._pos.y);
		for (int y = startY; y <= endY; ++y)
		{
			float t = static_cast<float>(y - startY) / dy;
			Vertex aSide = LerpVertex(a, c, t);
			Vertex bSide = LerpVertex(b, c, t);
			DrawLine(aSide, bSide);
		}
	}

	// if b and c are the same, triangle is a flat bottom
	else if (MathHelper::CheckEqual(b._pos.y, c._pos.y))
	{
		int startY = static_cast<int>(a._pos.y);
		int endY = static_cast<int>(c._pos.y);
		for (int y = startY; y <= endY; ++y)
		{
			float t = static_cast<float>(y - startY) / dy;
			Vertex bSide = LerpVertex(a, b, t);
			Vertex cSide = LerpVertex(a, c, t);
		}
	}

	// no edges, need a split vertex
	else
	{
		float t = (b._pos.y - a._pos.y) / dy;
		Vertex splitVertex = LerpVertex(a, c, t);
		// bottom flat fill
		DrawFilledTriangle(a, b, splitVertex);
		// top is flat fill
		DrawFilledTriangle(b, splitVertex, c);
	}

}
