/*!
  @file gob_unifiedButton.cpp
  @brief Touch buttons for CoreS3 and commonality with conventional buttons (M5.BtnX)
  @author GOB @GOB_52_GOB https://twitter.com/GOB_52_GOB
*/
#include <M5Unified.h>
#include "gob_unifiedButton.hpp"

namespace gob
{
// class UnifiedButton
void UnifiedButton::begin(LovyanGFX* gfx, const appearance_t app)
{
    _board = M5.getBoard();
    assert(gfx);
    _gfx = gfx;
    _appearance = app;
    _dirty = true;
    createButtons(_appearance);
}

void UnifiedButton::createButtons(const appearance_t app)
{
    int32_t w{_gfx->width() / 3};
    int32_t h{32};
    int32_t left{(_gfx->width() - w * 3)/2} ;
    int32_t top{};
    switch(app)
    {
    case appearance_t::bottom:
    case appearance_t::transparent_bottom:
        top = _gfx->height() - h/2;
        break;
    case appearance_t::top:
    case appearance_t::transparent_top:
        top = h/2;
        break;
    default: // transparent_all
        h = _gfx->height();
        top = h/2;
        break;
    }

    constexpr int32_t olClr = lgfx::color565(64,64,64);
    
    _btnA.initButton(_gfx, left + w * 0 + w / 2, top, w, h, olClr, TFT_DARKGRAY, TFT_BLACK, "BtnA");
    _btnB.initButton(_gfx, left + w * 1 + w / 2, top, w, h, olClr, TFT_DARKGRAY, TFT_BLACK, "BtnB");
    _btnC.initButton(_gfx, left + w * 2 + w / 2, top, w, h, olClr, TFT_DARKGRAY, TFT_BLACK, "BtnC");

    M5_LOGI("[gob] change appearance_t:%02xH", app);
}

void UnifiedButton::update()
{
    if(_board != m5::board_t::board_M5StackCoreS3) { return; }

    // Processes buttons in the same way as they are processed in Core2
    auto ms = m5gfx::millis();
    M5.Touch.update(ms);

    uint_fast8_t btn_bits{};
    uint_fast8_t prev = _press_bits;
    _press_bits = btn_bits = 0;
    int i = M5.Touch.getCount();

    while (--i >= 0)
    {
        auto raw = M5.Touch.getTouchPointRaw(i);
        auto& det = M5.Touch.getDetail(i);
        if (det.state & m5::touch_state_t::touch)
        {
            if (M5.BtnA.isPressed()) { btn_bits |= 1 << 0; }
            if (M5.BtnB.isPressed()) { btn_bits |= 1 << 1; }
            if (M5.BtnC.isPressed()) { btn_bits |= 1 << 2; }
            if (btn_bits || !(det.state & m5::touch_state_t::mask_moving))
            {
                _press_bits = btn_bits |= _btnA.contains(raw.x, raw.y) << 0;
                _press_bits = btn_bits |= _btnB.contains(raw.x, raw.y) << 1;
                _press_bits = btn_bits |= _btnC.contains(raw.x, raw.y) << 2;
            }
        }
    }

    // Set status to M5.BtnX
    M5.BtnA.setRawState(ms, btn_bits & 1);
    M5.BtnB.setRawState(ms, btn_bits & 2);
    M5.BtnC.setRawState(ms, btn_bits & 4);

    _dirty |= prev != _press_bits;
}

void UnifiedButton::draw(const bool force)
{
    if(_board != m5::board_t::board_M5StackCoreS3) { return; }

    if(!(_appearance & appearance_t::transparent_bottom) && _show && (_dirty || force))
    {
        _dirty = false;
        _btnA.drawButton(_press_bits & 1);
        _btnB.drawButton(_press_bits & 2);
        _btnC.drawButton(_press_bits & 4);
    }
}
//
}
