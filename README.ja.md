# gob_unifiedButton

![gob_unifiedButton](https://github.com/GOB52/gob_unifiedButton/assets/26270227/590cde0d-f4b6-4fe6-8cae-e25d27b32f8b)

[English](README.md)

## 概要
物理ボタン、タッチボタンを持たない CoreS3 上にタッチボタンを追加し、 M5.BtnX 経由で状態を取得できるようにしたライブラリです。  
将来的に [M5Unified](https://github.com/m5stack/M5Unified) に同様の機能がつくまでの暫定としてお使いください。  
CoreS3 以外では処理をしないので、Basic, Gray, Core2 と共通のソースで作っている方にも有用です。

## 必要なもの
* [M5Unified](https://github.com/m5stack/M5Unified)
* [M5GFX](https://github.com/m5stack/M5GFX)

**M5Unified 前提ですので、 M5Core3.h を使用した物には適用できません。**

## 導入
環境によって適切な方法でインストールしてください
* git clone や Zip ダウンロードからの展開
* platformio.ini
```ini
lib_deps = gob/gob_unifiedButton
```
* ArduinoIDE ライブラリマネージャからのインストール

## 使い方
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
    unifiedButton.update(); // M5.update() の後に呼ぶ事 (0.1.0 から後呼びに変更されました)

    // M5.BtnX 経由で同様に状態取得
    if(M5.BtnA.wasHold())
    {
        // ...
    }
    else if(M5.BtnA.wasClicked())
    {
        // ...
    }

    // ボタンを描画する
    unifiedButton.draw();
}
```

## ボタンのテキストフォント変更
M5GFX で使用できるフォントを設定できます。
```cpp
    unifiedButton.setFont(&fonts::Font4);
```

## 外観変更
begin で指定、または changeAppearance で変更できます。

|引数 goblib::UnifiedButton::appearance\_t|外観|
|---|---|
|bottom| 画面下側にボタンを表示 (default)|
|top|画面上側にボタンを表示|
|custom|独自にボタンをカスタマイズ(下記参照)|
|transparent\_bottom|bottom と同様の位置に透明ボタンを配置|
|transparent\_top|top と同様の位置に透明ボタンを配置|
|transparent_all|画面全体に透明ボタンを配置(縦3分割)|

## ボタンのカスタマイズ
goblib::UnifiedButton::appearance\_t::custom を指定した後であれば、
getButoonA / getButtonB / getButtonC で LGFX_Button\* を取得できます。  
```cpp
void setup()
{
    M5.begin();
    unifiedButton.begin(&M5.Display, goblib::UnifiedButton::appearance_t::custom);

    auto btnA = unifiedButton.getButtonA();
    auto btnB = unifiedButton.getButtonB();
    auto btnC = unifiedButton.getButtonC();

    // 独自形状、色、テキストのボタンを再作成
    btnA->initButton(unifiedButton.gfx(), 40, 120, 80, 240 ,TFT_GREEN, TFT_BLUE, TFT_WHITE, "[A]");
    ...
}
```

## ドキュメント
[Doxygen](https://www.doxygen.nl/) 用の[設定ファイル](doc/Doxyfile)と[シェルスクリプト](doc/doxy.sh)で作成できます。  
出力先は doc/html です。
```
bash doc/doxy.sh
```

または[GitHub Pages](https://gob52.github.io/gob_unifiedButton/)を参照してください。

