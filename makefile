all: install move_license

install:
		rm ccalc.c
		sudo mv ccalc /usr/bin/
		sudo chmod +x /usr/bin/ccalc
		sudo mv ccalc.1 /usr/share/man/man1

move_license:
		mkdir -p ~/.config/ccalc/LICENSE/
		mv LICENSE ~/.config/ccalc/LICENSE/