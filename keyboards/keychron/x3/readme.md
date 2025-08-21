# Lemokey X3

![Lemokey X3]https://cdn.shopify.com/s/files/1/0059/0630/1017/files/Lemokey-X3-3.jpg)

A customizable 100% full size keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Lemokey X3
* Hardware Availability: [Keychron](https://www.keychron.com/products/lemokey-x3-qmk-via-wired-mechanical-keyboard)

Make example for this keyboard (after setting up your build environment):

    make keychron/x3/ansi/red:keychron
    make keychron/x3/ansi/rgb:keychron
    make keychron/x3/iso/red:keychron
    make keychron/x3/iso/rgb:keychron

Flashing example for this keyboard:

    make keychron/x3/ansi/red:keychron:flash
    make keychron/x3/ansi/rgb:keychron:flash
    make keychron/x3/iso/red:keychron:flash
    make keychron/x3/iso/rgb:keychron:flash

## bootloader

Enter the bootloader in two ways:

* **Bootmagic reset**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.
* **Physical reset button**: Briefly press the RESET button under the spacebar.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
