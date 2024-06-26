/*!
  @file gob_unifiedButton.cpp
  @brief Library main source
  @author GOB @GOB_52_GOB https://twitter.com/GOB_52_GOB
*/
#include <M5Unified.h>
#include "gob_unifiedButton.hpp"

namespace
{
constexpr char labelA[] = "BtnA";
constexpr char labelB[] = "BtnB";
constexpr char labelC[] = "BtnC";
constexpr const char* label_table[] = { labelA, labelB, labelC };
constexpr decltype(TFT_DARKGRAY) olClr = lgfx::color565(64,64,64);
}
namespace goblib
{
// class UnifiedButton
void UnifiedButton::begin(LovyanGFX* gfx, const appearance_t app)
{
    assert(gfx);
    _gfx = gfx;
    _appearance = app;
    _dirty = true;
    _font = gfx->getFont();

    auto bd = M5.getBoard();
    _enable = (bd ==  m5::board_t::board_M5StackCoreS3 || bd ==  m5::board_t::board_M5Tough)
               && M5.Touch.isEnabled();
    _rotation = _gfx->getRotation();
    if(_enable) { create_buttons(_appearance); }

    if(M5.Touch.isEnabled() && !_enable)
    {
        M5_LOGW("Unsupported devices. getBoard() %u\n", bd);
    }
}

void UnifiedButton::create_buttons(const appearance_t app)
{
    int32_t w{_gfx->width() / 3};
    int32_t h{32};
    int32_t left{(_gfx->width() - w * 3)/2} ;
    int32_t top{};
    switch(app)
    {
    case appearance_t::bottom:
    case appearance_t::transparent_bottom:
        top = _gfx->height() - h;
        break;
    case appearance_t::top:
    case appearance_t::transparent_top:
        break;
    default: // transparent_all
        h = _gfx->height();
        break;
    }
    for(uint_fast8_t i = 0; i < 3; ++i)
    {
        _btns[i].initButtonUL(_gfx, left + w * i, top, w, h, olClr, TFT_DARKGRAY, TFT_BLACK,label_table[i]);
    }
}

void UnifiedButton::setRotation(const uint_fast8_t rot)
{
    _rotation = rot & 0x07; // Valid values are [0...7]
    create_buttons(_appearance);
}

void UnifiedButton::update()
{
    if(!_enable) { return; }

    // Processes buttons in the same way as they are processed in Core2
    auto ms = m5gfx::millis();
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
                // Correct coordinates to match rotation.
                auto x = raw.x;
                auto y = raw.y;
                const uint32_t rot = _gfx->getRotation();
                const auto wid = _gfx->width();
                const auto hgt = _gfx->height();

                if(!(rot & 1)) { std::swap(x, y); }
                const auto rot4 = rot ^ ((((rot >> 2) ^ 1) - 1) & 0x07); // 0-3 => 0-3,  4-7 => 3-0
                switch(rot4)
                {
                case 0: x = wid - x - 1; break;
                case 2: y = hgt - y - 1; break;
                case 3: x = wid - x - 1; y = hgt - y - 1; break;
                default: break;
                }

                for(int i=0; i<3; ++i)
                {
                    btn_bits |= (_btns[i].contains(x, y) << i);
                }
                //M5_LOGI("%d,%d : %x", x, y, btn_bits);
                _press_bits = btn_bits;
            }
        }
    }
    // Set status to M5.BtnX
    M5.BtnA.setRawState(ms, btn_bits & 1);
    M5.BtnB.setRawState(ms, btn_bits & 2);
    M5.BtnC.setRawState(ms, btn_bits & 4);

    _dirty |= (prev != _press_bits);
}

void UnifiedButton::draw(const bool force)
{
    if(_enable && !(_appearance & appearance_t::transparent_bottom) && _show && (_dirty || force))
    {
        auto gfont = _gfx->getFont();
        _gfx->setFont(_font);

        _dirty = false;
        for(int i=0; i < 3; ++i)
        {
            _btns[i].drawButton(_press_bits & (1<<i));
        }
        _gfx->setFont(gfont);
    }
}
//
}
