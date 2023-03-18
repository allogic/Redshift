#include <Engine/Mesh.h>
#include <Engine/Shader.h>
#include <Engine/Scene.h>

#include <Engine/Components/Camera.h>

#include <Engine/Renderer/DebugRenderer.h>

///////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////

extern rs::Scene* gScene;

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  DebugRenderer::DebugRenderer(U32 VertexBufferSize, U32 ElementBufferSize)
    : mMesh{ new Mesh<LineVertex, U32> }
    , mShader{ new Shader{ "Debug.vert", "Debug.frag" } }
  {
    mVertexBuffer.resize(VertexBufferSize);
    mElementBuffer.resize(ElementBufferSize);
  }

  DebugRenderer::~DebugRenderer()
  {
    delete mShader;
    delete mMesh;
  }

  void DebugRenderer::Render()
  {
    if (gScene)
    {
      Camera* camera = gScene->GetMainCamera();
    
      if (camera)
      {
        mShader->Bind();
    
        mShader->SetUniformR32M4("UniformProjectionMatrix", camera->GetProjectionMatrix());
        mShader->SetUniformR32M4("UniformViewMatrix", camera->GetViewMatrix());
    
        // Clear previous entries...
    
        mMesh->Bind();
        mMesh->UploadVertices(mVertexBuffer);
        mMesh->UploadElements(mElementBuffer);
        mMesh->Render(eRenderModeLines);
        mMesh->Unbind();
    
        mShader->Unbind();
      }
    }

    mVertexOffset = 0;
    mElementOffset = 0;
  }

  void DebugRenderer::Line(R32V3 P0, R32V3 P1, R32V4 C)
  {
    mVertexBuffer[mVertexOffset + 0].Position = P0;
    mVertexBuffer[mVertexOffset + 1].Position = P1;

    mVertexBuffer[mVertexOffset + 0].Color = C;
    mVertexBuffer[mVertexOffset + 1].Color = C;

    mElementBuffer[mElementOffset + 0] = mVertexOffset + 0;
    mElementBuffer[mElementOffset + 1] = mVertexOffset + 1;

    mVertexOffset += 2;
    mElementOffset += 2;
  }

  void DebugRenderer::Quad(R32V2 P, R32V2 S, R32V4 C)
  {
    mVertexBuffer[mVertexOffset + 0].Position = R32V3{ P.x, P.y, 0.0F };
    mVertexBuffer[mVertexOffset + 1].Position = R32V3{ P.x + S.x, P.y, 0.0F };
    mVertexBuffer[mVertexOffset + 2].Position = R32V3{ P.x + S.x, P.y + S.y, 0.0F };
    mVertexBuffer[mVertexOffset + 3].Position = R32V3{ P.x, P.y + S.y, 0.0F };

    mVertexBuffer[mVertexOffset + 0].Color = C;
    mVertexBuffer[mVertexOffset + 1].Color = C;
    mVertexBuffer[mVertexOffset + 2].Color = C;
    mVertexBuffer[mVertexOffset + 3].Color = C;

    mElementBuffer[mElementOffset + 0] = mVertexOffset + 0;
    mElementBuffer[mElementOffset + 1] = mVertexOffset + 1;

    mElementBuffer[mElementOffset + 2] = mVertexOffset + 1;
    mElementBuffer[mElementOffset + 3] = mVertexOffset + 2;

    mElementBuffer[mElementOffset + 4] = mVertexOffset + 2;
    mElementBuffer[mElementOffset + 5] = mVertexOffset + 3;

    mElementBuffer[mElementOffset + 6] = mVertexOffset + 3;
    mElementBuffer[mElementOffset + 7] = mVertexOffset + 0;

    mVertexOffset += 4;
    mElementOffset += 8;
  }
}