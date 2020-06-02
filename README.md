# My crkbd keymap
This repository contains my custom crkbd keymap of [QMK](https://qmk.fm/).

The keymap works with core [QMK source codes](https://github.com/qmk/qmk_firmware).

# Pre requirements
- [QMK Installation](https://beta.docs.qmk.fm/tutorial/newbs_getting_started)

# Installation
```shell script
cd qmk_firmware/keyboards/crkbd/keymaps
git clone git@github.com:nemolize/qmk-crkbd-keymap.git n
``` 

# Build
```shell script
# left hand
make EXTRAFLAGS=-DMASTER_LEFT crkbd:n  crkbd:n:avrdude

# right hand
make EXTRAFLAGS=-DMASTER_RIGHT crkbd:n  crkbd:n:avrdude
```
