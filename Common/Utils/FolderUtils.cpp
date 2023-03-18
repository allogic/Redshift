#include <Common/Utils/FolderUtils.h>

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  void FolderUtils::CreateIfNotExists(const fs::path& File)
  {
    if (!fs::exists(File))
    {
      fs::create_directory(File);
    }
  }

  fs::path FolderUtils::ToPosixPath(const fs::path& File)
  {
    std::string result = File.string();
    U64 position = 0;

    while ((position = result.find("\\", position)) != std::string::npos)
    {
      result.replace(position, 1, "/");
      position++;
    }

    return result;
  }
}