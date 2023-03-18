#pragma once

#include <Common/Types.h>

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  enum VertexType
  {
    eVertexTypeDefault,
    eVertexTypeLine,
  };

#pragma pack(push, 1)
  struct DefaultVertex
  {
    static constexpr VertexType Type = eVertexTypeDefault;

    R32V3 Position;
    R32V3 Normal;
    R32V2 Uv;
    R32V4 Color;
  };
#pragma pack(pop)

#pragma pack(push, 1)
  struct LineVertex
  {
    static constexpr VertexType Type = eVertexTypeLine;

    R32V3 Position;
    R32V4 Color;
  };
#pragma pack(pop)
}