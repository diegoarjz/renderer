#pragma once

#include "image_creation_params.h"

#include <cstdint>
#include <memory>

namespace r
{
struct Pixel
{
	uint8_t m_red;
	uint8_t m_green;
	uint8_t m_blue;
};

class Image
{
public:
	Image(const ImageCreationParams &creationParams);
	~Image();

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	void SetPixel(uint32_t x, uint32_t y, const Pixel &pixel);
	Pixel GetPixel(uint32_t x, uint32_t y);
	uint8_t *GetImageData();

private:
	struct Impl;
	std::unique_ptr<Impl> m_implementation;
};
}  // namespace r
