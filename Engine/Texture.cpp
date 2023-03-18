#include <Engine/Texture.h>

#include <Vendor/GLAD/glad.h>

#include <Vendor/GLI/gli.hpp>

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  Texture::Texture(const fs::path& File, TextureWrap Wrap, TextureFilter Filter)
    : mWrap{ Wrap }
    , mFilter{ Filter }
  {
    gli::texture texture = gli::load(File.string());

    if (!texture.empty())
    {
      gli::gl gl = gli::gl::PROFILE_GL33;

      gli::gl::format format = gl.translate(texture.format(), texture.swizzles());

      mType = (TextureType)gl.translate(texture.target());
      mFormatExternal = (TextureFormatExternal)format.External;
      mFormatInternal = (TextureFormatInternal)format.Internal;
      mValueType = (TextureValueType)format.Type;

      I32V3 extend = texture.extent(0);

      mWidth = extend.x;
      mHeight = extend.y;

      switch (mType)
      {
        case eTextureType2D:
        {
          glGenTextures(1, &mTid);

          glBindTexture(mType, mTid);

          glTextureParameteri(mTid, GL_TEXTURE_WRAP_S, (I32)mWrap);
          glTextureParameteri(mTid, GL_TEXTURE_WRAP_T, (I32)mWrap);

          glTextureParameteri(mTid, GL_TEXTURE_MIN_FILTER, (I32)mFilter);
          glTextureParameteri(mTid, GL_TEXTURE_MAG_FILTER, (I32)mFilter);

          glTexImage2D(mType, 0, mFormatInternal, mWidth, mHeight, 0, mFormatExternal, mValueType, texture.data(0, 0, 0));

          glBindTexture(mType, 0);

          break;
        }
      }
    }
  }

  Texture::Texture(TextureType Type, TextureFormatExternal FormatExternal, TextureFormatInternal FormatInternal, TextureWrap Wrap, TextureFilter Filter, TextureValueType ValueType)
    : mType{ Type }
    , mFormatExternal{ FormatExternal }
    , mFormatInternal{ FormatInternal }
    , mWrap{ Wrap }
    , mFilter{ Filter }
    , mValueType{ ValueType }
  {
    glGenTextures(1, &mTid);

    glBindTexture(mType, mTid);

    glTextureParameteri(mTid, GL_TEXTURE_WRAP_S, (I32)mWrap);
    glTextureParameteri(mTid, GL_TEXTURE_WRAP_T, (I32)mWrap);

    glTextureParameteri(mTid, GL_TEXTURE_MIN_FILTER, (I32)mFilter);
    glTextureParameteri(mTid, GL_TEXTURE_MAG_FILTER, (I32)mFilter);

    glTexImage2D(mType, 0, mFormatInternal, mWidth, mHeight, 0, mFormatExternal, mValueType, nullptr);

    glBindTexture(mType, 0);
  }

  Texture::~Texture()
  {
    glDeleteTextures(1, &mTid);
  }

  void Texture::Resize(U32 Width, U32 Height)
  {
    mWidth = Width;
    mHeight = Height;

    glTexImage2D(mType, 0, mFormatInternal, mWidth, mHeight, 0, mFormatExternal, mValueType, nullptr);
  }

  void Texture::Bind()
  {
    glBindTexture(mType, mTid);
  }

  void Texture::Mount(U32 Index)
  {
    glBindTextureUnit(Index, mTid);
  }

  void Texture::Unbind()
  {
    glBindTexture(mType, 0);
  }
}