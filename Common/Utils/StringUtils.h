#pragma once

#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>

#include <Common/Types.h>

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  class StringUtils
  {
  public:

    static std::string CutFront(const std::string& String, U64 Size);
    static std::string CutBack(const std::string& String, U64 Size);
    static std::string RemoveNulls(const std::string& String);
    static std::string ToLower(std::string String);
    static std::string ToUpper(std::string String);
  };
}