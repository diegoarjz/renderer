#include "gl_debug.h"

#include "common/logger.h"

namespace r
{
const char* get_gl_error(GLenum error)
{
	switch (error)
	{
		case GL_NO_ERROR:
			return "GL_NO_ERROR";
		case GL_INVALID_ENUM:
			return "GL_INVALID_ENUM";
		case GL_INVALID_VALUE:
			return "GL_INVALID_VALUE";
		case GL_INVALID_OPERATION:
			return "GL_INVALID_OPERATION";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return "GL_INVALID_FRAMEBUFFER_OPERATION";
		case GL_OUT_OF_MEMORY:
			return "GL_OUT_OF_MEMORY";
		default:
			return "Unkown error";
	}
}
void check_gl_error(const char* file, uint32_t line)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		LOG_ERROR("%s:%d OpenGL error: %s (%d)", file, line, get_gl_error(error), error);
	}
}
}  // namespace r
