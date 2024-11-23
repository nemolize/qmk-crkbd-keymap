KEYMAP_DIR = "qmk_firmware/keyboards/crkbd/keymaps/n"

build:
	make init
	cd qmk_firmware && qmk compile -kb crkbd -km n

init:
	@[ -L $(KEYMAP_DIR) ] || ln -s $(PWD)/n $(KEYMAP_DIR)
