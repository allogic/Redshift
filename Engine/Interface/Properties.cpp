#include <Engine/Actor.h>
#include <Engine/Interface.h>

#include <Engine/Components/Camera.h>
#include <Engine/Components/Transform.h>

#include <Engine/Interface/Properties.h>

#include <Vendor/IMGUI/imgui.h>

///////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////

extern rs::Interface* gInterface;

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  void Properties::Render()
  {
    ImGui::Begin("Properties");

    if (Actor* actor = gInterface->GetSelectedActor())
    {
      if (Transform* transform = actor->GetComponent<Transform>())
      {
        ImGui::PushID(transform);
        if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_DefaultOpen))
        {
          ImGui::PushItemWidth(ImGui::GetWindowWidth() - ImGui::GetTreeNodeToLabelSpacing());

          R32V3 position = transform->GetPosition();
          if (ImGui::InputFloat3("##Position", &position[0], "%.3F", ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue))
          {
            transform->SetPosition(position);
          }

          R32V3 rotation = transform->GetRotation();
          if (ImGui::InputFloat3("##Rotation", &rotation[0], "%.3F", ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue))
          {
            transform->SetRotation(rotation);
          }

          R32V3 scale = transform->GetScale();
          if (ImGui::InputFloat3("##Scale", &scale[0], "%.3F", ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue))
          {
            transform->SetScale(scale);
          }

          ImGui::PopItemWidth();
          ImGui::TreePop();
        }
        ImGui::PopID();
      }

      if (Camera* camera = actor->GetComponent<Camera>())
      {
        ImGui::PushID(camera);
        if (ImGui::TreeNodeEx("Camera", ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_DefaultOpen))
        {
          ImGui::PushItemWidth(ImGui::GetWindowWidth() - ImGui::GetTreeNodeToLabelSpacing());

          R32 fov{ camera->GetFov() };
          if (ImGui::DragFloat("##Fov", &fov, 0.1F, 0.1F, 90.0F, "Fov %.3F"))
          {
            camera->SetFov(fov);
          }

          R32 near{ camera->GetNear() };
          if (ImGui::DragFloat("##Near", &near, 0.1F, 0.1F, 100.0F, "Near %.3F"))
          {
            camera->SetNear(near);
          }

          R32 far{ camera->GetFar() };
          if (ImGui::DragFloat("##Far", &far, 1.0F, 100.0F, 100000.0F, "Far %.3F"))
          {
            camera->SetFar(far);
          }

          ImGui::PopItemWidth();
          ImGui::TreePop();
        }
        ImGui::PopID();
      }
    }

    ImGui::End();
  }
}