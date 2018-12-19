#pragma once

#include <cstdint>
#include <memory>

namespace r
{
class ImageCreationParams
{
public:
	ImageCreationParams(uint32_t width, uint32_t height);
	~ImageCreationParams();

	ImageCreationParams& Size(uint32_t width, uint32_t height);

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

private:
	struct Impl;
	std::unique_ptr<Impl> m_implementation;
};
}  // namespace r
