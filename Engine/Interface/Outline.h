#pragma once

#include <string>

#include <Common/Types.h>

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  class Outline
  {
  public:

    void Render();

  private:

    void DrawActorRecursive(Actor* Actor);

  private:

    void HandleDragActor();
    bool ActorContainsChild(Actor* Node);

  private:

    Actor* mDragSourceActor = nullptr;
    Actor* mDragTargetActor = nullptr;
  };
}