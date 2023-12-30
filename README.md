# gob_unifiedButton

[日本語](https://github.com/GOB52/gob_unifiedButton/blob/master/README.ja.md)

![gob_unifiedButton](https://github.com/GOB52/gob_unifiedButton/assets/26270227/590cde0d-f4b6-4fe6-8cae-e25d27b32f8b)

## Overview
This library adds touch buttons on CoreS3, which does not have physical buttons or touch buttons, and enables the user to acquire the status via M5.BtnX.  
Please use this as an interim feature until a similar feature is added to [M5Unified](https://github.com/m5stack/M5Unified) in the future.  
It is also useful for those who are making a common source for Basic, Gray, and Core2, as it does not process anything other than CoreS3.

## Required libraries
* [M5Unified](https://github.com/m5stack/M5Unified)
* [M5GFX](https://github.com/m5stack/M5GFX)

**M5Unified is assumed, so it cannot be applied to those using M5Core3.h.**

## How to install
Install in an appropriate way depending on your environment.
* git clone or download zip, and extract into place
* platformio.ini
```ini
lib_deps = gob/gob_unifiedButton
```
* Use library manager on ArduinoIDE

## How to use
```cpp
#include <M5Unified.h>
#include <gob_unifiedButton.hpp>

goblib::UnifiedButton unifiedButton;

void setup()
{
    M5.begin();
    unifiedButton.begin(&M5.Display);
}

void loop()
{
    M5.update();
    unifiedButton.update(); // Must be call after M5.update. (Changed to call after M5.update() since 0.1.0)

    // M5.BtnX can be used to obtain status
    if(M5.BtnA.wasHold())
    {
        // ...
    }
    else if(M5.BtnA.wasClicked())
    {
        // ...
    }

    // Drawing Buttons
    unifiedButton.draw();
}
```
## Button text font changes
You can configure which fonts can be used with M5GFX.
```cpp
    unifiedButton.setFont(&fonts::Font4);
```

## Appearance changes
You can specify it with begin or change it with changeAppearance.

|Argument goblib::UnifiedButton::appearance\_t|Description|
|---|---|
|bottom| Display buttons at the bottom of the screen (default)|
|top|Display buttons at the top of the screen|
|custom|Customize your own buttons|
|transparent\_bottom|Transparent buttons on the bottom of the screen|
|transparent\_top|Transparent buttons on the top of the screen|
|transparent_all|Transparent buttons are placed on the entire screen (three vertical sections)|

## Customize Buttons
If after specifying goblib::UnifiedButton::appearance\_t::custom,
getButtonA / getButtonB / getButtonC to get LGFX_Button\*.

```cpp
void setup()
{
    M5.begin();
    unifiedButton.begin(&M5.Display, goblib::UnifiedButton::appearance_t::custom);

    auto btnA = unifiedButton.getButtonA();
    auto btnB = unifiedButton.getButtonB();
    auto btnC = unifiedButton.getButtonC();

    // Re-create buttons with unique shape, color, and text
    btnA->initButton(unifiedButton.gfx(), 40, 120, 80, 240 ,TFT_GREEN, TFT_BLUE, TFT_WHITE, "[A]");
    ...
}
```

## Document
Can be created from a [configuration file](doc/Doxyfile) and [shell script](doc/doxy.sh) for [Doxygen](https://www.doxygen.nl/).  
Output is to doc/html
```
bash doc/doxy.sh
```
or
See also [GitHub Pages](https://gob52.github.io/gob_unifiedButton/annotated.html)
