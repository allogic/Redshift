#include <Engine/Textures/DepthStencilTexture.h>

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  DepthStencilTexture::DepthStencilTexture()
    : Texture{ eTextureType2D, eTextureFormatExternalDS, eTextureFormatInternalD24S8, eTextureWrapClampToEdge, eTextureFilterNearest, eTextureValueTypeD24S8 }
  {

  }
}