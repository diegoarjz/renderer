#include "image_creation_params.h"

namespace r
{
struct ImageCreationParams::Impl
{
public:
	Impl(uint32_t width, uint32_t height) : m_width(width), m_height(height) {}

	void Size(uint32_t width, uint32_t height)
	{
		m_width = width;
		m_height = height;
	}

	uint32_t GetWidth() const { return m_width; }
	uint32_t GetHeight() const { return m_height; }

private:
	uint32_t m_width;
	uint32_t m_height;
};

ImageCreationParams::ImageCreationParams(uint32_t width, uint32_t height)
    : m_implementation(std::make_unique<Impl>(width, height))
{
}

ImageCreationParams::~ImageCreationParams() {}

ImageCreationParams& ImageCreationParams::Size(uint32_t width, uint32_t height)
{
	m_implementation->Size(width, height);
	return *this;
}

uint32_t ImageCreationParams::GetWidth() const { return m_implementation->GetWidth(); }

uint32_t ImageCreationParams::GetHeight() const { return m_implementation->GetHeight(); }
}  // namespace r
