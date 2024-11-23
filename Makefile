KEYMAP_DIR = "qmk_firmware/keyboards/crkbd/keymaps/n"

build:
	@make init
	@cd qmk_firmware && qmk compile -kb crkbd -km n

flash-left:
	@EXTRAFLAGS='-D MASTER_LEFT'
	@make flash

flash-right:
	@EXTRAFLAGS='-D MASTER_RIGHT'
	@make flash

flash:
	@make init
	@cd qmk_firmware && qmk flash -kb crkbd -km n

init:
	@[ -L $(KEYMAP_DIR) ] || ln -s $(PWD)/n $(KEYMAP_DIR)
