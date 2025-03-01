# gob_unifiedButton

![gob_unifiedButton](https://github.com/GOB52/gob_unifiedButton/assets/26270227/590cde0d-f4b6-4fe6-8cae-e25d27b32f8b)

[English](README.md)

## 概要
物理ボタン、タッチボタンを持たない CoreS3、Tough 上にソフトウェアタッチボタンを追加し、 M5.BtnX 経由で状態を取得できるようにしたライブラリです。  

~~将来的に [M5Unified](https://github.com/m5stack/M5Unified) に同様の機能がつくまでの暫定としてお使いください。~~  
M5Unified 0.2.3 より、 **M5.setTouchButtonHeightByRatio(uint8_t ratio)** が追加され、画面を M5.BtnX として使用できるようになりました。  
今後はこちらの機能を使うと良いでしょう。

CoreS3、Tough 以外では処理をしないので、Basic, Gray, Core2 等と共通のソースで作っている方にも有用です。  

なお CoreS3SE では M5Unified を使用していればも画面外の部分が Core2 同様にボタンとして機能します。(CoreS3 ではその部分はタッチとして機能しません)


## 必要なもの
* [M5Unified](https://github.com/m5stack/M5Unified) 0.1.16 以降
* [M5GFX](https://github.com/m5stack/M5GFX) 0.1.16 以降

**M5Unifiedを前提としているため、M5Core3.hなどデバイス固有のヘッダを使用している場合は適用できません。**

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
|transparent\_bottom|bottom と同様の位置に透明ボタンを配置|
|transparent\_top|top と同様の位置に透明ボタンを配置|
|transparent_all|画面全体に透明ボタンを配置(縦3分割)|

## ボタンのカスタマイズ
LGFX\_Button\* を取得できます。  
```cpp
void setup()
{
    M5.begin();
    unifiedButton.begin(&M5.Display);

    auto btnA = unifiedButton.getButtonA();
    // 独自形状、色、テキストのボタンを再作成
    btnA->initButton(unifiedButton.gfx(), 40, 120, 80, 240 ,TFT_GREEN, TFT_BLUE, TFT_WHITE, "[A]");
    // ラベル変更
	btnA->setLabelText("Own");
}
```
LGFX\_Button については[こちら](https://github.com/m5stack/M5GFX/blob/master/src/lgfx/v1/LGFX_Button.hpp)を参照してください。


## ドキュメント
[Doxygen](https://www.doxygen.nl/) 用の[設定ファイル](docs/Doxyfile)と[シェルスクリプト](docs/doxy.sh)で作成できます。  
出力先は doc/html です。
```
bash docs/doxy.sh
```

または[GitHub Pages](https://gob52.github.io/gob_unifiedButton/)を参照してください。

