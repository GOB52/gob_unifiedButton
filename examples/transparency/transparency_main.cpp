/*
  gob_unifiedButton example
  tranparency for Core/Core2/CoreS3
 */
#include <M5Unified.h>
#include <gob_unifiedButton.hpp>

goblib::UnifiedButton unifiedButton; // gob_unifiedButton instance

void setup()
{
    M5.begin();
    /*
      3 transparent buttons.
      Split screen vertically into 3 sections.
      +---+---+---+
      |   |   |   | 
      | A | B | C |
      |   |   |   |
      +---+---+---+
    */
    unifiedButton.begin(&M5.Display, goblib::UnifiedButton::transparent_all);
    M5.Display.clear(TFT_DARKGREEN);
}

void loop()
{
    M5.update();
    unifiedButton.update();

    if(M5.BtnA.wasHold())
    {
        M5_LOGI("A button was hold");
    }
    else if(M5.BtnA.wasClicked())
    {
        M5_LOGI("A button was clicked");
    }

    if(M5.BtnB.pressedFor(1000))
    {
        M5_LOGI("B button pressed for 1000 ms");
    }

    if(M5.BtnC.wasReleased())
    {
        M5_LOGI("C button was released");
    }

    unifiedButton.draw(); // For transparent buttons, nothing is drawn when invoked.
}
