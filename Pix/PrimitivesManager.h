#pragma once

#include "Vertex.h"

// purpose of the Primitives Manager is to store all of the vertices
// render all of the shapes based on topology
// clip/cull all of the non visible faces

enum class Topology
{
	Point,
	Line,
	Triangle
};

class PrimitivesManager
{
public:
	static PrimitivesManager* Get();

	// Start accepting vertices
	bool BeginDraw(Topology topology);
	// Add vertices to the manager
	void AddVertex(const Vertex& v);
	// Send all the stored vertices to render as specified
	// by topology, to the rasterizer
	void EndDraw();

private:
	PrimitivesManager();

	std::vector<Vertex> m_VertexBuffer;
	Topology m_Topology = Topology::Point;
	bool m_DrawBegin = false;

};