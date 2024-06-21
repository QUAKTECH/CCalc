all: install move_license

install:
		@if [ "`uname`" = "Darwin" ]; then \
			echo "Detected macOS"; \
			sudo mv ccalc /usr/local/bin/; \
		else \
			echo "Detected Linux"; \
			sudo mv ccalc /usr/bin/; \
		fi
		sudo chmod +x /usr/local/bin/ccalc || sudo chmod +x /usr/bin/ccalc
		sudo mv ccalc.1 /usr/share/man/man1

move_license:
		mkdir -p ~/.config/ccalc/LICENSE/
		mv LICENSE ~/.config/ccalc/LICENSE/
