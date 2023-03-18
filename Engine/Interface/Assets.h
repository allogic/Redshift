#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <map>
#include <set>

#include <Common/Types.h>

#include <Vendor/RAPIDJSON/rapidjson.h>

///////////////////////////////////////////////////////////
// Namespaces
///////////////////////////////////////////////////////////

namespace fs = std::filesystem;
namespace rj = rapidjson;

///////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////

namespace rs
{
  class FileTree;
}

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  class Assets
  {
  public:

    Assets();
    virtual ~Assets();

  public:

    void Render();

  private:

    void GenerateTreeRecursive(FileTree* Node);
    void DrawTreeRecursive(FileTree* Node);

  private:

    fs::path mAssetFile;
    FileTree* mFileTree;

    std::map<fs::path, void*> mAssets = {};
  };
}