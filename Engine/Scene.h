#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <utility>

#include <Common/Types.h>

#include <Engine/Actor.h>
#include <Engine/FrameBuffer.h>

#include <Engine/Renderer/DebugRenderer.h>

///////////////////////////////////////////////////////////
// Namespaces
///////////////////////////////////////////////////////////

namespace fs = std::filesystem;

///////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////

namespace rs
{
  class Camera;
}

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  class Scene
  {
  public:

    Scene();
    ~Scene();

  public:

    inline auto GetWidth() const { return mWidth; }
    inline auto GetHeight() const { return mHeight; }
    inline auto GetAspectRatio() const { return (R32)mWidth / mHeight; }

    inline const auto& GetActors() const { return mActors; }
    inline const auto& GetFrameBuffer() const { return mFrameBuffer; }

  public:

    Actor* GetMainActor();
    Camera* GetMainCamera();

  public:

    template<typename A, typename ... Args>
    A* CreateActor(const std::string& Name, Actor* Parent, Args&& ... Arguments);

    void DestroyActor(Actor* Actor);

  public:

    void Resize(U32 Width, U32 Height);
    void Update();
    void Render();

  public:

    void Load(const fs::path& File);
    void Save(const fs::path& File);

  private:

    U32 mWidth = 0;
    U32 mHeight = 0;

    std::vector<Actor*> mActors = {};

    Actor* mRootActor = nullptr;
    Actor* mMainActor = nullptr;

    DebugRenderer mDebugRenderer = { 65535, 65535 * 2 };

    FrameBuffer mFrameBuffer = {};
  };
}

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  template<typename A, typename ... Args>
  A* Scene::CreateActor(const std::string& Name, Actor* Parent, Args&& ... Arguments)
  {
    auto actor = mActors.emplace_back(new A{ Name, std::forward<Args>(Arguments) ... });

    if (Parent)
    {
      actor->SetParent(Parent);
      Parent->AddChild(actor);
    }

    return (A*)actor;
  }
}