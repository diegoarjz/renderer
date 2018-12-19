#include "common/logger.h"

#include "model/model.h"
#include "model/render_model.h"

#include "geometry/element_data_source.h"
#include "geometry/geometry.h"
#include "geometry/load_geometry.h"
#include "geometry/render_geometry.h"
#include "geometry/vertex.h"
#include "geometry/vertex_data_source.h"

#include "material/create_shader_program.h"
#include "material/set_shader_program.h"
#include "material/shader.h"
#include "material/shader_program.h"

#include "camera/camera.h"
#include "camera/lens.h"
#include "camera/set_camera_on_renderer.h"
#include "system/frame_memory.h"

#include "rendering/command_list.h"
#include "rendering/render_pool.h"
#include "rendering/renderer.h"

#include "update_loop.h"

#include "basic_test_application.h"

const char *vertexShader =
    "#version 330 core\n"
    "layout(location = 0) in vec3 vertexPosition_modelSpace;\n"
    "layout(location = 1) in vec3 vertexColor;\n"
    "uniform mat4 viewMatrix;\n"
    "uniform mat4 projectionMatrix;\n"
    "uniform mat4 modelMatrix;\n"
    "out vec3 vColor;\n"
    "void main(){\n"
    "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition_modelSpace.xyz, 1.0);\n"
    "   vColor = vertexColor;\n"
    "}";

const char *fragmentShader = "#version 330 core\n"
                             "out vec3 color;\n"
                             "in vec3 vColor;\n"
                             "void main() {\n"
                             "color = vColor;\n"
                             "}";

class TriangleUpdateLoop : public r::UpdateLoop
{
public:
	TriangleUpdateLoop()
	    : m_frameMemory(nullptr),
	      m_loadCommandList(nullptr),
	      m_renderCommandList(nullptr),
	      m_shouldStop(false),
	      m_lens(std::make_shared<r::Lens>())
	{
	}

	void Initialize()
	{
		m_camera = std::make_shared<r::Camera>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
		m_camera->SetPosition(glm::vec3(0, 0, -5));
		m_lens->SetPerspective(45, 800.0f / 600.0f, 0.1f, 100);
		m_camera->SetLens(m_lens);
		m_frameMemory = std::make_shared<r::FrameMemory>(1024);
		CreateShaders();
		CreateGeometry();
		CreateLoadCommandList();
		CreateRenderCommandList();
	}

	void CreateShaders()
	{
		m_shaderProgram = std::make_shared<r::ShaderProgram>();
		r::ShaderPtr vertShader = std::make_shared<r::Shader>(r::Shader::ShaderType::Vertex);
		r::ShaderPtr fragShader = std::make_shared<r::Shader>(r::Shader::ShaderType::Fragment);

		vertShader->SetShaderSource(vertexShader);
		fragShader->SetShaderSource(fragmentShader);
		m_shaderProgram->SetShader(vertShader);
		m_shaderProgram->SetShader(fragShader);

		auto viewMatrixUniform =
		    m_shaderProgram->CreateUniform("viewMatrix", r::Uniform::Type::Matrix4, r::Uniform::Semantics::ViewMatrix);
		auto projectionMatrixUniform = m_shaderProgram->CreateUniform("projectionMatrix", r::Uniform::Type::Matrix4,
		                                                              r::Uniform::Semantics::ProjectionMatrix);
		auto modelMatrix = m_shaderProgram->CreateUniform("modelMatrix", r::Uniform::Type::Matrix4,
		                                                  r::Uniform::Semantics::ModelMatrix);
	}

	void CreateGeometry()
	{
		// clang-format off
        r::Vertex vertices[] = {
            {glm::vec3(-1, -1, 0), glm::vec3(1,0,0)},
            {glm::vec3( 1, -1, 0), glm::vec3(0,1,0)},
            {glm::vec3( 0,  1, 0), glm::vec3(0,0,1)}
        };
        uint32_t indices[] = {0u,1u,2u};
		// clang-format on

		std::map<r::VertexDataSourceSemantics, r::VertexDataSourcePtr> semanticMap;
		semanticMap[r::VertexDataSourceSemantics::Position] = std::make_shared<r::VertexDataSource>(
		    r::VertexDataSourceSemantics::Position, true, 3, 0, sizeof(r::Vertex));
		semanticMap[r::VertexDataSourceSemantics::Normal] = std::make_shared<r::VertexDataSource>(
		    r::VertexDataSourceSemantics::Normal, true, 3, 3 * sizeof(float), sizeof(r::Vertex));

		r::ElementDataSourcePtr elementDataSource =
		    std::make_shared<r::ElementDataSource>(indices, r::PrimitiveType::Triangles, 1, 3);
		m_geometry = std::make_shared<r::CustomGeometry<r::Vertex>>(vertices, 3, semanticMap, elementDataSource);

		m_triangleModel = std::make_shared<r::Model>(m_geometry, m_shaderProgram);
	}

	void CreateLoadCommandList()
	{
		m_loadCommandList = std::make_shared<r::CommandList>(m_frameMemory);
		auto loadGeometry = m_loadCommandList->CreateCommand<r::LoadGeometry>();
		loadGeometry->SetGeometry(m_geometry);
		auto createShaderProgram = m_loadCommandList->CreateCommand<r::CreateShaderProgram>();
		createShaderProgram->SetShaderProgram(m_shaderProgram);
	}

	void CreateRenderCommandList()
	{
		m_renderCommandList = std::make_shared<r::CommandList>(m_frameMemory);
		auto setCamera = m_renderCommandList->CreateCommand<r::SetCameraOnRenderer>();
		setCamera->SetCamera(m_camera);
		auto renderModel = m_renderCommandList->CreateCommand<r::RenderModel>();
		renderModel->SetModel(m_triangleModel);
	}

	bool Update() override
	{
		r::CommandListPtr commandListToRender = nullptr;

		m_triangleModel->GetTransformation().Roll(0.01);

		if (GetCurrentFrame() == 0)
		{
			m_loadCommandList->GetTail()->SetNext(m_renderCommandList->GetHead());
			commandListToRender = m_loadCommandList;
		}
		else
		{
			m_loadCommandList->GetTail()->SetNext(nullptr);
			commandListToRender = m_renderCommandList;
		}

		GetRenderPool()->AddCommandList(commandListToRender);

		return m_shouldStop;
	}

	void ShouldStop() override
	{
		GetRenderPool()->NotifyRenderDone();
		m_shouldStop = true;
	}

private:
	r::FrameMemoryPtr m_frameMemory;
	r::CommandListPtr m_loadCommandList;
	r::CommandListPtr m_renderCommandList;
	r::CameraPtr m_camera;
	std::shared_ptr<r::GeometryBase> m_geometry;
	r::ModelPtr m_triangleModel;
	r::ShaderProgramPtr m_shaderProgram;
	bool m_shouldStop;
	r::LensPtr m_lens;
};

int main(int argc, char *argv[])
{
	r::BasicTestApplication app;
	app.ParseCommandLine(argc, argv);
	std::shared_ptr<TriangleUpdateLoop> updateLoop = std::make_shared<TriangleUpdateLoop>();
	updateLoop->Initialize();
	app.SetUpdateLoop(updateLoop);

	app.Start();

	return 0;
}
