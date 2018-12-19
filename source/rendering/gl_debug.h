#pragma once

#include <GL/glew.h>

namespace r
{
void check_gl_error(const char *file, uint32_t line);

#define CHECK_GL_ERROR r::check_gl_error(__FILE__, __LINE__);
}  // namespace r
