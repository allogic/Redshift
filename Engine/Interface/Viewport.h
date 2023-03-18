#pragma once

#include <Common/Types.h>

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  class Viewport
  {
  public:

    inline auto IsFocused() const { return mIsFocused; }

  public:

    void Render();

  private:

    bool HasResized();

  private:

    U32 mWidth = 0;
    U32 mHeight = 0;

    bool mIsFocused = false;
  };
}