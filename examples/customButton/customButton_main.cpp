/*
  gob_unifiedButton example
  customButton for CoreS3
 */
#include <M5Unified.h>
#include <gob_unifiedButton.hpp>

goblib::UnifiedButton unifiedButton; // gob_unifiedButton instance

void setup()
{
    M5.begin();
    unifiedButton.begin(&M5.Display, goblib::UnifiedButton::appearance_t::custom);
    M5.Display.clear(TFT_DARKGREEN);

    // Customize buttons
    // see also https://github.com/m5stack/M5GFX/blob/master/src/lgfx/v1/LGFX_Button.hpp
    auto btnA = unifiedButton.getButtonA();
    assert(btnA);
    btnA->initButton(unifiedButton.gfx(),
                     M5.Display.width()/2, M5.Display.height()/8, M5.Display.width(), M5.Display.height()/4,
                     TFT_ORANGE, TFT_WHITE, TFT_BLUE, "A Button", 2.0f, 4.0f);

    auto btnB = unifiedButton.getButtonB();
    assert(btnB);
    btnB->initButton(unifiedButton.gfx(),
                     M5.Display.width()/4, M5.Display.height()/8*5, M5.Display.width()/2, M5.Display.height()*3/4,
                     TFT_LIGHTGRAY, TFT_DARKGRAY, TFT_BLACK, " Btn-B", 4.0f, 6.0f);

    auto btnC = unifiedButton.getButtonC();
    assert(btnC);
    btnC->initButtonUL(unifiedButton.gfx(),
                     M5.Display.width()/2, M5.Display.height()/4, M5.Display.width()/2, M5.Display.height()*3/4,
                     TFT_CYAN, TFT_MAGENTA, TFT_RED, " CCC", 3.0f, 3.0f);

}

void loop()
{
    M5.update();
    unifiedButton.update();

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
