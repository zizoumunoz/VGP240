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

enum class CullMode
{
	None,	// no culling used
	Back,	// cull anything facing away from the camera
	Front	// cull anything facing the camera
};

class PrimitivesManager
{
public:
	static PrimitivesManager* Get();

	void OnNewFrame();
	void SetCullMode(CullMode mode);

	// Start accepting vertices
	bool BeginDraw(Topology topology, bool applyTransform);
	// Add vertices to the manager
	void AddVertex(const Vertex& v);
	// Send all the stored vertices to render as specified
	// by topology, to the rasterizer
	void EndDraw();


private:
	PrimitivesManager();

	std::vector<Vertex> m_vertexBuffer;
	Topology m_topology = Topology::Point;
	CullMode m_cullMode = CullMode::None;
	bool m_drawBegin = false;
	bool m_applyTransform = false;
};