#include <Engine/Actor.h>
#include <Engine/Interface.h>
#include <Engine/Scene.h>

#include <Engine/Interface/Outline.h>

#include <Vendor/IMGUI/imgui.h>

///////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////

namespace rs
{
  class Actor;
}

///////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////

extern rs::Interface* gInterface;
extern rs::Scene* gScene;

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  static char sPayloadIdentifier[] = "Actor";

  void Outline::Render()
  {
    ImGui::Begin("Outline");

    if (ImGui::Button("Add"))
    {
      gScene->CreateActor<Actor>("Actor", gInterface->GetSelectedActor());
    }

    if (gScene)
    {
      for (auto& actor : gScene->GetActors())
      {
        if (!actor->HasParent())
        {
          DrawActorRecursive(actor);
        }
      }

      if (mDragSourceActor && mDragTargetActor)
      {
        HandleDragActor();

        mDragSourceActor = nullptr;
        mDragTargetActor = nullptr;
      }
    }

    ImGui::End();
  }

  void Outline::DrawActorRecursive(Actor* Node)
  {
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0F, 0.0F });
    ImGui::PushID(Node);

    U32 flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;

    if (Node == gInterface->GetSelectedActor()) flags |= ImGuiTreeNodeFlags_Selected;

    if (Node->IsChild())
    {
      flags |= ImGuiTreeNodeFlags_Leaf;
    }

    U32 opened = ImGui::TreeNodeEx(Node->GetName().c_str(), flags);

    if (ImGui::IsItemClicked(0) || ImGui::IsItemClicked(1))
    {
      gInterface->SetSelectedActor(Node);
    }

    if (ImGui::BeginPopupContextItem())
    {
      std::string buffer = Node->GetName();
      buffer.resize(32);

      if (ImGui::InputText("##", buffer.data(), buffer.size(), ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue))
      {
        Node->SetName(buffer);
      }

      ImGui::EndPopup();
    }

    if (ImGui::BeginDragDropSource())
    {
      ImGui::SetDragDropPayload(sPayloadIdentifier, &Node, sizeof(Actor*));
      ImGui::Text(Node->GetName().c_str());
      ImGui::EndDragDropSource();
    }

    if (ImGui::BeginDragDropTarget())
    {
      const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(sPayloadIdentifier);

      if (payload)
      {
        mDragSourceActor = *(Actor**)payload->Data;
        mDragTargetActor = Node;
      }

      ImGui::EndDragDropTarget();
    }

    if (opened)
    {
      for (auto& child : *Node)
      {
        DrawActorRecursive(child);
      }

      ImGui::TreePop();
    }

    ImGui::PopID();
    ImGui::PopStyleVar();
  }

  void Outline::HandleDragActor()
  {
    if (!mDragSourceActor->ContainsChildRecursive(mDragTargetActor))
    {
      if (mDragSourceActor->GetParent())
      {
        mDragSourceActor->GetParent()->RemoveChild(mDragSourceActor);
      }

      mDragSourceActor->SetParent(mDragTargetActor);
      mDragTargetActor->AddChild(mDragSourceActor);
    }
  }
}