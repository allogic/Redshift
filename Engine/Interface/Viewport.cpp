#include <Engine/Scene.h>

#include <Engine/Textures/RenderTexture.h>

#include <Engine/Interface/Viewport.h>

#include <Vendor/IMGUI/imgui.h>

///////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////

extern rs::Scene* gScene;

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  void Viewport::Render()
  {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0F, 0.0F });
    ImGui::Begin("Viewport");

    mIsFocused = ImGui::IsWindowFocused();

    if (gScene)
    {
      if (HasResized())
      {
        gScene->Resize(mWidth, mHeight);
      }

      gScene->Update();
      gScene->Render();

      ImGui::Image((void*)(U64)gScene->GetFrameBuffer().GetColorTexture()->GetId(), ImVec2{ (R32)mWidth, (R32)mHeight }, ImVec2{ 0.0F, 1.0F }, ImVec2{ 1.0F, 0.0F });
    }

    ImGui::End();
    ImGui::PopStyleVar();
  }

  bool Viewport::HasResized()
  {
    ImVec2 view = ImGui::GetContentRegionAvail();

    if ((U32)view.x != mWidth || (U32)view.y != mHeight)
    {
      if ((U32)view.x == 0 || (U32)view.y == 0)
      {
        return false;
      }

      mWidth = (U32)view.x;
      mHeight = (U32)view.y;

      return true;
    }

    return false;
  }
}