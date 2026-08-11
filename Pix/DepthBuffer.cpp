#include "DepthBuffer.h"

DepthBuffer* DepthBuffer::Get()
{
	static DepthBuffer s_instance;
	return &s_instance;
}

void DepthBuffer::OnNewFrame()
{
	m_enabled = false;
	for (int i = 0; i < m_width * m_height; ++i)
	{
		m_depthBuffer[i] = 1.0f;
	}
}

void DepthBuffer::Initialize(int width, int height)
{
	if (width != m_width || height != m_height)
	{
		m_depthBuffer = std::make_unique<float[]>(width * height);
		m_width = width;
		m_height = height;
		OnNewFrame();
	}
}

void DepthBuffer::SetEnabled(bool enabled)
{
	m_enabled = enabled;
}

bool DepthBuffer::CheckDepthBuffer(int x, int y, float depth)
{
	if (!m_enabled)
	{
		return true;
	}

	if (x >= 0 && x < m_width && y >= 0.0f && y < m_height && depth > 0.0f)
	{
		const int index = x + (y * m_width);
		if (depth <= m_depthBuffer[index])
		{
			m_depthBuffer[index] = depth;
			return true;
		}
	}
	return false;
}
