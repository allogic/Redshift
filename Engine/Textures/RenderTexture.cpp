#include <Engine/Textures/RenderTexture.h>

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  RenderTexture::RenderTexture()
    : Texture{ eTextureType2D, eTextureFormatExternalRGBA, eTextureFormatInternalRGBA32R, eTextureWrapClampToEdge, eTextureFilterNearest, eTextureValueTypeR32 }
  {

  }
}