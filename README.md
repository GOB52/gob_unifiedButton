# gob_unifiedButton

[日本語](https://github.com/GOB52/gob_unifiedButton/blob/master/README.ja.md)

![gob_unifiedButton](https://github.com/GOB52/gob_unifiedButton/assets/26270227/590cde0d-f4b6-4fe6-8cae-e25d27b32f8b)

## Overview
This library adds software touch buttons on CoreS3 and Tough, which does not have physical buttons or touch buttons, and enables the user to acquire the status via M5.BtnX.  
~~Please use this as an interim feature until a similar feature is added to [M5Unified](https://github.com/m5stack/M5Unified) in the future.~~  

Since M5Unified 0.2.3, **M5.setTouchButtonHeightByRatio(uint8_t ratio)** has been added, allowing the screen to be used as button (M5.BtnX)  
You may want to use this feature.

It is also useful for those who are making a common source for Basic, Gray, Core2 and more, as it does not process anything other than CoreS3 and Tough.  

In CoreS3SE, if M5Unified is used, the off-screen part functions as a button, as in Core2 .(In CoreS3, that part does not function as touch)

## Required libraries
* [M5Unified](https://github.com/m5stack/M5Unified) 0.1.16 or later
* [M5GFX](https://github.com/m5stack/M5GFX) 0.1.16 or later

**M5Unified is assumed, it is not applicable when device-specific headers such as M5Core3.h are used.**

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
|transparent\_bottom|Transparent buttons on the bottom of the screen|
|transparent\_top|Transparent buttons on the top of the screen|
|transparent_all|Transparent buttons are placed on the entire screen (three vertical sections)|

## Customize Buttons
You can get LGFX\_Button\*.

```cpp
void setup()
{
    M5.begin();
    unifiedButton.begin(&M5.Display);

    auto btnA = unifiedButton.getButtonA();

    // Re-create buttons with unique shape, color, and text
    btnA->initButton(unifiedButton.gfx(), 40, 120, 80, 240 ,TFT_GREEN, TFT_BLUE, TFT_WHITE, "[A]");
    // Change label text
    btnA->setLabelText("Own");
}
```
Click [here](https://github.com/m5stack/M5GFX/blob/master/src/lgfx/v1/LGFX_Button.hpp) for more information about LGFX\_Button].

## Document
Can be created from a [configuration file](docs/Doxyfile) and [shell script](docs/doxy.sh) for [Doxygen](https://www.doxygen.nl/).  
Output is to doc/html
```
bash doc/doxy.sh
```
or
See also [GitHub Pages](https://gob52.github.io/gob_unifiedButton/)
