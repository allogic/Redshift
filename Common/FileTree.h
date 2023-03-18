#pragma once

#include <filesystem>
#include <map>

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
  class FileTree
  {
  public:

    FileTree(const fs::path& File);
    virtual ~FileTree();

  public:

    inline auto IsDirectory() const { return fs::is_directory(mFile); }
    inline auto IsFile() const { return fs::is_regular_file(mFile); }

    inline auto GetFile() const { return mFile; }
    inline auto GetParent() const { return mFile.parent_path(); }
    inline auto GetPath() const { return mFile; }
    inline auto GetName() const { return mFile.stem(); }
    inline auto GetExtension() const { return mFile.extension(); }
    inline auto GetSize() const { return fs::file_size(mFile); }

  public:

    inline auto begin() { return mNodes.begin(); }
    inline const auto begin() const { return mNodes.cbegin(); }

    inline auto end() { return mNodes.end(); }
    inline const auto end() const { return mNodes.cend(); }

  private:

    fs::path mFile;

    std::map<fs::path, FileTree*> mNodes = {};
  };
}