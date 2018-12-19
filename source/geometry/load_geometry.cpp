#include "load_geometry.h"

#include "element_data_source.h"
#include "geometry_base.h"
#include "vertex_data_source.h"

#include "common/logger.h"

#include "rendering/gl_debug.h"

#include <GL/glew.h>

namespace r
{
void LoadGeometry::Execute(Renderer *)
{
	// Load vertex buffer
	GLuint vertexBufferId = 0;
	glGenBuffers(1, &vertexBufferId);
	CHECK_GL_ERROR;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	CHECK_GL_ERROR;
	glBufferData(GL_ARRAY_BUFFER, m_geometry->GetVertexBufferSizeInBytes(), m_geometry->GetVertexBufferData(),
	             GL_STATIC_DRAW);
	CHECK_GL_ERROR;

	// Create vertex array object
	GLuint vertexArrayObjectId = 0;
	glGenVertexArrays(1, &vertexArrayObjectId);
	CHECK_GL_ERROR;
	glBindVertexArray(vertexArrayObjectId);
	CHECK_GL_ERROR;
	for (int i = 0; i < (int)VertexDataSourceSemantics::MAX_VERTEX_DATA_SOURCE_SEMANTICS; ++i)
	{
		auto vds = m_geometry->GetVertexDataSourceForSemantics((VertexDataSourceSemantics)i);
		glEnableVertexAttribArray(i);
		CHECK_GL_ERROR;
		glVertexAttribPointer(i, vds->GetComponentCount(), GL_FLOAT, GL_FALSE, vds->GetStride(),
		                      reinterpret_cast<void *>(vds->GetOffset()));
		CHECK_GL_ERROR;
	}

	ElementDataSourcePtr elementDataSource = m_geometry->GetElementDataSource();
	if (elementDataSource)
	{
		GLuint elementBufferId;
		glGenBuffers(1, &elementBufferId);
		CHECK_GL_ERROR;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
		CHECK_GL_ERROR;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementDataSource->GetSizeInBytes(), elementDataSource->GetElements(),
		             GL_STATIC_DRAW);
		CHECK_GL_ERROR;

		Bindable &elementsBinding = elementDataSource->GetBindingData();
		elementsBinding.SetBindingData(elementBufferId);
		elementsBinding.SetBindState(Bindable::BindState::Bound);
	}

	Bindable &vb = m_geometry->GetVertexBufferBindable();
	vb.SetBindingData(vertexBufferId);
	vb.SetBindState(Bindable::BindState::Bound);

	Bindable &vao = m_geometry->GetVertexArrayObjectBindable();
	vao.SetBindingData(vertexArrayObjectId);
	vao.SetBindState(Bindable::BindState::Bound);
}
}  // namespace r
