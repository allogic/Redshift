#include <Engine/Input.h>

#include <Vendor/IMGUI/imgui.h>

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  R32V2 Input::GetMousePosition()
  {
    R32V2 windowPosition = { ImGui::GetWindowPos().x, ImGui::GetWindowPos().y };
    R32V2 mousePosition = { ImGui::GetMousePos().x, ImGui::GetMousePos().y };

    return glm::clamp(mousePosition - windowPosition, R32V2{ 0.0F, 0.0F }, { ImGui::GetWindowWidth(), ImGui::GetWindowHeight() });
  }

  bool Input::IsKeyPressed(Key Key)
  {
    return ImGui::IsKeyPressed(Key);
  }

  bool Input::IsKeyDown(Key Key)
  {
    return ImGui::IsKeyDown(Key);
  }

  bool Input::IsKeyReleased(Key Key)
  {
    return ImGui::IsKeyReleased(Key);
  }

  bool Input::IsMousePressed(Mouse Key)
  {
    return ImGui::IsMouseClicked(Key);
  }

  bool Input::IsMouseDown(Mouse Key)
  {
    return ImGui::IsMouseDown(Key);
  }

  bool Input::IsMouseReleased(Mouse Key)
  {
    return ImGui::IsMouseReleased(Key);
  }
}