#include "render_geometry.h"

#include "element_data_source.h"
#include "geometry_base.h"
#include "vertex_data_source.h"

#include "rendering/gl_debug.h"

#include <GL/glew.h>

namespace r
{
void RenderGeometry::Execute(Renderer*)
{
	Bindable& vao = m_geometry->GetVertexArrayObjectBindable();
	Bindable& vb = m_geometry->GetVertexBufferBindable();

	glBindVertexArray(vao.GetBindingData());
	CHECK_GL_ERROR;
	glBindBuffer(GL_ARRAY_BUFFER, vb.GetBindingData());
	CHECK_GL_ERROR;

	for (int i = 0; i < (int)VertexDataSourceSemantics::MAX_VERTEX_DATA_SOURCE_SEMANTICS; ++i)
	{
		auto vds = m_geometry->GetVertexDataSourceForSemantics((VertexDataSourceSemantics)i);
		glEnableVertexAttribArray(i);
		CHECK_GL_ERROR;
	}

	ElementDataSourcePtr elementDataSource = m_geometry->GetElementDataSource();
	if (elementDataSource)
	{
		glDrawElements(GL_TRIANGLES, elementDataSource->GetElementsCount(), GL_UNSIGNED_INT, (void*)0);
		CHECK_GL_ERROR;
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, m_geometry->GetVertexCount());
		CHECK_GL_ERROR;
	}

	for (int i = 0; i < (int)VertexDataSourceSemantics::MAX_VERTEX_DATA_SOURCE_SEMANTICS; ++i)
	{
		auto vds = m_geometry->GetVertexDataSourceForSemantics((VertexDataSourceSemantics)i);
		glDisableVertexAttribArray(i);
		CHECK_GL_ERROR;
	}
}
}  // namespace r
