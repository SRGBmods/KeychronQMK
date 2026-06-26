# Keychron K1 Version 6

![Keychron K1 Version 6](https://cdn.shopify.com/s/files/1/0059/0630/1017/files/K1_Version_6_6.jpg)

A customizable 87 keys TKL keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron K1 Version 6
* Hardware Availability: [Keychron K1 Version 6 QMK/VIA Wireless Custom Mechanical Keyboard](https://www.keychron.com/products/keychron-k1-qmk-wireless-mechanical-keyboard-version-6)

## Option A: Build And Flash Firmware

Make example for this keyboard (after setting up your build environment):

    make keychron/k1_version_6/ansi/rgb:keychron
    make keychron/k1_version_6/ansi/white:keychron
    make keychron/k1_version_6/iso/rgb:keychron
    make keychron/k1_version_6/iso/white:keychron
    make keychron/k1_version_6/jis/rgb:keychron
    make keychron/k1_version_6/jis/white:keychron

Flashing example for this keyboard:

    make keychron/k1_version_6/ansi/rgb:keychron:flash
    make keychron/k1_version_6/ansi/white:keychron:flash
    make keychron/k1_version_6/iso/rgb:keychron:flash
    make keychron/k1_version_6/iso/white:keychron:flash
    make keychron/k1_version_6/jis/rgb:keychron:flash
    make keychron/k1_version_6/jis/white:keychron:flash

**Reset Key**: Toggle mode switch to "Cable", hold down the *Esc* key or reset button underneath space bar while connecting the USB cable,

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Option B: Use Keychron Launcher (no code required)

If you just want to remap keys, configure layers, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, and adjust lighting - changes apply instantly

Keychron Launcher works out of the box with no JSON import required, providing a simpler browser-based setup flow for supported boards. Safari and other non-Chromium browsers will not work with Keychron Launcher.

