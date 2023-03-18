#pragma once

#include <map>

#include <Common/Types.h>

///////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////

struct GLFWwindow;
struct ImGuiContext;

namespace rs
{
  class Actor;
  class Outline;
  class Assets;
  class Properties;
  class Viewport;
  class FileTree;
}

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  class Interface
  {
  public:

    inline auto GetSelectedActor() const { return mSelectedActor; }
    inline auto GetSelectedFile() const { return mSelectedFile; }

  public:

    inline void SetSelectedActor(Actor* Value) { mSelectedActor = Value; }
    inline void SetSelectedFile(FileTree* Value) { mSelectedFile = Value; }

  public:

    Interface(GLFWwindow* GlfwContext);
    virtual ~Interface();

  public:

    inline auto GetViewportFor(Actor* Actor) { return mViewports[Actor]; }

  public:

    void Render();

  private:

    ImGuiContext* mImGuiContext = nullptr;

    Outline* mOutline = nullptr;
    Assets* mAssets = nullptr;
    Properties* mProperties = nullptr;
    std::map<Actor*, Viewport*> mViewports = {};

    Actor* mSelectedActor = nullptr;
    FileTree* mSelectedFile = nullptr;
  };
}