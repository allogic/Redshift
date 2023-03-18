#pragma once

#include <Common/Types.h>

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  class Input
  {
  public:

    enum Key
    {
      eKeyTab = 512,
      eKeyLeftArrow,
      eKeyRightArrow,
      eKeyUpArrow,
      eKeyDownArrow,
      eKeyPageUp,
      eKeyPageDown,
      eKeyHome,
      eKeyEnd,
      eKeyInsert,
      eKeyDelete,
      eKeyBackspace,
      eKeySpace,
      eKeyEnter,
      eKeyEscape,
      eKeyLeftCtrl,
      eKeyLeftShift,
      eKeyLeftAlt,
      eKeyLeftSuper,
      eKeyRightCtrl,
      eKeyRightShift,
      eKeyRightAlt,
      eKeyRightSuper,
      eKeyMenu,
      eKey0,
      eKey1,
      eKey2,
      eKey3,
      eKey4,
      eKey5,
      eKey6,
      eKey7,
      eKey8,
      eKey9,
      eKeyA,
      eKeyB,
      eKeyC,
      eKeyD,
      eKeyE,
      eKeyF,
      eKeyG,
      eKeyH,
      eKeyI,
      eKeyJ,
      eKeyK,
      eKeyL,
      eKeyM,
      eKeyN,
      eKeyO,
      eKeyP,
      eKeyQ,
      eKeyR,
      eKeyS,
      eKeyT,
      eKeyU,
      eKeyV,
      eKeyW,
      eKeyX,
      eKeyY,
      eKeyZ,
      eKeyF1,
      eKeyF2,
      eKeyF3,
      eKeyF4,
      eKeyF5,
      eKeyF6,
      eKeyF7,
      eKeyF8,
      eKeyF9,
      eKeyF10,
      eKeyF11,
      eKeyF12,
      eKeyApostrophe,
      eKeyComma,
      eKeyMinus,
      eKeyPeriod,
      eKeySlash,
      eKeySemicolon,
      eKeyEqual,
      eKeyLeftBracket,
      eKeyBackslash,
      eKeyRightBracket,
      eKeyGraveAccent,
      eKeyCapsLock,
      eKeyScrollLock,
      eKeyNumLock,
      eKeyPrintScreen,
      eKeyPause,
      eKeyKeypad0,
      eKeyKeypad1,
      eKeyKeypad2,
      eKeyKeypad3,
      eKeyKeypad4,
      eKeyKeypad5,
      eKeyKeypad6,
      eKeyKeypad7,
      eKeyKeypad8,
      eKeyKeypad9,
      eKeyKeypadDecimal,
      eKeyKeypadDivide,
      eKeyKeypadMultiply,
      eKeyKeypadSubtract,
      eKeyKeypadAdd,
      eKeyKeypadEnter,
      eKeyKeypadEqual,

      eKeyGamepadStart,
      eKeyGamepadBack,
      eKeyGamepadFaceUp,
      eKeyGamepadFaceDown,
      eKeyGamepadFaceLeft,
      eKeyGamepadFaceRight,
      eKeyGamepadDpadUp,
      eKeyGamepadDpadDown,
      eKeyGamepadDpadLeft,
      eKeyGamepadDpadRight,
      eKeyGamepadL1,
      eKeyGamepadR1,
      eKeyGamepadL2,
      eKeyGamepadR2,
      eKeyGamepadL3,
      eKeyGamepadR3,
      eKeyGamepadLStickUp,
      eKeyGamepadLStickDown,
      eKeyGamepadLStickLeft,
      eKeyGamepadLStickRight,
      eKeyGamepadRStickUp,
      eKeyGamepadRStickDown,
      eKeyGamepadRStickLeft,
      eKeyGamepadRStickRight,

      eKeyModCtrl,
      eKeyModShift,
      eKeyModAlt,
      eKeyModSuper,
    };

    enum Mouse
    {
      eMouseLeft = 0,
      eMouseRight = 1,
      eMouseMiddle = 2,
    };

  public:

    static R32V2 GetMousePosition();

    static bool IsKeyPressed(Key Key);
    static bool IsKeyDown(Key Key);
    static bool IsKeyReleased(Key Key);

    static bool IsMousePressed(Mouse Key);
    static bool IsMouseDown(Mouse Key);
    static bool IsMouseReleased(Mouse Key);
  };
}