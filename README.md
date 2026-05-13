# glyph_ctrl
Simple helper used by Glyphs Lights click app for Ubuntu Touch on Nothing Phone (1)

# Compile it (on the phone)
`gcc -o glyph_ctrl glyph_ctrl.c
sudo chown root:root glyph_ctrl && sudo chmod u+s glyph_ctrl
sudo mv glyph_ctrl /usr/bin/`

_Might need to install build-essentials package first_
