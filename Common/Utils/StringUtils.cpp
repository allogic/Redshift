#include <Common/Utils/StringUtils.h>

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  std::string StringUtils::CutFront(const std::string& String, U64 Size)
  {
    return String.substr(Size);
  }

  std::string StringUtils::CutBack(const std::string& String, U64 Size)
  {
    return String.substr(0, String.size() - Size);
  }

  std::string StringUtils::RemoveNulls(const std::string& String)
  {
    std::stringstream stream;

    for (U32 i = 0; i < String.size(); i++)
    {
      if (String[i] != 0)
      {
        stream << String[i];
      }
    }

    return stream.str();
  }

  std::string StringUtils::ToLower(std::string String)
  {
    std::transform(String.begin(), String.end(), String.begin(), [](U8 Chr)
      {
        return std::tolower(Chr);
      }
    );

    return String;
  }

  std::string StringUtils::ToUpper(std::string String)
  {
    std::transform(String.begin(), String.end(), String.begin(), [](U8 Chr)
      {
        return std::toupper(Chr);
      }
    );

    return String;
  }
}