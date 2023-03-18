#pragma once

#include <filesystem>
#include <cassert>

#include <Common/Types.h>

///////////////////////////////////////////////////////////
// Namespaces
///////////////////////////////////////////////////////////

namespace fs = std::filesystem;

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  enum TextureType
  {
    eTextureType1D = 0x0DE0,
    eTextureType1DArray = 0x8C18,
    eTextureType2D = 0x0DE1,
    eTextureType2DArray = 0x8C1A,
    eTextureType3D = 0x806F,
    eTextureTypeCube = 0x8513,
    eTextureTypeCubeArray = 0x9009,
  };

  enum TextureFormatExternal
  {
    eTextureFormatExternalRGB = 0x1907,
    eTextureFormatExternalRGBA = 0x1908,
    eTextureFormatExternalD = 0x1902,
    eTextureFormatExternalS = 0x1901,
    eTextureFormatExternalDS = 0x84F9,
  };

  enum TextureFormatInternal
  {
    eTextureFormatInternalRGBA8UNORM = 0x8058,
    eTextureFormatInternalRGBA8U = 0x8D7C,
    eTextureFormatInternalRGBA32R = 0x8814,
    eTextureFormatInternalD24S8 = 0x88F0,
  };

  enum TextureWrap
  {
    eTextureWrapRepeat = 0x2901,
    eTextureWrapClampToEdge = 0x812F,
  };

  enum TextureFilter
  {
    eTextureFilterNearest = 0x2600,
    eTextureFilterLinear = 0x2601,
  };

  enum TextureValueType
  {
    eTextureValueTypeU8 = 0x1401,
    eTextureValueTypeU32 = 0x1405,
    eTextureValueTypeR32 = 0x1406,
    eTextureValueTypeD24S8 = 0x84FA, // ?
  };

  class Texture
  {
  public:

    Texture(const fs::path& File, TextureWrap Wrap, TextureFilter Filter);
    Texture(TextureType Type, TextureFormatExternal FormatExternal, TextureFormatInternal FormatInternal, TextureWrap Wrap, TextureFilter Filter, TextureValueType ValueType);
    virtual ~Texture();

  public:

    inline auto GetId() const { return mTid; }
    inline auto GetWidth() const { return mWidth; }
    inline auto GetHeight() const { return mHeight; }

  public:

    void Resize(U32 Width, U32 Height);
    void Bind();
    void Mount(U32 Index);
    void Unbind();

  private:

    TextureType mType = {};
    TextureFormatExternal mFormatExternal = {};
    TextureFormatInternal mFormatInternal = {};
    TextureWrap mWrap = {};
    TextureFilter mFilter = {};
    TextureValueType mValueType = {};

    U32 mTid = 0;
    U32 mWidth = 1;
    U32 mHeight = 1;
  };
}