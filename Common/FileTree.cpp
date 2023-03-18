#include <Common/FileTree.h>

#include <Common//Utils/FolderUtils.h>

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  FileTree::FileTree(const fs::path& File)
    : mFile{ FolderUtils::ToPosixPath(File) }
  {
    if (fs::is_directory(mFile))
    {
      for (const auto& file : fs::directory_iterator{ mFile })
      {
        mNodes[FolderUtils::ToPosixPath(file)] = new FileTree{ file };
      }
    }
  }

  FileTree::~FileTree()
  {
    for (auto& [file, node] : mNodes)
    {
      delete node;
    }
  }
}