#pragma once

#include <XEngine.h>
#include  "Vertex.h"

class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);

	void DrawPoint(int x, int y);

	// topology renders
	void DrawPoint(const Vertex& v);
	void DrawLine(const Vertex& a, const Vertex& b);
	void DrawTriangle(const Vertex& a, const Vertex& b, const Vertex& c);

private:
	X::Color mColor = X::Colors::White;
};