/*
  gob_unifiedButton example
  simple for Core/Core2/CoreS3
 */
#include <M5Unified.h>
#include <gob_unifiedButton.hpp>
#include <gob_unifiedButton_version.hpp>

goblib::UnifiedButton unifiedButton; // gob_unifiedButton instance

void setup()
{
    M5.begin();
    unifiedButton.begin(&M5.Display);
    M5.Display.clear(TFT_DARKGREEN);
    M5_LOGI("gob_unifiedButton %s / %x", GOBLIB_UNIFIED_BUTTON_VERSION_STRING, GOBLIB_UNIFIED_BUTTON_VERSION_VALUE);
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

    if(M5.BtnC.wasReleased())
    {
        M5_LOGI("C button was released");
    }

    unifiedButton.draw();
}
