KEYMAP_DIR = "qmk_firmware/keyboards/crkbd/keymaps/n"

build:
	@[ -L $(KEYMAP_DIR) ] || make init
	cd qmk_firmware && qmk compile -kb crkbd -km n

init:
	ln -s $(PWD)/n $(KEYMAP_DIR)
