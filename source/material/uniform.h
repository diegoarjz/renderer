#pragma once

#include "rendering/bindable.h"

#include <glm/glm.hpp>

#include <string>

namespace r
{
class Uniform
{
public:
	enum class Type
	{
		Float,
		Vec2,
		Vec3,
		Vec4,
		Integer,
		Unsigned,
		Matrix2,
		Matrix3,
		Matrix4
	};

	enum class Semantics
	{
		ModelMatrix,
		ViewMatrix,
		ProjectionMatrix,
		Custom,
		MAX
	};

	Uniform(const std::string &name, Type type);
	Uniform(const std::string &name, Type type, Semantics semantics);

	const std::string &GetName() const { return m_name; }
	Type GetType() const { return m_type; }
	Semantics GetSemantics() const { return m_semantics; }

	void SetFloat(float f);
	float GetFloat() const;
	void SetVec2(const glm::vec2 &v);
	glm::vec2 GetVec2() const;
	void SetVec3(const glm::vec3 &v);
	glm::vec3 GetVec3() const;
	void SetVec4(const glm::vec4 &v);
	glm::vec4 GetVec4() const;
	void SetInteger(int32_t i);
	int32_t GetInteger() const;
	void SetUnsigned(uint32_t ui);
	uint32_t GetUnsigned() const;
	void SetMatrix2(const glm::mat2 &m);
	glm::mat2 GetMatrix2() const;
	void SetMatrix3(const glm::mat3 &m);
	glm::mat3 GetMatrix3() const;
	void SetMatrix4(const glm::mat4 &m);
	glm::mat4 GetMatrix4() const;

	Bindable &GetBindable() { return m_bindingData; }

	bool IsDirty() const { return m_isDirty; }
	void NotDirty() { m_isDirty = false; }

private:
	union uniform_value
	{
		float f;
		glm::vec2 f2;
		glm::vec3 f3;
		glm::vec4 f4;
		int32_t i;
		// TODO i2, i3, i4
		uint32_t ui;
		// TODO ui2, ui3, ui4
		glm::mat2 m2f;
		glm::mat3 m3f;
		glm::mat4 m4f;

		// TODO Arrays
	};

	std::string m_name;
	Bindable m_bindingData;
	uniform_value m_value;
	bool m_isDirty;
	Type m_type;
	Semantics m_semantics;
};

using UniformPtr = std::shared_ptr<Uniform>;

}  // namespace r
