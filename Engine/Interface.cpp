#include <Engine/Interface.h>
#include <Engine/Scene.h>

#include <Engine/Interface/Outline.h>
#include <Engine/Interface/Assets.h>
#include <Engine/Interface/Properties.h>
#include <Engine/Interface/Viewport.h>

#include <Vendor/IMGUI/imgui.h>
#include <Vendor/IMGUI/imgui_impl_glfw.h>
#include <Vendor/IMGUI/imgui_impl_opengl3.h>

///////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////

extern rs::Scene* gScene;

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  Interface::Interface(GLFWwindow* GlfwContext)
  {
    IMGUI_CHECKVERSION();

    mImGuiContext = ImGui::CreateContext();

    ImGuiIO& imGuiIo = ImGui::GetIO();
    imGuiIo.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    imGuiIo.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    imGuiIo.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    imGuiIo.ConfigWindowsMoveFromTitleBarOnly = true;

    ImGuiStyle& imGuiStyle =ImGui::GetStyle();
    imGuiStyle.WindowRounding = 0.0F;
    imGuiStyle.FrameBorderSize = 0.0F;
    imGuiStyle.Colors[ImGuiCol_MenuBarBg] = { 0.1F, 0.1F, 0.1F, 1.0F };
    imGuiStyle.Colors[ImGuiCol_WindowBg] = { 0.1F, 0.1F, 0.1F, 1.0F };
    imGuiStyle.Colors[ImGuiCol_TitleBg] = { 0.1F, 0.1F, 0.1F, 1.0F };
    imGuiStyle.Colors[ImGuiCol_TitleBgActive] = { 0.1F, 0.1F, 0.1F, 1.0F };
    imGuiStyle.Colors[ImGuiCol_TitleBgCollapsed] = { 0.1F, 0.1F, 0.1F, 1.0F };

    ImGui_ImplGlfw_InitForOpenGL(GlfwContext, 1);
    ImGui_ImplOpenGL3_Init("#version 450 core");

    mOutline = new Outline;
    mAssets = new Assets;
    mProperties = new Properties;
    mViewports.emplace(gScene->GetMainActor(), new Viewport);
  }

  Interface::~Interface()
  {
    for (auto& [actor, viewport] : mViewports)
    {
      delete viewport;
    }

    if (mProperties)
    {
      delete mProperties;
    }

    if (mAssets)
    {
      delete mAssets;
    }

    if (mOutline)
    {
      delete mOutline;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext(mImGuiContext);
  }

  void Interface::Render()
  {
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();

    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("Scene"))
    {
      if (ImGui::MenuItem("New"))
      {
        if (gScene)
        {
          delete gScene;
        }

        gScene = new Scene;
      }

      if (ImGui::MenuItem("Load"))
      {
        if (gScene)
        {
          gScene->Load("");
        }
      }

      if (ImGui::MenuItem("Save"))
      {
        if (gScene)
        {
          gScene->Save("");
        }
      }

      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();

    mOutline->Render();
    mAssets->Render();
    mProperties->Render();

    for (const auto& [actor, viewport] : mViewports)
    {
      viewport->Render();
    }

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
  }
}