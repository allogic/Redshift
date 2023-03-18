#include <Engine/Actor.h>
#include <Engine/Scene.h>

#include <Engine/Components/Transform.h>
#include <Engine/Components/Camera.h>

#include <Vendor/GLM/gtc/matrix_transform.hpp>

///////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////

extern rs::Scene* gScene;

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  Camera::Camera(Actor* Actor)
    : Component{ Actor }
  {

  }

  R32M4 Camera::GetProjectionMatrix()
  {
    R32 fov = glm::radians(mFov);
    R32 aspectRatio = (gScene) ? gScene->GetAspectRatio() : 1.0F;
    
    return glm::perspective(fov, aspectRatio, mNear, mFar);
  }

  R32M4 Camera::GetViewMatrix()
  {
    Transform* transform = mActor->GetTransform();

    R32V3 position = transform->GetPosition();
    R32V3 up = transform->GetLocalUp();
    R32V3 front = transform->GetLocalFront();
    
    return glm::lookAt(position, position + front, up);
  }
}