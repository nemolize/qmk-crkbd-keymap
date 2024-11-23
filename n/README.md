# My crkbd keymap
This repository contains my custom crkbd keymap of [QMK](https://qmk.fm/).

The keymap works with core [QMK source codes](https://github.com/qmk/qmk_firmware).

# Pre requirements
- [QMK Installation](https://docs.qmk.fm/newbs_getting_started)

# Installation
```shell script
cd qmk_firmware/keyboards/crkbd/keymaps
git clone git@github.com:nemolize/qmk-crkbd-keymap.git n
``` 

# Build
```shell script
# left hand
make flash-left

# right hand
make flash-right
```
