#pragma once

#include <XEngine.h>
#include  "Vertex.h"

enum class FillMode
{
	Wireframe,
	Solid
};

class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);
	void SetFillMode(FillMode fillMode);

	void DrawPoint(int x, int y);

	// topology renders
	void DrawPoint(const Vertex& v);
	void DrawLine(const Vertex& a, const Vertex& b);
	void DrawTriangle(const Vertex& a, const Vertex& b, const Vertex& c);

private:
	void DrawFilledTriangle(const Vertex& a, const Vertex& b, const Vertex& c);
	X::Color m_Color = X::Colors::White;
	FillMode m_FillMode = FillMode::Wireframe;

};