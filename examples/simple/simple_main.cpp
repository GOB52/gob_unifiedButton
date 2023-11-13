/*
  gob_unifiedButton example
  simple for Core/Core2/CoreS3
 */
#include <M5Unified.h>
#include <gob_unifiedButton.hpp>

goblib::UnifiedButton unifiedButton; // gob_unifiedButton instance

void setup()
{
    M5.begin();
    unifiedButton.begin(&M5.Display);
    M5.Display.clear(TFT_DARKGREEN);
}

void loop()
{
    unifiedButton.update();
    M5.update();

    // Core/Core2/CoreS3 Can work with common code.
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
    
    if(M5.BtnC.wasDoubleClicked())
    {
        M5_LOGI("C button was double clicked");
    }

    unifiedButton.draw();
}
