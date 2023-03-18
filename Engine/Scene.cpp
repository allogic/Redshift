#include <Engine/Scene.h>

#include <Engine/Actors/Player.h>

#include <Engine/Renderer/DebugRenderer.h>

#include <Engine/Components/Camera.h>
#include <Engine/Components/Transform.h>

#include <Vendor/GLAD/glad.h>

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  Scene::Scene()
  {
    mRootActor = CreateActor<Actor>("Root", nullptr);
    mMainActor = CreateActor<Player>("Player", mRootActor);
  }

  Scene::~Scene()
  {
    for (auto& actor : mActors)
    {
      delete actor;
    }
  }

  Actor* Scene::GetMainActor()
  {
    return mMainActor;
  }

  Camera* Scene::GetMainCamera()
  {
    if (mMainActor)
    {
      return mMainActor->GetComponent<Camera>();
    }

    return nullptr;
  }

  void Scene::DestroyActor(Actor* Actor)
  {
    auto actorIt = std::find(mActors.begin(), mActors.end(), Actor);

    if (actorIt != mActors.end())
    {
      delete *actorIt;

      mActors.erase(actorIt);
    }
  }

  void Scene::Resize(U32 Width, U32 Height)
  {
    mWidth = Width;
    mHeight = Height;

    mFrameBuffer.Resize(mWidth, mHeight);
  }

  void Scene::Update()
  {
    mDebugRenderer.Line(R32V3{ -10000.0F, 0.0F, 0.0F }, R32V3{ 10000.0F, 0.0F, 0.0F }, R32V4{ 1.0F, 0.0F, 0.0F, 1.0F });
    mDebugRenderer.Line(R32V3{ 0.0F, -10000.0F, 0.0F }, R32V3{ 0.0F, 10000.0F, 0.0F }, R32V4{ 0.0F, 1.0F, 0.0F, 1.0F });
    mDebugRenderer.Line(R32V3{ 0.0F, 0.0F, -10000.0F }, R32V3{ 0.0F, 0.0F, 10000.0F }, R32V4{ 0.0F, 0.0F, 1.0F, 1.0F });

    mDebugRenderer.Quad(R32V2{ -25.0F, -25.0F }, R32V2{ 50.0F, 50.0F }, R32V4{ 1.0F, 1.0F, 0.0F, 1.0F });

    for (const auto& actor : mActors)
    {
      actor->Update();

      //Transform* transform = actor->GetTransform();
      //Renderable* renderable = actor->GetComponent<Renderable>();
      //
      //if (transform && renderable)
      //{
      //  mDefaultRenderer.AddRenderTask(RenderTask{ transform, renderable->GetMeshPtr() });
      //}
      //
      //if (actor != mMainActor)
      //{
      //  mDebugRenderer.Line(transform->GetWorldPosition(), transform->GetWorldPosition() + transform->GetWorldRight(), R32V4{ 1.0F, 0.0F, 0.0F, 1.0F });
      //  mDebugRenderer.Line(transform->GetWorldPosition(), transform->GetWorldPosition() + transform->GetWorldUp(), R32V4{ 0.0F, 1.0F, 0.0F, 1.0F });
      //  mDebugRenderer.Line(transform->GetWorldPosition(), transform->GetWorldPosition() + transform->GetWorldFront(), R32V4{ 0.0F, 0.0F, 1.0F, 1.0F });
      //
      //  mDebugRenderer.Line(transform->GetWorldPosition(), transform->GetWorldPosition() + transform->GetLocalRight(), R32V4{ 1.0F, 0.0F, 0.0F, 1.0F });
      //  mDebugRenderer.Line(transform->GetWorldPosition(), transform->GetWorldPosition() + transform->GetLocalUp(), R32V4{ 0.0F, 1.0F, 0.0F, 1.0F });
      //  mDebugRenderer.Line(transform->GetWorldPosition(), transform->GetWorldPosition() + transform->GetLocalFront(), R32V4{ 0.0F, 0.0F, 1.0F, 1.0F });
      //
      //  if (actor->GetParent())
      //  {
      //    mDebugRenderer.Line(transform->GetWorldPosition(), transform->GetWorldPosition(), R32V4{ 1.0F, 1.0F, 1.0F, 1.0F });
      //  }
      //}
    }
  }

  void Scene::Render()
  {
    glViewport(0, 0, (I32)mWidth, (I32)mHeight);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFrameBuffer.GetId());

    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    //mDefaultRenderer.Render();

    glDisable(GL_CULL_FACE);

    mDebugRenderer.Render();

    glDisable(GL_DEPTH_TEST);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  }

  void Scene::Load(const fs::path& File)
  {

  }

  void Scene::Save(const fs::path& File)
  {
    
  }
}