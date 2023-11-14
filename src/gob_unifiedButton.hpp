/*!
  @file gob_unifiedButton.hpp
  @brief Add touch buttons for CoreS3 and commonality with conventional buttons (M5.BtnX)

  @mainpage gob_unifiedButton
  Add touch buttons for CoreS3 and commonality with conventional buttons (M5.BtnX)

  @author GOB / GitHub:<a href="https://github.com/GOB52/">GOB52</a> / Twitter:<a href="https://twitter.com/gob_52_gob">@GOB_52_GOB</a>

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
        custom,             //!< Customize your own buttons
        transparent_bottom = 0x40, //!< Transparent buttons on the bottom of the screen
        transparent_top,    //!< Transparent buttons on the top of the screen
        transparent_all,    //!< Transparent buttons are placed on the entire screen (three vertical sections)
    };

    UnifiedButton() {}

    //! @brief Gets the target gfx
    LovyanGFX* gfx() { return _gfx; }
    
    /*!
      @brief Initialize
      @param gfx Target for drawing
      @param app Button appearance
    */
    void begin(LovyanGFX* gfx, const appearance_t app = appearance_t::bottom);

    /// @name Drawing control
    ///@{
    inline void show(const bool b) { _dirty |= _show = b; } //!< @brief Show or hide buttons
    inline void show() { show(true);  } //!< @brief Show buttons
    inline void hide() { show(false); } //!< @brief Hide buttons
    ///@}

    /// @cond 0
    [[deprecated("please use show()")]]
    inline void showButtons(const bool b) { show(b); }
    [[deprecated("please use show()")]]
    inline void showButtons() { show(true);  }
    [[deprecated("please use hide()")]]
    inline void hideButtons() { show(false); }
    /// @endcond
    
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
            createButtons(_appearance);
        }
    }

    ///@name For customize buttons
    ///@warning Must be appearance is custom.
    ///@{
    LGFX_Button* getButtonA() { return _appearance == appearance_t::custom ? &_btnA : nullptr; } //!< @brief Gets the LGFX_Button A
    LGFX_Button* getButtonB() { return _appearance == appearance_t::custom ? &_btnB : nullptr; } //!< @brief Gets the LGFX_Button B
    LGFX_Button* getButtonC() { return _appearance == appearance_t::custom ? &_btnC : nullptr; } //!< @brief Gets the LGFX_Button C
    ///@}
    
  private:
    void createButtons(const appearance_t app);

    LGFX_Button _btnA{};
    LGFX_Button _btnB{};
    LGFX_Button _btnC{};

    LovyanGFX* _gfx{};
    uint_fast8_t _press_bits{};
    bool _dirty{}, _show{true};;
    appearance_t _appearance{appearance_t::bottom};
    m5::board_t _board{m5::board_t::board_unknown};
};
//
}
#endif
