#include "png_writer.h"

#include "image.h"

#include <png.h>
#include <cstdio>

namespace r
{
struct PngWriter::Impl
{
	Impl(ImagePtr image) : m_image(image) {}

	bool WriteToFile(const char *file)
	{
		uint32_t width = m_image->GetWidth();
		uint32_t height = m_image->GetHeight();
		uint8_t *data = m_image->GetImageData();

		m_row = nullptr;
		m_infoPtr = nullptr;
		m_pngPtr = nullptr;

		std::FILE *fp = std::fopen(file, "w");
		if (fp == nullptr)
		{
			return false;
		}

		m_pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
		if (m_pngPtr == nullptr)
		{
			std::fclose(fp);
			FreeResources();
			return false;
		}

		m_infoPtr = png_create_info_struct(m_pngPtr);
		if (m_infoPtr == nullptr)
		{
			std::fclose(fp);
			FreeResources();
			return false;
		}

		if (setjmp(png_jmpbuf(m_pngPtr)))
		{
			std::fclose(fp);
			FreeResources();
			return false;
		}

		png_init_io(m_pngPtr, fp);
		png_set_IHDR(m_pngPtr, m_infoPtr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
		             PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

		png_write_info(m_pngPtr, m_infoPtr);

		// Flipped since OpenGL 0,0 is at the bottom left
		for (int32_t y = height - 1; y >= 0; --y)
		{
			m_row = data + y * width * 3;
			png_write_row(m_pngPtr, m_row);
		}

		png_write_end(m_pngPtr, nullptr);

		std::fclose(fp);
		FreeResources();

		return true;
	}

private:
	void FreeResources()
	{
		if (m_infoPtr != nullptr)
		{
			png_free_data(m_pngPtr, m_infoPtr, PNG_FREE_ALL, -1);
		}
		if (m_pngPtr)
		{
			png_destroy_write_struct(&m_pngPtr, nullptr);
		}
	}

	ImagePtr m_image;
	png_bytep m_row;
	png_structp m_pngPtr;
	png_infop m_infoPtr;
};

PngWriter::PngWriter(ImagePtr image) : m_implementation(std::make_unique<Impl>(image)) {}
PngWriter::~PngWriter() { m_implementation = nullptr; }

bool PngWriter::WriteToFile(const char *file) { return m_implementation->WriteToFile(file); }
}  // namespace r
