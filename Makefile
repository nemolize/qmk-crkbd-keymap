KEYMAP_DIR = "qmk_firmware/keyboards/crkbd/keymaps/n"

build:
	@make init
	@cd qmk_firmware && qmk compile -kb crkbd -km n

flash-left:
	@make flash EXTRAFLAGS='-D MASTER_LEFT'

flash-right:
	@make flash EXTRAFLAGS='-D MASTER_RIGHT'

flash:
	@make init
	@echo "Build & Flashing with EXTRAFLAGS='$(EXTRAFLAGS)'"
	@export EXTRAFLAGS=$(EXTRAFLAGS)
	@cd qmk_firmware && qmk flash -kb crkbd -km n

init:
	@[ -L $(KEYMAP_DIR) ] || ln -s $(PWD)/n $(KEYMAP_DIR)
