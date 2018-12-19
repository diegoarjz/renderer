#include "version.h"

namespace r
{
const char* get_version_string() { return RENDERER_VERSION; }

const char* get_build_number() { return RENDERER_BUILD_NUMBER; }

const char* get_build_date() { return RENDERER_BUILD_DATE; }

}  // namespace r
