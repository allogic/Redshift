#pragma once

#include <Common/Types.h>

///////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////

namespace rs
{
  class RenderTexture;
  class DepthStencilTexture;
}

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  class FrameBuffer
  {
  public:

    FrameBuffer();
    virtual ~FrameBuffer();

  public:

    inline auto GetId() const { return mFbo; }
    inline auto GetColorTexture() const { return mColorTexture; }
    inline auto GetDepthStencilTexture() const { return mDepthStencilTexture; }

  public:

    void Resize(U32 Width, U32 Height);

  private:

    U32 mFbo = 0;

    RenderTexture* mColorTexture = nullptr;
    DepthStencilTexture* mDepthStencilTexture = nullptr;
  };
}