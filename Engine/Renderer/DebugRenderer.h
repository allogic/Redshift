#pragma once

#include <vector>

#include <Common/Types.h>

#include <Engine/Vertex.h>

///////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////

namespace rs
{
  template<typename V, typename E>
  class Mesh;

  class Shader;
}

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  class DebugRenderer
  {
  public:

    DebugRenderer(U32 VertexBufferSize, U32 ElementBufferSize);
    virtual ~DebugRenderer();

  public:

    void Render();

  public:

    void Line(R32V3 P0, R32V3 P1, R32V4 C);
    void Quad(R32V2 P, R32V2 S, R32V4 C);

  private:

    Mesh<LineVertex, U32>* mMesh;
    Shader* mShader;

    std::vector<LineVertex> mVertexBuffer = {};
    std::vector<U32> mElementBuffer = {};

    U32 mVertexOffset = 0;
    U32 mElementOffset = 0;
  };
}