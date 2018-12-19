#pragma once

#include <memory>

namespace r
{
class Image;
using ImagePtr = std::shared_ptr<Image>;

class PngWriter
{
public:
	PngWriter(ImagePtr image);
	~PngWriter();

	bool WriteToFile(const char *file);

private:
	struct Impl;
	std::unique_ptr<Impl> m_implementation;
};

}  // namespace r
