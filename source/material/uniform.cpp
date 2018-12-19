#include "uniform.h"

namespace r
{
Uniform::Uniform(const std::string &name, Uniform::Type type)
    : m_name(name),
      m_bindingData(Bindable::BindableType::Uniform),
      m_type(type),
      m_semantics(Uniform::Semantics::Custom),
      m_isDirty(true)
{
}

Uniform::Uniform(const std::string &name, Uniform::Type type, Uniform::Semantics semantics)
    : m_name(name),
      m_bindingData(Bindable::BindableType::Uniform),
      m_type(type),
      m_semantics(semantics),
      m_isDirty(true)
{
}

void Uniform::SetFloat(float f)
{
	m_value.f = f;
	m_isDirty = true;
}

float Uniform::GetFloat() const { return m_value.f; }

void Uniform::SetVec2(const glm::vec2 &v)
{
	m_value.f2 = v;
	m_isDirty = true;
}

glm::vec2 Uniform::GetVec2() const { return m_value.f2; }

void Uniform::SetVec3(const glm::vec3 &v)
{
	m_value.f3 = v;
	m_isDirty = true;
}

glm::vec3 Uniform::GetVec3() const { return m_value.f3; }

void Uniform::SetVec4(const glm::vec4 &v)
{
	m_value.f4 = v;
	m_isDirty = true;
}

glm::vec4 Uniform::GetVec4() const { return m_value.f4; }

void Uniform::SetInteger(int32_t i)
{
	m_value.i = i;
	m_isDirty = true;
}

int32_t Uniform::GetInteger() const { return m_value.i; }

void Uniform::SetUnsigned(uint32_t ui)
{
	m_value.ui = ui;
	m_isDirty = true;
}

uint32_t Uniform::GetUnsigned() const { return m_value.ui; }

void Uniform::SetMatrix2(const glm::mat2 &m)
{
	m_value.m2f = m;
	m_isDirty = true;
}

glm::mat2 Uniform::GetMatrix2() const { return m_value.m2f; }

void Uniform::SetMatrix3(const glm::mat3 &m)
{
	m_value.m3f = m;
	m_isDirty = true;
}

glm::mat3 Uniform::GetMatrix3() const { return m_value.m3f; }

void Uniform::SetMatrix4(const glm::mat4 &m)
{
	m_value.m4f = m;
	m_isDirty = true;
}

glm::mat4 Uniform::GetMatrix4() const { return m_value.m4f; }

}  // namespace r
