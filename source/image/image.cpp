#include "image.h"

namespace r
{
struct Image::Impl
{
public:
	Impl(const ImageCreationParams &creationParams)
	    : m_width(creationParams.GetWidth()), m_height(creationParams.GetHeight())
	{
		m_pixels = new uint8_t[m_width * m_height * 3];
	}

	~Impl() { delete[] m_pixels; }

	uint32_t GetWidth() const { return m_width; }
	uint32_t GetHeight() const { return m_height; }

	void SetPixel(uint32_t x, uint32_t y, const Pixel &rgb)
	{
		uint32_t offset = offset_to_pixel(x, y);
		m_pixels[offset + 0] = rgb.m_red;
		m_pixels[offset + 1] = rgb.m_green;
		m_pixels[offset + 2] = rgb.m_blue;
	}

	Pixel GetPixel(uint32_t x, uint32_t y)
	{
		Pixel p;
		uint32_t offset = offset_to_pixel(x, y);
		p.m_red = m_pixels[offset + 0];
		p.m_green = m_pixels[offset + 1];
		p.m_blue = m_pixels[offset + 2];
		return p;
	}

	uint8_t *GetImageData() { return m_pixels; }

private:
	uint32_t offset_to_pixel(uint32_t x, uint32_t y) { return 3 * (y * m_width + x); }

	uint32_t m_width;
	uint32_t m_height;

	uint8_t *m_pixels;
};

Image::Image(const ImageCreationParams &creationParams) : m_implementation(std::make_unique<Impl>(creationParams)) {}

Image::~Image() { m_implementation = nullptr; }

uint32_t Image::GetWidth() const { return m_implementation->GetWidth(); }
uint32_t Image::GetHeight() const { return m_implementation->GetHeight(); }

void Image::SetPixel(uint32_t x, uint32_t y, const Pixel &rgb) { m_implementation->SetPixel(x, y, rgb); }
Pixel Image::GetPixel(uint32_t x, uint32_t y) { return m_implementation->GetPixel(x, y); }
uint8_t *Image::GetImageData() { return m_implementation->GetImageData(); }
}  // namespace r
