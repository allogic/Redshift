#pragma once

#include <string>

#include <Common/Types.h>

#include <Engine/Actor.h>

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
  class Player : public Actor
  {
  public:

    Player(std::string const& Name);

  public:

    void Update() override;

  private:

    Camera* mCamera;

    R32 mKeyboardMovementSpeedNormal = 0.05F;
    R32 mKeyboardMovementSpeedFast = 2.0F;

    R32 mMouseMovementSpeedNormal = 0.005F;
    R32 mMouseMovementSpeedFast = 0.2F;

    R32 mMouseRotationSpeed = 0.045F;

    R32 mMouseDragDamping = 0.2F;
  };
}