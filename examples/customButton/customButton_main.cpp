/*
  gob_unifiedButton example
  customButton for CoreS3
 */
#include <M5Unified.h>
#include <gob_unifiedButton.hpp>
#include "esp_random.h"

goblib::UnifiedButton unifiedButton; // gob_unifiedButton instance

void setup()
{
    M5.begin();
    unifiedButton.begin(&M5.Display);
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
    bool force{};

    M5.update();
    unifiedButton.update();

    auto btnA = unifiedButton.getButtonA();
    auto btnB = unifiedButton.getButtonB();

    static bool pa{};
    bool ba = M5.BtnA.isPressed();
    if(pa != ba)
    {
        M5_LOGI("A button was changed");
        btnA->setLabelText(M5.BtnA.isPressed() ? "Pressed" : "Released");
        force = true;
    }
    pa = ba;

    if(M5.BtnB.wasClicked())
    {
        M5_LOGI("B button was clicked");
        uint16_t clr = esp_random() & 0xFFFF;
        btnB->setOutlineColor(clr);
        btnB->setFillColor(clr ^ 0xFFFF);
        btnB->setTextColor(clr ^ 0xFF00);
        force = true;
    }
    
    if(M5.BtnC.wasReleased())
    {
        M5_LOGI("C button was released");
    }

    unifiedButton.draw(force /*Force drawing to immediately reflect changes to LGFX_Button if true*/ );
}
