#include <Engine/Input.h>
#include <Engine/Interface.h>

#include <Engine/Interface/Viewport.h>

#include <Engine/Actors/Player.h>

#include <Engine/Components/Camera.h>
#include <Engine/Components/Transform.h>

///////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////

extern rs::R32 gTimeDelta;

extern rs::Interface* gInterface;

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  Player::Player(std::string const& Name)
    : Actor{ Name }
    , mCamera{ AttachComponent<Camera>() }
  {
    GetTransform()->SetPosition(R32V3{ 0.0F, 0.0F, -100.0F });
  }

  void Player::Update()
  {
    Viewport* viewport = gInterface->GetViewportFor(this);

    if (viewport && viewport->IsFocused())
    {
      R32 keyboardMovementSpeed = (Input::IsKeyDown(Input::eKeyLeftShift)) ? mKeyboardMovementSpeedFast : mKeyboardMovementSpeedNormal;

      if (Input::IsKeyDown(Input::eKeyD)) GetTransform()->AddPosition(-GetTransform()->GetLocalRight() * keyboardMovementSpeed);
      if (Input::IsKeyDown(Input::eKeyA)) GetTransform()->AddPosition(GetTransform()->GetLocalRight() * keyboardMovementSpeed);
    
      if (Input::IsKeyDown(Input::eKeyE)) GetTransform()->AddPosition(GetTransform()->GetWorldUp() * keyboardMovementSpeed);
      if (Input::IsKeyDown(Input::eKeyQ)) GetTransform()->AddPosition(-GetTransform()->GetWorldUp() * keyboardMovementSpeed);
    
      if (Input::IsKeyDown(Input::eKeyW)) GetTransform()->AddPosition(GetTransform()->GetLocalFront() * keyboardMovementSpeed);
      if (Input::IsKeyDown(Input::eKeyS)) GetTransform()->AddPosition(-GetTransform()->GetLocalFront() * keyboardMovementSpeed);
    
      static R32V2 mousePositionStart;
      static R32V2 mousePositionDelta;
    
      if (Input::IsMousePressed(Input::eMouseRight))
      {
        mousePositionStart = Input::GetMousePosition();
      }

      if (Input::IsMouseDown(Input::eMouseRight) && Input::IsMouseDown(Input::eMouseLeft))
      {
        mousePositionDelta = mousePositionStart - Input::GetMousePosition();
    
        R32V3 position = GetTransform()->GetPosition();
    
        R32 mouseMovementSpeed = (Input::IsKeyDown(Input::eKeyLeftShift)) ? mMouseMovementSpeedFast : mMouseMovementSpeedNormal;
    
        position += GetTransform()->GetLocalRight() * mousePositionDelta.x * mouseMovementSpeed;
        position += GetTransform()->GetWorldUp() * mousePositionDelta.y * mouseMovementSpeed;
    
        GetTransform()->SetPosition(position);
      }
      else if (Input::IsMouseDown(Input::eMouseRight))
      {
        mousePositionDelta = mousePositionStart - Input::GetMousePosition();

        R32V3 rotation = GetTransform()->GetRotation();
    
        rotation.x -= mousePositionDelta.y * mMouseRotationSpeed;
        rotation.y += mousePositionDelta.x * mMouseRotationSpeed;
    
        if (rotation.x < -90.0F) rotation.x = -90.0F;
        if (rotation.x > 90.0F) rotation.x = 90.0F;
    
        GetTransform()->SetRotation(rotation);
      }
    
      mousePositionStart -= mousePositionDelta * mMouseDragDamping;
    }
  }
}