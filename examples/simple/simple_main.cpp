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

    // You can change text font of button.
    unifiedButton.setFont(&fonts::Font4);
}

void loop()
{
    static bool showButton{true};

    M5.update();
    unifiedButton.update();

    // Core/Core2/CoreS3 Can work with common code.
    if(M5.BtnA.wasHold())
    {
        M5_LOGI("A button was hold");
    }
    else if(M5.BtnA.wasClicked())
    {
        showButton = !showButton;
        M5_LOGI("A button was clicked. button %s", showButton ? "show" : "hide(clear screen)");
        if(!showButton) { M5.Display.clear(TFT_DARKGREEN); }
        unifiedButton.show(showButton);
    }

    if(M5.BtnB.pressedFor(1000))
    {
        M5_LOGI("B button pressed for 1000 ms");
    }

    if(M5.BtnC.wasReleased())
    {
        M5_LOGI("C button was released");
    }

    // Can use with behavior as a touch screen if exists.
    if(M5.Touch.isEnabled())
    {
        auto dt = M5.Touch.getDetail();
        if(dt.y < M5.Display.height() - 32+8)
        {
            if(dt.isHolding())
            {
                M5.Lcd.fillCircle(dt.x, dt.y, 8, TFT_ORANGE);
            }
            else if(dt.isPressed())
            {
                M5.Lcd.fillCircle(dt.x, dt.y, 8, TFT_WHITE);
            }
        }
    }
    
    unifiedButton.draw();
}
