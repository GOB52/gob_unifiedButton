/*
  gob_unifiedButton example
  rotation for CoreS3
 */
#include <M5Unified.h>
#include <gob_unifiedButton.hpp>

goblib::UnifiedButton unifiedButton; // gob_unifiedButton instance
auto& display = M5.Display;

void setup()
{
    M5.begin();
    unifiedButton.begin(&display);
    //unifiedButton.begin(&display, goblib::UnifiedButton::appearance_t::top);
    display.clear(TFT_DARKGREEN);
    unifiedButton.getButtonA()->setLabelText("ROTATE");
}

void loop()
{
    bool force{};
    static uint_fast8_t rot{display.getRotation()};
    
    M5.update();
    unifiedButton.update();

    // Change rotation
    if(M5.BtnA.wasClicked())
    {
        rot = (rot + 1) & 0x07;
        M5_LOGI("setRotation:%u", rot);

        display.clear(TFT_DARKGREEN);

        display.setRotation(rot);
        unifiedButton.setRotation(display.getRotation()); // Do not use a value different from the target!
        // If you have already customized the buttons, you will need to do it again.
        unifiedButton.getButtonA()->setLabelText("ROTATE");

        force = true;
    }

    display.setCursor(16, 64);
    display.printf("R:%u W:%d H:%d\n", display.getRotation(), display.width(), display.height());
    display.printf("Click A to rotate buttons");
    unifiedButton.draw(force);
}
