	#pragma once

#include <XEngine.h>
#include  "Vertex.h"

enum class FillMode
{
	Wireframe,
	Solid
};

enum class ShadeMode
{
	Flat,	// per face lighting
	Gouraud,	// per vertex lighting
	Phong,	// Per pixel lighting
};

class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);
	void SetFillMode(FillMode fillMode);
	void SetShadeMode(ShadeMode shadeMode);
	ShadeMode GetShadeMode() const;

	void DrawPoint(int x, int y);

	// topology renders
	void DrawPoint(const Vertex& v);
	void DrawLine(const Vertex& a, const Vertex& b);
	void DrawTriangle(const Vertex& a, const Vertex& b, const Vertex& c);

private:
	X::Color m_Color = X::Colors::White;
	FillMode m_FillMode = FillMode::Solid;
	ShadeMode m_shadeMode = ShadeMode::Flat;
	void DrawFilledTriangle(const Vertex& a, const Vertex& b, const Vertex& c);
};