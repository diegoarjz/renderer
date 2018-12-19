#include "image/image.h"
#include "image/image_creation_params.h"
#include "image/png_writer.h"

#include <iostream>

int main(int argc, char *argv[])
{
	r::ImageCreationParams params(255, 255);
	auto image = std::make_shared<r::Image>(params);
	r::PngWriter writer(image);

	r::Pixel pixel;
	pixel.m_blue = 255;

	for (uint32_t y = 0; y < image->GetHeight(); ++y)
	{
		pixel.m_green = y;
		for (uint32_t x = 0; x < image->GetWidth(); ++x)
		{
			pixel.m_red = x;
			image->SetPixel(x, y, pixel);
		}
	}

	writer.WriteToFile("image.png");

	return 0;
}
