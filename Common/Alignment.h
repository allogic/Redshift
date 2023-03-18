#pragma once

#include <type_traits>

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  template<unsigned P>
  class Align
  {
  public:

    template<typename T>
    requires std::is_integral_v<T>
    constexpr static inline T Down(T Value) { return Value & (~(P - 1)); }

    template<typename T>
    requires std::is_integral_v<T>
    constexpr static inline T Up(T Value) { return (Value + (P - 1)) & (~(P - 1)); }
  };
}