#pragma once

#include <map>
#include <string>

////////////////////////////////////////////////////////
// Primitive types
////////////////////////////////////////////////////////

using I8 = char;
using I16 = short;
using I32 = int;
using I64 = long long;

using U8 = char unsigned;
using U16 = short unsigned;
using U32 = int unsigned;
using U64 = long long unsigned;

using R32 = float;
using R64 = double;

////////////////////////////////////////////////////////
// Math operators
////////////////////////////////////////////////////////

using R32V2 = glm::fvec2;
using R32V3 = glm::fvec3;
using R32V4 = glm::fvec4;

using R64V2 = glm::dvec2;
using R64V3 = glm::dvec3;
using R64V4 = glm::dvec4;

using R32M3 = glm::fmat3;
using R32M4 = glm::fmat4;

using R64M3 = glm::dmat3;
using R64M4 = glm::dmat4;

using R32Q = glm::fquat;

using R64Q = glm::dquat;

////////////////////////////////////////////////////////
// Shader types
////////////////////////////////////////////////////////

namespace EShaderType
{
  enum Type : U32
  {
    Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER,
    Compute = GL_COMPUTE_SHADER,
  };
}

////////////////////////////////////////////////////////
// Program types
////////////////////////////////////////////////////////

namespace EProgramType
{
  enum Type : U32
  {
    Render,
    Compute,
  };
}

////////////////////////////////////////////////////////
// Event types
////////////////////////////////////////////////////////

namespace EInputState
{
  enum Type : U32
  {
    None,
    Pressed,
    Held,
    Released,
  };
}

////////////////////////////////////////////////////////
// Texture types
////////////////////////////////////////////////////////

namespace ETextureWrap
{
  enum Type : U32
  {
    Repeat = GL_REPEAT,
    ClampToEdge = GL_CLAMP_TO_EDGE,
  };
}
namespace ETextureFilter
{
  enum Type : U32
  {
    Linear = GL_LINEAR,
    Nearest = GL_NEAREST,
  };
}