#include "bindable.h"

#include <limits>

namespace r
{
Bindable::Bindable(Bindable::BindableType type)
    : m_type(type), m_bindState(Bindable::BindState::NotBound), m_bindingData(std::numeric_limits<GLuint>::max())
{
}
}  // namespace r
