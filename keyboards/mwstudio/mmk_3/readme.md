# 3Key

![3Key](https://i.imgur.com/WuwlVknh.jpeg)

Support APM32F103C8T6 keyboard.

* Keyboard Maintainer: [TW59420](https://github.com/TW59420)
* Hardware Supported: APM32F103C8T6

Make example for this keyboard (after setting up your build environment):

    make mwstudio/mmk_3:default 

Flashing example for this keyboard:

    make mwstudio/mmk_3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader
* **Physical reset button**: Short press the button on the back of the PCB to enter the Bootloader and flash the firmware
* **Keycode in layout**: Press the key mapped to RESET if it is available
