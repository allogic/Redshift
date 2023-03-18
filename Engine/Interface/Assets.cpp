#include <Common/FileTree.h>

#include <Common/Utils/StringUtils.h>

#include <Engine/Interface.h>
#include <Engine/Texture.h>

#include <Engine/Interface/Assets.h>

#include <Vendor/IMGUI/imgui.h>

#include <Vendor/RAPIDJSON/document.h>

///////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////

extern rj::Document gConfig;

extern rs::Interface* gInterface;

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  Assets::Assets()
    : mAssetFile{ gConfig["assetsDir"].GetString() }
    , mFileTree{ new FileTree{ mAssetFile } }
  {
    GenerateTreeRecursive(mFileTree);
  }

  Assets::~Assets()
  {
    delete mFileTree;
  }

  void Assets::Render()
  {
    ImGui::Begin("Assets");

    DrawTreeRecursive(mFileTree);

    ImGui::End();
  }

  void Assets::GenerateTreeRecursive(FileTree* Node)
  {
    for (auto& [file, node] : *Node)
    {
      if (node->IsDirectory())
      {
        GenerateTreeRecursive(node);
      }
      else
      {
        fs::path relativeFile = StringUtils::CutFront(node->GetFile().string(), mAssetFile.string().size());

        if (!mAssets[relativeFile])
        {
          if (node->GetExtension() == ".dds")
          {
            mAssets[relativeFile] = new Texture{ node->GetFile(), eTextureWrapClampToEdge, eTextureFilterNearest };
          }
        }
      }
    }
  }

  void Assets::DrawTreeRecursive(FileTree* Node)
  {
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0F, 0.0F });
    ImGui::PushID(Node);
    
    U32 flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;
    
    if (Node == gInterface->GetSelectedFile()) flags |= ImGuiTreeNodeFlags_Selected;
    
    U32 opened = ImGui::TreeNodeEx(Node->GetName().string().c_str(), flags);
    
    if (ImGui::IsItemClicked(0) || ImGui::IsItemClicked(1))
    {
      gInterface->SetSelectedFile(Node);
    }
    
    if (ImGui::BeginPopupContextItem())
    {    
      ImGui::EndPopup();
    }
    
    if (opened)
    {
      for (auto& [file, node] : *Node)
      {
        if (node->IsDirectory())
        {
          DrawTreeRecursive(node);
        }
        else
        {
          fs::path relativeFile = StringUtils::CutFront(node->GetFile().string(), mAssetFile.string().size());

          if (node->GetExtension() == ".dds")
          {
            Texture* texture = (Texture*)mAssets[relativeFile];

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 5.0F, 5.0F });
            ImGui::Image((void*)(U64)texture->GetId(), ImVec2{ (R32)texture->GetWidth(), (R32)texture->GetHeight() });
            ImGui::PopStyleVar();
          }
        }
      }
    
      ImGui::TreePop();
    }
    
    ImGui::PopID();
    ImGui::PopStyleVar();
  }
}