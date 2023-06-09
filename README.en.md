# gob_unifiedButton

[日本語](README.md)

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
* git clone and extract into place  
or
* platformio.ini
```ini
lib_deps = https://github.com/GOB52/gob_unifiedButton
```

## How to use

```cpp
#include <M5Unified.h>
#include <gob_unifiedButton.hpp>

gob::UnifiedButton unfiedButton;

void setup()
{
    M5.begin();
    unfiedButton.begin(&M5.Display);
}

void loop()
{
    unfiedButton.update(); // Must be call before M5.update
    M5.update();

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
    unfiedButton.draw();
}
```

## Appearance changes
You can specify it with begin or change it with changeAppearance.

|Argument gob::UnifiedButton::appearance\_t|Description|
|---|---|
|bottom| Display buttons at the bottom of the screen (default)|
|top|Display buttons at the top of the screen|
|custom|Customize your own buttons|
|transparent\_bottom|Transparent buttons on the bottom of the screen|
|transparent\_top|Transparent buttons on the top of the screen|
|transparent_all|Transparent buttons are placed on the entire screen (three vertical sections)|


## Customize Buttons
If after specifying gob::UnifiedButton::appearance\_t::custom,
getButtonA / getButtonB / getButtonC to get LGFX_Button\*.

```cpp

void setup()
{
    M5.begin();
    unfiedButton.begin(&M5.Display, gob::UnifiedButton::appearance_t::custom);

    auto btnA = unfiedButton.getButtonA();
    auto btnB = unfiedButton.getButtonB();
    auto btnC = unfiedButton.getButtonC();

    // Re-create buttons with unique shape, color, and text
    btnA->initButton(unfiedButton.gfx(), 40, 120, 80, 240 ,TFT_GREEN, TFT_BLUE, TFT_WHITE, "[A]");
    ...
}
```
