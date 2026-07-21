#include "Clipper.h"
#include "Viewport.h"	// we need something to clip against

Clipper* Clipper::Get()
{
	static Clipper s_Instance;
	return &s_Instance;
}

void Clipper::OnNewFrame()
{
	m_IsClipping = false;
}

bool Clipper::ClipPoint(const Vertex& v)
{
	if (!m_IsClipping)
	{
		return false;	// means render it, do not clip it
	}

	Viewport* vp = Viewport::Get();
	float minX = vp->GetMinX();
	float maxX = vp->GetMaxX();
	float minY = vp->GetMinY();
	float maxY = vp->GetMaxX();

	return v.m_pos.x < minX || v.m_pos.x > maxX
		|| v.m_pos.y < minY || v.m_pos.y > maxY;

}

bool Clipper::ClipLine(Vertex& a, Vertex& b)
{
	if (!m_IsClipping)
	{
		return false;
	}


}

bool Clipper::IsClipping() const
{
	return m_IsClipping;
}

void Clipper::SetClipping(bool enable)
{
	m_IsClipping = enable;
}
