#pragma once

#include <memory>

class DepthBuffer
{
public:
	static DepthBuffer* Get();

	void OnNewFrame();

	void Initialize(int width, int height);

	void SetEnabled(bool enabled);
	bool CheckDepthBuffer(int x, int y, float depth);

private:
	std::unique_ptr<float[]> m_depthBuffer;
	int m_width = 0;
	int m_height = 0;
	bool m_enabled = false;
};