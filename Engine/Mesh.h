#pragma once

#include <vector>

#include <Common/Types.h>

#include <Engine/Vertex.h>

#include <Vendor/GLAD/glad.h>

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  enum RenderMode
  {
    eRenderModeLines = 1,
    eRenderModeTriangles = 4,
  };

  template<typename V, typename E>
  class Mesh
  {
  public:

    Mesh();
    virtual ~Mesh();

  public:

    void Bind() const;
    void Render(RenderMode RenderMode) const;
    void Unbind() const;

  public:

    void UploadVertices(const std::vector<V>& VertexBuffer);
    void UploadElements(const std::vector<E>& ElementBuffer);

  private:

    U32 mVao;
    U32 mVbo;
    U32 mEbo;

    U32 mElementSize = 0;
  };
}

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  template<typename V, typename E>
  Mesh<V, E>::Mesh()
  {
    glGenVertexArrays(1, &mVao);

    glGenBuffers(1, &mVbo);
    glGenBuffers(1, &mEbo);

    glBindVertexArray(mVao);

    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_READ | GL_STATIC_DRAW);

    switch (V::Type)
    {
      case VertexType::eVertexTypeDefault:
      {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DefaultVertex), (void*)(0));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(DefaultVertex), (void*)(sizeof(R32V3)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(DefaultVertex), (void*)(sizeof(R32V3) + sizeof(R32V3)));
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(DefaultVertex), (void*)(sizeof(R32V3) + sizeof(R32V3) + sizeof(R32V2)));
        break;
      }
      case VertexType::eVertexTypeLine:
      {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (void*)(0));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (void*)(sizeof(R32V3)));
        break;
      }
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_READ | GL_STATIC_DRAW);

    glBindVertexArray(0);
  }

  template<typename V, typename E>
  Mesh<V, E>::~Mesh()
  {
    glDeleteBuffers(1, &mVbo);
    glDeleteBuffers(1, &mEbo);

    glDeleteVertexArrays(1, &mVao);
  }

  template<typename V, typename E>
  void Mesh<V, E>::Bind() const
  {
    glBindVertexArray(mVao);
  }

  template<typename V, typename E>
  void Mesh<V, E>::Render(RenderMode renderMode) const
  {
    glDrawElements(renderMode, mElementSize, GL_UNSIGNED_INT, NULL);
  }

  template<typename V, typename E>
  void Mesh<V, E>::Unbind() const
  {
    glBindVertexArray(0);
  }

  template<typename V, typename E>
  void Mesh<V, E>::UploadVertices(const std::vector<V>& VertexBuffer)
  {
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, VertexBuffer.size() * sizeof(V), &VertexBuffer[0], GL_STATIC_READ | GL_STATIC_DRAW);
  }

  template<typename V, typename E>
  void Mesh<V, E>::UploadElements(const std::vector<E>& ElementBuffer)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementBuffer.size() * sizeof(E), &ElementBuffer[0], GL_STATIC_READ | GL_STATIC_DRAW);

    mElementSize = (U32)ElementBuffer.size();
  }
}