#include "Rasterizer.h"

// A function for drawing a line where the slope is <= 1
// Left is the smaller x position, right is the highest x position
// this allows us to always index in a positive direction (sipmle math)
void DrawLineHorizontal(const Vertex& left, const Vertex& right)
{
	float dx = right.m_pos.x - left.m_pos.x;
	int startX = static_cast<int>(left.m_pos.x);
	int endX = static_cast<int>(right.m_pos.x);
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
	float dy = high.m_pos.y - low.m_pos.y;
	int startY = static_cast<int>(low.m_pos.y);
	int endY = static_cast<int>(high.m_pos.y);
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
	X::DrawPixel(v.m_pos.x, v.m_pos.y, v.m_color);
}

void Rasterizer::DrawLine(const Vertex& a, const Vertex& b)
{
	float dx = b.m_pos.x - a.m_pos.x;
	float dy = b.m_pos.y - a.m_pos.y;

	// check if vertical, else horizontal
	if (MathHelper::CheckEqual(dx, 0.0f) || abs(dy / dx) > 1.0f)
	{
		if (a.m_pos.y < b.m_pos.y)
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
		if (a.m_pos.x < b.m_pos.x)
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
				return lhs.m_pos.y < rhs.m_pos.y;
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

	float dy = c.m_pos.y - a.m_pos.y;
	// if a and b are the same, triangle is a flat top
	if (MathHelper::CheckEqual(a.m_pos.y, b.m_pos.y))
	{
		int startY = static_cast<int>(a.m_pos.y);
		int endY = static_cast<int>(c.m_pos.y);
		for (int y = startY; y <= endY; ++y)
		{
			float t = static_cast<float>(y - startY) / dy;
			Vertex aSide = LerpVertex(a, c, t);
			Vertex bSide = LerpVertex(b, c, t);
			DrawLine(aSide, bSide);
		}
	}

	// if b and c are the same, triangle is a flat bottom
	else if (MathHelper::CheckEqual(b.m_pos.y, c.m_pos.y))
	{
		int startY = static_cast<int>(a.m_pos.y);
		int endY = static_cast<int>(c.m_pos.y);
		for (int y = startY; y <= endY; ++y)
		{
			float t = static_cast<float>(y - startY) / dy;
			Vertex bSide = LerpVertex(a, b, t);
			Vertex cSide = LerpVertex(a, c, t);
			DrawLine(bSide, cSide);
		}
	}

	// no edges, need a split vertex
	else
	{
		float t = (b.m_pos.y - a.m_pos.y) / dy;
		Vertex splitVertex = LerpVertex(a, c, t);
		// bottom flat fill
		DrawFilledTriangle(a, b, splitVertex);
		// top is flat fill
		DrawFilledTriangle(b, splitVertex, c);
	}

}
