#include "command.h"

namespace r
{
Command::Command(/*CommandType type*/) : /*m_type(type),*/ m_next(nullptr), m_prev(nullptr) {}

Command::~Command() {}
}  // namespace r
