/*!
  @file gob_unifiedButton.hpp
  @brief Library main header

  @mainpage gob_unifiedButton
  This library adds software touch buttons on CoreS3 and Tough, which does not have physical buttons or touch buttons, and enables the user to acquire the status via M5.BtnX.  

  @author GOB / GitHub:<a href="https://github.com/GOB52/">GOB52</a> / X:<a href="https://twitter.com/gob_52_gob">@GOB_52_GOB</a>

  @copyright 2023 GOB
  @copyright Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */
#ifndef GOB_UNIFIED_BUTTON_HPP
#define GOB_UNIFIED_BUTTON_HPP

#include <utility/Button_Class.hpp>
#include <M5GFX.h>

/*!
  @namespace goblib
  @brief Top level namespace of mine
 */
namespace goblib
{

/*!
  @class UnifiedButton
  @brief Drawing buttons. Processing of  buttons and setting their state to M5.BtnX.
 */
class UnifiedButton
{
  public:
    /*!
      @enum appearance_t
      @brief Button appearance
    */
    enum appearance_t : uint8_t
    {
        bottom,             //!< Display buttons at the bottom of the screen (default)
        top,                //!< Display buttons at the top of the screen
        transparent_bottom = 0x40, //!< Transparent buttons on the bottom of the screen
        transparent_top,    //!< Transparent buttons on the top of the screen
        transparent_all,    //!< Transparent buttons are placed on the entire screen (three vertical sections)
    };

    UnifiedButton() {}

    ///@cond
    UnifiedButton(const UnifiedButton&) = delete;
    UnifiedButton& operator=(const UnifiedButton&) = delete;
    ///@endcond
    
    /*!
      @brief Begin the unified button
      @param gfx Target for drawing
      @param app Button appearance
    */
    void begin(LovyanGFX* gfx, const appearance_t app = appearance_t::bottom);

    /*!
      @brief Update status
      @warning Call it after M5.update()
     */
    void update();

    /*!
      @brief Draw buttons when the state changes
      @param force Force drawing if true
     */
    void draw(const bool force = false);

    //! @brief Gets the target gfx
    LovyanGFX* gfx() { return _gfx; }

    /// @name Drawing control
    ///@{
    inline void show(const bool b) { _dirty |= _show = b; } //!< @brief Show or hide buttons
    inline void show() { show(true);  } //!< @brief Show buttons
    inline void hide() { show(false); } //!< @brief Hide buttons
    ///@}

    ///@name Font
    ///@{
    const lgfx::IFont* getFont() const { return _font; } //!< @brief Getss the font of the button text
    void setFont(const lgfx::IFont* f) { assert(f && "nullptr"); _font = f; } //!< @brief Set font of the button text
    ///@}

    /*!
      @brief Change appearance
      @param app Button appearance
    */
    void changeAppearance(const appearance_t app)
    {
        if(app != _appearance)
        {
            _dirty = true;
            _appearance = app;
            create_buttons(_appearance);
        }
    }

    /*!
      @brief Change rotation
      @param rot Rotation code same as M5GFX [0...7]
      @warning If you have already customized the buttons, you will need to do it again.
    */
    void setRotation(const uint_fast8_t rot);
    
    ///@name Gets the LGFX_Button
    ///@{
    LGFX_Button* getButtonA() { return  &_btns[0]; } //!< @brief Gets the button A
    LGFX_Button* getButtonB() { return  &_btns[1]; } //!< @brief Gets the button B
    LGFX_Button* getButtonC() { return  &_btns[2]; } //!< @brief Gets the button C
    ///@}

    /// @cond
    [[deprecated("please use show(const bool)")]]
    inline void showButtons(const bool b) { show(b); }
    [[deprecated("please use show()")]]
    inline void showButtons() { show(true);  }
    [[deprecated("please use hide()")]]
    inline void hideButtons() { show(false); }
    /// @endcond
    
  private:
    void create_buttons(const appearance_t app);

    LGFX_Button _btns[3]; // 0:A, 1:B, 2:C
    LovyanGFX* _gfx{};
    uint_fast8_t _press_bits{};
    bool _enable{}, _dirty{}, _show{true};
    appearance_t _appearance{appearance_t::bottom};
    const lgfx::IFont* _font{};
    uint_fast8_t _rotation{(uint_fast8_t)-1}; // Same as M5GFX
    m5::Button_Class _m5btns[3];
};
//
}
#endif
