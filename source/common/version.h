#pragma once

namespace r
{
/**
 * Returns the current version for the project.
 */
const char* get_version_string();

/**
 * Returns the current build number for the project.
 */
const char* get_build_number();

/**
 * Returns the date this project was built.
 */
const char* get_build_date();

}  // namespace r
