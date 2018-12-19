#pragma once

// Typedef to avoid including gl headers. Faster builds
using GLuint = unsigned int;

namespace r
{
class Bindable
{
public:
	enum class BindableType
	{
		ElementBuffer,
		VertexBuffer,
		VertexArrayBuffer,
		Shader,
		ShaderProgram,
		Uniform,
		MAX
	};

	enum class BindState
	{
		NotBound,
		Bound
	};

	explicit Bindable(BindableType type);

	const GLuint GetBindingData() { return m_bindingData; }
	const GLuint SetBindingData(GLuint data)
	{
		GLuint oldBindingData = m_bindingData;
		m_bindingData = data;
		return oldBindingData;
	}

	BindState GetBindState() { return m_bindState; }
	void SetBindState(BindState bindState) { m_bindState = bindState; }

private:
	BindableType m_type;
	BindState m_bindState;
	GLuint m_bindingData;
};  // class Bindable
}  // namespace r
