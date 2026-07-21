#include "Clipper.h"
#include "Viewport.h"	// we need something to clip against


const short BIT_INSIDE = 0;		// 0000
const short BIT_LEFT = 1 << 0;	// 0001
const short BIT_RIGHT = 1 << 1;	// 0010
const short BIT_BOTTOM = 1 << 2;	// 0100
const short BIT_TOP = 1 << 3;	// 1000

// generate a bit code that signifies where the point is
// If code is not 0, it is outside of the screen in one of the 8 regions
// compare code with other point's code to confirm if the line crosses screen
short GetOutputCode(float x, float y)
{
	Viewport* vp = Viewport::Get();
	short code = BIT_INSIDE;
	if (x < vp->GetMinX())
	{
		code |= BIT_LEFT;
	}
	else if (x > vp->GetMaxX())
	{
		code |= BIT_RIGHT;
	}
	if (y < vp->GetMinY())
	{
		// example
		// 0001 |= 1000
		code |= BIT_TOP;
		// code = 1001
	}
	else if (y > vp->GetMaxY())
	{
		code |= BIT_BOTTOM;
	}
	return code;
}

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


	Viewport* vp = Viewport::Get();

	float minX = vp->GetMinX();
	float maxX = vp->GetMaxX();
	float minY = vp->GetMinY();
	float maxY = vp->GetMaxX();

	// we need codes for each point
	short codeA = GetOutputCode(a.m_pos.x, a.m_pos.y);
	short codeB = GetOutputCode(b.m_pos.x, b.m_pos.y);
	while (true)
	{
		if (!(codeA | codeB))
		{
			// both are 0000, so both are in the viewportb
			break;
		}
		else if (codeA & codeB)
		{
			// both are along the same edge, so they will never cross the viewport
			break;
		}

		float t = 0.0f;
		// pick a code that is not 0000
		// If the value is > than that is not 0000
		short outCode = codeB > codeA ? codeB : codeA;
		if (outCode & BIT_TOP)
		{
			t = (minY - a.m_pos.y) / (b.m_pos.y - a.m_pos.y);
		}
		else if (outCode & BIT_BOTTOM)
		{
			t = (maxY - a.m_pos.y) / (b.m_pos.y - a.m_pos.y);
		}
		else if (outCode & BIT_LEFT)
		{
			t = (minX - a.m_pos.x) / (b.m_pos.x - a.m_pos.x);
		}

		if (outCode == codeA)
		{
			a = LerpVertex(a, b, t);
			codeA = GetOutputCode(a.m_pos.x, a.m_pos.y);
		}
		else
		{
			b = LerpVertex(a, b, t);
			codeB = GetOutputCode(b.m_pos.x, b.m_pos.y);
		}

	}

	return (codeA | codeB);
}

bool Clipper::IsClipping() const
{
	return m_IsClipping;
}

void Clipper::SetClipping(bool enable)
{
	m_IsClipping = enable;
}
