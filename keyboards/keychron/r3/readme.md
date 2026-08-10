# Keychron R3

![Keychron R3](https://cdn.shopify.com/s/files/1/0059/0630/1017/files/Keychron_R3_QMK_Wireless_Mechanical_Keyboard-80layout_c7f991ff-5e6e-4ac9-ba0f-5296e589746e.jpg)

A customizable TKL(80%) keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron R3
* Hardware Availability: [Keychron R3 QMK/VIA Wireless Custom Mechanical Keyboard](https://www.keychron.com/products/keychron-r3-qmk-wireless-mechanical-keyboard)

Make example for this keyboard (after setting up your build environment):

    make keychron/r3/ansi/rgb:keychron
    make keychron/r3/jis/rgb:keychron
    make keychron/r3/th/rgb:keychron

Flashing example for this keyboard:

    make keychron/r3/ansi/rgb:keychron:flash
    make keychron/r3/jis/rgb:keychron:flash
    make keychron/r3/th/rgb:keychron:flash

**Reset Key**: Disconnect the USB cable, toggle mode switch to "Cable", hold down the *Esc* key or reset button underneath space bar, then connect the USB cable.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Option B: Use Keychron Launcher (no code required)

If you just want to remap keys, configure layers, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, and adjust lighting - changes apply instantly

Keychron Launcher works out of the box with no JSON import required, providing a simpler browser-based setup flow for supported boards. Safari and other non-Chromium browsers will not work with Keychron Launcher.

