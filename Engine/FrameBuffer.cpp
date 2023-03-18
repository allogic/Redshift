#include <Engine/FrameBuffer.h>

#include <Engine/Textures/RenderTexture.h>
#include <Engine/Textures/DepthStencilTexture.h>

#include <Vendor/GLAD/glad.h>

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  FrameBuffer::FrameBuffer()
    : mColorTexture{ new RenderTexture }
    , mDepthStencilTexture{ new DepthStencilTexture }
  {
    glGenFramebuffers(1, &mFbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFbo);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorTexture->GetId(), 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, mDepthStencilTexture->GetId(), 0);

    U32 attachments[1] = { GL_COLOR_ATTACHMENT0 };

    glDrawBuffers(1, attachments);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  }

  FrameBuffer::~FrameBuffer()
  {
    glDeleteFramebuffers(1, &mFbo);

    delete mDepthStencilTexture;
    delete mColorTexture;
  }

  void FrameBuffer::Resize(U32 Width, U32 Height)
  {
    mColorTexture->Bind();
    mColorTexture->Resize(Width, Height);
    mColorTexture->Unbind();

    mDepthStencilTexture->Bind();
    mDepthStencilTexture->Resize(Width, Height);
    mDepthStencilTexture->Unbind();
  }
}